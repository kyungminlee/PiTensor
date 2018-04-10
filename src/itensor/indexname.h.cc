#include "../pitensor.h"
#include "itensor/indexname.h"
namespace py = pybind11;
using namespace itensor;

static inline
auto
initIndexName(pybind11::module& module)
{
  using Type = IndexName;
  py::class_<IndexName> type(module, "IndexName");

  type
      .def(py::init<>())
      .def(py::init<const char*>())
  ;

  type
      .def_property_readonly_static("size", &IndexName::size)
      .def_property_readonly("name",
           [](Type const & self) -> std::string {
             return std::string(self.c_str());
           })
  ;

  type
      .def("__getitem__",
           [](IndexName const & obj, size_t i) -> char { return obj[i]; })
      .def("__setitem__",
           [](IndexName& obj, size_t i, char c) -> void { obj[i] = c; })
      .def("__repr__", [](IndexName const & obj) -> std::string { std::stringstream ss; ss << std::scientific << static_cast<const char*>(obj); return ss.str(); })
  ;

  // TODO read write

  return type;
}
void pitensor::indexname(pybind11::module& module)
{
#if 0
  py::class_<IndexName> type(module, "IndexName");
  type
      .def(py::init<>())
      .def(py::init<const char *>())
  ;
  py::implicitly_convertible<std::string, IndexName>();
#endif
}
