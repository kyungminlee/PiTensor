## pitensor: a Python wrapper for ITensor

[![Build Status][travis-img]][travis-url]

### Introduction

### Installation

### Getting Started

```python
import pitensor
i = pitensor.Index("I", 3)
j = pitensor.Index("J", 4)
T = pitensor.ITensor(i,j)
T.fill(1.0)
U = pitensor.ITensor(i)
S = pitensor.ITensor()
V = pitensor.ITensor()
foo = pitensor.svd(T, U, S, V)
print(foo)
```

### Contributing

Contributions are welcome


[travis-img]: https://travis-ci.org/kyungminlee/PiTensor.svg?branch=master
[travis-url]: https://travis-ci.org/kyungminlee/PiTensor
