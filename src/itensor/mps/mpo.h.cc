#include "../../pitensor.h"
#include "itensor/mps/mpo.h"
namespace py = pybind11;
using namespace itensor;

template <typename Tensor>
auto
initMPOt(pybind11::module& module, const char* typeName)
{
  using mpo_type = MPOt<Tensor>;
  using mps_type = MPSt<Tensor>;
  py::class_<mpo_type> type(module, typeName);

  type
      .def(py::init<>())
      .def(py::init<SiteSet const&, Real>(),
           py::arg("sites"),
           py::arg("refNorm")=DefaultLogRefScale) // TODO: variable name mismatch with ITensor
  ;

  type
      .def("__bool__", [](mpo_type const & self) { return static_cast<bool>(self); })
  ;

  type
      .def("logRefNorm", &mpo_type::logRefNorm)
      .def("plusEq", &mpo_type::plusEq)
      .def("toMPO", &mpo_type::toMPO)
      .def("primeall", &mpo_type::primeall)
      .def("svdBond", &mpo_type::svdBond)
      .def("position", &mpo_type::position)
      .def("orthogonalize", &mpo_type::orthogonalize)
  ;

  type
      .def(py::self *= Real())
      .def(py::self *= Cplx())
      .def(py::self /= Real())
      .def(py::self /= Cplx())
      .def(py::self * Real())
      .def(Real() * py::self)
      .def(py::self * Cplx())
      .def(Cplx() * py::self)
  ;

  module
      .def("isComplex",
           (bool (*)(mpo_type const &)) &isComplex)
      .def("isOrtho",
           (bool (*)(mpo_type const &)) &isOrtho)
      .def("orthoCenter",
           (int (*)(mpo_type const &)) &orthoCenter)
  ;

  module
      .def("sum",
           (mpo_type (*)(mpo_type, mpo_type const &, Args const &)) &sum,
           py::arg("L"),
           py::arg("R"),
           py::arg("args")=Args::global())
      // TODO Did not implement overlap with intent(OUT) arguments
      .def("overlap",
           (Real (*)(mps_type const & , mpo_type const &, mps_type const &)) &overlap,
           py::arg("psi"),
           py::arg("H"),
           py::arg("phi"))
      .def("overlapC",
           (Complex (*)(mps_type const & , mpo_type const &, mps_type const &)) &overlapC,
           py::arg("psi"),
           py::arg("H"),
           py::arg("phi"))
      .def("overlap",
           (Real (*)(mps_type const &,
                     mpo_type const &,
                     Tensor const &,
                     Tensor const &,
                     mps_type const &)) &overlap)
      .def("overlap",
           (Real (*)(mps_type const &,
                     mpo_type const &,
                     mpo_type const &,
                     mps_type const &)) &overlap)
#if 0 // TODO: why is this missing?
      .def("overlapC",
           (Complex (*)(mps_type const &,
                     mpo_type const &,
                     Tensor const &,
                     Tensor const &,
                     mps_type const &)) &overlapC)
#endif
      .def("overlapC",
           (Complex (*)(mps_type const &,
                        mpo_type const &,
                        mpo_type const &,
                        mps_type const &)) &overlapC)
      .def("nmultMPO",
           (void (*)(mpo_type const &,
                     mpo_type const &,
                     mpo_type &,
                     Args)) &nmultMPO,
           py::arg("Aorig"),
           py::arg("Borig"),
           py::arg("res"),
           py::arg("args")=Args::global())
      // PYTHON IMPLEMENTATION
      .def("nmultMPO",
           [](mpo_type const & Aorig, mpo_type const & Borig, Args arg) {
             mpo_type res;
             nmultMPO(Aorig, Borig, res, arg);
             return res;
           },
           py::arg("Aorig"),
           py::arg("Borig"),
           py::arg("args")=Args::global())
      .def("zipUpApplyMPO",
           (void (*)(mps_type const &,
                     mpo_type const &,
                     mps_type &,
                     Args const &)) &zipUpApplyMPO,
           py::arg("psi"),
           py::arg("K"),
           py::arg("res"),
           py::arg("args")=Args::global())
      // PYTHON IMPLEMENTATION
      .def("zipUpApplyMPO",
           [](mps_type const & psi, mpo_type const & K, Args const &args) {
             mps_type res;
             zipUpApplyMPO(psi, K, res, args);
             return res;
           },
           py::arg("psi"),
           py::arg("K"),
           py::arg("args")=Args::global())
      .def("exactApplyMPO",
           (mps_type (*)(mpo_type const &, mps_type const &, Args const &)) &exactApplyMPO,
           py::arg("K"),
           py::arg("x"),
           py::arg("args") = Args::global())
      .def("fitApplyMPO",
           (mps_type (*)(mps_type const &, mpo_type const &, Args const &)) &fitApplyMPO,
           py::arg("psi"),
           py::arg("K"),
           py::arg("args") = Args::global())
      .def("fitApplyMPO",
           (void (*)(Real,
                     mps_type const &,
                     mpo_type const &,
                     mps_type &,
                     Sweeps const &,
                     Args)) &fitApplyMPO,
           py::arg("fac"),
           py::arg("psi"),
           py::arg("K"),
           py::arg("res"),
           py::arg("sweeps"),
           py::arg("args") = Args::global()
           // TODO: ITensor does not have default argument here.
      )
    // TODO fitApplyMPO
    // TODO fitApplyMPO
    // TODO fitApplyMPO
    // TODO fitApplyMPO
    // TODO fitApplyMPO
    // TODO expH
    // TODO applyExpH
    // TODO putMPOLinks
    // TODO putMPOLinks
      // TODO exactApplyMPO
      // TODO exactApplyMPO
      .def("__repr__", [](mpo_type const & obj) { std::stringstream ss; ss << obj; return ss.str(); })
  ;
  return type;
}

void pitensor::mps::mpo(pybind11::module& module)
{
  auto typeMPO = initMPOt<ITensor>(module, "MPO");
  auto typeIQMPO = initMPOt<IQTensor>(module, "IQMPO");

  module
      .def("findCenter",
           (int (*)(IQMPO const &)) &findCenter)
      .def("checkQNs",
           (void (*)(MPO const &)) & checkQNs)
      .def("checkQNs",
           (void (*)(IQMPO const &)) & checkQNs)
  ;
}
