#include "../pitensor.h"
#include "itensor/eigensolver.h"
namespace py = pybind11;
using namespace itensor;

template <typename BigMatrixT, typename Tensor>
static inline
auto
init(pybind11::module& module)
{
  module
      .def("davidson",
           (Real (*)(BigMatrixT const &, Tensor&, Args const &)) &davidson)
  ;
}


void pitensor::eigensolver(pybind11::module& module)
{

}
