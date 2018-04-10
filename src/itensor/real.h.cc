#include "../pitensor.h"
#include "itensor/real.h"
namespace py = pybind11;
using namespace itensor;

// TODO: decide whether necessary
void pitensor::real(pybind11::module& module)
{
  py::register_exception<TooBigForReal>(module, "TooBigForReal");
  py::register_exception<TooSmallForReal>(module, "TooSmallForReal");


  py::class_<LogNum> type(module, "LogNum");

  type
      .def(py::init<>())
      .def(py::init<Real>())
      .def(py::init<Real, int>(), py::arg("lognum"), py::arg("sign"))
  ;

  type
      .def("logNum", &LogNum::logNum)
      .def("sign", &LogNum::sign)
      .def("isZero", &LogNum::isZero)
      .def("isRealZero", &LogNum::isRealZero)
      .def("isFiniteReal", &LogNum::isFiniteReal)
      .def("isTooBigForReal", &LogNum::isTooBigForReal)
      .def("isTooSmallForReal", &LogNum::isTooSmallForReal)
      .def("real", &LogNum::real)
      .def("real0", &LogNum::real0)
      .def("approxEquals", &LogNum::approxEquals)
      .def("negate", &LogNum::negate)
      .def("swap", &LogNum::swap)
      .def("magnitudeLessThan", &LogNum::magnitudeLessThan)
      .def("pow", &LogNum::pow)
  ;
  // TODO read write

  type
      .def(py::self += py::self)
      .def(py::self == py::self)
      .def(py::self != py::self)
      .def(py::self *= py::self)
      .def(py::self *= Real())
      .def(py::self /= py::self)
      .def(py::self /= Real())
      .def(-py::self)
      .def(py::self / py::self)
      .def(py::self * py::self)
      .def(py::self < py::self)
      .def(py::self <= py::self)
      .def(py::self > py::self)
      .def(py::self >= py::self)
      .def(py::self * Real())
      .def(Real() * py::self)
  ;

  type
      .def("__repr__", [](LogNum const & self) { std::stringstream ss; ss << std::scientific << self; ss.str(); })
  ;

  module
      .def("sqrt", (LogNum (*)(LogNum)) &sqrt )
      .def("isnan",[](LogNum const & i) -> bool { return isnan(i); })
  ;
}
