#include "../pitensor.h"
#include "itensor/global.h"
namespace py = pybind11;
using namespace itensor;

static inline
auto
initDirection(pybind11::module& module)
{
  py::enum_<Direction> type(module, "Direction");
  type
      .value("Fromright", Direction::Fromright)
      .value("Fromleft", Direction::Fromleft)
      .value("BothDir", Direction::BothDir)
      .value("NoDir", Direction::NoDir)
  ;
  return type;
}

static inline
auto
initGlobal(pybind11::module& module)
{
  using Type = Global;
  py::class_<Global> type(module, "Global");

  type
      .def_property_static(
          "checkArrows",
          [](py::object) -> bool { return Global::checkArrows(); },
          [](py::object, bool val) { Global::checkArrows() = val; }
      )
      .def_property_static(
          "debug1",
          [](py::object) -> bool { return Global::debug1(); },
          [](py::object, bool val) { Global::debug1() = val; }
      )
      .def_property_static(
          "debug2",
          [](py::object) -> bool { return Global::debug2(); },
          [](py::object, bool val) { Global::debug2() = val; }
      )
      .def_property_static(
          "debug3",
          [](py::object) -> bool { return Global::debug3(); },
          [](py::object, bool val) { Global::debug3() = val; }
      )
      .def_property_static(
          "debug4",
          [](py::object) -> bool { return Global::debug4(); },
          [](py::object, bool val) { Global::debug4() = val; }
      )
          //TODO args
      .def_property_static(
          "args",
          [](py::object) { return Global::args(); },
          [](py::object, Args const & val) { Global::args() = val; }
      )
      .def_property_static(
          "printdat",
          [](py::object) -> bool { return Global::printdat(); },
          [](py::object, bool val) { Global::checkArrows() = val; }
      )
      .def_property_static(
          "printScale",
          [](py::object) -> Real { return Global::printScale(); },
          [](py::object, Real val) { Global::printScale() = val; }
      )
      .def_property_static(
          "showIDs",
          [](py::object) -> bool { return Global::showIDs(); },
          [](py::object, bool val) { Global::showIDs() = val; }
      )
      .def_property_static(
          "read32BitIDs",
          [](py::object) -> bool { return Global::read32BitIDs(); },
          [](py::object, bool val) { Global::read32BitIDs() = val; }
      )
      .def_static("random", &Global::random)
      .def_static("warnDeprecated", &Global::warnDeprecated) // TODO: necessary?
  ;
  return type;
}


void pitensor::global(pybind11::module& module)
{
  auto typeDirection = initDirection(module);
  auto typeGlobal = initGlobal(module);
}
