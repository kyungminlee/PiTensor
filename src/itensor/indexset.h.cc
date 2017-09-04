#include "../pitensor.h"
#include "itensor/indexset.h"
namespace py = pybind11;
using namespace itensor;



template <typename index_type>
void initIndexSetT(pybind11::module& module, const char* name)
{
  using index_set_type = IndexSetT<index_type>;
  using size_type = typename index_set_type::size_type;
  /*
  using extent_type = index_set_type::extent_type;
  using range_type = index_set_type::range_type;
  using parent = index_set_type::parent;
  using storage_type = index_set_type::storage_type;
  using value_type = index_set_type::value_type;
  using iterator = index_set_type::iterator;
  using const_iterator = index_set_type::const_iterator;
  using indexval_type = index_set_type::indexval_type;
  */
  using label_type = std::string; //TODO: LabelT ???

  py::class_<index_set_type> type(module, name);
  type
    .def(py::init<>())
    .def(py::init<index_type const &>())
    .def(py::init<index_type const &,
                  index_type const &>())
    .def(py::init<index_type const &,
                  index_type const &,
                  index_type const &>())
    .def(py::init<index_type const &,
                  index_type const &,
                  index_type const &,
                  index_type const &>())
    .def(py::init<index_type const &,
                  index_type const &,
                  index_type const &,
                  index_type const &,
                  index_type const &>())
    .def(py::init<index_type const &,
                  index_type const &,
                  index_type const &,
                  index_type const &,
                  index_type const &,
                  index_type const &>())
    .def(py::init<index_type const &,
                  index_type const &,
                  index_type const &,
                  index_type const &,
                  index_type const &,
                  index_type const &,
                  index_type const &>())
    .def(py::init<index_type const &,
                  index_type const &,
                  index_type const &,
                  index_type const &,
                  index_type const &,
                  index_type const &,
                  index_type const &,
                  index_type const &>())
    .def(py::init<index_type const &,
                  index_type const &,
                  index_type const &,
                  index_type const &,
                  index_type const &,
                  index_type const &,
                  index_type const &,
                  index_type const &,
                  index_type const &>())
  ;

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
        std::stringstream ss; ss << obj; return ss.str();
      });

  module
      // TODO: read
      // TODO: write
      // TODO: rangeBegin
      // TODO: rangeEnd
      .def("prime",
           (void (*)(index_set_type &, int)) &prime,
           py::arg("indexset"),
           py::arg("inc") = 1)
          // TODO prime variadic
      .def("primeExcept",
           (void (*)(index_set_type &,
                     index_type const &,
                     int const &)) &primeExcept)
      .def("primeExcept",
           (void (*)(index_set_type &,
                     index_type const &,
                     index_type const &,
                     int const &)) &primeExcept)
      .def("primeExcept",
           (void (*)(index_set_type &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     int const &)) &primeExcept)
      .def("primeExcept",
           (void (*)(index_set_type &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     int const &)) &primeExcept)
      .def("primeExcept",
           (void (*)(index_set_type &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     int const &)) &primeExcept)
      .def("primeExcept",
           (void (*)(index_set_type &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     int const &)) &primeExcept)
      .def("primeExcept",
           (void (*)(index_set_type &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     int const &)) &primeExcept)
      .def("primeExcept",
           (void (*)(index_set_type &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     int const &)) &primeExcept)
      .def("primeExcept",
           (void (*)(index_set_type &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     int const &)) &primeExcept)
      .def("primeExcept",
           (void (*)(index_set_type &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     int const &)) &primeExcept)

      .def("primeExcept",
           (void (*)(index_set_type &,
                     IndexType,
                     int const &)) &primeExcept)
      .def("primeExcept",
           (void (*)(index_set_type &,
                     IndexType,
                     IndexType const &,
                     int const &)) &primeExcept)
      .def("primeExcept",
           (void (*)(index_set_type &,
                     IndexType,
                     IndexType const &,
                     IndexType const &,
                     int const &)) &primeExcept)
      .def("primeExcept",
           (void (*)(index_set_type &,
                     IndexType,
                     IndexType const &,
                     IndexType const &,
                     int const &)) &primeExcept)
      .def("primeExcept",
           (void (*)(index_set_type &,
                     IndexType,
                     IndexType const &,
                     IndexType const &,
                     int const &)) &primeExcept)
      .def("primeExcept",
           (void (*)(index_set_type &,
                     IndexType,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     int const &)) &primeExcept)
      .def("primeExcept",
           (void (*)(index_set_type &,
                     IndexType,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     int const &)) &primeExcept)    
      .def("primeExcept",
           (void (*)(index_set_type &,
                     IndexType,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     int const &)) &primeExcept)
      .def("primeExcept",
           (void (*)(index_set_type &,
                     IndexType,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     int const &)) &primeExcept)
      .def("primeExcept",
           (void (*)(index_set_type &,
                     IndexType,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     int const &)) &primeExcept)
      .def("primeExcept",
           (void (*)(index_set_type &,
                     IndexType,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     int const &)) &primeExcept)
      .def("primeExcept",
           (void (*)(index_set_type &,
                     IndexType,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     int const &)) &primeExcept)
                     
      .def("noprime",
           (void (*)(index_set_type &,
                     IndexType)) &noprime,
           "",
           py::arg("indexset"),
           py::arg("type") = All)
      .def("noprime",
           (void (*)(index_set_type &,
                     IndexType,
                     IndexType)) &noprime)
      .def("noprime",
           (void (*)(index_set_type &,
                     IndexType,
                     IndexType,
                     IndexType const &)) &noprime)
      .def("noprime",
           (void (*)(index_set_type &,
                     IndexType,
                     IndexType,
                     IndexType const &,
                     IndexType const &)) &noprime)
      .def("noprime",
           (void (*)(index_set_type &,
                     IndexType,
                     IndexType,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &)) &noprime)
      .def("noprime",
           (void (*)(index_set_type &,
                     IndexType,
                     IndexType,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &)) &noprime)
      .def("noprime",
           (void (*)(index_set_type &,
                     IndexType,
                     IndexType,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &)) &noprime)
      .def("noprime",
           (void (*)(index_set_type &,
                     IndexType,
                     IndexType,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &)) &noprime)
      .def("noprime",
           (void (*)(index_set_type &,
                     IndexType,
                     IndexType,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &)) &noprime)
      .def("noprime",
           (void (*)(index_set_type &,
                     IndexType,
                     IndexType,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &,
                     IndexType const &)) &noprime)

      .def("noprime",
           (void (*)(index_set_type &,
                     index_type const &)) &noprime)
      .def("noprime",
           (void (*)(index_set_type &,
                     index_type const &,
                     index_type const &)) &noprime)
      .def("noprime",
           (void (*)(index_set_type &,
                     index_type const &,
                     index_type const &,
                     index_type const &)) &noprime)
      .def("noprime",
           (void (*)(index_set_type &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &)) &noprime)
      .def("noprime",
           (void (*)(index_set_type &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &)) &noprime)
      .def("noprime",
           (void (*)(index_set_type &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &)) &noprime)
      .def("noprime",
           (void (*)(index_set_type &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &)) &noprime)
      .def("noprime",
           (void (*)(index_set_type &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &)) &noprime)
      .def("noprime",
           (void (*)(index_set_type &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &)) &noprime)
      .def("noprime",
           (void (*)(index_set_type &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &,
                     index_type const &)) &noprime)

      .def("mapprime",
           (void (*)(index_set_type &,
                     int, int, IndexType)) &mapprime,
           "",
           py::arg("indexset"),
           py::arg("plevold"),
           py::arg("plevnew"),
           py::arg("type") = All)
          //TODO: Why order different?
      .def("mapprime",
           (void (*)(index_set_type &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &
           )) &mapprime)
      .def("mapprime",
           (void (*)(index_set_type &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &
           )) &mapprime)
      .def("mapprime",
           (void (*)(index_set_type &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &
           )) &mapprime)
      .def("mapprime",
           (void (*)(index_set_type &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &
           )) &mapprime)
      .def("mapprime",
           (void (*)(index_set_type &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &
           )) &mapprime)
      .def("mapprime",
           (void (*)(index_set_type &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &
           )) &mapprime)
      .def("mapprime",
           (void (*)(index_set_type &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &
           )) &mapprime)
      .def("mapprime",
           (void (*)(index_set_type &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &
           )) &mapprime)
      .def("mapprime",
           (void (*)(index_set_type &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &,
                     IndexType const &, int const &, int const &
           )) &mapprime)

      .def("mapprime",
           (void (*)(index_set_type &,
                     index_type const &, int const &, int const &
           )) &mapprime)
      .def("mapprime",
           (void (*)(index_set_type &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &
           )) &mapprime)
      .def("mapprime",
           (void (*)(index_set_type &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &
           )) &mapprime)
      .def("mapprime",
           (void (*)(index_set_type &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &
           )) &mapprime)
      .def("mapprime",
           (void (*)(index_set_type &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &
           )) &mapprime)
      .def("mapprime",
           (void (*)(index_set_type &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &
           )) &mapprime)
      .def("mapprime",
           (void (*)(index_set_type &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &
           )) &mapprime)
      .def("mapprime",
           (void (*)(index_set_type &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &
           )) &mapprime)
      .def("mapprime",
           (void (*)(index_set_type &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &
           )) &mapprime)
      .def("mapprime",
           (void (*)(index_set_type &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &
           )) &mapprime)
      .def("mapprime",
           (void (*)(index_set_type &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &,
                     index_type const &, int const &, int const &
           )) &mapprime)

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


void pitensor::indexset(pybind11::module& module)
{
  initIndexSetT<Index>(module, "IndexSet");
  initIndexSetT<IQIndex>(module, "IQIndexSet");

}
