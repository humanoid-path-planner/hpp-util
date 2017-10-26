hpp-util
========

[![Building Status](https://travis-ci.org/humanoid-path-planner/hpp-util.svg?branch=master)](https://travis-ci.org/humanoid-path-planner/hpp-util)
[![Pipeline status](https://gepgitlab.laas.fr/humanoid-path-planner/hpp-util/badges/master/pipeline.svg)](https://gepgitlab.laas.fr/humanoid-path-planner/hpp-util/commits/master)
[![Coverage report](https://gepgitlab.laas.fr/humanoid-path-planner/hpp-util/badges/master/coverage.svg?job=doc-coverage)](http://projects.laas.fr/gepetto/doc/humanoid-path-planner/hpp-util/master/coverage/)

This package gathers technical tools for the HPP project. Features include:
 - debugging
 - benchmarks

Setup
-----

To compile this package, it is recommended to create a separate build
directory:

    mkdir _build
    cd _build
    cmake [OPTIONS] ..
    make install

Please note that CMake produces a `CMakeCache.txt` file which should
be deleted to reconfigure a package from scratch.


### Dependencies

The package depends on several packages which have to be available on
your machine.

 - System tools:
   - CMake (>=2.6)
   - pkg-config
   - usual compilation tools (GCC/G++, make, etc.)
 - libtinyxml-dev
