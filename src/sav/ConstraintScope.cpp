/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/*
 * ConstraintScope.cpp
 *
 *  Created on: Jul 5, 2020
 *      Author: ballance
 */

#include "sav/ConstraintScope.h"

namespace vsc {

ConstraintScope::ConstraintScope() {
	// TODO Auto-generated constructor stub

}

ConstraintScope::ConstraintScope(
		std::initializer_list<ConstraintStmt *> stmts) {
	for (std::initializer_list<ConstraintStmt *>::iterator it=stmts.begin();
			it!=stmts.end(); it++) {
		m_constraints.push_back(ConstraintStmtSP(*it));
	}
}

ConstraintScope::~ConstraintScope() {
	// TODO Auto-generated destructor stub
}

} /* namespace vsc */
