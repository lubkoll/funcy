macro(add_header header)
    list(APPEND HEADER_FILES $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${header}>)
endmacro(add_header)

add_header(concepts.h)
add_header(constant.h)
add_header(identity.h)
add_header(generate.h)
add_header(linalg.h)
add_header(math.h)
add_header(texy.h)
add_header(variable.h)
add_header(cmath/arccos.h)
add_header(cmath/arcsine.h)
add_header(cmath/cosine.h)
add_header(cmath/exp.h)
add_header(cmath/log.h)
add_header(cmath/pow.h)
add_header(cmath/sine.h)
add_header(cmath/tan.h)
add_header(linalg/cofactor.h)
add_header(linalg/determinant.h)
add_header(linalg/deviator.h)
add_header(linalg/deviatoric_invariants.h)
add_header(linalg/frobenius_norm.h)
add_header(linalg/mixed_invariants.h)
add_header(linalg/principal_invariants.h)
add_header(linalg/strain_tensor.h)
add_header(linalg/trace.h)
add_header(linalg/transpose.h)
add_header(util/string.h)
