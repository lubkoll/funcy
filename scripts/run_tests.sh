#!/usr/bin/env bash

set -e

COMPILER=$1
COMPILER_VERSION=$2
BUILD_TYPE=$3
FLAGS=$4
COVERALLS_TOKEN=$5

if [ "$COMPILER" = "gcc" ]; then
    export CXX=g++-$COMPILER_VERSION
    export CC=gcc-$COMPILER_VERSION
fi

if [ "$COMPILER" = "clang" ]; then
    export CXX=clang++-$COMPILER_VERSION
    export CC=clang-$COMPILER_VERSION
fi

mkdir -p build
cd build || exit 1
conan install .. --build=missing -s build_type=Release -s compiler=$COMPILER -s compiler.version=$COMPILER_VERSION -s compiler.libcxx=libstdc++11
cmake .. -GNinja -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_TOOLCHAIN_FILE=conan_paths.cmake -DCMAKE_CXX_FLAGS=$FLAGS -DFuncy_BuildTest=ON
cmake --build .
cd test || exit 1
ctest

if [ "$FLAGS" = "-coverage" ]; then
    lcov --gcov-tool gcov-${COMPILER_VERSION} --capture --no-external --directory . --base-directory /home/funcy/include -rc lcov_branch_coverage=1 --output-file coverage.info
    coveralls-lcov --repo-token ${COVERALLS_TOKEN} coverage.info
fi
