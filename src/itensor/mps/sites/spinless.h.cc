#include "../../../pitensor.h"
#include "itensor/mps/sites/spinless.h"

#include "../siteset.h"

namespace py = pybind11;
using namespace itensor;

static inline
auto
initSpinlessSite(pybind11::module& module)
{
  using Type = SpinlessSite;
  py::class_<SpinlessSite> type(module, "SpinlessSite");

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

void pitensor::mps::sites::spinless(pybind11::module& module)
{
  auto typeSpinless = initBasicSiteSet<SpinlessSite>(module, "Spinless");
  auto typeSpinlessSite = initSpinlessSite(module);
}


