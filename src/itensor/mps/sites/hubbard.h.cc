#include "../../../pitensor.h"
#include "itensor/mps/sites/hubbard.h"

#include "../siteset.h"

namespace py = pybind11;
using namespace itensor;

static inline
auto
initHubbardSite(pybind11::module& module)
{
  using Type = HubbardSite;
  py::class_<HubbardSite> type(module, "HubbardSite");

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

void pitensor::mps::sites::hubbard(pybind11::module& module)
{
  auto typeHubbard = initBasicSiteSet<HubbardSite>(module, "Hubbard");
  auto typeHubbardSite = initHubbardSite(module);
}
