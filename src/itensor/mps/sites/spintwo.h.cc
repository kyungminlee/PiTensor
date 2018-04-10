#include "../../../pitensor.h"
#include "itensor/mps/sites/spintwo.h"

#include "../siteset.h"

namespace py = pybind11;
using namespace itensor;

static inline
auto
initSpinTwo(pybind11::module& module)
{
  using Type = SpinTwo;
  py::class_<SpinTwo, SiteSet> type(module, "SpinTwo");

  type.def(py::init<>());
  type.def(py::init<int, Args const&>(),
           py::arg("N"),
           py::arg("args")=Args::global());

  // TODO: how should I treat istream?
  type
      .def("read", &Type::read)
      ;
  return type;
}

static inline
auto
initSpinTwoSite(pybind11::module& module)
{
  using Type = SpinTwoSite;
  py::class_<SpinTwoSite> type(module, "SpinTwoSite");

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

void pitensor::mps::sites::spintwo(pybind11::module& module)
{
  auto typeSpinTwo = initSpinTwo(module);
  auto typeSpinTwoSite = initSpinTwoSite(module);
}
