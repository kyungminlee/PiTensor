#include "../../pitensor.h"
#include "itensor/mps/sweeps.h"
namespace py = pybind11;
using namespace itensor;


static inline
auto
initSweeps(pybind11::module& module)
{
  py::class_<Sweeps> type(module, "Sweeps");

  type.def(py::init<>());
  type.def(py::init<int, int, int, Real>(),
           py::arg("nsweeps"),
           py::arg("minm")=1,
           py::arg("maxm")=500,
           py::arg("cutoff")=1E-8);
  type.def(py::init<int, InputGroup &>()); // TODO: InputGroup

  // std::vector<int> maxm_, minm_, niter_;
  // std::vector<Real> cutoff_, noise_;
  // int nsweep_;

  type
      .def_property("nsweep",
                    (int (Sweeps::*)() const) &Sweeps::nsweep,
                    (void (Sweeps::*)(int)) &Sweeps::nsweep)
      .def_property_readonly("size", &Sweeps::size)
      .def_property("minm",
                    [](Sweeps const & self) -> std::vector<int> {
                      std::vector<int> res;
                      // TODO: check 0-based or 1-based.
                      for (int i = 0, ns = self.nsweep() ; i < ns ; ++i) {
                        res.push_back(self.minm(i));
                      }
                      return res;
                    },
                    [](Sweeps & self, std::vector<int> const & minm) {
                      int curMinM = 1;
                      for (int i = 0, ns = self.nsweep() ; i < ns ; ++i) {
                        if (i < minm.size()) { curMinM = minm[i]; }
                        if (curMinM > 0) { self.setminm(i, curMinM); }
                        // TODO: document : set only positive
                      }
                    }
      )
      .def("setminm", // TODO bound check
           (int (Sweeps::*)(int, int)) &Sweeps::setminm)
      .def_property("maxm",
        [](Sweeps const & self) -> std::vector<int> {
          std::vector<int> res;
          // TODO: check 0-based or 1-based.
          for (int i = 0, ns = self.nsweep() ; i < ns ; ++i) {
            res.push_back(self.maxm(i));
          }
          return res;
        },
        [](Sweeps & self, std::vector<int> const & maxm) {
          int curMaxM = 1;
          for (int i = 0, ns = self.nsweep() ; i < ns ; ++i) {
            if (i < maxm.size()) { curMaxM = maxm[i]; }
            if (curMaxM > 0) { self.setmaxm(i, curMaxM); }
            // TODO: document : set only positive
          }
        }
      )
      .def("setmaxm", // TODO bound check
           (int (Sweeps::*)(int, int)) &Sweeps::setmaxm)
          // TODO: bound check
      .def("__repr__", [](Sweeps const & obj) { std::stringstream ss; ss << obj; return ss.str(); })
      .def_property("cutoff",
          [](Sweeps const & self) -> std::vector<Real> {
            std::vector<Real> res;
            for (int i = 0, ns = self.nsweep() ; i < ns ; ++i) {
              res.push_back(self.cutoff(i));
            }
            return res;
          },
          [](Sweeps & self, py::object obj) { // Overloading (list vs single Real)
            if (py::isinstance<py::list>(obj)) {
              if (py::list(obj).size() != self.nsweep()) {
                throw std::length_error("Length of the list does not match the number of sweeps");
              }

              int i = 0;
              for (auto const & item : py::list(obj)) {
                Real r = item.cast<Real>(); // this does type check
                self.setcutoff(i, r);
                ++i;
              }
            } else if (py::isinstance<py::float_>(obj)) {
              Real v = obj.cast<Real>();
              for (int i = 0, ns = self.nsweep() ; i < ns ; ++i) {
                self.setcutoff(i, v);
              }
            } else {
              throw std::domain_error("Unsupported type");
            }
          }
      )
    // TODO noise
    // TODO niter
    // TODO write
  ;
}

void pitensor::mps::sweeps(pybind11::module& module)
{
  initSweeps(module);
}
