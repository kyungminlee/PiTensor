#include "../../pitensor.h"
#include "itensor/mps/hambuilder.h"
namespace py = pybind11;
using namespace itensor;


// TODO: String "defined" to be String in ITensor

template <typename Tensor>
static inline
auto
initHamBuilder(pybind11::module& module, const char* typeName)
{
  using Type = HamBuilder<Tensor>;
  using String = std::string;

  py::class_<Type> type(module, typeName);

  type.def(py::init<>());
  type.def(py::init<SiteSet const &>());
  type.def(py::init <
      SiteSet const &,
      String const &, int,
      String const &, int,
      String const &, int,
      String const &, int>(),
      py::arg("sites"),
      py::arg("opname1"), py::arg("j1"),
      py::arg("opname2")="", py::arg("j2")=0,
      py::arg("opname3")="", py::arg("j3")=0,
      py::arg("opname4")="", py::arg("j4")=0);
  type.def(py::init <
      SiteSet const &,
      Tensor const &, int,
      Tensor const &, int,
      Tensor const &, int,
      Tensor const &, int>(),
      py::arg("sites"),
      py::arg("op1"), py::arg("j1"),
      py::arg("op2")=Tensor(), py::arg("j2")=0,
      py::arg("op3")=Tensor(), py::arg("j3")=0,
      py::arg("op4")=Tensor(), py::arg("j4")=0)
  ;

  type
      .def("set",
           (Type& (Type::*)(const String &, int,
                            const String &, int,
                            const String &, int,
                            const String &, int)) &Type::set,
           py::arg("opname1"), py::arg("j1"),
           py::arg("opname2")="", py::arg("j2")=0,
           py::arg("opname3")="", py::arg("j3")=0,
           py::arg("opname4")="", py::arg("j4")=0)
      .def("set",
           (Type& (Type::*)(const Tensor &, int,
                            const Tensor &, int,
                            const Tensor &, int,
                            const Tensor &, int)) &Type::set,
           py::arg("op1"), py::arg("j1"),
           py::arg("op2")=Tensor(), py::arg("j2")=0,
           py::arg("op3")=Tensor(), py::arg("j3")=0,
           py::arg("op4")=Tensor(), py::arg("j4")=0)
  ;

  // TODO
  type
      .def("toMPO", [](Type const & self) { return MPOt<Tensor>(self); })
  ;

  type
      .def(py::self *= Real())
      .def(py::self *= Complex())
      .def(py::self * Real())
      .def(Real() * py::self)
      .def(py::self * Complex())
      .def(Complex() * py::self)
    // TODO operators
    #if 0
      .def("__mul__", [](HamBuilder<Tensor> const & hb, Real x) {
        return hb * x;
      })
      .def("__mul__", [](Real x, HamBuilder<Tensor> const & hb) {
        return x * hb;
      })
      .def("__mul__", [](HamBuilder<Tensor> const & hb, Complex x) {
        return hb * x;
      })
      .def("__mul__", [](Complex x, HamBuilder<Tensor> const & hb) {
        return x * hb;
      })
    #endif
  ;
  return type;
}

void pitensor::mps::hambuilder(pybind11::module& module)
{
  auto typeHamBuilder = initHamBuilder<ITensor>(module, "HamBuilder");
  auto typeIQHamBuilder = initHamBuilder<IQTensor>(module, "IQHamBuilder");
}
