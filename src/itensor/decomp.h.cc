#include "../pitensor.h"
#include "itensor/decomp.h"
namespace py = pybind11;
using namespace itensor;

template <class Tensor>
static
Spectrum
safeSvd(Tensor AA, Tensor& U, Tensor& D, Tensor& V, Args args)
{
  if (!AA.store()) {
    throw ITError("Called svd on tensor not yet allocated");
  } else {
    return svd(AA, U, D, V, args);
  }
}

template <class Tensor>
static
Spectrum
safeFactor(Tensor const & T, Tensor& A, Tensor& B, Args const & args)
{
  if (!T.store()) {
    throw ITError("Called factor on tensor not yet allocated");
  } else {
    return factor(T, A, B, args);
  }
}


template <class Tensor>
static
Spectrum
safeDenmatDecomp(Tensor const & AA, Tensor& A, Tensor& B, Direction dir, Args const & args)
{
  if (!AA.store()) {
    throw ITError("Called denmatDecomp on tensor not yet allocated");
  } else {
    return denmatDecomp(AA, A, B, dir, args);
  }
}

// TODO denmatDecomp with BigMatrixT


template <class Tensor>
static
Spectrum
safeDiagHermitian(Tensor const & M, Tensor& U, Tensor& D, Args args)
{
  if (!M.store()) {
    throw ITError("Called diagHermitian on tensor not yet allocated");
  } else {
    return diagHermitian(M, U, D, args);
  }
}


template <class Tensor>
static inline
auto
initDecomp(pybind11::module& module)
{
  module
      .def("svd",
           (Spectrum (*)(Tensor, Tensor &, Tensor &, Tensor &, Args)) &safeSvd,
           "Singular value decomposition",
           py::arg("AA"),
           py::arg("U"),
           py::arg("D"),
           py::arg("V"),
           py::arg("args") = Global::args())
      .def("factor",
           (Spectrum (*)(Tensor const &, Tensor &, Tensor &, Args const &)) &safeFactor,
           "Factor Decomposition",
           py::arg("T"),
           py::arg("A"),
           py::arg("B"),
           py::arg("args") = Args::global())
      .def("denmatDecomp",
           (Spectrum (*)(Tensor const &, Tensor &, Tensor &, Direction, Args const &)) &safeDenmatDecomp,
           "Density matrix decomposition",
           py::arg("AA"),
           py::arg("A"),
           py::arg("B"),
           py::arg("dir"),
           py::arg("args") = Args::global())
      // TODO: denmatDecomp with BigMatrixT
      .def("diagHermitian",
           (Spectrum (*)(Tensor const &, Tensor &, Tensor &, Args)) &safeDiagHermitian,
           "Hermitian diagonalization",
           py::arg("M"),
           py::arg("U"),
           py::arg("D"),
           py::arg("args") = Args::global())
      .def("expHermitian",
           (Tensor (*)(Tensor const &, Cplx)) &expHermitian,
           "Hermitian Exponential",
           py::arg("T"),
           py::arg("t") = 1.)
      .def("eigen",
           (void (*)(Tensor const &, Tensor &, Tensor & D, Args const &)) &eigen,
           "Eigenvalues and eigenvectors",
           py::arg("T"),
           py::arg("V"),
           py::arg("D"),
           py::arg("args") = Args::global())

      ;
}


void pitensor::decomp(pybind11::module& module)
{
  initDecomp<ITensor>(module);
  // TODO initDecomp<IQTensor>(module);
}
