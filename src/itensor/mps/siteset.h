#pragma once

#include "../../pitensor.h"
#include "itensor/mps/siteset.h"

template <typename SiteType>
auto
initBasicSiteSet(pybind11::module & module, const char* typeName)
{
  namespace py = pybind11;
  using namespace itensor;

  using Type = BasicSiteSet<SiteType>;
  py::class_<Type, SiteSet> type(module, typeName);

  type.def(py::init<>());
  type.def(py::init<int, Args const &>(),
           py::arg("N"),
           py::arg("args")=Args::global());
  type.def(py::init<std::vector<IQIndex> const &>());
  type
      .def("__repr__", [](Type const & obj) { std::stringstream ss; ss << std::scientific << obj; return ss.str(); })
  ;

  // TODO read write
  return type;
}