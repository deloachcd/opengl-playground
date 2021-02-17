#!/bin/bash
# This script just runs cmake to generate the makefiles,
# and then make to compile them.
cmake -G "Unix Makefiles" .
make
