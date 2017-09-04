#include "../../pitensor.h"
#include "itensor/mps/mps.h"
namespace py = pybind11;
using namespace itensor;

template <typename Tensor>
static inline
auto
initMPSt(pybind11::module& module, const char* typeName)
{
  using mps_type = MPSt<Tensor>;
  using TensorT = Tensor;
  using IndexT = typename Tensor::index_type;
  using IndexValT = typename Tensor::indexval_type;
  using MPOType = MPOt<Tensor>;

  py::class_<MPSt<Tensor>> type(module, typeName);
  type.def(py::init<>());
  type.def(py::init<int>());
  type.def(py::init<SiteSet const&>());
  type.def(py::init<mps_type const&>());

  type
      .def("N", (int (mps_type::*)() const) &mps_type::N)
      .def("sites", (SiteSet const & (mps_type::*)() const) &mps_type::sites)
      .def("__bool__", [](mps_type const & self) { return static_cast<bool>(self);})
      .def("rightLim", (int (mps_type::*)() const) &mps_type::rightLim)
      .def("leftLim", (int (mps_type::*)() const) &mps_type::leftLim)
      .def("A", (Tensor const & (mps_type::*)(int) const) &mps_type::A)
      .def("setA", (void (mps_type::*)(int, Tensor const &)) &mps_type::setA)
      //TODO void setA(int i, Tensor && nA) ;
      .def("Aref", (Tensor& (mps_type::*)(int i)) &mps_type::Aref)
      .def("Anc", (Tensor& (mps_type::*)(int)) &mps_type::Anc)
      .def("plusEq",
           (mps_type& (mps_type::*)(mps_type const&, Args const&)) &mps_type::plusEq,
           py::arg("R"),
           py::arg("args") = Args::global())
      .def("mapprime",
           (void (mps_type::*)(int, int, IndexType)) &mps_type::mapprime,
           py::arg("oldp"),
           py::arg("newp"),
           py::arg("type")=All)
      .def("primelinks", (void (mps_type::*)(int, int)) &mps_type::primelinks)
      .def("noprimelink", (void (mps_type::*)()) &mps_type::noprimelink)
      .def("svdBond",
           (Spectrum (mps_type::*)(int, Tensor const&, Direction, Args const&)) &mps_type::svdBond,
           py::arg("b"),
           py::arg("AA"),
           py::arg("dir"),
           py::arg("args") = Args::global())
      //TODO svdBond with LocalOpT
      .def("position",
           (void (mps_type::*)(int, Args const&)) &mps_type::position,
           py::arg("i"),
           py::arg("args") = Args::global())
      .def("orthogonalize",
           (void (mps_type::*)(Args const&)) &mps_type::orthogonalize,
           py::arg("args") = Args::global())
      .def("swap", (void (mps_type::*)(mps_type& other)) &mps_type::swap)
      .def("rightLim", (void (mps_type::*)(int)) &mps_type::rightLim)
      .def("leftLim", (void (mps_type::*)(int)) &mps_type::leftLim)
      .def("norm", (Real (mps_type::*)() const) &mps_type::norm)
      .def("normalize", (Real (mps_type::*)()) &mps_type::normalize)
      .def("isOrtho", (bool (mps_type::*)() const) &mps_type::isOrtho)
      .def("orthoCenter", (int (mps_type::*)() const) &mps_type::orthoCenter)
      .def("isComplex", (bool (mps_type::*)() const) &mps_type::isComplex)
  ;
}

void pitensor::mps::mps(pybind11::module& module)
{
  initMPSt<ITensor>(module, "MPS");
  initMPSt<IQTensor>(module, "IQMPS");
}
