#include "../pitensor.h"
#include "itensor/indextype.h"
namespace py = pybind11;
using namespace itensor;

void pitensor::indextype(pybind11::module& module)
{
  py::class_<IndexType> type(module, "IndexType");

  type
    .def(py::init<const char*>())
    .def_property_readonly_static("size", &IndexType::size)
    .def("c_str", &IndexType::c_str)
    .def("__repr__",
         [](IndexType const & obj) -> std::string {
           std::stringstream ss; ss << static_cast<const char*>(obj); return ss.str();
         })
    .def("__getitem__",
         [](IndexType const & obj, size_t i) -> char { return obj[i]; })
    .def("__setitem__",
         [](IndexType& obj, size_t i, char c) -> void { obj[i] = c; })
  ;

  module.attr("All") = All;
  module.attr("All") = All;
  module.attr("NullInd") = NullInd;
  module.attr("Link") = Link;
  module.attr("Site") = Site;
  module.attr("Atype") = Atype;
  module.attr("Btype") = Btype;
  module.attr("Ctype") = Ctype;
  module.attr("Dtype") = Dtype;
  module.attr("Vtype") = Vtype;
  module.attr("Wtype") = Wtype;
  module.attr("Xtype") = Xtype;
  module.attr("Ytype") = Ytype;
  module.attr("Ztype") = Ztype;
  ;
}
