#include "../../pitensor.h"
#include "itensor/mps/DMRGObserver.h"
namespace py = pybind11;
using namespace itensor;


template <typename Tensor>
static inline
auto
initDMRGObserver(pybind11::module& module, const char* typeName)
{
  using mps_type = MPSt<Tensor>;
  using mpo_type = MPOt<Tensor>;
  using dmrg_observer_type = DMRGObserver<Tensor>;

  py::class_<dmrg_observer_type> type(module, typeName);

  type.def(py::init<mps_type const &, Args const &>(),
           py::arg("psi"),
           py::arg("args") = Global::args());

  type
      .def("measure", &dmrg_observer_type::measure)
      .def("checkDone", &dmrg_observer_type::checkDone)
      .def("lastSpectrum", &dmrg_observer_type::lastSpectrum)
      .def_property_readonly("psi",
                             &dmrg_observer_type::psi)
      .def_property_readonly("spectrum",
                             &dmrg_observer_type::spectrum)
  ;

  return type;
}


void pitensor::mps::DMRGObserver(pybind11::module& module)
{
  auto typeDMRGObserver = initDMRGObserver<ITensor>(module, "DMRGObserver");
  auto typeIQDMRGObserver = initDMRGObserver<IQTensor>(module, "IQDMRGObserver");
}
