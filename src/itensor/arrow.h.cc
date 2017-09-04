#include "../pitensor.h"
#include "itensor/arrow.h"
namespace py = pybind11;
using namespace itensor;

void pitensor::arrow(pybind11::module& module)
{
  {
    py::enum_<Arrow> type(module, "Arrow");
    type
        .value("In", Arrow::In)
        .value("Out", Arrow::Out)
        .value("Neither", Arrow::Neither);
  }
  {
    py::class_<ArrowError> type(module, "ArrowError");
    type.def(py::init<std::string const&>());
  }
}
