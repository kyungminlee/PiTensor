#include "../pitensor.h"
#include "itensor/spectrum.h"
namespace py = pybind11;
using namespace itensor;

void pitensor::spectrum(pybind11::module& module)
{
  {
    py::class_<Spectrum> type(module, "Spectrum");
    type
        // TODO: decide whether to expose constructors
        .def("truncerr", &Spectrum::truncerr)
        .def("eigs", &Spectrum::eigs)
        .def("eig", &Spectrum::eig)
        .def("numEigsKept", &Spectrum::numEigsKept)
        .def("hasQNs", &Spectrum::hasQNs)
        .def("qn", &Spectrum::qn)
        .def("qns", &Spectrum::qns)
        .def("size", &Spectrum::size)
        .def("__repr__", [](Spectrum const & obj) -> std::string { std::stringstream ss; ss << std::scientific << obj; return ss.str(); })
    ;

  }
}
