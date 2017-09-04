#include "../pitensor.h"
#include "itensor/indexname.h"
namespace py = pybind11;
using namespace itensor;

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
