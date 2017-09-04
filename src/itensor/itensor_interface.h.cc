#include "../pitensor.h"
#include "itensor/itensor_interface.h"
#include "itensor/itensor.h"
#include "itensor/iqtensor.h"

namespace py = pybind11;
using namespace itensor;

template <typename Container>
void static inline
initDiagTensor(pybind11::module& module);


template <typename IndexT>
void static inline
initRandomTensor(pybind11::module& module);


template <typename index_type>
static inline
py::class_< ITensorT<index_type> >
initITensorT(pybind11::module& module, const char* name)
{

  using itensor_type = ITensorT<index_type>;
  using indexval_type = typename itensor_type::indexval_type;
  using storage_ptr = typename itensor_type::storage_ptr;
  using const_storage_ptr = typename itensor_type::const_storage_ptr;
  using scale_type = typename itensor_type::scale_type;

  py::class_<itensor_type> type(module, name);

  pitensor::recursiveConstructor<
      py::class_<itensor_type>,
      index_type const&,
      index_type const&,
      index_type const&,
      index_type const&,
      index_type const&,
      index_type const&,
      index_type const&,
      index_type const&,
      index_type const&,
      index_type const&
          >(type);

  type
      // TODO: using list
      .def(py::init<Cplx>());

  type
      .def_property_readonly("r", &itensor_type::r)
      .def("__bool__", [](itensor_type const& obj) { return static_cast<bool>(obj);})

      .def("real",
           (Real (itensor_type::*)(indexval_type const &) const) &itensor_type::real)
      .def("real",
           (Real (itensor_type::*)(indexval_type const &,
                                   indexval_type const &) const) &itensor_type::real)
      .def("real",
           (Real (itensor_type::*)(indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &) const) &itensor_type::real)
      .def("real",
           (Real (itensor_type::*)(indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &) const) &itensor_type::real)
      .def("real",
           (Real (itensor_type::*)(indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &) const) &itensor_type::real)
      .def("real",
           (Real (itensor_type::*)(indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &) const) &itensor_type::real)
      .def("real",
           (Real (itensor_type::*)(indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &) const) &itensor_type::real)
      .def("real",
           (Real (itensor_type::*)(indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &) const) &itensor_type::real)
      .def("real",
           (Real (itensor_type::*)(indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &) const) &itensor_type::real)
      .def("real",
           (Real (itensor_type::*)(indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &) const) &itensor_type::real)

      .def("cplx",
           (Cplx (itensor_type::*)(indexval_type const &) const) &itensor_type::cplx)
      .def("cplx",
           (Cplx (itensor_type::*)(indexval_type const &,
                                   indexval_type const &) const) &itensor_type::cplx)
      .def("cplx",
           (Cplx (itensor_type::*)(indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &) const) &itensor_type::cplx)
      .def("cplx",
           (Cplx (itensor_type::*)(indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &) const) &itensor_type::cplx)
      .def("cplx",
           (Cplx (itensor_type::*)(indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &) const) &itensor_type::cplx)
      .def("cplx",
           (Cplx (itensor_type::*)(indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &) const) &itensor_type::cplx)
      .def("cplx",
           (Cplx (itensor_type::*)(indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &) const) &itensor_type::cplx)
      .def("cplx",
           (Cplx (itensor_type::*)(indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &) const) &itensor_type::cplx)
      .def("cplx",
           (Cplx (itensor_type::*)(indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &) const) &itensor_type::cplx)
      .def("cplx",
           (Cplx (itensor_type::*)(indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &) const) &itensor_type::cplx)
      .def("set",
           (void (itensor_type::*)(Cplx)) &itensor_type::set)
      .def("set",
           (void (itensor_type::*)(indexval_type const &, Cplx const &)) &itensor_type::set)
      .def("set",
           (void (itensor_type::*)(indexval_type const &,
                                   indexval_type const &, Cplx const &)) &itensor_type::set)
      .def("set",
           (void (itensor_type::*)(indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &, Cplx const &)) &itensor_type::set)
      .def("set",
           (void (itensor_type::*)(indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &, Cplx const &)) &itensor_type::set)
      .def("set",
           (void (itensor_type::*)(indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &, Cplx const &)) &itensor_type::set)
      .def("set",
           (void (itensor_type::*)(indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &, Cplx const &)) &itensor_type::set)
      .def("set",
           (void (itensor_type::*)(indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &, Cplx const &)) &itensor_type::set)
      .def("set",
           (void (itensor_type::*)(indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &, Cplx const &)) &itensor_type::set)
      .def("set",
           (void (itensor_type::*)(indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &, Cplx const &)) &itensor_type::set)
      .def("set",
           (void (itensor_type::*)(indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &,
                                   indexval_type const &, Cplx const &)) &itensor_type::set)
      .def("fill", &itensor_type::fill)
      .def("generate", [](itensor_type& self, py::function &func) {
        auto f = [&func]() -> Cplx {
          py::object ret = func();
          return ret.cast<Cplx>();
        };
        self.generate(f);
      })
      .def("apply", [](itensor_type& self, py::function &func) {
        // TODO: take Cplx? or Real?
        auto f = [&func](Cplx x) -> Cplx {
          py::object ret = func(x);
          return ret.cast<Cplx>();
        };
        self.apply(f);
      })
      .def("visit", [](itensor_type& self, py::function &func) {
        auto f = [&func](Cplx x) {
          func(x);
        };
        self.visit(f);
      })
      .def("conj", &itensor_type::conj)
      .def("dag", &itensor_type::dag)
      .def("takeReal", &itensor_type::takeReal)
      .def("takeImag", &itensor_type::takeImag)
  ;

  type
      .def(py::self *= py::self)
      .def(py::self /= py::self)
      .def(py::self += py::self)
      .def(py::self -= py::self)
      .def(py::self *= Real())
      .def(py::self /= Real())
      .def(py::self *= Cplx())
      .def(py::self /= Cplx())
      .def("__neg__", [](itensor_type & self) { return -self; }) // TODO BEHAVIOR....
  ;

  type
      .def("scale", py::overload_cast<>(&itensor_type::scale, py::const_))
      .def("scale", py::overload_cast<>(&itensor_type::scale))
      .def("store", py::overload_cast<>(&itensor_type::store, py::const_))
      .def("store", py::overload_cast<>(&itensor_type::store))
      .def("scaleTo", py::overload_cast<scale_type const &>(&itensor_type::scaleTo))
      .def("scaleTo", py::overload_cast<Real>(&itensor_type::scaleTo))
      .def("swap", &itensor_type::swap)

      .def("__repr__", [](itensor_type const & obj) { std::stringstream ss; ss << obj; return ss.str(); })
  ;


  module
    // TODO: setElt
    // TODO: prime
    // TODO: primeExcept
    // TODO: noprime
    // TODO: mapprime
    // TODO: sim
      .def("hasindex",
           (bool (*)(itensor_type const &, index_type const &))&hasindex) // TODO: why redundant type spec?
      .def("findtype",
           (index_type (*)(itensor_type const &, IndexType))&findtype)
    // TODO: findindex
      .def("commonIndex",
           (index_type (*)(itensor_type const &, itensor_type const &, IndexType))&commonIndex,
           py::arg("A"),
           py::arg("B"),
           py::arg("t")=All)
      .def("uniqueIndex",
           (index_type (*)(itensor_type const &, itensor_type const &, IndexType))&uniqueIndex,
           py::arg("A"),
           py::arg("B"),
           py::arg("t")) // TODO: default argument?

      .def("swapPrime",
           (itensor_type (*)(itensor_type, int, int, IndexType))&swapPrime,
           py::arg("T"),
           py::arg("plev1"),
           py::arg("plev2"),
           py::arg("type")=All)
    // TODO: apply
      .def("realPart",
           (itensor_type (*)(itensor_type)) &realPart)
      .def("imagPart",
           (itensor_type (*)(itensor_type)) &imagPart)
      .def("isComplex",
           (bool (*)(itensor_type const &)) &isComplex)
      .def("isReal",
           (bool (*)(itensor_type const &)) &isReal)
      .def("rank",
           (long (*)(itensor_type const &)) &rank)
      .def("order",
           (long (*)(itensor_type const &)) &order)
      .def("norm",
           (Real (*)(itensor_type const &)) &norm)
      .def("randomize",
           (void (*)(itensor_type &, Args const &)) &randomize,
           py::arg("T"),
           py::arg("args")=Args::global())
      .def("random",
           (itensor_type (*)(itensor_type, Args const &)) &random,
           py::arg("T"),
           py::arg("args")=Args::global())
      .def("conj",
           (itensor_type (*)(itensor_type)) &conj)
      .def("dag",
           (itensor_type (*)(itensor_type)) &dag)
      .def("sumels",
           (Real (*)(itensor_type const &)) &sumels)
      .def("sumelsC",
           (Cplx (*)(itensor_type const &)) &sumelsC)
    // TODO multiSiteOps
  ;


  return type;
} // initITensorT(pybind11::module& module, const char* name)


void pitensor::itensor_interface(pybind11::module& module)
{
  auto typeITensor = initITensorT<Index>(module, "ITensor");
  auto typeIQTensor = initITensorT<IQIndex>(module, "IQTensor");

  typeITensor
      .def(py::self *= IndexVal())
      .def(py::self * IndexVal())
      .def(IndexVal() * py::self)
          ;

  module
      .def("combiner",
           (ITensor (*)(Index const &)) &combiner)
      .def("combiner",
           (ITensor (*)(Index const &,
                        Index const &,
                        Index const &)) &combiner)
      .def("combiner",
           (ITensor (*)(Index const &,
                        Index const &,
                        Index const &,
                        Index const &)) &combiner)
      .def("combiner",
           (ITensor (*)(Index const &,
                        Index const &,
                        Index const &,
                        Index const &,
                        Index const &)) &combiner)
      .def("combiner",
           (ITensor (*)(Index const &,
                        Index const &,
                        Index const &,
                        Index const &,
                        Index const &,
                        Index const &)) &combiner)
      .def("combiner",
           (ITensor (*)(Index const &,
                        Index const &,
                        Index const &,
                        Index const &,
                        Index const &,
                        Index const &,
                        Index const &)) &combiner)
      .def("combiner",
           (ITensor (*)(Index const &,
                        Index const &,
                        Index const &,
                        Index const &,
                        Index const &,
                        Index const &,
                        Index const &,
                        Index const &)) &combiner)
      .def("combinedIndex",
           (Index (*)(ITensor const &)) &combinedIndex)
      .def("delta",
           (ITensor (*)(Index const &)) &delta)
      .def("delta",
           (ITensor (*)(Index const &,
                        Index const &)) &delta)
      .def("delta",
           (ITensor (*)(Index const &,
                        Index const &,
                        Index const &)) &delta)
      .def("delta",
           (ITensor (*)(Index const &,
                        Index const &,
                        Index const &,
                        Index const &)) &delta)
      .def("delta",
           (ITensor (*)(Index const &,
                        Index const &,
                        Index const &,
                        Index const &,
                        Index const &)) &delta)
      .def("delta",
           (ITensor (*)(Index const &,
                        Index const &,
                        Index const &,
                        Index const &,
                        Index const &,
                        Index const &)) &delta)
      .def("delta",
           (ITensor (*)(Index const &,
                        Index const &,
                        Index const &,
                        Index const &,
                        Index const &,
                        Index const &,
                        Index const &)) &delta)
      ;


  //initDiagTensor<>(module);
  initDiagTensor<std::vector<Real> >(module);
  initDiagTensor<std::vector<Cplx> >(module);


  // TODO operator IndexVal * IndexVal
  // TODO IndexVal * Cplx

  initRandomTensor<Index>(module);
  initRandomTensor<IQIndex>(module);

  module
      // TODO check rvalue reference
      //.def("matrixTensor",
      //     (ITensor (*)(Matrix &&, Index const &, Index const&)) &matrixTensor)
      .def("matrixTensor",
           (ITensor (*)(Matrix const&, Index const &, Index const&)) &matrixTensor)
      //.def("matrixTensor",
      //     (ITensor (*)(CMatrix &&, Index const &, Index const&)) &matrixTensor)
      .def("matrixTensor",
           (ITensor (*)(CMatrix const&, Index const &, Index const&)) &matrixTensor)
  ;


  // TODO ordered
  // TODO orderedC


  // TODO ITensor.data returning ndarray?
}

template <typename IndexT>
void static inline
initRandomTensor(pybind11::module& module)
{
  module
      .def("randomTensor",
           (ITensorT<IndexT> (*)(IndexSetT<IndexT> const &)) &randomTensor)
  ;
}


template <typename Container>
void static initDiagTensor(pybind11::module& module) {
  module
      .def("diagTensor",
           (ITensor(*)(Container const & ,
                       Index const &)) &diagTensor)
      .def("diagTensor",
           (ITensor(*)(Container const & ,
                       Index const &,
                       Index const &)) &diagTensor)
      .def("diagTensor",
           (ITensor(*)(Container const & ,
                       Index const &,
                       Index const &,
                       Index const &)) &diagTensor)
      .def("diagTensor",
           (ITensor(*)(Container const & ,
                       Index const &,
                       Index const &,
                       Index const &,
                       Index const &)) &diagTensor)
      .def("diagTensor",
           (ITensor(*)(Container const & ,
                       Index const &,
                       Index const &,
                       Index const &,
                       Index const &,
                       Index const &)) &diagTensor)
      .def("diagTensor",
           (ITensor(*)(Container const & ,
                       Index const &,
                       Index const &,
                       Index const &,
                       Index const &,
                       Index const &,
                       Index const &)) &diagTensor);
}
