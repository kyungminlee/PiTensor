#include "../pitensor.h"
#include "itensor/index.h"
namespace py = pybind11;
using namespace itensor;

static inline
auto
initIndex(pybind11::module& module)
{
  py::class_<Index> type(module, "Index");

  type
      .def(py::init<>(), "Constructor")
      .def(py::init<std::string const &, long, IndexType, int>(),
           "Constructor",
           py::arg("name"),
           py::arg("m")=1,
           py::arg("it")=Link,
           py::arg("primelev")=0)
      .def("prime",
           py::overload_cast<int>(&Index::prime),
           "Increase primelevel",
           py::arg("inc")=1)
      .def("prime",
           py::overload_cast<IndexType, int>(&Index::prime),
           "Increase primelevel",
           py::arg("type"),
           py::arg("inc")=1)
      .def("noprime",
           &Index::noprime,
           "Set primelevel to zero (optionally only if type matches)",
           py::arg("type")=All)
      .def("mapprime",
           &Index::mapprime,
           "Switch primelevel from plevold to plevnew",
           py::arg("plevold"),
           py::arg("plevnew"),
           py::arg("type")=All)
      .def("noprimeEquals",
           &Index::noprimeEquals,
           "Check if other Index is a copy of this, ignoring primeLevel")
      .def("dag", &Index::dag)
    // TODO read write
      //.def("write", &Index::write)
      //.def("read", &Index::read)
  ;

  type
      .def_property_readonly("size", &Index::size)
      .def_property_readonly("m", &Index::m)
      .def_property_readonly("type",&Index::type)
      .def_property_readonly("name", &Index::name)
      .def_property_readonly("rawname", &Index::rawname)
      .def_property_readonly("id", &Index::id)
      .def("dir", py::overload_cast<>(&Index::dir, py::const_))
      .def_property("primeLevel",
                    py::overload_cast<>(&Index::primeLevel, py::const_),
                    py::overload_cast<int>(&Index::primeLevel))

    //.def("dir", // TODO: why is this here?
  //    py::overload_cast<Arrow>(&Index::dir, py::const_))
  ;

  type
      .def(py::self == py::self)
      .def(py::self != py::self)
      .def(py::self < py::self)
      .def(py::self > py::self)
      .def(py::self == IndexVal())
  ;

  type
      .def("__bool__",
           [](const Index& index) { return static_cast<bool>(index); } )
      .def("__call__",
           [](Index const & obj, long val) -> IndexVal { return obj(val); },
           "Return an IndexVal with specific value")
      .def("__getitem__",
           [](Index const & obj, int plev) -> Index { return obj[plev]; },
           "Return copy of this Index with primelevel plev")
      .def("__int__",
           [](const Index& index) { return static_cast<long>(index); } )
      .def("__index__",
           [](const Index& index) { return static_cast<size_t>(index); } )
      .def("__repr__",
           [](Index const & obj) -> std::string { std::stringstream ss; ss << std::scientific << obj; return ss.str(); })
  ;

  module
      .def("dag",
           (Index (*)(Index)) &dag)
      .def("dag",
           (IndexVal (*)(IndexVal)) &dag)
      .def("prime",
           (Index (*)(Index)) &prime)
      .def("prime",
           (Index (*)(Index, int const &)) &prime,
           "Prime",
           py::arg("I"),
           py::arg("inc") = 1
      )
      .def("prime",
           (Index (*)(Index, IndexType const &, int const &)) &prime,
           "Prime",
           py::arg("I"),
           py::arg("type"),
           py::arg("inc") = 1)
      .def("noprime",
           (Index (*)(Index, IndexType const &)) &noprime,
           "Remove prime",
           py::arg("I"),
           py::arg("type") = All)
      .def("mapprime",
           (Index (*)(Index, int, int, IndexType)) &mapprime,
           "Switch primelevel from plevold to plevnew",
           py::arg("I"),
           py::arg("plevold"),
           py::arg("plevnew"),
           py::arg("type") = All)
      .def("sim",
           (Index (*)(Index const &, int)) &sim,
           "Make a new index with same properties as I, "
           "but a different id number (will not compare equal) "
           "and primelevel zero (or specified value)",
           py::arg("I"),
           py::arg("plev") = 0)
      .def("showm",
           (std::string (*)(Index const &)) &showm)
          ;

  return type;
}

static inline
auto
initIndexVal(pybind11::module& module)
{ // IndexVal
  py::class_<IndexVal> type(module, "IndexVal");
  type
      .def(py::init<>())
      .def(py::init<const Index &, long>())
      .def_property_readonly("m", &IndexVal::m)
      .def("__bool__",
           [](const IndexVal& iv) { return static_cast<bool>(iv); } )
      .def("prime",
           py::overload_cast<int>(&IndexVal::prime),
           "",
           py::arg("inc") = 1)
      .def("prime",
           py::overload_cast<IndexType, int>(&IndexVal::prime),
           "",
           py::arg("type"),
           py::arg("inc") = 1)
      .def("noprime",
           &IndexVal::noprime,
           "",
           py::arg("type") = All)
      .def("mapprime",
           &IndexVal::mapprime,
           "",
           py::arg("plevold"),
           py::arg("plevnew"),
           py::arg("type") = All)
      .def("dag", &IndexVal::dag)
      .def(py::self == py::self)
      .def(py::self != py::self)
      .def(py::self == Index())
      .def("__repr__", [](IndexVal const & obj) -> std::string { std::stringstream ss; ss << std::scientific << obj; return ss.str(); })
  ;
  return type;
}

void pitensor::index(pybind11::module& module) {
  auto typeIndex = initIndex(module);
  auto typeIndexVal = initIndexVal(module);

  module
      .def("dag", (Index (*)(Index)) &dag)
      .def("dag", (IndexVal (*)(IndexVal)) &dag)
      .def("prime", (Index (*)(Index)) &prime)
      .def("prime", (Index (*)(Index, int const&)) &prime)
      .def("prime", (Index (*)(Index, IndexType const&, int const&)) &prime)
      .def("noprime", (Index (*)(Index)) &noprime)
      .def("noprime", (Index (*)(Index, IndexType const&)) &noprime)
      .def("mapprime",
           (Index (*)(Index, int, int, IndexType)) &mapprime,
           "Return a copy of I with prime level changed to plevnew if old prime level was plevold."
               "Otherwise has no effect.",
           py::arg("I"),
           py::arg("plevold"),
           py::arg("plevnew"),
           py::arg("type") = All)
      .def("prime", (IndexVal (*)(IndexVal)) &prime)
      .def("prime", (IndexVal (*)(IndexVal, int const&)) &prime)
      .def("prime", (IndexVal (*)(IndexVal, IndexType const&, int const&)) &prime)
      .def("noprime", (IndexVal (*)(IndexVal)) &noprime)
      .def("noprime", (IndexVal (*)(IndexVal, IndexType const&)) &noprime)
      .def("mapprime",
           (IndexVal (*)(IndexVal, int, int, IndexType)) &mapprime,
           "Return a copy of I with prime level changed to plevnew if old prime level was plevold."
               "Otherwise has no effect.",
           py::arg("I"),
           py::arg("plevold"),
           py::arg("plevnew"),
           py::arg("type") = All)
      .def("sim",
           (Index (*)(Index const &, int)) &sim,
           "",
           py::arg("I"),
           py::arg("plev") = 0)
      .def("showm",
           (std::string (*)(Index const &)) &showm,
           "")
      .def("nameint",
           (std::string (*)(std::string const &, int)) &nameint)
      .def("add",
           (void (*)(Args&, Args::Name const &, IndexType)) &add)
      .def("getIndexType",
           (IndexType (*)(Args const &, Args::Name const &)) &getIndexType)
      .def("getIndexType",
           (IndexType (*)(Args const &, Args::Name const&, IndexType)) &getIndexType)
      ;
}
