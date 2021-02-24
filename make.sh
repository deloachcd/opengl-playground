#!/bin/bash
# This script just runs cmake to generate the makefiles,
# and then make to compile them.

# TODO: implement SOGLUP
export CC=/usr/bin/gcc-10
export CXX=/usr/bin/g++-10
cmake -G "Unix Makefiles" .
make
