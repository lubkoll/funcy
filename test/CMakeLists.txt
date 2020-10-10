include(CTest)
enable_testing()

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
find_package(Eigen3)
find_package(dune-common)

if(EIGEN3_FOUND)
    set(LINALG_TEST_SRCS
        linalg/cofactor.cpp
        linalg/determinant.cpp
        linalg/trace.cpp
        examples/exampleTest_Eigen.cpp
        examples/exampleTest_DynamicEigen.cpp
    )
endif()
if(dune-common_FOUND)
    set(DUNE_TEST_SRCS
        examples/exampleTest_DUNE.cpp
    )
endif()

if(Funcy_Texy)
    set(TEXY_TEST_SRCS
        cmath/texify/arccos.cpp
        cmath/texify/arcsine.cpp
        cmath/texify/cosine.cpp
        cmath/texify/exp.cpp
        cmath/texify/log.cpp
        cmath/texify/pow.cpp
        cmath/texify/sine.cpp
        cmath/texify/tan.cpp
        linalg/texify/cofactor.cpp
        linalg/texify/determinant.cpp
        linalg/texify/frobenius_norm.cpp
        linalg/texify/trace.cpp
        linalg/texify/transpose.cpp
        mathop/texify/squared.cpp
        mathop/texify/sum.cpp
    )
endif()

add_executable(tests
    cmath/arccos.cpp
    cmath/arcsine.cpp
    cmath/cnd.cpp
    cmath/cosine.cpp
    cmath/exp.cpp
    cmath/erf.cpp
    cmath/log.cpp
    cmath/pow.cpp
    cmath/sine.cpp
    cmath/tan.cpp
    funcy/at.cpp
    funcy/bulk_update.cpp
    funcy/generate.cpp
    funcy/function_interface.cpp
    funcy/variable.cpp
    mathop/chain.cpp
    mathop/dot.cpp
    mathop/max.cpp
    mathop/min.cpp
    mathop/product.cpp
    mathop/scale.cpp
    mathop/squared.cpp
    mathop/subtraction.cpp
    mathop/sum.cpp
    ${LINALG_TEST_SRCS}
    ${TEXY_TEST_SRCS}
    ${DUNE_TEST_SRCS}
)
target_link_libraries(tests Funcy::Funcy GTest::GTest GTest::Main Threads::Threads)
if(Funcy_Texy)
    target_link_libraries(tests Funcy::Texy)
endif()
if(EIGEN3_FOUND)
    target_link_libraries(tests Eigen3::Eigen)
endif()
if(dune-common_FOUND)
    add_definitions(-DFUNCY_FOUND_DUNE)
    target_include_directories(tests PRIVATE ${dune-common_INCLUDE_DIRS})
    target_link_libraries(tests ${dune-common_LIBS})
endif()
target_compile_definitions(tests PRIVATE CATCH_CONFIG_ENABLE_ALL_STRINGMAKERS)

add_test(NAME tests COMMAND tests WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
add_test(NAME tests-random COMMAND tests --order rand WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
add_test(NAME tests-lex COMMAND tests --order lex WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
