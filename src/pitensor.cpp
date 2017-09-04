#include <iostream>

#include "itensor/all.h"
#include "pitensor.h"

PYBIND11_MODULE(pitensor, module) {
  namespace py = pybind11;
  using namespace itensor;

  py::add_ostream_redirect(module);

  module.doc() = "Python  wrapper for ITensor";
  //module.attr("ostream_redirect") = py::cast( py::scoped_ostream_redirect(std::cout, py::module::import("sys").attr("stdout")) );
  //module.attr("estream_redirect") = py::cast( py::scoped_ostream_redirect(std::cerr, py::module::import("sys").attr("stderr")) );

  pitensor::util::args(module);
  pitensor::util::autovector(module);
  //pitensor::util::cplx_literal(module);
  pitensor::util::cputime(module);
  pitensor::util::error(module);
  pitensor::util::flstring(module);
  pitensor::util::infarray(module);
  pitensor::util::input(module);
  pitensor::util::multalloc(module);
  //pitensor::util::optional_ptr(module);
  //pitensor::util::parallel(module);
  pitensor::util::print(module);
  //pitensor::util::print_macro(module);
  pitensor::util::range(module);
  pitensor::util::readwrite(module);
  //pitensor::util::safe_ptr(module);
  pitensor::util::set_scoped(module);
  pitensor::util::static_count(module);
  pitensor::util::stats(module);
  //pitensor::util::stdx(module);
  //pitensor::util::timers(module);
  //pitensor::util::tinyformat(module);
  pitensor::util::typelist(module);
  pitensor::util::vararray(module);

  pitensor::global(module);

  pitensor::arrow(module);
  pitensor::eigensolver(module);
  pitensor::indextype(module);
  pitensor::index(module);
  pitensor::indexname(module);
  pitensor::indexset(module);
  pitensor::iqindex(module);
  //pitensor::iqtensor(module);

  //pitensor::itensor(module);
  pitensor::itensor_interface(module);



  pitensor::decomp(module);



  pitensor::qn(module);
  pitensor::real(module);
  pitensor::spectrum(module);
  //pitensor::svdalgs(module);
  //pitensor::types(module);

#if 0
  pitensor::detail::algs(module);
  pitensor::detail::call_rewrite(module);
  pitensor::detail::gcounter(module);
  pitensor::detail::skip_iterator(module);
#endif

#if 0
  pitensor::itdata::applyfunc(module);
  pitensor::itdata::combiner(module);
  pitensor::itdata::dense(module);
  pitensor::itdata::diag(module);
  pitensor::itdata::dotask(module);
  pitensor::itdata::itdata(module);
  pitensor::itdata::itlazy(module);
  pitensor::itdata::qcombiner(module);
  pitensor::itdata::qdense(module);
  pitensor::itdata::qdiag(module);
  pitensor::itdata::qmixed(module);
  pitensor::itdata::qutil(module);
  pitensor::itdata::returntype(module);
  pitensor::itdata::scalar(module);
  pitensor::itdata::storage_types(module);
  pitensor::itdata::synchronized(module);
  pitensor::itdata::task_types(module);
#endif

  pitensor::mps::autompo(module);
  pitensor::mps::bondgate(module);
  pitensor::mps::dmrg(module);
  pitensor::mps::DMRGObserver(module);
  pitensor::mps::hambuilder(module);
  pitensor::mps::idmrg(module);
  pitensor::mps::integrators(module);
  pitensor::mps::localmpo(module);
  pitensor::mps::localmpo_mps(module);
  pitensor::mps::localmposet(module);
  pitensor::mps::localop(module);
  pitensor::mps::master_autompo(module);
  pitensor::mps::mpo(module);
  pitensor::mps::mps(module);
  pitensor::mps::observer(module);
  pitensor::mps::siteset(module);
  pitensor::mps::sweeps(module);
  pitensor::mps::tevol(module);
  pitensor::mps::TEvolObserver(module);

  pitensor::mps::lattice::latticebond(module);
  pitensor::mps::lattice::square(module);
  pitensor::mps::lattice::triangular(module);

  pitensor::mps::sites::hubbard(module);
  pitensor::mps::sites::spinhalf(module);
  pitensor::mps::sites::spinless(module);
  pitensor::mps::sites::spinone(module);
  pitensor::mps::sites::spintwo(module);
  pitensor::mps::sites::tj(module);
  pitensor::mps::sites::Z3(module);

  pitensor::tensor::algs(module);
  pitensor::tensor::contract(module);
  //pitensor::tensor::lapack_wrap(module);
  pitensor::tensor::mat(module);
  pitensor::tensor::matrange(module);
  pitensor::tensor::permutation(module);
  pitensor::tensor::range(module);
  pitensor::tensor::rangeiter(module);
  pitensor::tensor::slicemat(module);
  pitensor::tensor::slicerange(module);
  pitensor::tensor::sliceten(module);
  pitensor::tensor::ten(module);
  pitensor::tensor::teniter(module);
  pitensor::tensor::types(module);
  pitensor::tensor::vec(module);
  pitensor::tensor::vecrange(module);

  pitensor::tests(module);

}

//PYBIND11_MODULE(pitensor, m) {
//  namespace py = pybind11;
//}