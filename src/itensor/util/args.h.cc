#include "../../pitensor.h"
#include "itensor/util/args.h"
#include <pybind11/embed.h>

namespace py = pybind11;
using namespace itensor;

// TODO: Implement python version altogether!

#if 1
class PyArgs : public Args
{
 public:

  PyArgs() : Args() {}
  PyArgs(Args const & args) : Args(args) { }
  PyArgs(Args && args) : Args(std::forward<Args>(args)) { }

  operator Args const &() const { return *this; }
  operator Args () const { return *this; }

  PyArgs(py::dict kwargs) : Args() {
    for (auto const & kv : kwargs) {
      auto key = kv.first.cast<std::string>();
      auto val = kv.second;
      if (py::isinstance<py::bool_>(val)) {
        add(key, val.cast<bool>());
      } else if (py::isinstance<py::int_>(val)) {
        add(key, val.cast<long>());
      } else if (py::isinstance<py::float_>(val)) {
        add(key, val.cast<double>());
      } else if (py::isinstance<py::str>(val)) {
        add(key, val.cast<std::string>());
      } else {
        throw std::invalid_argument("unsupported argument type");
      }
    }
  }
};
#endif

static inline
auto
initArgs(pybind11::module& module)
{
  //using PyArgs = Args;
  py::class_<Args> foo(module, "_Args");
  foo
      .def(py::init([](const PyArgs& args) {
        return new Args(args);
      }))
  ;
  py::class_<PyArgs, Args> type(module, "Args");

  using namespace pybind11::literals;

  type
      .def(py::init<>())
      .def(py::init<py::dict>())
#if 1
      .def(py::init(
           [](py::kwargs kwargs) {
             auto self = new PyArgs();
             for (auto const & kv : kwargs) {
               auto key = kv.first.cast<std::string>();
               auto val = kv.second;
               if (py::isinstance<py::bool_>(val)) {
                 self->add(key, val.cast<bool>());
               } else if (py::isinstance<py::int_>(val)) {
                 self->add(key, val.cast<long>());
               } else if (py::isinstance<py::float_>(val)) {
                 self->add(key, val.cast<double>());
               } else if (py::isinstance<py::str>(val)) {
                 self->add(key, val.cast<std::string>());
               } else {
                 throw std::invalid_argument("unsupported argument type");
               }
             }
             return self;
           })
      )
#endif
      .def("add",
           (void (PyArgs::*)(std::string const &, bool)) &PyArgs::add)
      .def("add",
           (void (PyArgs::*)(std::string const &, long)) &PyArgs::add)
      .def("add",
           (void (PyArgs::*)(std::string const &, std::string const &)) &PyArgs::add)
      .def("add",
           (void (PyArgs::*)(std::string const &, Real)) &PyArgs::add)
      .def("defined", &PyArgs::defined)
      .def("remove", &PyArgs::remove)
      // TODO: getBool
      // TODO: getString
      // TODO: getInt
      // TODO: getReal
  ;
  type
      .def("__repr__",
           [](PyArgs const & obj) -> std::string { std::stringstream ss; ss << std::scientific << obj; return ss.str(); })
      .def("__setitem__",
           (void (PyArgs::*)(std::string const &, bool)) &PyArgs::add)
      .def("__setitem__",
           (void (PyArgs::*)(std::string const &, long)) &PyArgs::add)
      .def("__setitem__",
           (void (PyArgs::*)(std::string const &, std::string const &)) &PyArgs::add)
      .def("__setitem__",
           (void (PyArgs::*)(std::string const &, Real)) &PyArgs::add)
  ;

  type
      .def(py::self + py::self)
  ;

  // TODO: test if this works
  // https://github.com/pybind/pybind11/blob/086d53e8c66a84d0ec723d5435918c76edd878e8/tests/test_smart_ptr.cpp#L79
  py::implicitly_convertible<py::dict, PyArgs>();
  py::implicitly_convertible<PyArgs, Args>();

  return type;
}

void pitensor::util::args(pybind11::module& module)
{
  auto typeArgs = initArgs(module);
}