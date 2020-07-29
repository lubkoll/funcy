macro(add_header header)
    list(APPEND HEADER_FILES $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${header}>)
endmacro(add_header)

add_header(concepts.h)
add_header(constant.h)
add_header(finalize.h)
add_header(funcy.h)
add_header(generate.h)
add_header(identity.h)
add_header(linalg.h)
add_header(math.h)
add_header(operations.h)
add_header(variable.h)
add_header(cmath/arccos.h)
add_header(cmath/arcsine.h)
add_header(cmath/cnd.h)
add_header(cmath/cosine.h)
add_header(cmath/erf.h)
add_header(cmath/exp.h)
add_header(cmath/log.h)
add_header(cmath/pow.h)
add_header(cmath/sine.h)
add_header(cmath/tan.h)
add_header(linalg/cofactor.h)
add_header(linalg/concepts.h)
add_header(linalg/determinant.h)
add_header(linalg/dimension.h)
add_header(linalg/deviator.h)
add_header(linalg/deviatoric_invariants.h)
add_header(linalg/frobenius_norm.h)
add_header(linalg/mixed_invariants.h)
add_header(linalg/principal_invariants.h)
add_header(linalg/rows_and_cols.h)
add_header(linalg/strain_tensor.h)
add_header(linalg/tensor_product.h)
add_header(linalg/trace.h)
add_header(linalg/transpose.h)
add_header(linalg/type_traits.h)
add_header(linalg/unit_matrix.h)
add_header(mathop/chain.h)
add_header(mathop/dot.h)
add_header(mathop/max.h)
add_header(mathop/min.h)
add_header(mathop/product.h)
add_header(mathop/scale.h)
add_header(mathop/squared.h)
add_header(mathop/subtraction.h)
add_header(mathop/sum.h)
add_header(util/at.h)
add_header(util/chainer.h)
add_header(util/compute_chain.h)
add_header(util/compute_conditional.h)
add_header(util/compute_dot.h)
add_header(util/compute_product.h)
add_header(util/compute_subtraction.h)
add_header(util/compute_sum.h)
add_header(util/derivative_wrappers.h)
add_header(util/evaluate_if_present.h)
add_header(util/exceptions.h)
add_header(util/macros.h)
add_header(util/mathop_traits.h)
add_header(util/static_checks.h)
add_header(util/third.h)
add_header(util/traverse.h)
add_header(util/type_traits.h)
add_header(examples/nonlinear_heat.h)
add_header(examples/volumetric_penalty_functions.h)
add_header(examples/yield_surface.h)
add_header(examples/rubber/neo_hooke.h)
add_header(examples/rubber/mooney_rivlin.h)
add_header(examples/biomechanics/adipose_tissue_sommer_holzapfel.h)
add_header(examples/biomechanics/muscle_tissue_martins.h)
add_header(examples/biomechanics/skin_tissue_hendriks.h)
