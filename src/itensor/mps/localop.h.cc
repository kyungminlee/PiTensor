#include "../../pitensor.h"
#include "itensor/mps/localop.h"
namespace py = pybind11;
using namespace itensor;

template <typename Tensor>
auto
initLocalOp(pybind11::module& module, const char* typeName)
{
  using Type = LocalOp<Tensor>;
  py::class_<Type> type(module, typeName);

  type
      .def(py::init<>())
      .def(py::init<Tensor const &, Tensor const &, Args const &>(),
           py::arg("Op1"),
           py::arg("Op2"),
           py::arg("args")=Args::global() // TODO: report to ITensor (Global::args vs Args::global)
      )
      .def(py::init<Tensor const &, Tensor const &, Tensor const &, Tensor const &, Args const &>(),
           py::arg("Op1"),
           py::arg("Op2"),
           py::arg("L"),
           py::arg("R"),
           py::arg("args")=Args::global() // TODO: report to ITensor (Global::args vs Args::global)
      )
  ;
  type
      .def("product", &Type::product)
      .def("expect", &Type::expect)
      .def("deltaRho", &Type::deltaRho)
      .def("diag", &Type::diag)
      .def("size", &Type::size)
      .def("update",
           (void (Type::*)(Tensor const &, Tensor const &)) &Type::update,
           py::arg("Op1"),
           py::arg("Op2")
      )
      .def("update",
           (void (Type::*)(Tensor const &,
                           Tensor const &,
                           Tensor const &,
                           Tensor const &)) &Type::update,
           py::arg("Op1"),
           py::arg("Op2"),
           py::arg("L"),
           py::arg("R")
      )
      .def_property_readonly("Op1", &Type::Op1)
      .def_property_readonly("Op2", &Type::Op2)
      .def_property_readonly("L", &Type::L)
      .def_property_readonly("R", &Type::R)
      .def("__bool__", [](Type const & self) { return static_cast<bool>(self); })
      .def_property_readonly("LIsNull", &Type::LIsNull)
      .def_property_readonly("RIsNull", &Type::RIsNull)
      ;
  return type;
}

void pitensor::mps::localop(pybind11::module& module) {
  auto typeLocalOp = initLocalOp<ITensor>(module, "LocalOp");
  auto typeIQLocalOp = initLocalOp<IQTensor>(module, "IQLocalOp");
}
