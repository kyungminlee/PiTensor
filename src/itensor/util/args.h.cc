#include "../../pitensor.h"
#include "itensor/util/args.h"
#include <pybind11/embed.h>

namespace py = pybind11;
using namespace itensor;

// TODO: Implement python version altogether?

static inline
auto
initArgs(pybind11::module& module)
{
  py::class_<Args> type(module, "Args");
  using namespace pybind11::literals;
  type
      .def(py::init<>())
      .def(py::init(
           [](py::kwargs kwargs) {
             auto self = new Args();
             for (auto const & kv : kwargs) {
               auto key = kv.first.cast<std::string>();
               auto val = kv.second;
               auto typestr = py::str(val.get_type()).cast<std::string>();
               if (typestr == "<class 'bool'>") {
                 self->add(key, val.cast<bool>());
               } else if (typestr == "<class 'int'>") {
                 self->add(key, val.cast<long>());
               } else if (typestr == "<class 'float'>") {
                 self->add(key, val.cast<double>());
               } else if (typestr == "<class 'str'>") {
                 self->add(key, val.cast<std::string>());
               } // TODO: Find better way.
             }
             return self;
           })
      )
      .def("add",
           (void (Args::*)(std::string const &, bool)) &Args::add)
      .def("add",
           (void (Args::*)(std::string const &, long)) &Args::add)
      .def("add",
           (void (Args::*)(std::string const &, std::string const &)) &Args::add)
      .def("add",
           (void (Args::*)(std::string const &, Real)) &Args::add)
      .def("defined", &Args::defined)
      .def("remove", &Args::remove)
      // TODO: getBool
      // TODO: getString
      // TODO: getInt
      // TODO: getReal
      .def("__repr__",
           [](Args const & obj) -> std::string { std::stringstream ss; ss << obj; return ss.str(); })
      .def(py::self + py::self)
  ;
  return type;
}

void pitensor::util::args(pybind11::module& module)
{
  auto typeArgs = initArgs(module);
}