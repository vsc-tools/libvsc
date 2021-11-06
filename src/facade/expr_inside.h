/*
 * expr_inside.h
 *
 *  Created on: Nov 5, 2021
 *      Author: mballance
 */

#pragma once
#include "expr.h"
#include "expr_rangelist.h"

namespace vsc {
namespace facade {

expr (inside)(
		const expr				&cond,
		const expr_rangelist	&rangelist,
		const char				*file=0,
		int32_t					lineno=-1);

expr (inside)(
		const expr							&cond,
		std::initializer_list<expr>			rangelist,
		const char							*file=0,
		int32_t								lineno=-1);

expr (inside)(
		const expr							&cond,
		std::initializer_list<expr_range>	rangelist,
		const char							*file=0,
		int32_t								lineno=-1);

/*
#define __unwrap(...) __VA_ARGS__
#define inside(cond, rng) \
	inside(cond, rng, __FILE__, __LINE__)
 */


} /* namespace facade */
} /* namespace vsc */

