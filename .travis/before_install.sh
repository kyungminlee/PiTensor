#!/bin/bash

set -e
set -v

if [ "$TRAVIS_OS_NAME" == linux ]; then
    sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y
    sudo apt-get update -q
    sudo apt-get install liblapack-dev libopenblas-dev
    sudo apt-get install g++-7
    python -m pip install --upgrade pip setuptools wheel
elif [ "$TRAVIS_OS_NAME" == osx ]; then
    brew update
    brew outdated python || brew upgrade python
    python -m pip install --upgrade pip setuptools wheel
fi