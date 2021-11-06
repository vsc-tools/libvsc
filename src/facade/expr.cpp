/*
 * Copyright 2019-2021 Matthew Ballance and contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * expr.cpp
 *
 *  Created on: Aug 9, 2021
 *      Author: mballance
 */

#include "attr_scalar.h"
#include "ctor.h"
#include "expr.h"
#include "ModelExprFieldRef.h"

namespace vsc {
namespace facade {

expr::expr(const attr_scalar &attr) :
		m_core(new ModelExprFieldRef(attr.field())) {
	ctor::inst()->push_expr(m_core);
}

expr::expr(ModelExpr *core) : m_core(core) {
	ctor::inst()->push_expr(m_core);
}

expr::expr(const int_t &val) {
	m_core = val.toExpr();
	ctor::inst()->push_expr(m_core);
}

expr::expr(int32_t val) {
	DataTypeInt *dt = ctor::inst()->type_int(true, 32);
	ModelExprVal *e = new ModelExprVal(ModelVal(dt));
	e->val().u32(val);
	m_core = e;
	ctor::inst()->push_expr(m_core);
}

expr::expr(int64_t val) {
	DataTypeInt *dt = ctor::inst()->type_int(true, 64);
	ModelExprVal *e = new ModelExprVal(ModelVal(dt));
	e->val().u64(val);
	m_core = e;
	ctor::inst()->push_expr(m_core);
}

expr::~expr() {
	// TODO Auto-generated destructor stub
}

/*
expr expr::operator == (int32_t v) {
	;
}
 */

} /* namespace facade */
} /* namespace vsc */
