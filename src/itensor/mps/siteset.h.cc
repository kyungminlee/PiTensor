#include "../../pitensor.h"
#include "itensor/mps/siteset.h"
namespace py = pybind11;
using namespace itensor;

static inline
auto
initSiteSet(pybind11::module& module)
{
  using Type = SiteSet;
  using String = SiteSet::String;
  py::class_<SiteSet> type(module, "SiteSet");

  type.def(py::init<>());
  type.def(py::init<int, int>());
  type.def(py::init<std::vector<IQIndex> const &>());

  type
      .def("__bool__", [](SiteSet const & self) { return static_cast<bool>(self); })
      .def("__getitem__", [](SiteSet const & self, int i) {
                            if (i <= 0 || i > self.N()) {
                              throw std::invalid_argument("SiteSet::operator(i) out of bounds");
                            }
                            return self(i);
                          })
      .def("__call__", [](SiteSet const & self, int i) {
                          // TODO check for bound
                          if (i <= 0 || i > self.N()) {
                            throw std::invalid_argument("SiteSet::operator(i) out of bounds");
                          }
                          return self(i);
                        })
      .def("__call__", [](SiteSet const & self,
                          int i,
                          std::string const & state) { // TODO check for bound
                         if (i <= 0 || i > self.N()) {
                           throw std::invalid_argument("SiteSet::operator(i) out of bounds");
                         }
                         return self(i, state);
                       })
      .def("__repr__", [](Type const & obj) { std::stringstream ss; ss << std::scientific << obj; return ss.str(); })
  ;

  type
      .def("N", &SiteSet::N)
      .def("op", [](SiteSet const & self,
                    String const & opname,
                    int i, Args const & args) {
                    return self.op(opname, i, args);
                    // TODO bound checking
                  },
                  py::arg("opname"),
                  py::arg("i"),
                  py::arg("args")=Args::global()
                  )
      .def("si", [](SiteSet const & self, int i) {
                   if (i <= 0 || i > self.N()) { // TODO check for bound
                     throw std::invalid_argument("SiteSet::si out of bounds");
                   }
                   return self.si(i);
                 })
      .def("siP", [](SiteSet const & self, int i) {
                    if (i <= 0 || i > self.N()) { // TODO check for bound
                      throw std::invalid_argument("SiteSet::siP out of bounds");
                    }
                    return self.siP(i);
                  })
      .def("st", [](SiteSet const & self, int i, String const & state) {
                   if (i <= 0 || i > self.N()) { // TODO check for bound
                     throw std::invalid_argument("SiteSet::st out of bounds");
                   }
                   return self.st(i, state);
                 })
      .def("stP", [](SiteSet const & self, int i, String const & state) {
                    if (i <= 0 || i > self.N()) { // TODO check for bound
                      throw std::invalid_argument("SiteSet::stP out of bounds");
                    }
                    return self.stP(i, state);
                  })
      // TODO read, write
  ;

  return type;
}

void pitensor::mps::siteset(pybind11::module& module)
{
  auto typeSiteSet = initSiteSet(module);
}
