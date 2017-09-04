#include "../../pitensor.h"
#include "itensor/mps/dmrg.h"
namespace py = pybind11;
using namespace itensor;


template <typename Tensor>
static inline
void
init(pybind11::module& module)
{
  using mps_type = MPSt<Tensor>;
  using mpo_type = MPOt<Tensor>;

  module
      .def("dmrg",
           (Real (*)(mps_type & psi,
                     mpo_type const &,
                     Sweeps const &,
                     Args const &)) &dmrg,
           py::arg("psi"),
           py::arg("H"),
           py::arg("sweeps"),
           py::arg("args")=Global::args())
      .def("dmrg",
           (Real (*)(mps_type & psi,
                     mpo_type const &,
                     Sweeps const &,
                     DMRGObserver<Tensor>&,
                     Args const &)) &dmrg,
           py::arg("psi"),
           py::arg("H"),
           py::arg("sweeps"),
           py::arg("obs"),
           py::arg("args")=Global::args())
      .def("dmrg",
           (Real (*)(mps_type & psi,
                     mpo_type const &,
                     Tensor const & LH,
                     Tensor const & RH,
                     Sweeps const &,
                     Args const &)) &dmrg,
           py::arg("psi"),
           py::arg("H"),
           py::arg("LH"),
           py::arg("RH"),
           py::arg("sweeps"),
           py::arg("args")=Global::args())
      .def("dmrg",
           (Real (*)(mps_type & psi,
                     mpo_type const &,
                     Tensor const & LH,
                     Tensor const & RH,
                     Sweeps const &,
                     DMRGObserver<Tensor>&,
                     Args const &)) &dmrg,
           py::arg("psi"),
           py::arg("H"),
           py::arg("LH"),
           py::arg("RH"),
           py::arg("sweeps"),
           py::arg("obs"),
           py::arg("args")=Global::args())
      .def("dmrg",
           (Real (*)(mps_type & psi,
                     std::vector<mpo_type> const &,
                     Sweeps const &,
                     Args const &)) &dmrg,
           py::arg("psi"),
           py::arg("Hset"),
           py::arg("sweeps"),
           py::arg("args")=Global::args())
      .def("dmrg",
           (Real (*)(mps_type & psi,
                     std::vector<mpo_type> const &,
                     Sweeps const &,
                     DMRGObserver<Tensor>&,
                     Args const &)) &dmrg,
           py::arg("psi"),
           py::arg("Hset"),
           py::arg("sweeps"),
           py::arg("obs"),
           py::arg("args")=Global::args())
      .def("dmrg",
           (Real (*)(mps_type & psi,
                     mpo_type const &,
                     std::vector<mps_type> const &,
                     Sweeps const &,
                     Args const &)) &dmrg,
           py::arg("psi"),
           py::arg("H"),
           py::arg("psis"),
           py::arg("sweeps"),
           py::arg("args")=Global::args())
      .def("dmrg",
           (Real (*)(mps_type & psi,
                     mpo_type const &,
                     std::vector<mps_type> const &,
                     Sweeps const &,
                     DMRGObserver<Tensor>&,
                     Args const &)) &dmrg,
           py::arg("psi"),
           py::arg("H"),
           py::arg("psis"),
           py::arg("sweeps"),
           py::arg("obs"),
           py::arg("args")=Global::args())
  ;

  // TODO DMRGWorker

}


void pitensor::mps::dmrg(pybind11::module& module)
{
  init<ITensor>(module);
  init<IQTensor>(module);
}
