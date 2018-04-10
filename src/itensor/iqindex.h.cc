#include "../pitensor.h"
#include "itensor/iqindex.h"
#include "itensor/itensor.h"
namespace py = pybind11;
using namespace itensor;

void static inline
initIQIndex(pybind11::module& module)
{
  py::class_<IQIndex, Index> type(module, "IQIndex");

  type.def(py::init<>(), "Constructor");
  type.def(py::init <
      std::string const &,
      Index const &, QN const &,
  const Arrow &> (),
      "Constructor",
      py::arg("name"),
      py::arg("i1"), py::arg("q1"),
      py::arg("dir") = Out);
  type.def(py::init <
      std::string const &,
      Index const &, QN const &,
      Index const &, QN const &,
  const Arrow &> (),
      "Constructor",
      py::arg("name"),
      py::arg("i1"), py::arg("q1"),
      py::arg("i2"), py::arg("q2"),
      py::arg("dir") = Out);
  type.def(py::init <
      std::string const &,
      Index const &, QN const &,
      Index const &, QN const &,
      Index const &, QN const &,
  const Arrow &> (),
      "Constructor",
      py::arg("name"),
      py::arg("i1"), py::arg("q1"),
      py::arg("i2"), py::arg("q2"),
      py::arg("i3"), py::arg("q3"),
      py::arg("dir") = Out);
  type.def(py::init <
      std::string const &,
      Index const &, QN const &,
      Index const &, QN const &,
      Index const &, QN const &,
      Index const &, QN const &,
  const Arrow &> (),
      "Constructor",
      py::arg("name"),
      py::arg("i1"), py::arg("q1"),
      py::arg("i2"), py::arg("q2"),
      py::arg("i3"), py::arg("q3"),
      py::arg("i4"), py::arg("q4"),
      py::arg("dir") = Out);
  type.def(py::init <
      std::string const &,
      Index const &, QN const &,
      Index const &, QN const &,
      Index const &, QN const &,
      Index const &, QN const &,
      Index const &, QN const &,
  const Arrow &> (),
      "Constructor",
      py::arg("name"),
      py::arg("i1"), py::arg("q1"),
      py::arg("i2"), py::arg("q2"),
      py::arg("i3"), py::arg("q3"),
      py::arg("i4"), py::arg("q4"),
      py::arg("i5"), py::arg("q5"),
      py::arg("dir") = Out);
  type.def(py::init <
      std::string const &,
      Index const &, QN const &,
      Index const &, QN const &,
      Index const &, QN const &,
      Index const &, QN const &,
      Index const &, QN const &,
      Index const &, QN const &,
  const Arrow &> (),
      "Constructor",
      py::arg("name"),
      py::arg("i1"), py::arg("q1"),
      py::arg("i2"), py::arg("q2"),
      py::arg("i3"), py::arg("q3"),
      py::arg("i4"), py::arg("q4"),
      py::arg("i5"), py::arg("q5"),
      py::arg("i6"), py::arg("q6"),
      py::arg("dir") = Out);
  type.def(py::init <
      std::string const &,
      Index const &, QN const &,
      Index const &, QN const &,
      Index const &, QN const &,
      Index const &, QN const &,
      Index const &, QN const &,
      Index const &, QN const &,
      Index const &, QN const &,
  const Arrow &> (),
      "Constructor",
      py::arg("name"),
      py::arg("i1"), py::arg("q1"),
      py::arg("i2"), py::arg("q2"),
      py::arg("i3"), py::arg("q3"),
      py::arg("i4"), py::arg("q4"),
      py::arg("i5"), py::arg("q5"),
      py::arg("i6"), py::arg("q6"),
      py::arg("i7"), py::arg("q7"),
      py::arg("dir")=Out)
  ;


  type
      .def("nblock", &IQIndex::nblock)
      .def("nindex", &IQIndex::nindex)
      .def("index", &IQIndex::index)
      .def("__getitem__", [](IQIndex const &self, long i) -> Index { return self[i]; })
      .def("qn", &IQIndex::qn)
      .def("dir", &IQIndex::dir)
      .def("__call__", [](IQIndex const &self, long n) -> IQIndexVal { return self(n); })
      .def("dag", &IQIndex::dag)
      .def("__iter__", [](IQIndex &self) { return py::make_iterator(self.begin(), self.end()); });

}


void static
initIQIndexVal(pybind11::module& module)
{
  py::class_<IQIndexVal> type(module, "IQIndexVal");

  type
      .def_readwrite("index", &IQIndexVal::index)
      .def_readwrite("val", &IQIndexVal::val)
  ;

  type
      .def(py::init<>())
      .def(py::init<IQIndex const&, long>())
  ;

  type
      .def("qn", &IQIndexVal::qn)
      // TODO: IndexVal
      // TODO: bool
      .def("indexqn", &IQIndexVal::indexqn)
      .def("blockIndexVal", &IQIndexVal::blockIndexVal)
      .def("dag", &IQIndexVal::dag)
      .def("prime",
           (IQIndexVal& (IQIndexVal::*)(int)) &IQIndexVal::prime,
           "Prime",
           py::arg("inc")=1)
      .def("prime",
           (IQIndexVal& (IQIndexVal::*)(IndexType, int)) &IQIndexVal::prime,
           py::arg("type"),
           py::arg("inc")=1)
      .def("noprime",
           &IQIndexVal::noprime,
           py::arg("type")=All)
      .def("mapprime",
           &IQIndexVal::mapprime,
           py::arg("plevold"),
           py::arg("plevnew"),
           py::arg("type")=All)
  ;

  type
      .def("__mul__",
           [](IQIndexVal const &iqiv, IndexVal const & iv) {
             return iqiv * iv;
           })
      .def(py::self == py::self)
      .def(py::self != py::self)
      .def(py::self == IQIndex())
      .def(py::self != IQIndex())
      //.def(IQIndex() == py::self)
      //.def(IQIndex() != py::self)
      .def("__repr__", [](IQIndex const & obj) -> std::string { std::stringstream ss; ss << std::scientific << obj; return ss.str(); })
  ;



  module
      .def("dag",
           (IQIndex (*)(IQIndex)) &dag)
      .def("dag",
           (IndexQN (*)(IndexQN)) &dag)
      .def("dag",
           (IQIndexVal (*)(IQIndexVal)) &dag)
      .def("hasindex", (bool (*)(IQIndex const &, Index const &)) &hasindex)
      .def("findindex", (long (*)(IQIndex const &, Index const &)) &findindex)
      .def("offset", (long (*)(IQIndex const &, Index const&)) &offset)
      .def("qn", (QN (*)(IQIndex const &, Index const &)) &qn)
      .def("findByQN", (Index (*)(IQIndex const &, QN const &))&findByQN)
      .def("sim",
           (IQIndex (*)(IQIndex const &, int)) &sim,
           py::arg("I"),
           py::arg("plev")=0)
      .def("showm",
           (std::string (*)(IQIndex const &)) &showm)


      .def("prime",
           (IQIndexVal (*)(IQIndexVal, int const &)) &prime,
           "Prime",
           py::arg("I"),
           py::arg("inc")=1)
      .def("prime",
           (IQIndexVal (*)(IQIndexVal, IndexType const &, int const &)) &prime,
           py::arg("I"),
           py::arg("type"),
           py::arg("inc")=1)
      .def("noprime",
           (IQIndexVal (*)(IQIndexVal, IndexType const &)) &noprime,
           py::arg("I"),
           py::arg("type")=All)
      .def("mapprime",
           (IQIndexVal (*)(IQIndexVal, int, int, IndexType)) &mapprime,
           py::arg("I"),
           py::arg("plevold"),
           py::arg("plevnew"),
           py::arg("type")=All)
  ;

}

void static inline
initIndexQN(pybind11::module& module)
{
  py::class_<IndexQN> type(module, "IndexQN");
  type.def(py::init<>())
      .def(py::init<Index const&, QN const&>())
  ;
  type
      // TODO explicit casting
      .def("dag", &IndexQN::dag)
      .def("m", &IndexQN::m)
      .def("type", &IndexQN::type)
      ;
}

void pitensor::iqindex(pybind11::module& module)
{

  initIQIndex(module);

  initIndexQN(module);
  initIQIndexVal(module);
}
