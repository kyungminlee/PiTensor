#include "../../pitensor.h"
#include "itensor/mps/bondgate.h"
namespace py = pybind11;
using namespace itensor;

template <typename Tensor>
static inline
auto
initBondGate(py::module& module, const char * typeName)
{
  using GateType = BondGate<Tensor>;
  py::class_<GateType> type(module, typeName);

  py::enum_<typename GateType::Type>(type, "Type")
      .value("tReal", GateType::tReal)
      .value("tImag", GateType::tImag)
      .value("Swap", GateType::Swap)
      .export_values()
  ;

  type
      .def(py::init<SiteSet const &,
                    int,
                    int>(),
           py::arg("sites"),
           py::arg("i1"),
           py::arg("i2")
      )
      .def(py::init<SiteSet const &,
                    int,
                    int,
                    typename GateType::Type,
                    Real,
                    Tensor>(),
           py::arg("sites"),
           py::arg("i1"),
           py::arg("i2"),
           py::arg("type"),
           py::arg("tau"),
           py::arg("bondH")
      )
  ;

  type
    .def_property_readonly("i1", &GateType::i1)
    .def_property_readonly("i2", &GateType::i2)
    .def_property_readonly("gate", &GateType::gate)
    .def_property_readonly("type", &GateType::type)
  ;

  type
    .def(py::self * Tensor())
    .def(Tensor() * py::self)
  ;

  return type;
}
void pitensor::mps::bondgate(pybind11::module& module) {
  auto typeGate = initBondGate<ITensor>(module, "Gate");
  auto typeIQGate = initBondGate<IQTensor>(module, "IQGate");
}
