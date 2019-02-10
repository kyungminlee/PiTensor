#include "../../pitensor.h"
#include "itensor/mps/localmpo.h"
namespace py = pybind11;
using namespace itensor;

template <typename Tensor>
auto
initLocalMPO(pybind11::module& module, const char* typeName) {
  using Type = LocalMPO<Tensor>;
  using mpo_type = MPOt<Tensor>;
  using mps_type = MPSt<Tensor>;

  py::class_<Type> type(module, typeName);

  type
      .def(py::init<>())
      .def(py::init<mpo_type const &, Args const &>(),
           py::arg("H"),
           py::arg("args")=Args::global()
      )
      .def(py::init<mps_type const &, Args const &>(),
           py::arg("psi"),
           py::arg("args")=Args::global()
      )
      .def(py::init<mpo_type const &,
                    Tensor const &,
                    Tensor const &,
                    Args const &>(),
           py::arg("H"),
           py::arg("LH"),
           py::arg("RH"),
           py::arg("args")=Args::global()
      )
      .def(py::init<mps_type const &,
                    Tensor const &,
                    Tensor const &,
                    Args const &>(),
           py::arg("psi"),
           py::arg("LP"),
           py::arg("RP"),
           py::arg("args")=Args::global()
      )
      .def(py::init<mpo_type const &,
                    Tensor const &,
                    int,
                    Tensor const &,
                    int,
                    Args const &>(),
           py::arg("H"),
           py::arg("LH"),
           py::arg("LHlim"),
           py::arg("RH"),
           py::arg("RHlim"),
           py::arg("args")=Args::global()
      )
  ;

  type
      .def("product", &Type::product)
      .def("expect", &Type::expect)
      .def("deltaRho", &Type::deltaRho)
      .def("diag", &Type::diag)
          // TODO position
      .def("shift", &Type::shift)
      .def("reset", &Type::reset)
      // Accessor methods
      .def_property("L",
                    (Tensor const & (Type::*)() const) &Type::L,
                    (void (Type::*)(Tensor const &)) &Type::L
      )
          // TODO L with int and Tensor
      .def_property("R",
                    (Tensor const & (Type::*)() const) &Type::R,
                    (void (Type::*)(Tensor const &)) &Type::R
      )
          // TODO R with int and Tensor
      .def_property_readonly("H", &Type::H)
      .def_property("numCenter",
                    (int (Type::*)() const) &Type::numCenter,
                    (void (Type::*)(int)) &Type::numCenter
      )
      .def_property_readonly("size", &Type::size)
      .def("__bool__", [](Type const & self) { return static_cast<bool>(self); })
      .def_property("doWrite",
                    (bool (Type::*)() const) &Type::doWrite,
                    (void (Type::*)(bool)) &Type::doWrite
      )
      .def_property_readonly("writeDir", &Type::writeDir)
      .def_property_readonly("leftLim", &Type::leftLim)
      .def_property_readonly("rightLim", &Type::rightLim)
  ;
  return type;
}

void pitensor::mps::localmpo(pybind11::module& module) {
  auto typeLocalMPO = initLocalMPO<ITensor>(module, "LocalMPO");
  auto typeIQLocalMPO = initLocalMPO<IQTensor>(module, "IQLocalMPO");
}
