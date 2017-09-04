#include "../../../pitensor.h"
#include "itensor/mps/sites/spinhalf.h"

#include "../siteset.h"

namespace py = pybind11;
using namespace itensor;

static inline
auto
initSpinHalfSite(pybind11::module& module)
{
  using Type = SpinHalfSite;
  py::class_<SpinHalfSite> type(module, "SpinHalfSite");

  type.def(py::init<>());
  type.def(py::init<IQIndex>());
  type.def(py::init<int, Args const&>(),
           py::arg("n"),
           py::arg("args")=Args::global());

  type
      .def("index", &Type::index)
      .def("state", &Type::state)
      .def("op", &Type::op)
      ;
  return type;
}

void pitensor::mps::sites::spinhalf(pybind11::module& module)
{
  auto typeSpinHalf = initBasicSiteSet<SpinHalfSite>(module, "SpinHalf");
  auto typeSpinHalfSite = initSpinHalfSite(module);
}
