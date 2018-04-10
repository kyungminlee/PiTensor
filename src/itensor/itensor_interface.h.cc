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

template <typename IndexT>
struct InitializerITensorT {
  using index_type = IndexT;
  using itensor_type = ITensorT<index_type>;
  using indexval_type = typename itensor_type::indexval_type;
  using storage_ptr = typename itensor_type::storage_ptr;
  using const_storage_ptr = typename itensor_type::const_storage_ptr;
  using scale_type = typename itensor_type::scale_type;

  py::module & module;
  const char * name;
  py::class_<itensor_type> type;

  InitializerITensorT(pybind11::module & theModule, const char *theName)
  : module (theModule), name(theName), type(module, name) {
    initConstructor();
    initOperator();
    initRealCplx();
  }

  void initConstructor() {
    pitensor::recursiveConstructor<
        py::class_<itensor_type>,
        index_type const &,
        index_type const &,
        index_type const &,
        index_type const &,
        index_type const &,
        index_type const &,
        index_type const &,
        index_type const &,
        index_type const &,
        index_type const &
    >(type); // includes default constructor

    type
        .def(py::init<std::vector<index_type> const &>())
            // don't need std::array or initializer list
        .def(py::init<Cplx>())
    ;
  }

  void initOperator()
  {
    type
        .def_property_readonly("r", &itensor_type::r)
        .def_property_readonly("inds", &itensor_type::inds)
        .def("__bool__", [](itensor_type const &obj) { return static_cast<bool>(obj); })
        .def("__repr__", [](itensor_type const &obj) { std::stringstream ss; ss << std::scientific << obj; return ss.str(); })
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
        .def("__neg__", [](itensor_type &self) { return -self; }) // TODO BEHAVIOR....
    ;

  }

  void initRealCplx()
  {
    type
        .def("real",
             (Real(itensor_type::*)(indexval_type const &) const) &itensor_type::real)
        .def("real",
             (Real(itensor_type::*)(indexval_type const &,
                                    indexval_type const &) const) &itensor_type::real)
        .def("real",
             (Real(itensor_type::*)(indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &) const) &itensor_type::real)
        .def("real",
             (Real(itensor_type::*)(indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &) const) &itensor_type::real)
        .def("real",
             (Real(itensor_type::*)(indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &) const) &itensor_type::real)
        .def("real",
             (Real(itensor_type::*)(indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &) const) &itensor_type::real)
        .def("real",
             (Real(itensor_type::*)(indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &) const) &itensor_type::real)
        .def("real",
             (Real(itensor_type::*)(indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &) const) &itensor_type::real)
        .def("real",
             (Real(itensor_type::*)(indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &) const) &itensor_type::real)
        .def("real",
             (Real(itensor_type::*)(indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &) const) &itensor_type::real)
    ;

    type
        .def("cplx",
             (Cplx(itensor_type::*)(indexval_type const &) const) &itensor_type::cplx)
        .def("cplx",
             (Cplx(itensor_type::*)(indexval_type const &,
                                    indexval_type const &) const) &itensor_type::cplx)
        .def("cplx",
             (Cplx(itensor_type::*)(indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &) const) &itensor_type::cplx)
        .def("cplx",
             (Cplx(itensor_type::*)(indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &) const) &itensor_type::cplx)
        .def("cplx",
             (Cplx(itensor_type::*)(indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &) const) &itensor_type::cplx)
        .def("cplx",
             (Cplx(itensor_type::*)(indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &) const) &itensor_type::cplx)
        .def("cplx",
             (Cplx(itensor_type::*)(indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &) const) &itensor_type::cplx)
        .def("cplx",
             (Cplx(itensor_type::*)(indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &) const) &itensor_type::cplx)
        .def("cplx",
             (Cplx(itensor_type::*)(indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &,
                                    indexval_type const &) const) &itensor_type::cplx)
    ;
  }

  void initMethod()
  {
    type
        .def("set",
             (void (itensor_type::*)(Cplx)) &itensor_type::set
        )
        .def("set",
             (void (itensor_type::*)(std::vector<indexval_type> const &,
                                     Cplx)) &itensor_type::set
        )
        .def("set",
             (void (itensor_type::*)(indexval_type const &,
                                     Cplx const &)) &itensor_type::set)
        .def("set",
             (void (itensor_type::*)(indexval_type const &,
                                     indexval_type const &,
                                     Cplx const &)) &itensor_type::set)
        .def("set",
             (void (itensor_type::*)(indexval_type const &,
                                     indexval_type const &,
                                     indexval_type const &,
                                     Cplx const &)) &itensor_type::set)
        .def("set",
             (void (itensor_type::*)(indexval_type const &,
                                     indexval_type const &,
                                     indexval_type const &,
                                     indexval_type const &,
                                     Cplx const &)) &itensor_type::set)
        .def("set",
             (void (itensor_type::*)(indexval_type const &,
                                     indexval_type const &,
                                     indexval_type const &,
                                     indexval_type const &,
                                     indexval_type const &,
                                     Cplx const &)) &itensor_type::set)
        .def("set",
             (void (itensor_type::*)(indexval_type const &,
                                     indexval_type const &,
                                     indexval_type const &,
                                     indexval_type const &,
                                     indexval_type const &,
                                     indexval_type const &,
                                     Cplx const &)) &itensor_type::set)
        .def("set",
             (void (itensor_type::*)(indexval_type const &,
                                     indexval_type const &,
                                     indexval_type const &,
                                     indexval_type const &,
                                     indexval_type const &,
                                     indexval_type const &,
                                     indexval_type const &,
                                     Cplx const &)) &itensor_type::set)
        .def("set",
             (void (itensor_type::*)(indexval_type const &,
                                     indexval_type const &,
                                     indexval_type const &,
                                     indexval_type const &,
                                     indexval_type const &,
                                     indexval_type const &,
                                     indexval_type const &,
                                     indexval_type const &,
                                     Cplx const &)) &itensor_type::set)
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
                                     Cplx const &)) &itensor_type::set)
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
                                     indexval_type const &,
                                     Cplx const &)) &itensor_type::set)
    ;

    // Using IndexType

    type
        .def("fill", &itensor_type::fill)
        /*
        .def("generate", [](itensor_type &self, py::function &func) {
          auto f = [&func]() -> Cplx {
            py::object ret = func();
            return ret.cast<Cplx>();
          };
          self.generate(f);
        })
        .def("apply", [](itensor_type &self, py::function &func) {
          // TODO: take Cplx? or Real?
          auto f = [&func](Cplx x) -> Cplx {
            py::object ret = func(x);
            return ret.cast<Cplx>();
          };
          self.apply(f);
        })
        .def("visit", [](itensor_type &self, py::function &func) {
          auto f = [&func](Cplx x) {
            func(x);
          };
          self.visit(f);
        })
         */
        // TODO: check interface
        .def("generate", [](itensor_type &self, std::function<Cplx()> func) {
          self.generate(func);
        })
        .def("apply", [](itensor_type &self, std::function<Cplx(Cplx)> func) {
          self.apply(func);
        })
        .def("visit", [](itensor_type &self, std::function<void(Cplx&)> func) {
          self.visit(func);
        })
        .def("conj", &itensor_type::conj)
        .def("dag", &itensor_type::dag)
        .def("takeReal", &itensor_type::takeReal)
        .def("takeImag", &itensor_type::takeImag)
    ;

    type
        .def("scale", py::overload_cast<>(&itensor_type::scale, py::const_))
        .def("scale", py::overload_cast<>(&itensor_type::scale))
        .def("store", py::overload_cast<>(&itensor_type::store, py::const_))
        .def("store", py::overload_cast<>(&itensor_type::store))
        .def("scaleTo", py::overload_cast<scale_type const &>(&itensor_type::scaleTo))
        .def("scaleTo", py::overload_cast<Real>(&itensor_type::scaleTo))
        .def("swap", &itensor_type::swap)
    ;
  }

  void initPrime() {
    auto matchAny = [](index_type const &i, py::iterable specs) {
      auto cmp_index_type = detail::IndexCmp<index_type>();
      for (auto const &spec : specs) {
        if (py::isinstance<IndexType>(spec)) {
          auto t = spec.cast<IndexType>();
          if (i.type() == t) { return true; }
        } else if (py::isinstance<index_type>(spec)) {
          auto j = spec.cast<index_type>();
          if (cmp_index_type(i, j)) { return true; }
        } else {
          throw std::domain_error("Unsupported type in crits");
        }
      }
      return false;
    };

    type
        .def("prime", [&matchAny](itensor_type &self, py::args args, py::kwargs kwargs) {
          // args can be a mixture of IndexType and Index.
          // An index of the ITensor will be primed if it
          int inc = kwargs.contains(py::cast("inc")) ? kwargs[py::cast("inc")].cast<int>() : 1;
          auto inds = self.inds();
          for (auto const &ind : inds) {
            if (matchAny(ind, args)) { self.prime(ind, inc); }
          }
          return self;
        })
        .def("noprime", [&matchAny](itensor_type &self, py::args args) -> itensor_type & {
          auto inds = self.inds();
          for (auto const &ind : inds) {
            if (matchAny(ind, args)) { self.noprime(ind); }
          }
          return self;
        })
        .def("primeExcept", [&matchAny](itensor_type &self, py::args args, py::kwargs kwargs) -> itensor_type & {
          int inc = kwargs.contains(py::cast("inc")) ? kwargs[py::cast("inc")].cast<int>() : 1;
          auto inds = self.inds();
          for (auto const &ind : inds) {
            if (!matchAny(ind, args)) { self.prime(ind, inc); }
          }
          return self;
        })
        .def("mapprime",
             (itensor_type &(itensor_type::*)(int,
                                              int,
                                              IndexType)) &itensor_type::mapprime,
             py::arg("plevold"),
             py::arg("plevnew"),
             py::arg("type") = All
        );

#if 0
    type
        // noprime
        .def("noprime",
             (itensor_type& (itensor_type::*)()) &itensor_type::noprime
        )
        .def("noprime",
             (itensor_type& (itensor_type::*)(IndexType const&)) &itensor_type::noprime
        )
        .def("noprime",
             (itensor_type& (itensor_type::*)(IndexType const&,
                                              IndexType const&)) &itensor_type::noprime
        )
        .def("noprime",
             (itensor_type& (itensor_type::*)(IndexType const&,
                                              IndexType const&,
                                              IndexType const&)) &itensor_type::noprime
        )
        .def("noprime",
             (itensor_type& (itensor_type::*)(IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&)) &itensor_type::noprime
        )
        .def("noprime",
             (itensor_type& (itensor_type::*)(IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&)) &itensor_type::noprime
        )
        .def("noprime",
             (itensor_type& (itensor_type::*)(IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&)) &itensor_type::noprime
        )
        .def("noprime",
             (itensor_type& (itensor_type::*)(IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&)) &itensor_type::noprime
        )
        .def("noprime",
             (itensor_type& (itensor_type::*)(IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&)) &itensor_type::noprime
        )
        .def("noprime",
             (itensor_type& (itensor_type::*)(IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&)) &itensor_type::noprime
        )
        .def("noprime",
             (itensor_type& (itensor_type::*)(IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&)) &itensor_type::noprime
        )
        // prime
        .def("prime",
             (itensor_type& (itensor_type::*)(int)) &itensor_type::prime,
             py::arg("inc")=1
        )
        .def("prime",
             (itensor_type& (itensor_type::*)(IndexType const&,
                                              int)) &itensor_type::prime,
             py::arg("type"),
             py::arg("inc")=1
        )
        .def("prime",
             (itensor_type& (itensor_type::*)(IndexType const&,
                                              IndexType const&,
                                              int)) &itensor_type::prime,
             py::arg("type1"),
             py::arg("type2"),
             py::arg("inc")=1
        )
        .def("prime",
             (itensor_type& (itensor_type::*)(IndexType const&,
                                              IndexType const&,
                                              IndexType const&
                                              int)) &itensor_type::prime,
             py::arg("type1"),
             py::arg("type2"),
             py::arg("type3"),
             py::arg("inc")=1
        )
        .def("prime",
             (itensor_type& (itensor_type::*)(IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&
                                              int)) &itensor_type::prime,
             py::arg("type1"),
             py::arg("type2"),
             py::arg("type3"),
             py::arg("type4"),
             py::arg("inc")=1
        )
        .def("prime",
             (itensor_type& (itensor_type::*)(IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&
                                              int)) &itensor_type::prime,
             py::arg("type1"),
             py::arg("type2"),
             py::arg("type3"),
             py::arg("type4"),
             py::arg("type5"),
             py::arg("inc")=1
        )
        .def("prime",
             (itensor_type& (itensor_type::*)(IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&
                                              int)) &itensor_type::prime,
             py::arg("type1"),
             py::arg("type2"),
             py::arg("type3"),
             py::arg("type4"),
             py::arg("type5"),
             py::arg("type6"),
             py::arg("inc")=1
        )
        .def("prime",
             (itensor_type& (itensor_type::*)(IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&
                                              int)) &itensor_type::prime,
             py::arg("type1"),
             py::arg("type2"),
             py::arg("type3"),
             py::arg("type4"),
             py::arg("type5"),
             py::arg("type6"),
             py::arg("type7"),
             py::arg("inc")=1
        )
        .def("prime",
             (itensor_type& (itensor_type::*)(IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&
                                              int)) &itensor_type::prime,
             py::arg("type1"),
             py::arg("type2"),
             py::arg("type3"),
             py::arg("type4"),
             py::arg("type5"),
             py::arg("type6"),
             py::arg("type7"),
             py::arg("type8"),
             py::arg("inc")=1
        )
        .def("prime",
             (itensor_type& (itensor_type::*)(IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&
                                              int)) &itensor_type::prime,
             py::arg("type1"),
             py::arg("type2"),
             py::arg("type3"),
             py::arg("type4"),
             py::arg("type5"),
             py::arg("type6"),
             py::arg("type7"),
             py::arg("type8"),
             py::arg("type9"),
             py::arg("inc")=1
        )
        .def("prime",
             (itensor_type& (itensor_type::*)(IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&,
                                              IndexType const&
                                              int)) &itensor_type::prime,
             py::arg("type1"),
             py::arg("type2"),
             py::arg("type3"),
             py::arg("type4"),
             py::arg("type5"),
             py::arg("type6"),
             py::arg("type7"),
             py::arg("type8"),
             py::arg("type9"),
             py::arg("type10"),
             py::arg("inc")=1
        )
    ;
#endif

    //TODO Use args, and kwargs for inc
#if 0
    type
      .def("prime", [](itensor_type & self, py::args args, py::kwargs kwargs) {
        int inc = 1;
        if(kwargs.contains("inc"_a)) {
          inc = kwargs["inc"_a].cast<int>();
          // TODO: check domain of inc
        } // TODO: check this works

        if (py::len(args) == 0) {
          // prime all indices
          return self.prime(inc);
        } else {
          bool all_IndexType = true;
          bool all_IndexT = true;
          for (auto const &item : args) {
            all_IndexType = all_IndexType && (py::isinstance<IndexType>(item));
            all_IndexT = all_IndexT && (py::isinstance<index_type>(item));
          }

          if(all_IndexType) {
            //TODO MAtch

          } else if (all_IndexT) {
            //TODO MAtch
          }
        }
        //detail::computeMatchInc()
      })
    ;
#endif

#if 0
    type
        .def("noprime",
             (itensor_type& (itensor_type::*)(index_type const&)) &itensor_type::noprime
        )
        .def("noprime",
             (itensor_type& (itensor_type::*)(index_type const&,
                                              index_type const&)) &itensor_type::noprime
        )
        .def("noprime",
             (itensor_type& (itensor_type::*)(index_type const&,
                                              index_type const&,
                                              index_type const&)) &itensor_type::noprime
        )
        .def("noprime",
             (itensor_type& (itensor_type::*)(index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&)) &itensor_type::noprime
        )
        .def("noprime",
             (itensor_type& (itensor_type::*)(index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&)) &itensor_type::noprime
        )
        .def("noprime",
             (itensor_type& (itensor_type::*)(index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&)) &itensor_type::noprime
        )
        .def("noprime",
             (itensor_type& (itensor_type::*)(index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&)) &itensor_type::noprime
        )
        .def("noprime",
             (itensor_type& (itensor_type::*)(index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&)) &itensor_type::noprime
        )
        .def("noprime",
             (itensor_type& (itensor_type::*)(index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&)) &itensor_type::noprime
        )
        .def("noprime",
             (itensor_type& (itensor_type::*)(index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&)) &itensor_type::noprime
        )
        // prime
        .def("prime",
             (itensor_type& (itensor_type::*)()) &itensor_type::prime
        )
        .def("prime",
             (itensor_type& (itensor_type::*)(index_type const&)) &itensor_type::prime
        )
        .def("prime",
             (itensor_type& (itensor_type::*)(index_type const&,
                                              index_type const&)) &itensor_type::prime
        )
        .def("prime",
             (itensor_type& (itensor_type::*)(index_type const&,
                                              index_type const&,
                                              index_type const&)) &itensor_type::prime
        )
        .def("prime",
             (itensor_type& (itensor_type::*)(index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&)) &itensor_type::prime
        )
        .def("prime",
             (itensor_type& (itensor_type::*)(index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&)) &itensor_type::prime
        )
        .def("prime",
             (itensor_type& (itensor_type::*)(index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&)) &itensor_type::prime
        )
        .def("prime",
             (itensor_type& (itensor_type::*)(index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&)) &itensor_type::prime
        )
        .def("prime",
             (itensor_type& (itensor_type::*)(index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&)) &itensor_type::prime
        )
        .def("prime",
             (itensor_type& (itensor_type::*)(index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&)) &itensor_type::prime
        )
        .def("prime",
             (itensor_type& (itensor_type::*)(index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&)) &itensor_type::prime
        )
            // primeExcept
        .def("prime",
             (itensor_type& (itensor_type::*)()) &itensor_type::prime
        )
        .def("prime",
             (itensor_type& (itensor_type::*)(index_type const&)) &itensor_type::prime
        )
        .def("prime",
             (itensor_type& (itensor_type::*)(index_type const&,
                                              index_type const&)) &itensor_type::prime
        )
        .def("prime",
             (itensor_type& (itensor_type::*)(index_type const&,
                                              index_type const&,
                                              index_type const&)) &itensor_type::prime
        )
        .def("prime",
             (itensor_type& (itensor_type::*)(index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&)) &itensor_type::prime
        )
        .def("prime",
             (itensor_type& (itensor_type::*)(index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&)) &itensor_type::prime
        )
        .def("prime",
             (itensor_type& (itensor_type::*)(index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&)) &itensor_type::prime
        )
        .def("prime",
             (itensor_type& (itensor_type::*)(index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&)) &itensor_type::prime
        )
        .def("prime",
             (itensor_type& (itensor_type::*)(index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&)) &itensor_type::prime
        )
        .def("prime",
             (itensor_type& (itensor_type::*)(index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&)) &itensor_type::prime
        )
        .def("prime",
             (itensor_type& (itensor_type::*)(index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&,
                                              index_type const&)) &itensor_type::prime
        )
    ;
#endif

  }




  void initFunction()
  {
    module
        // TODO: setElt
        // TODO: Check prime
        .def("prime",
             [](itensor_type self, py::args args, py::kwargs kwargs) -> itensor_type {
               int inc = kwargs.contains(py::cast("inc")) ? kwargs[py::cast("inc")].cast<int>() : 1;
               for (auto const &item : args) {
                 if (py::isinstance<IndexType>(item)) {
                   self.prime(item.cast<IndexType>(), inc);
                   // TODO: Can IndexType overlap? multiple prime? probably not...
                   // https://github.com/ITensor/ITensor/blob/e459a293b69a51c47844e57aa4b86cb75b8870ee/itensor/iqindex.h#L150
                 } else if (py::isinstance<index_type>(item)) {
                   self.prime(item.cast<index_type>(), inc);
                 }
               }
               return self;
             })
            // TODO: primeExcept
        .def("noprime", [](itensor_type self, py::args args, py::kwargs kwargs) -> itensor_type {
          for (auto const &item : args) {
            if (py::isinstance<IndexType>(item)) {
              self.noprime(item.cast<IndexType>());
            } else if (py::isinstance<index_type>(item)) {
              self.noprime(item.cast<index_type>());
            }
          }
          return self;
        })
        .def("mapprime",
             (itensor_type (*)(itensor_type, int const &, int const &, IndexType const &)) &mapprime,
             py::arg("A"),
             py::arg("plevold"),
             py::arg("plevnew"),
             py::arg("type") = All
        )
            // TODO: mapprime with variadic blah
            // TODO: sim
        .def("hasindex",
             (bool (*)(itensor_type const &, index_type const &)) &hasindex) // TODO: why redundant type spec?
        .def("findtype",
             (index_type (*)(itensor_type const &, IndexType)) &findtype)
            // TODO: findindex
        .def("findindex", [](itensor_type const &T, std::function<bool(index_type)> const &cond) {
          return findindex(T, cond);
        })
        .def("commonIndex",
             (index_type (*)(itensor_type const &, itensor_type const &, IndexType)) &commonIndex,
             py::arg("A"),
             py::arg("B"),
             py::arg("t") = All)
        .def("uniqueIndex",
             (index_type (*)(itensor_type const &, itensor_type const &, IndexType)) &uniqueIndex,
             py::arg("A"),
             py::arg("B"),
             py::arg("t")) // TODO: default argument?
        .def("swapPrime",
             (itensor_type (*)(itensor_type, int, int, IndexType)) &swapPrime,
             py::arg("T"),
             py::arg("plev1"),
             py::arg("plev2"),
             py::arg("type") = All)
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
             (Real(*)(itensor_type const &)) &norm)
    .def("randomize",
         (void (*)(itensor_type &, Args const &)) &randomize,
         py::arg("T"),
         py::arg("args") = Args::global())
        .def("random",
             (itensor_type (*)(itensor_type, Args const &)) &random,
             py::arg("T"),
             py::arg("args") = Args::global())
        .def("conj",
             (itensor_type (*)(itensor_type)) &conj)
        .def("dag",
             (itensor_type (*)(itensor_type)) &dag)
        .def("sumels",
             (Real(*)(itensor_type const &)) &sumels)
    .def("sumelsC",
         (Cplx(*)(itensor_type const &)) &sumelsC)
    // TODO multiSiteOps
    ;

    return type;
  } // initITensorT(pybind11::module& module, const char* name)

};



void pitensor::itensor_interface(pybind11::module& module)
{
  auto initITensor = InitializerITensorT<Index>(module, "ITensor");
  auto initIQTensor = InitializerITensorT<IQIndex>(module, "IQTensor");

  auto typeITensor = initITensor.type;
  auto typeIQTensor = initIQTensor.type;

  //auto typeITensor = InitializerinitITensorT<Index>(module, "ITensor");
  //auto typeIQTensor = initITensorT<IQIndex>(module, "IQTensor");

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

  typeIQTensor
    //TODO specialization for IQTensor
  //  .def('__imul__', )
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
