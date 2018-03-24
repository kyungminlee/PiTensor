cmake_minimum_required(VERSION 3.5)
project(pitensor)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS ON)

if (WIN32)
    set(PYTHON_EXECUTABLE "C:/Users/kmlee/Anaconda3/python.exe")
elseif (APPLE)
    #set(PYTHON_EXECUTABLE "/Users/lee.8024/.brew/miniconda3/bin/python")
endif ()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/pybind11/tools/")

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

target_include_directories(pitensor PUBLIC ${CMAKE_BINARY_DIR}/deps/ITensor)

if (APPLE)
    set(ITENSOR_PLATFORM macos)
    set(ITENSOR_BLAS_LAPACK_LIBFLAGS "-framework Accelerate")
    set(ITENSOR_BLAS_LAPACK_INCLUDEFLAGS "")
    find_library(ACCELERATE_LIBRARY Accelerate)
    set(ITENSOR_LIB_OPTIMIZED ${CMAKE_BINARY_DIR}/deps/ITensor/lib/libitensor.a)
    set(ITENSOR_LIB_DEBUG ${CMAKE_BINARY_DIR}/deps/ITensor/lib/libitensor-g.a)
    target_link_libraries(pitensor 
        PRIVATE 
            optimized ${ITENSOR_LIB_OPTIMIZED}
            debug ${ITENSOR_LIB_DEBUG}
            general ${ACCELERATE_LIBRARY})
elseif(UNIX)
    set(BLAS_LAPACK_ROOT "/usr")
    target_include_directories(pitensor PUBLIC "${BLAS_LAPACK_ROOT}/include")
    find_library(LAPACK_LIBRARY NAMES lapack HINTS "${BLAS_LAPACK_ROOT}/lib")
    find_library(BLAS_LIBRARY NAMES blas HINTS "${BLAS_LAPACK_ROOT}/lib")

    set(ITENSOR_PLATFORM lapack)
    set(ITENSOR_BLAS_LAPACK_LIBFLAGS "${LAPACK_LIBRARY} ${BLAS_LIBRARY} -lpthread")
    set(ITENSOR_BLAS_LAPACK_INCLUDEFLAGS "-I${BLAS_LAPACK_ROOT}/include")
    set(ITENSOR_LIB_OPTIMIZED ${CMAKE_BINARY_DIR}/deps/ITensor/lib/libitensor.a)
    set(ITENSOR_LIB_DEBUG ${CMAKE_BINARY_DIR}/deps/ITensor/lib/libitensor-g.a)
    target_link_libraries(pitensor
        PRIVATE
            optimized ${ITENSOR_LIB_OPTIMIZED}
            debug ${ITENSOR_LIB_DEBUG}
    )
    target_link_libraries(pitensor
        PRIVATE
            general ${LAPACK_LIBRARY}
            general ${BLAS_LIBRARY}
            general pthread
    )
    set(CMAKE_AR "gcc-ar")
    set(CMAKE_RANLIB "gcc-ranlib")
elseif(MINGW)
    add_definitions(-DMS_WIN64)
    set(OPENBLAS_ROOT "${CMAKE_SOURCE_DIR}/deps-bin/win/OpenBLAS-v0.2.20-Win64-int32")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_hypot=hypot") # workaround for mismatch between pyconfig.h and mingw-gcc
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O2 -Wa,-mbig-obj")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} -Wa,-mbig-obj")
    target_include_directories(pitensor
        PUBLIC
            "${OPENBLAS_ROOT}/include")
    find_library(OPENBLAS_LIBRARY
            NAMES openblas
            HINTS "${OPENBLAS_ROOT}/lib"
            )
    set(ITENSOR_PLATFORM openblas)
    set(ITENSOR_BLAS_LAPACK_LIBFLAGS "${OPENBLAS_LIBRARY}")
    set(ITENSOR_BLAS_LAPACK_INCLUDEFLAGS "-I${OPENBLAS_ROOT}/include")

    target_link_libraries(pitensor
            PRIVATE
            optimized ${CMAKE_BINARY_DIR}/deps/ITensor/lib/libitensor.a 
            debug ${CMAKE_BINARY_DIR}/deps/ITensor/lib/libitensor-g.a
            general ${OPENBLAS_LIBRARY}
            general pthread
            general gfortran
            general quadmath
            )
elseif(MSVC)
    message(FATAL_ERROR "MSVC not yet supported")
else()
    message(FATAL_ERROR "Platform not yet supported")
endif()

string(REPLACE ";" " " LTO_FLAGS "${PYBIND11_LTO_CXX_FLAGS}")

file(WRITE "${CMAKE_BINARY_DIR}/deps/options.mk" "\
CCCOM=${CMAKE_CXX_COMPILER} ${CMAKE_CXX14_EXTENSION_COMPILE_OPTION} ${LTO_FLAGS} ${CMAKE_CXX_COMPILE_OPTIONS_PIC}
AR=${CMAKE_AR}
RANLIB=${CMAKE_RANLIB}

PLATFORM=${ITENSOR_PLATFORM}
BLAS_LAPACK_LIBFLAGS=${ITENSOR_BLAS_LAPACK_LIBFLAGS}
BLAS_LAPACK_INCLUDEFLAGS=${ITENSOR_BLAS_LAPACK_INCLUDEFLAGS}
OPTIMIZATIONS=-O2 -DNDEBUG -Wall
DEBUGFLAGS=-DDEBUG -g -Wall -pedantic
ITENSOR_MAKE_DYLIB=0
PREFIX=$(THIS_DIR)
ITENSOR_LIBDIR=$(PREFIX)/lib
ITENSOR_INCLUDEDIR=$(PREFIX)

ITENSOR_LIBNAMES=itensor
ITENSOR_LIBFLAGS=$(patsubst %,-l%, $(ITENSOR_LIBNAMES))
ITENSOR_LIBFLAGS+= $(BLAS_LAPACK_LIBFLAGS)
ITENSOR_LIBGFLAGS=$(patsubst %,-l%-g, $(ITENSOR_LIBNAMES))
ITENSOR_LIBGFLAGS+= $(BLAS_LAPACK_LIBFLAGS)
ITENSOR_LIBS=$(patsubst %,$(ITENSOR_LIBDIR)/lib%.a, $(ITENSOR_LIBNAMES))
ITENSOR_GLIBS=$(patsubst %,$(ITENSOR_LIBDIR)/lib%-g.a, $(ITENSOR_LIBNAMES))
ITENSOR_INCLUDEFLAGS=-I$(ITENSOR_INCLUDEDIR) $(BLAS_LAPACK_INCLUDEFLAGS)

CCFLAGS=-I. $(ITENSOR_INCLUDEFLAGS) $(OPTIMIZATIONS) -Wno-unused-variable
CCGFLAGS=-I. $(ITENSOR_INCLUDEFLAGS) $(DEBUGFLAGS)
LIBFLAGS=-L$(ITENSOR_LIBDIR) $(ITENSOR_LIBFLAGS)
LIBGFLAGS=-L$(ITENSOR_LIBDIR) $(ITENSOR_LIBGFLAGS)
")

include(ExternalProject)
ExternalProject_Add(ITensor_external
    TMP_DIR      "${CMAKE_BINARY_DIR}/deps/ITensor-tmp"
    STAMP_DIR    "${CMAKE_BINARY_DIR}/deps/ITensor-stamp"
    DOWNLOAD_DIR "${CMAKE_BINARY_DIR}/deps"
    SOURCE_DIR   "${CMAKE_BINARY_DIR}/deps/ITensor"
    BINARY_DIR   "${CMAKE_BINARY_DIR}/deps/ITensor"
    INSTALL_DIR  "${CMAKE_BINARY_DIR}/deps/ITensor"
    GIT_REPOSITORY https://github.com/kyungminlee/ITensor.git
    GIT_TAG pitensor
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    CONFIGURE_COMMAND ${CMAKE_COMMAND} -E copy 
        "${CMAKE_BINARY_DIR}/deps/options.mk"
        "${CMAKE_BINARY_DIR}/deps/ITensor/options.mk"
    BUILD_COMMAND "make" "-j"
    INSTALL_COMMAND ""
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/deps/ITensor"
    )

add_dependencies(pitensor ITensor_external)
