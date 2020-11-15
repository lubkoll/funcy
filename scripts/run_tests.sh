#!/usr/bin/env bash

set -e

COMPILER=$1
COMPILER_VERSION=$2
BUILD_TYPE=$3
FLAGS=$4
COVERALLS_TOKEN=$5
SRC_DIR=/home/funcy/src

conan profile new default --detect
conan profile update settings.build_type=Release default
conan profile update settings.compiler=$COMPILER default
conan profile update settings.compiler.version=$COMPILER_VERSION default
conan profile update settings.compiler.libcxx=libstdc++11 default

if [ "$COMPILER" = "gcc" ]; then
    export CXX=g++-$COMPILER_VERSION
    export CC=gcc-$COMPILER_VERSION
fi

if [ "$COMPILER" = "clang" ]; then
    export CXX=clang++-$COMPILER_VERSION
    export CC=clang-$COMPILER_VERSION
fi

cd $SRC_DIR || exit 1
mkdir -p buildx
cd buildx || exit 1
conan install $SRC_DIR --build=missing
cmake $SRC_DIR -GNinja -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_TOOLCHAIN_FILE=conan_paths.cmake -DCMAKE_CXX_FLAGS=$FLAGS -DFuncy_BuildTest=ON
cmake --build .
cd test || exit 1
ctest

if [ "$FLAGS" = "-coverage" ]; then
    lcov --gcov-tool gcov-${COMPILER_VERSION} --capture --no-external --directory . --base-directory $SRC_DIR/include -rc lcov_branch_coverage=1 --output-file coverage.info
    coveralls-lcov --repo-token ${COVERALLS_TOKEN} coverage.info
fi
