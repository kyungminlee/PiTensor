#ifndef PITENSOR_LIBRARY_H
#define PITENSOR_LIBRARY_H

#include <cmath>

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/complex.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <pybind11/iostream.h>
#include <pybind11/cast.h>

//#include "itensor/all.h"
namespace pitensor {


template<typename T>
void recursiveConstructor(T & type) {
  type.def(pybind11::init<>());
}

template<typename T, typename Arg, typename ... Args>
void recursiveConstructor(T & type) {
  recursiveConstructor<T, Args...>(type);
  type.def(pybind11::init<Arg, Args...>());
}


#if 1
template <typename T,
    typename RetType,
    typename NameSpace,
    typename FuncType>
void recursiveMember(const char* funcName, T& type, RetType r, NameSpace n, FuncType && f)
{
  type.def(funcName, (RetType (NameSpace::*)()) f);
};

template <typename T,
    typename RetType,
    typename NameSpace,
    typename FuncType,
    typename ...ArgTypes,
    typename ArgType>
void recursiveMember(const char* funcName, T& type, RetType r, NameSpace n, FuncType && f, ArgTypes... args, ArgType arg)
{
  recursiveMember(funcName, type, r, n, f, args...);
  type.def(funcName, (RetType (NameSpace::*)(ArgTypes..., ArgType)) f);
}

template <typename T,
    typename RetType,
    typename NameSpace,
    typename FuncType,
    typename ArgType>
void recursiveMemberConst(const char* funcName, T& type, RetType r, NameSpace n, FuncType && f, ArgType arg)
{
  type.def(funcName, (RetType (NameSpace::*)(ArgType)) f);
}

template <typename T,
    typename RetType,
    typename NameSpace,
    typename FuncType,
    typename ...ArgTypes,
    typename ArgType>
void recursiveMemberConst(const char* funcName, T& type, RetType r, NameSpace n, FuncType && f, ArgTypes... args, ArgType arg)
{
  recursiveMemberConst(funcName, type, r, n, f, args...);
  type.def(funcName, (RetType (NameSpace::*)(ArgTypes..., ArgType)) f);
}
#endif


void arrow(pybind11::module& module);
//void config(pybind11::module& module);
//void core(pybind11::module& module);
void decomp(pybind11::module& module);
void eigensolver(pybind11::module& module);
void global(pybind11::module& module);
void index(pybind11::module& module);
void indexname(pybind11::module& module);
void indexset(pybind11::module& module);
void indextype(pybind11::module& module);
void iqindex(pybind11::module& module);
//void iqtensor(pybind11::module& module);
//void itensor(pybind11::module& module);
void itensor_interface(pybind11::module& module);

void qn(pybind11::module& module);
void real(pybind11::module& module);
void spectrum(pybind11::module& module);
void svdalgs(pybind11::module& module);
void types(pybind11::module& module);

#if 0
namespace detail {
void algs(pybind11::module& module);
void call_rewrite(pybind11::module& module);
void gcounter(pybind11::module& module);
void skip_iterator(pybind11::module& module);
}
#endif

#if 0
namespace itdata {
void applyfunc(pybind11::module& module);
void combiner(pybind11::module& module);
void dense(pybind11::module& module);
void diag(pybind11::module& module);
void dotask(pybind11::module& module);
void itdata(pybind11::module& module);
void itlazy(pybind11::module& module);
void qcombiner(pybind11::module& module);
void qdense(pybind11::module& module);
void qdiag(pybind11::module& module);
void qmixed(pybind11::module& module);
void qutil(pybind11::module& module);
void returntype(pybind11::module& module);
void scalar(pybind11::module& module);
void storage_types(pybind11::module& module);
void synchronized(pybind11::module& module);
void task_types(pybind11::module& module);
}
#endif

namespace mps {
void autompo(pybind11::module& module);
void bondgate(pybind11::module& module);
void dmrg(pybind11::module& module);
void DMRGObserver(pybind11::module& module);
void hambuilder(pybind11::module& module);
void idmrg(pybind11::module& module);
void integrators(pybind11::module& module);
void localmpo(pybind11::module& module);
void localmpo_mps(pybind11::module& module);
void localmposet(pybind11::module& module);
void localop(pybind11::module& module);
void master_autompo(pybind11::module& module);
void mpo(pybind11::module& module);
void mps(pybind11::module& module);
void observer(pybind11::module& module);
void siteset(pybind11::module& module);
void sweeps(pybind11::module& module);
void tevol(pybind11::module& module);
void TEvolObserver(pybind11::module& module);


namespace lattice {
void latticebond(pybind11::module &module);
void square(pybind11::module &module);
void triangular(pybind11::module &module);
}
namespace sites {
void hubbard(pybind11::module &module);
void spinhalf(pybind11::module &module);
void spinless(pybind11::module &module);
void spinone(pybind11::module &module);
void spintwo(pybind11::module &module);
void tj(pybind11::module &module);
void Z3(pybind11::module &module);
}
}

namespace tensor {
void algs(pybind11::module& module);
void contract(pybind11::module& module);
void lapack_wrap(pybind11::module& module);
void mat(pybind11::module& module);
void matrange(pybind11::module& module);
void permutation(pybind11::module& module);
void range(pybind11::module& module);
void rangeiter(pybind11::module& module);
void slicemat(pybind11::module& module);
void slicerange(pybind11::module& module);
void sliceten(pybind11::module& module);
void ten(pybind11::module& module);
void teniter(pybind11::module& module);
void types(pybind11::module& module);
void vec(pybind11::module& module);
void vecrange(pybind11::module& module);
}

namespace util {
void args(pybind11::module& module);
void autovector(pybind11::module& module);
//void cplx_literal(pybind11::module& module);
void cputime(pybind11::module& module);
void error(pybind11::module& module);
void flstring(pybind11::module& module);
void infarray(pybind11::module& module);
void input(pybind11::module& module);
void multalloc(pybind11::module& module);
void optional_ptr(pybind11::module& module);
//void parallel(pybind11::module& module);
void print(pybind11::module& module);
//void print_macro(pybind11::module& module);
void range(pybind11::module& module);
void readwrite(pybind11::module& module);
//void safe_ptr(pybind11::module& module);
void set_scoped(pybind11::module& module);
void static_count(pybind11::module& module);
void stats(pybind11::module& module);
//void stdx(pybind11::module& module);
//void timers(pybind11::module& module);
//void tinyformat(pybind11::module& module);
void typelist(pybind11::module& module);
void vararray(pybind11::module& module);
}



void tests(pybind11::module& module);

} //namespace pitensor





#endif