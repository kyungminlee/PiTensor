#include "../../../pitensor.h"
#include "itensor/mps/sites/spinone.h"

#include "../siteset.h"

namespace py = pybind11;
using namespace itensor;

static inline
auto
initSpinOneSite(pybind11::module& module)
{
  using Type = SpinOneSite;
  py::class_<SpinOneSite> type(module, "SpinOneSite");

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

void pitensor::mps::sites::spinone(pybind11::module& module)
{
  py::class_<SpinOne, SiteSet> typeSpinOne(module, "SpinOne");
  auto typeSpinOneSite = initSpinOneSite(module);
}
