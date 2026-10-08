# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/).

## [Unreleased]

## [9.0.2] - 2026-07-24



## [9.0.0] - 2026-07-06



## [7.0.0] - 2026-03-06



## [6.1.0] - 2025-10-23



## [6.0.0] - 2024-12-07

No changes


## [5.2.0] - 2024-10-09

Changes in v5.2.0:
- nix: move package to nixpkgs
- ci: use https
- setup mergify
- remove deprecated use of boost filesystem
- remove deprecated use of C++ 11

## [5.1.0] - 2024-07-02

Changes in v5.1.0:
- Nix: initial support
- update tooling


## [5.0.0] - 2024-03-31

Changes in v5.0.0:
- switch from TinyXML to TinyXML2
- update packaging
- update tooling


## [4.15.1] - 2023-01-20



## [4.14.0] - 2022-11-02



## [4.13.0] - 2022-05-31



## [4.12.0] - 2021-10-06

Changes in v4.12.0:
- switch to C++14

## [4.11.0] - 2021-05-04

Changes in v4.11.0:
- Switch to std::shared_ptr
- update doc
- improve serialization


## [4.10.1] - 2020-09-24

Changes since v4.9.0:
* Add macros, functions and test for serialization.
* Add package.xml.
* Use cmake to handle dependencies (submodule cmake).

## [4.10.0] - 2020-07-24



## [4.9.0] - 2020-04-29

Changes in v4.9.0:
- Add explicit bool cast for C++11
- CMake Exports

## [4.8.0] - 2019-11-28

Changes since v4.5.0:
- update CMake

## [4.5.0] - 2019-04-24



## [4.4.0] - 2019-03-15

Changes since v4.3.0:
- Fix logs with streams
- fix unit-test 'debug'


## [4.3.0] - 2019-01-31

- remove HPP_POSTCONDITION

## [4.2.0] - 2018-10-11

Changes since 3.3:
- remove HPP_POSTCONDITION, fix #12
- Remove bad assert in decindent
- Use HPP versionning scheme

## [3.2] - 2018-03-14

* Remove test "debug" that make distcheck target fail.
* Fix doc
* Add hppBenchmark to output to benchmark journal even without HPP_DEBUG
* Add min and max in TimeCounter
* Build exceptions from C string (char*)
* Document the code.
* Add macro HPP_THROW(TYPE,MSG) to throw exceptions using string stream
* [CMake] Append boost libs to the pkg file
* [CMake] Sync submodule cmake
* Update README.md and travis
* Update README.md and travix.yml
* Clean License in file tests/debug.cc
* Add test debug.cc
* Create log file before the first write and not only with HPP_DEBUG
* Add ability to write string stream
* Add macro HPP_STOP_AND_DISPLAY_TIMECOUNTER
* Fix CMakeLists
* Synchronise cmake submodule
* Use boost::function instead of function pointer for FactoryType
* Split declaration and definition of operator<< (ostream,TimeCounter)
* Enhance class TimeCounter
* Cosmetic changes: add missing license
* Add a time counter
* Make destructor of Object factory virtual.
* Synchronize cmake submodule
* Adding a XML parser.


[Unreleased]: https://github.com/humanoid-path-planner/hpp-util/compare/v9.0.2...HEAD
[9.0.2]: https://github.com/humanoid-path-planner/hpp-util/compare/v9.0.0...v9.0.2
[9.0.0]: https://github.com/humanoid-path-planner/hpp-util/compare/v7.0.0...v9.0.0
[7.0.0]: https://github.com/humanoid-path-planner/hpp-util/compare/v6.1.0...v7.0.0
[6.1.0]: https://github.com/humanoid-path-planner/hpp-util/compare/v6.0.0...v6.1.0
[6.0.0]: https://github.com/humanoid-path-planner/hpp-util/compare/v5.2.0...v6.0.0
[5.2.0]: https://github.com/humanoid-path-planner/hpp-util/compare/v5.1.0...v5.2.0
[5.1.0]: https://github.com/humanoid-path-planner/hpp-util/compare/v5.0.0...v5.1.0
[5.0.0]: https://github.com/humanoid-path-planner/hpp-util/compare/v4.15.1...v5.0.0
[4.15.1]: https://github.com/humanoid-path-planner/hpp-util/compare/v4.14.0...v4.15.1
[4.14.0]: https://github.com/humanoid-path-planner/hpp-util/compare/v4.13.0...v4.14.0
[4.13.0]: https://github.com/humanoid-path-planner/hpp-util/compare/v4.12.0...v4.13.0
[4.12.0]: https://github.com/humanoid-path-planner/hpp-util/compare/v4.11.0...v4.12.0
[4.11.0]: https://github.com/humanoid-path-planner/hpp-util/compare/v4.10.1...v4.11.0
[4.10.1]: https://github.com/humanoid-path-planner/hpp-util/compare/v4.10.0...v4.10.1
[4.10.0]: https://github.com/humanoid-path-planner/hpp-util/compare/v4.9.0...v4.10.0
[4.9.0]: https://github.com/humanoid-path-planner/hpp-util/compare/v4.8.0...v4.9.0
[4.8.0]: https://github.com/humanoid-path-planner/hpp-util/compare/v4.5.0...v4.8.0
[4.5.0]: https://github.com/humanoid-path-planner/hpp-util/compare/v4.4.0...v4.5.0
[4.4.0]: https://github.com/humanoid-path-planner/hpp-util/compare/v4.3.0...v4.4.0
[4.3.0]: https://github.com/humanoid-path-planner/hpp-util/compare/v4.2.0...v4.3.0
[4.2.0]: https://github.com/humanoid-path-planner/hpp-util/compare/v3.2...v4.2.0
[3.2]: https://github.com/humanoid-path-planner/hpp-util/releases/tag/v3.2
