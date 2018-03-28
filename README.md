## PiTensor: a Python wrapper for ITensor

[![Build Status][travis-img]][travis-url]
[![Build Status][appveyor-img]][appveyor-url]

### Introduction

PiTensor is a Python wrapper library for [ITensor](https://github.com/ITensor/ITensor.git), a C++ library for implementing tensor network calculations.

### Installation

```
git clone https://github.com/kyungminlee/PiTensor.git
cd PiTensor
git submodule update --init --recursive
python setup.py build_ext
python setup.py install
```

### Requirements

#### Linux
- LAPACK and BLAS libraries (`liblapack-dev`, `libblas-dev`)
- CMake
- Python 3

#### macOS
- XCode
- CMake
- Python 3

#### Windows (MSYS2 + MinGW)
- MSYS2 + MinGW
- OpenBLAS (`mingw-w64-i686-openblas` or `mingw-w64-x86_64-openblas`)
- CMake (`mingw-w64-i686-cmake` or `mingw-w64-x86_64-cmake`)
- Python 3 (for Windows, not for MSYS2)

### Getting Started

```python
import pitensor
i = pitensor.Index("I", 3)
j = pitensor.Index("J", 4)
T = pitensor.ITensor(i, j)
T.fill(1.0)
U = pitensor.ITensor(i)
S = pitensor.ITensor()
V = pitensor.ITensor()
foo = pitensor.svd(T, U, S, V)
print(foo)
print(T)
print(U)
print(S)
print(V)
```

### Contributing

All contributions are welcome

[travis-img]: https://travis-ci.org/kyungminlee/PiTensor.svg?branch=master
[travis-url]: https://travis-ci.org/kyungminlee/PiTensor
[appveyor-img]: https://ci.appveyor.com/api/projects/status/vk3fn99d4kql9a2g?svg=true
[appveyor-url]: https://ci.appveyor.com/project/kyungminlee/PiTensor
