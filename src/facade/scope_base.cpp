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
 * scope_base.cpp
 *
 *  Created on: Aug 9, 2021
 *      Author: mballance
 */
#include <stdio.h>
#include "ctor.h"
#include "scope_base.h"

namespace vsc {
namespace facade {

scope_base::scope_base(const std::string &name) :
	m_name(name), m_scope(0), m_ti(0) {
	ctor::inst()->scope_ctor(name, 0, 0);
}

scope_base::scope_base(
		obj						*s,
		const std::type_info	&ti) :
			m_scope(s), m_ti(&ti) {
	ctor::inst()->scope_ctor("", s, &ti);
}

scope_base::scope_base(
		obj						*s,
		const std::type_info	&ti,
		const std::string		&name) :
			m_name(name), m_scope(s), m_ti(&ti) {
	ctor::inst()->scope_ctor(name, s, &ti);
}

scope_base::~scope_base() {
	ctor::inst()->scope_dtor(m_name, m_scope, m_ti);
}

} /* namespace facade */
} /* namespace vsc */
