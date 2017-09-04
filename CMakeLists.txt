cmake_minimum_required(VERSION 3.6)
project(pitensor)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS ON)


if (WIN32)
    set(PYTHON_EXECUTABLE "C:/Users/kmlee/Miniconda3/envs/py36/python.exe")
elseif (APPLE)
    set(PYTHON_EXECUTABLE "/Users/lee.8024/.brew/miniconda3/bin/python")
endif ()

#link_directories(itensor/lib)
#include_directories(pybind11/include itensor/include ${PYTHON_INCLUDE_DIRS})

find_package(PythonInterp 3 REQUIRED)
find_package(PythonLibs 3 REQUIRED)

include_directories(${PYTHON_INCLUDE_DIRS})

set(SOURCE_FILES
        src/pitensor.cpp
        src/pitensor.h

        src/itensor/arrow.h.cc
        src/itensor/decomp.h.cc
        src/itensor/eigensolver.h.cc
        src/itensor/global.h.cc
        src/itensor/index.h.cc
        src/itensor/indexname.h.cc
        src/itensor/indexset.h.cc
        src/itensor/indextype.h.cc
        src/itensor/iqindex.h.cc
        src/itensor/itensor_interface.h.cc
        src/itensor/qn.h.cc
        src/itensor/real.h.cc
        src/itensor/spectrum.h.cc

#        src/detail/algs.h.cc
#        src/detail/call_rewrite.h.cc
#        src/detail/gcounter.h.cc
#        src/detail/skip_iterator.h.cc

#        src/itensor/itdata/applyfunc.h.cc
#        src/itensor/itdata/combiner.h.cc
#        src/itensor/itdata/dense.h.cc
#        src/itensor/itdata/diag.h.cc
#        src/itensor/itdata/dotask.h.cc
#        src/itensor/itdata/itdata.h.cc
#        src/itensor/itdata/itlazy.h.cc
#        src/itensor/itdata/qcombiner.h.cc
#        src/itensor/itdata/qdense.h.cc
#        src/itensor/itdata/qdiag.h.cc
#        src/itensor/itdata/qmixed.h.cc
#        src/itensor/itdata/qutil.h.cc
#        src/itensor/itdata/returntype.h.cc
#        src/itensor/itdata/scalar.h.cc
#        src/itensor/itdata/storage_types.h.cc
#        src/itensor/itdata/synchronized.h.cc
#        src/itensor/itdata/task_types.h.cc

        src/itensor/mps/autompo.h.cc
        src/itensor/mps/bondgate.h.cc
        src/itensor/mps/dmrg.h.cc
        src/itensor/mps/DMRGObserver.h.cc
        src/itensor/mps/hambuilder.h.cc
        src/itensor/mps/idmrg.h.cc
        src/itensor/mps/integrators.h.cc
        src/itensor/mps/lattice
        src/itensor/mps/lattice/latticebond.h.cc
        src/itensor/mps/lattice/square.h.cc
        src/itensor/mps/lattice/triangular.h.cc
        src/itensor/mps/localmpo.h.cc
        src/itensor/mps/localmpo_mps.h.cc
        src/itensor/mps/localmposet.h.cc
        src/itensor/mps/localop.h.cc
        src/itensor/mps/master_autompo.h.cc
        src/itensor/mps/mpo.h.cc
        src/itensor/mps/mps.h.cc
        src/itensor/mps/observer.h.cc
        src/itensor/mps/sites
        src/itensor/mps/sites/hubbard.h.cc
        src/itensor/mps/sites/spinhalf.h.cc
        src/itensor/mps/sites/spinless.h.cc
        src/itensor/mps/sites/spinone.h.cc
        src/itensor/mps/sites/spintwo.h.cc
        src/itensor/mps/sites/tj.h.cc
        src/itensor/mps/sites/Z3.h.cc
        src/itensor/mps/siteset.h.cc
        src/itensor/mps/sweeps.h.cc
        src/itensor/mps/tevol.h.cc
        src/itensor/mps/TEvolObserver.h.cc
        src/itensor/tensor/algs.h.cc
        src/itensor/tensor/contract.h.cc
        #src/itensor/tensor/lapack_wrap.h.cc
        src/itensor/tensor/mat.h.cc
        src/itensor/tensor/matrange.h.cc
        src/itensor/tensor/permutation.h.cc
        src/itensor/tensor/range.h.cc
        src/itensor/tensor/rangeiter.h.cc
        src/itensor/tensor/slicemat.h.cc
        src/itensor/tensor/slicerange.h.cc
        src/itensor/tensor/sliceten.h.cc
        src/itensor/tensor/ten.h.cc
        src/itensor/tensor/teniter.h.cc
        src/itensor/tensor/types.h.cc
        src/itensor/tensor/vec.h.cc
        src/itensor/tensor/vecrange.h.cc
        src/itensor/util/args.h.cc
        src/itensor/util/autovector.h.cc
        src/itensor/util/cputime.h.cc
        src/itensor/util/error.h.cc
        src/itensor/util/flstring.h.cc
        src/itensor/util/infarray.h.cc
        src/itensor/util/input.h.cc
        src/itensor/util/multalloc.h.cc
        #src/util/parallel.h.cc
        src/itensor/util/print.h.cc
        src/itensor/util/range.h.cc
        src/itensor/util/readwrite.h.cc
        src/itensor/util/set_scoped.h.cc
        src/itensor/util/static_count.h.cc
        src/itensor/util/stats.h.cc
        src/itensor/util/typelist.h.cc
        src/itensor/util/vararray.h.cc

        src/itensor/tests.cc

        )

add_subdirectory(pybind11)

pybind11_add_module(pitensor ${SOURCE_FILES})

target_include_directories(pitensor
        PUBLIC ${PYTHON_INCLUDE_DIRS})

if (APPLE)
    find_library(ACCELERATE_LIBRARY Accelerate)
    target_link_libraries(pitensor
            PRIVATE itensor ${PYTHON_LIBRARIES} ${ACCELERATE_LIBRARY})
elseif(MINGW)
    add_definitions(-DMS_WIN64)
    set(ITENSOR_ROOT "deps/win/ITensor")
    set(OPENBLAS_ROOT "deps/win/OpenBLAS-v0.2.20-Win64-int32")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_hypot=hypot") # workaround for mismatch between pyconfig.h and mingw-gcc
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O2 -Wa,-mbig-obj")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} -Wa,-mbig-obj")
    target_include_directories(pitensor
            PUBLIC
            "${ITENSOR_ROOT}/include"
            "${OPENBLAS_ROOT}/include")
    find_library(ITENSOR_LIBRARY
            NAMES itensor
            HINTS "${ITENSOR_ROOT}/lib"
            )
    find_library(ITENSOR_DEBUG_LIBRARY
            NAMES itensor-g
            HINTS "${ITENSOR_ROOT}/lib"
            )
    find_library(OPENBLAS_LIBRARY
            NAMES openblas
            HINTS "${OPENBLAS_ROOT}/lib"
            )
    target_link_libraries(pitensor
            PRIVATE
            optimized ${ITENSOR_LIBRARY}
            debug ${ITENSOR_DEBUG_LIBRARY}
            general ${OPENBLAS_LIBRARY}
            general pthread
            general gfortran
            general quadmath
            ${PYTHON_LIBRARIES} )
elseif(MSVC)
    message(FATAL_ERROR "MSVC not yet supported")
endif()
#set_target_properties(pitensor PROPERTIES PREFIX "")
#set_target_properties(pitensor PROPERTIES SUFFIX ".so")


