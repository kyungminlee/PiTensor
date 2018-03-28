## PiTensor: a Python wrapper for ITensor

[![Build Status][travis-img]][travis-url]

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
- Python 3 (Currently works with Python 3.6 in 64 bit systems)

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
