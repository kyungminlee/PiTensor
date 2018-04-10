#include "../pitensor.h"
#include "itensor/eigensolver.h"
#include "itensor/mps/mpo.h"
#include "itensor/mps/localmpo.h"

namespace py = pybind11;
using namespace itensor;

template <typename BigMatrixT, typename Tensor>
static inline
auto
_init(pybind11::module& module)
{
  module
      .def("davidson",
           (Real (*)(BigMatrixT const &, Tensor&, Args const &)) &davidson)
  ;
}


void pitensor::eigensolver(pybind11::module& module)
{
  _init<LocalMPO<ITensor>, ITensor>(module);
  _init<LocalMPO<IQTensor>, IQTensor>(module);
  // TODO: cross-combination?
  // TODO: BigMatrixT type?
}
