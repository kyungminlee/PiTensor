## PiTensor: a Python wrapper for ITensor

[![Build Status][travis-img]][travis-url]

### Introduction

PiTensor is a Python wrapper library for [ITensor](https://github.com/ITensor/ITensor.git), a C++ library for implementing tensor network calculations.

### Installation

```
python3 setup.py build_ext
python3 setup.py install --user
```

### Requirements

#### Linux
- LAPACK and BLAS libraries (`liblapack-dev`, `libblas-dev`)
- Python 3

#### macOS
- XCode
- Python 3

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

Contributions are welcome


[travis-img]: https://travis-ci.org/kyungminlee/PiTensor.svg?branch=master
[travis-url]: https://travis-ci.org/kyungminlee/PiTensor
