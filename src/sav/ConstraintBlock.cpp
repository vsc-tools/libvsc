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
 * ConstraintBlock.cpp
 *
 *  Created on: Jul 5, 2020
 *      Author: ballance
 */

#include "sav/ConstraintBlock.h"

namespace vsc {

ConstraintBlock::ConstraintBlock(const std::string	&name) :
		m_name(name), m_enabled(true) {

}

ConstraintBlock::ConstraintBlock(
		std::initializer_list<ConstraintStmt *>		stmts) :
				ConstraintScope(stmts), m_name(""), m_enabled(true) {
}

ConstraintBlock::ConstraintBlock(
		const std::string							&name,
		std::initializer_list<ConstraintStmt *>		stmts) :
				ConstraintScope(stmts), m_name(name), m_enabled(true) {
}

ConstraintBlock::~ConstraintBlock() {
	// TODO Auto-generated destructor stub
}

ConstraintBlockSP ConstraintBlock::toBlock(ConstraintStmtSP c) {
	return std::dynamic_pointer_cast<ConstraintBlock>(c);
}

ConstraintBlockSP ConstraintBlock::mk(
		std::initializer_list<ConstraintStmt *>	c) {
	return ConstraintBlockSP(new ConstraintBlock(c));
}

ConstraintBlockSP ConstraintBlock::mk(
			const std::string						&name,
			std::initializer_list<ConstraintStmt *>	c) {
	return ConstraintBlockSP(new ConstraintBlock(name, c));
}

} /* namespace vsc */
