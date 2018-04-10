#include "../pitensor.h"
#include "itensor/indexset.h"
namespace py = pybind11;
using namespace itensor;

template <typename CmpType, typename ItemType, typename Iterator>
bool matchAny(CmpType&& cmp, ItemType const & i, Iterator first, Iterator last)
{
  using IteratorItemType = decltype(*first);
  return std::any_of(first, last, [&cmp, &i](IteratorItemType const & j) -> bool { return cmp(i,j); });
}

template <typename IndexT>
struct InitializerIndexSetT
{
  using index_type = IndexT;
  using index_set_type = IndexSetT<index_type>;
  using size_type = typename index_set_type::size_type;
  using extent_type = typename index_set_type::extent_type;
  using range_type = typename index_set_type::range_type;
  using parent = typename index_set_type::parent;
  using storage_type = typename index_set_type::storage_type;
  using value_type = typename index_set_type::value_type;
  using iterator = typename index_set_type::iterator;
  using const_iterator = typename index_set_type::const_iterator;
  using indexval_type = typename index_set_type::indexval_type;
  using label_type = std::string; //TODO: LabelT ???

  py::module & module;
  const char * name;
  py::class_<index_set_type> type;

  InitializerIndexSetT(pybind11::module & theModule, const char * theName)
      : module(theModule), name(theName), type(module, name)
  {
      initConstructor();
      initMethod();
      initPrime();
      initFunction();
  }

  void initConstructor()
  {
    type
        .def(py::init([](py::args args) {
          bool all_index_type = true;
          for (auto const & item : args) {
            all_index_type = all_index_type && py::isinstance<index_type>(item);
          }
          if(!all_index_type) { throw std::domain_error("Arguments should all be of index_type"); }
          std::vector<index_type> cpp_args;
          cpp_args.reserve(py::len(args));
          for (auto const & item : args) {
            cpp_args.push_back(item.cast<index_type>());
          }
          return new index_set_type(cpp_args);
        }))
    ;

  }

  void initMethod()
  {
    type
        .def("__bool__", [](index_set_type const &obj) { return static_cast<bool>(obj); })
        .def("extent", &index_set_type::extent)
        .def("stride", &index_set_type::stride)
        .def_property_readonly("r", &index_set_type::r)
        .def("__getitem__",
             [](index_set_type const &obj, size_type i) { return obj[i]; })
        .def("__setitem__",
             [](index_set_type &obj, size_t i, index_type const &idx) { obj[i] = idx; })
        .def("__call__",
             [](index_set_type const &obj, size_type i) { return obj.index(i); })
        .def("range", &index_set_type::range)
        .def("dag", &index_set_type::dag)
        .def("swap", &index_set_type::swap)
        .def("front", &index_set_type::front)
        .def("back", &index_set_type::back)
        .def("__iter__", [](index_set_type &obj) {
          return py::make_iterator(obj.begin(), obj.end());
        })
        .def("__repr__", [](index_set_type const & obj) {
          std::stringstream ss; ss << std::scientific << obj; return ss.str();
        });
  }

  // TODO: check prime
  void initPrime()
  {
    // TODO: Check

    module
        .def("prime", [](index_set_type& is,
                         py::args args,
                         py::kwargs kwargs) -> void {
          int inc = kwargs.contains(py::cast("inc")) ? kwargs[py::cast("inc")].cast<int>() : 1;
          if (py::len(args)==0) {
            //std::cout << __PRETTY_FUNCTION__ << " (ALL TYPES):" << std::endl;
            return prime(is, inc); // TODO: ITensor Bug? prime with variadic (possibly empty) arguments
          }

          //std::cout << "IndexType = " << typeid(IndexType).name() << std::endl;
          //std::cout << "index_type = " << typeid(index_type).name() << std::endl;

          bool all_IndexType = true, all_IndexT = true;

          for (auto const &item : args) {
            //std::cout << "TYPE: " << item.get_type() << std::endl;
            //std::cout << py::isinstance<IndexType>(item) << std::endl;
            //std::cout << py::isinstance<index_type>(item) << std::endl;
            all_IndexType = all_IndexType && (py::isinstance<IndexType>(item));
            all_IndexT = all_IndexT && (py::isinstance<index_type>(item));
          }

          if(all_IndexType) {
            if (py::len(args) > 1) {
              throw std::domain_error("Priming multiple types not defined in ITensor");
            }
            std::vector<IndexType> types;    types.reserve(py::len(args));
            for(auto const & item : args) { types.push_back(item.cast<IndexType>()); }

            // prime if i matches any of the types
            for(auto & i : is) {
              if (matchAny([](const index_type & x, IndexType y) -> bool { return x.type() == y; },
                           i, types.begin(), types.end())) {
                //std::cout << __PRETTY_FUNCTION__<< "(IndexType) : " << i << " matches." << std::endl;
                i.prime(inc);
              }
            } // for i : is
          } // if all_IndexType
          else if (all_IndexT) {
            std::vector<index_type> types;    types.reserve(py::len(args));
            for(auto const & item : args) { types.push_back(item.cast<index_type>()); }
            for(auto & i : is) {
              if (matchAny(detail::IndexCmp<index_type>(), i, types.begin(), types.end())) {
                //std::cout << __PRETTY_FUNCTION__<< " (index_type): " << i << " matches." << std::endl;
                i.prime(inc);
              }
            }
          } // else if (all_IndexT)
          else {
            throw std::domain_error("Unsupported argument types");
          }
          // TODO: return or not return?
        })
  ;

    // TODO: Check. very error prone

  module
        .def("primeExcept", [](index_set_type& is,
                               py::object obj,
                               py::args args,
                               py::kwargs kwargs) {
          int inc = kwargs.contains(py::cast("inc")) ? kwargs[py::cast("inc")].cast<int>() : 1;

          bool all_IndexType = py::isinstance<IndexType>(obj);
          bool all_IndexT = py::isinstance<index_type>(obj);
          for (auto const &item : args) {
            all_IndexType = all_IndexType && (py::isinstance<IndexType>(item));
            all_IndexT = all_IndexT && (py::isinstance<index_type>(item));
          }

          if(all_IndexType) {
            std::vector<IndexType> types;    types.reserve(py::len(args)+1);
            types.push_back(obj.cast<IndexType>());
            for (auto const & item : args) { types.push_back(item.cast<IndexType>()); }
            // prime if i matches any of the types
            for(auto & i : is) {
              if (!matchAny([](const index_type & x, IndexType y) -> bool { return x.type() == y; },
                            i, types.begin(), types.end())) {
                i.prime(inc);
              }
            } // for i : is


          } // if all_IndexType
          else if (all_IndexT) {
            std::vector<index_type> types;    types.reserve(py::len(args)+1);
            types.push_back(obj.cast<index_type>());
            for (auto const & item : args) { types.push_back(item.cast<index_type>()); }
            for(auto & i : is) {
              if (!matchAny(detail::IndexCmp<index_type>(), i, types.begin(), types.end())) {
                i.prime(inc);
              }
            }
          } // else if (all_IndexT)
          else {
            throw std::domain_error("Unsupported argument types");
          }
        })
    ;

    module
        .def("noprime", [](index_set_type& is,
                           py::args args) -> void {

          if (len(args)==0) { return noprime(is); }

          bool all_IndexType = true, all_IndexT = true;
          for (auto const &item : args) {
            all_IndexType = all_IndexType && (py::isinstance<IndexType>(item));
            all_IndexT = all_IndexT && (py::isinstance<index_type>(item));
          }

          if(all_IndexType) {
            std::vector<IndexType> types;    types.reserve(py::len(args));
            for (auto const & item : args) { types.push_back(item.cast<IndexType>()); }
            // prime if i matches any of the types
            for(auto & i : is) {
              if (matchAny([](const index_type & x, IndexType y) -> bool { return x.type() == y; },
                            i, types.begin(), types.end())) {
                i.noprime();
              }
            } // for i : is
          } // if all_IndexType
          else if (all_IndexT) {
            std::vector<index_type> types;    types.reserve(py::len(args));
            for (auto const & item : args) { types.push_back(item.cast<index_type>()); }
            for(auto & i : is) {
              if (matchAny(detail::IndexCmp<index_type>(), i, types.begin(), types.end())) {
                i.noprime();
              }
            }
          } // else if (all_IndexT)
          else {
            throw std::domain_error("Unsupported argument types");
          }
        })

    ;


  } // initPrime

  void initFunction()
  {
      module
          .def("sim",
               (void (*)(index_set_type &, index_type const &)) &sim)
          .def("sim",
               (void (*)(index_set_type &, IndexType)) &sim)
          .def("findindex",
               (long (*)(index_set_type const &, index_type const &)) &findindex)
          .def("findtype",
               (index_type const & (*)(index_set_type const &, IndexType)) &findtype)
              // TODO: fix warning (dangling reference)
          .def("finddir",
               (index_type const & (*)(index_set_type const &, Arrow)) &finddir)
          .def("dir",
               (Arrow (*)(index_set_type const &, index_type const &)) &dir)

          .def("hasindex",
               (bool (*)(index_set_type const &, index_type const &)) &hasindex)
          .def("hastype",
               (bool (*)(index_set_type const &, IndexType)) &hastype)

          .def("minM",
               (long (*)(index_set_type const &)) &minM)
          .def("maxM",
               (long (*)(index_set_type const &)) &maxM)
          .def("contractIS",
               (void (*)(index_set_type const &, index_set_type const &, index_set_type &, bool)) &contractIS,
               "",
               py::arg("Lis"),
               py::arg("Ris"),
               py::arg("Nis"),
               py::arg("sortResult") = false)
          .def("contractIS",
               (void (*)(index_set_type const &, label_type const &,
                         index_set_type const &, label_type const &,
                         index_set_type &, label_type &, bool)) &contractIS,
               "",
               py::arg("Lis"), py::arg("Lind"),
               py::arg("Ris"), py::arg("Rind"),
               py::arg("Nis"), py::arg("Nind"),
               py::arg("sortResult") = false)
          .def("ncprod",
               (void (*)(index_set_type const &, label_type const &,
                         index_set_type const &, label_type const &,
                         index_set_type &, label_type &)) &ncprod,
               "",
               py::arg("Lis"), py::arg("Lind"),
               py::arg("Ris"), py::arg("Rind"),
               py::arg("Nis"), py::arg("Nind"))
      ;
  }
}; // struct InitializerIndexSetT


void pitensor::indexset(pybind11::module& module)
{
  { InitializerIndexSetT<Index>   _(module, "IndexSet"); }
  { InitializerIndexSetT<IQIndex> _(module, "IQIndexSet"); }

}
