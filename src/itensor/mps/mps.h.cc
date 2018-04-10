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
  using Type = mps_type;

  py::class_<Type> type(module, typeName);

  type
      .def(py::init<>())
      .def(py::init<int>())
      .def(py::init<SiteSet const&>())
      .def(py::init<InitState const&>())
      .def(py::init<mps_type const&>())
  ;

  type
      .def("assign", [](mps_type & self, mps_type const & other) {
        self = other;
        return self;
      })
  ;

  type
      .def("N", (int (mps_type::*)() const) &mps_type::N)
      .def_property_readonly("sites", (SiteSet const & (mps_type::*)() const) &mps_type::sites)
      .def("__bool__", [](mps_type const & self) { return static_cast<bool>(self);})
      .def_property("rightLim",
                    [](mps_type const & self) { return self.rightLim(); },
                    [](mps_type & self, int i) { self.rightLim(i); }
      )
      .def_property("leftLim",
                    [](mps_type const & self) { return self.leftLim(); },
                    [](mps_type & self, int i) { self.leftLim(i); }
      )
      .def("A", (Tensor const & (mps_type::*)(int) const) &mps_type::A)
      .def("setA", (void (mps_type::*)(int, Tensor const &)) &mps_type::setA)
      //TODO void setA(int i, Tensor && nA) ;
      .def("Aref", (Tensor& (mps_type::*)(int i)) &mps_type::Aref)
      .def("Anc", (Tensor& (mps_type::*)(int)) &mps_type::Anc)
      .def("plusEq",
           (mps_type& (mps_type::*)(mps_type const&, Args const&)) &mps_type::plusEq,
           py::arg("R"),
           py::arg("args")=Args::global())
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
      .def("norm", (Real (mps_type::*)() const) &mps_type::norm)
      .def("normalize", (Real (mps_type::*)()) &mps_type::normalize)
      .def("isOrtho", (bool (mps_type::*)() const) &mps_type::isOrtho)
      .def("orthoCenter", (int (mps_type::*)() const) &mps_type::orthoCenter)
      .def("isComplex", (bool (mps_type::*)() const) &mps_type::isComplex)
  ;

  type
  /*
      .def("write", [](Type const & self, py::object pyostream) {
        pitensor::pythonbytebuf buffer(pyostream);
        std::ostream output_stream(&buffer);
        self.write(output_stream);
      })
          */
    // TODO: read with file stream
      //.def("write", [](Type const & self, std::string const & filename) {
      .def("write", [](Type const & self, py::object arg) {
        if (py::isinstance<py::str>(arg)) {
          std::ofstream output_stream(arg.cast<std::string>());
          self.write(output_stream);
        } else {
          auto io = py::module::import("io");
          if (py::isinstance(arg, io.attr("BufferedWriter"))) {
            // TODO: Create PyBind Wrapper for BufferedWriter
            std::ostringstream output_stream;
            self.write(output_stream);
            arg.attr("write")(py::bytes(output_stream.str()));
           } else {
            throw std::domain_error("Unsupported argument type for write");
          }
        }
        return self;
      })
      //.def("read", [](Type & self, std::string const & filename) {
      .def("read", [](Type & self, py::object arg) {
        if (py::isinstance<py::str>(arg)) {
          std::ifstream input_stream(arg.cast<std::string>());
          self.read(input_stream);
        } else {
          auto io = py::module::import("io");
          if (py::isinstance(arg, io.attr("BufferedReader"))) {
            py::bytes data = arg.attr("read")();
            std::istringstream input_stream(data);
            self.read(input_stream);
          } else {
            throw std::domain_error("Unsupported argument type for read");
          }
        }
        return self;
      })
      //.def("read", (void (mps_type::*)(std::istream&)) &mps_type::read)
  ;
  type
      .def("__repr__", [](Type const & obj) { std::stringstream ss; ss << std::scientific << obj; return ss.str(); })
  ;


  module
      .def("isComplex", (bool (*)(mps_type const &)) &isComplex)
      .def("isOrtho", (bool (*)(mps_type const &)) &isOrtho)
      .def("orthoCenter", (int (*)(mps_type const&)) &orthoCenter)
      .def("norm", (Real (*)(mps_type const&)) &norm)
      .def("normalize", (Real (*)(mps_type &)) &normalize)
      .def("linkInd", (IndexT (*)(mps_type const&, int)) &linkInd)
      .def("rightLinkInd", (IndexT (*)(mps_type const&, int)) &rightLinkInd)
      .def("leftLinkInd", (IndexT (*)(mps_type const&, int)) &leftLinkInd)
      .def("averageM", (Real (*)(mps_type const&)) &averageM)
      .def("maxM", (int (*)(mps_type const&)) &maxM)
      .def("applyGate", (void (*)(const Tensor&, mps_type&, const Args&)) &applyGate)
      .def("checkOrtho", (bool (*)(const mps_type& psi, int, bool)) &checkOrtho)
      .def("checkOrtho", (bool (*)(mps_type const& psi)) &checkOrtho)
      .def("checkQNs", (bool (*)(mps_type const& psi)) &checkQNs)
      .def("overlap", (Real (*)(mps_type const&, mps_type const&)) &overlap)
      .def("overlapC", (Cplx (*)(mps_type const&, mps_type const&)) &overlapC)
      .def("overlap", (void (*)(mps_type const&, mps_type const&, Real&, Real&)) &overlap)
      .def("fitWF", (void (*)(const mps_type&, mps_type&)) &fitWF)
      .def("sum", (mps_type (*)(mps_type const&, mps_type const&, Args const&)) &sum)
      .def("sum", (mps_type (*)(std::vector<mps_type> const&, Args const&)) &sum)
  ;

  return type;
}


static inline
auto
initInitState(pybind11::module& module)
{
  using Type = InitState;
  py::class_<InitState> type(module, "InitState");
  type
      .def(py::init<SiteSet const &>())
      .def(py::init<SiteSet const &, std::string const &>())
  ;
  type
      .def("set", &InitState::set)
      .def("setAll", &InitState::setAll)
      .def("__getitem__", [](InitState const & state, int i) {
        return state(i);
      })
      .def_property_readonly("sites", &InitState::sites)
  ;

  type
      .def("__repr__", [](Type const & obj) { std::stringstream ss; ss << std::scientific << obj; return ss.str(); })
      ;
  return type;
}

void pitensor::mps::mps(pybind11::module& module)
{
  initMPSt<ITensor>(module, "MPS");
  initMPSt<IQTensor>(module, "IQMPS");

  module
      .def("findCenter", (int (*)(IQMPS const& psi)) &findCenter)
      .def("totalQN", (QN (*)(IQMPS const& psi)) &totalQN)
  ;

  initInitState(module);
}
