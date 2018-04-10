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

  type
      .def_property("nsweep",
                    (int (Sweeps::*)() const) &Sweeps::nsweep,
                    (void (Sweeps::*)(int)) &Sweeps::nsweep)
      .def_property_readonly("size", &Sweeps::size)
      .def_property("minm",
                    [](Sweeps const & self) -> std::vector<int> {
                      std::vector<int> res;
                      for (int i = 0, ns = self.nsweep() ; i < ns ; ++i) {
                        res.push_back(self.minm(i+1));  // 1-based.
                      }
                      return res;
                    },
                    [](Sweeps & self, py::object obj) { // Overloading (list vs single Real)
                      if (py::isinstance<py::list>(obj)) {
                        py::list lst(obj);
                        int v = 1;
                        for (int i = 0, ns = self.nsweep() ; i < ns ; ++i) {
                          if (i < py::len(lst)) {
                            v = lst[i].cast<int>();
                          }
                          self.setminm(i+1, v);
                        }
                      } else if (py::isinstance<py::int_>(obj)) {
                        int v = obj.cast<int>();
                        for (int i = 0, ns = self.nsweep() ; i < ns ; ++i) {
                          self.setminm(i+1, v);
                        }
                      } else {
                        throw std::domain_error("Unsupported type");
                      }
                    })
      .def_property("maxm",
                    [](Sweeps const & self) -> std::vector<int> {
                      std::vector<int> res;
                      for (int i = 0, ns = self.nsweep() ; i < ns ; ++i) {
                        res.push_back(self.maxm(i+1));
                      }
                      return res;
                    },
                    [](Sweeps & self, py::object obj) { // Overloading (list vs single Real)
                      if (py::isinstance<py::list>(obj)) {
                        py::list lst(obj);
                        int v = 1;
                        for (int i = 0, ns = self.nsweep() ; i < ns ; ++i) {
                          if (i < py::len(lst)) { v = lst[i].cast<int>(); }
                          self.setmaxm(i+1, v);
                        }
                      } else if (py::isinstance<py::int_>(obj)) {
                        int v = obj.cast<int>();
                        for (int i = 0, ns = self.nsweep() ; i < ns ; ++i) {
                          self.setmaxm(i+1, v);
                        }
                      } else {
                        throw std::domain_error("Unsupported type");
                      }
                    })
      .def_property("niter",
                    [](Sweeps const & self) -> std::vector<int> {
                      std::vector<int> res;
                      for (int i = 0, ns = self.nsweep() ; i < ns ; ++i) {
                        res.push_back(self.niter(i+1));
                      }
                      return res;
                    },
                    [](Sweeps & self, py::object obj) { // Overloading (list vs single int)
                      if (py::isinstance<py::list>(obj)) {
                        py::list lst(obj);
                        int v = 1;
                        for (int i = 0, ns = self.nsweep() ; i < ns ; ++i) {
                          if (i < py::len(lst)) { v = lst[i].cast<int>(); }
                          self.setniter(i+1, v);
                        }
                      } else if (py::isinstance<py::int_>(obj)) {
                        int v = obj.cast<int>();
                        for (int i = 0, ns = self.nsweep() ; i < ns ; ++i) {
                          self.setniter(i+1, v);
                        }
                      } else {
                        throw std::domain_error("Unsupported type");
                      }
                    })
      .def_property("cutoff",
                    [](Sweeps const & self) -> std::vector<Real> {
                      std::vector<Real> res;
                      for (int i = 0, ns = self.nsweep() ; i < ns ; ++i) {
                        res.push_back(self.cutoff(i+1));
                      }
                      return res;
                      },
                    [](Sweeps & self, py::object obj) { // Overloading (list vs single Real)
                      if (py::isinstance<py::list>(obj)) {
                        py::list lst(obj);
                        Real v = 0;
                        for (int i = 0, ns = self.nsweep() ; i < ns ; ++i) {
                          if (i < py::len(lst)) { v = lst[i].cast<Real>(); }
                          self.setcutoff(i+1, v);
                        }
                      } else if (py::isinstance<py::float_>(obj)) {
                        int v = obj.cast<Real>();
                        for (int i = 0, ns = self.nsweep() ; i < ns ; ++i) {
                          self.setcutoff(i+1, v);
                        }
                      } else {
                        throw std::domain_error("Unsupported type");
                      }
                    })
      .def_property("noise",
                    [](Sweeps const & self) -> std::vector<Real> {
                      std::vector<Real> res;
                      for (int i = 0, ns = self.nsweep() ; i < ns ; ++i) {
                        res.push_back(self.noise(i+1));
                      }
                      return res;
                    },
                    [](Sweeps & self, py::object obj) { // Overloading (list vs single Real)
                      if (py::isinstance<py::list>(obj)) {
                        py::list lst(obj);
                        Real v = 0;
                        for (int i = 0, ns = self.nsweep() ; i < ns ; ++i) {
                          if (i < py::len(lst)) { v = lst[i].cast<Real>(); }
                          self.setnoise(i+1, v);
                        }
                      } else if (py::isinstance<py::float_>(obj)) {
                        Real v = obj.cast<Real>();
                        for (int i = 0, ns = self.nsweep() ; i < ns ; ++i) {
                          self.setnoise(i+1, v);
                        }
                      } else {
                        throw std::domain_error("Unsupported type");
                      }
                    })
      .def("setminm", // Bound check done by std::vector::at
           (void (Sweeps::*)(int, int)) &Sweeps::setminm)
      .def("setmaxm",
           (void (Sweeps::*)(int, int)) &Sweeps::setmaxm)
      .def("setniter",
           (void (Sweeps::*)(int, int)) &Sweeps::setniter)
      .def("setcutoff",
           (void (Sweeps::*)(int, Real)) &Sweeps::setcutoff)
      .def("setnoise",
           (void (Sweeps::*)(int, Real)) &Sweeps::setnoise)
      .def("__repr__", [](Sweeps const & obj) { std::stringstream ss; ss << std::scientific << obj; return ss.str(); })
      .def("read", &Sweeps::read)
      .def("write", &Sweeps::write)
  ;
}

void pitensor::mps::sweeps(pybind11::module& module)
{
  initSweeps(module);
  // TODO RampM
  // TODO ExpM
  // TODO sweepnext and sweepnext1
}
