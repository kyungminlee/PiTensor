#include "../pitensor.h"
#include "itensor/qn.h"
namespace py = pybind11;
using namespace itensor;

void pitensor::qn(pybind11::module& module) {
  module
      .def("Sz", &Sz)
      .def("Nb", &Nb)
      .def("Nf", &Nf)
      .def("Pf", &Pf)
      .def("Nfp", &Nfp)
      .def("QNSize", &QNSize);

  {
    py::class_<QNVal> type(module, "QNVal");
    using qn_t = QNVal::qn_t;

    type
        .def(py::init<>())
        .def(py::init([](qn_t v1) { return new QNVal(v1); }))
        .def(py::init([](qn_t v1, qn_t v2) { return new QNVal(v1, v2); }))
        .def("mod", &QNVal::mod)
        .def("val", &QNVal::val)
        .def("set", &QNVal::set)
        .def(-py::self) //TODO: Design flaw

        ;
  }

  {
    using qn_t = QN::qn_t;
    py::class_<QN> type(module, "QN");

    type
        .def(py::init<>())
        .def(py::init<Args const & >())
        .def(py::init([](qn_t v1) { return new QN(v1); }))
        .def(py::init([](qn_t v1, qn_t v2) { return new QN(v1, v2); }))
        .def(py::init([](qn_t v1, qn_t v2, qn_t v3) { return new QN(v1, v2, v3); }))
        .def(py::init([](qn_t v1, qn_t v2, qn_t v3, qn_t v4) { return new QN(v1, v2, v3, v4); }))
        .def(py::init([](QNVal v1, QNVal v2, QNVal v3, QNVal v4) {
               return new QN(v1, v2, v3, v4);
             }),
             py::arg("v0"),
             py::arg("v1") = QNVal(),
             py::arg("v2") = QNVal(),
             py::arg("v3") = QNVal())


        ;
  }


}
