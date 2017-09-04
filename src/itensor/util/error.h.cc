#include "../../pitensor.h"
#include "itensor/util/error.h"
namespace py = pybind11;
using namespace itensor;

void pitensor::util::error(pybind11::module& module)
{
  py::register_exception<ITError>(module, "ITError");
  py::register_exception<ResultIsZero>(module, "ResultIsZero");

#if 0
  module
      .def("error",
           (void (*)(std::string const &)) &itensor::error,
           py::call_guard<py::scoped_ostream_redirect, py::scoped_estream_redirect>())
  ;
#endif
}
