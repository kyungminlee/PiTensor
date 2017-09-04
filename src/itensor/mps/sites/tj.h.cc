#include "../../../pitensor.h"
#include "itensor/mps/sites/tj.h"

#include "../siteset.h"

namespace py = pybind11;
using namespace itensor;

static inline
auto
inittjSite(pybind11::module& module)
{
  using Type = tJSite;
  py::class_<tJSite> type(module, "tJSite");

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

void pitensor::mps::sites::tj(pybind11::module& module)
{
  auto typeSpinHalf = initBasicSiteSet<tJSite>(module, "tJ");
  auto typeSpinHalfSite = inittjSite(module);
}
