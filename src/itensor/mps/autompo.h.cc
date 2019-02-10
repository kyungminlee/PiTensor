#include "../../pitensor.h"
#include "itensor/mps/autompo.h"
namespace py = pybind11;
using namespace itensor;


template <typename Tensor>
static inline
void
_init(pybind11::module& module)
{
  using mpo_type = MPOt<Tensor>;
  using mps_type = MPSt<Tensor>;

  module
      .def("toMPO",
           (mpo_type (*)(AutoMPO const&, Args const &)) &toMPO,
           py::arg("a"),
           py::arg("args")=Args::global())
      .def("toExpH",
           (mpo_type (*)(AutoMPO const &, Cplx, Args const & args)) &toExpH,
           py::arg("a"),
           py::arg("tau"),
           py::arg("args")=Args::global())
  ;
}


static inline
auto initSiteTerm(pybind11::module& module)
{
  py::class_<SiteTerm> type(module, "SiteTerm");

  type.def(py::init<>());
  type.def(py::init<std::string const &, int>());

  type
      .def(py::self == py::self)
      .def(py::self != py::self)
      .def(py::self > py::self)
      .def(py::self < py::self)
  ;

  type
      .def("__repr__", [](SiteTerm const & obj) { std::stringstream ss; ss << std::scientific << obj; return ss.str(); })
  ;

  module
      .def("isFermionic", (bool (*)(SiteTerm const &)) &isFermionic)
  ;

  return type;
}


static inline
auto initHTerm(pybind11::module& module)
{
  using TheType = HTerm;
  py::class_<HTerm> type(module, "HTerm");

  type
      .def(py::init<>())
      .def(py::init<Cplx, SiteTermProd const&>())
  ;

  type
      .def("add",
            &HTerm::add,
           py::arg("op"),
           py::arg("i"),
           py::arg("x") = 1)
      .def("__bool__", [](TheType const & self) { return static_cast<bool>(self); })
      .def("Nops", &HTerm::Nops)
      .def("first", &HTerm::first)
      .def("last", &HTerm::last)
      .def(py::self *= Real())
      .def(py::self *= Complex())
      .def(py::self == py::self)
      .def(py::self != py::self)
      .def(py::self < py::self)
      .def("__repr__", [](TheType const & obj) { std::stringstream ss; ss << std::scientific << obj; return ss.str(); })
  ;
}


static inline
auto initAutoMPO(pybind11::module& module)
{
  py::class_<AutoMPO> type(module, "AutoMPO");

  type.def(py::init<SiteSet const&>());

  type
      .def("sites", &AutoMPO::sites)
      .def("terms", &AutoMPO::terms)
      .def("toMPO", [](AutoMPO const & self) -> MPO { return MPO(self);})
      .def("toIQMPO", [](AutoMPO const & self) -> IQMPO { return IQMPO(self);})
      .def("add", &AutoMPO::add)
      .def("reset", &AutoMPO::reset)
      .def("__repr__", [](AutoMPO const & obj) { std::stringstream ss; ss << std::scientific << obj; return ss.str(); })
  ;

  // TODO: Decision
  // Using += iterable instead of Accumulator. Is this a good idea?
  type
      .def("__iadd__",
           [](AutoMPO & ampo, HTerm const & hterm) { ampo.add(hterm); return ampo; }
      )
      .def("__iadd__",
           [](AutoMPO & ampo, py::iterable obj) {
        Complex coeff = 1.0;
        HTerm hterm;
        enum class State {New, Op} state = State::New;
        std::string op;
        for (auto const & item : obj) {
          if (py::isinstance<py::float_>(item)) {
            coeff *= item.cast<Real>();
          } else if (py::isinstance<py::class_<Complex>>(item)) { // TODO: pybind11 does not implement complex type
            coeff *= item.cast<Complex>();
          } else if (py::isinstance<py::str>(item)) {
            switch(state) {
              case State::New:
                op = item.cast<std::string>();
                state = State::Op;
                break;
              case State::Op:
                throw std::domain_error("Invalid input to AutoMPO (two strings in a row?)");
                break;
            }
          } else if (py::isinstance<py::int_>(item)) {
            auto i = item.cast<int>();
            switch(state) {
              case State::New:
                hterm *= static_cast<Real>(i);
                break;
              case State::Op:
                hterm.add(op, i);
                state = State::New;
                op = "";
                break;
            }
          } else {
            throw std::domain_error("Invalid input to AutoMPO (unsupported type)");
          }
        }

        if (!hterm) {
          throw std::domain_error("Invalid input to AutoMPO (no operators)");
        }
        hterm *= coeff;
        ampo.add(hterm);
        return ampo;
      }
      )
  ;

  return type;
}

void pitensor::mps::autompo(pybind11::module& module)
{
  _init<ITensor>(module);
  _init<IQTensor>(module);
  initSiteTerm(module);
  initHTerm(module);
  initAutoMPO(module);
}
