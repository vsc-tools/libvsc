
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
 * SolveGroup.h
 *
 *  Created on: Jul 5, 2020
 *      Author: ballance
 */

#ifndef SRC_SOLVER_SOLVEGROUP_H_
#define SRC_SOLVER_SOLVEGROUP_H_
#include <memory>
#include <set>
#include <vector>

#include "sav/ConstraintSoft.h"
#include "sav/Field.h"

namespace vsc {

/**
 * A SolveGroup captures a set of related fields and
 * constraints
 */
class SolveGroup {
public:
	SolveGroup();

	virtual ~SolveGroup();

	const std::set<Field *> &fields() const {
		return m_field_s;
	}

	const std::vector<Field *> &rand_fields() const {
		return m_rand_fields;
	}

	const std::vector<ConstraintSoft *> &soft_constraints() const {
		return m_soft_constraints;
	}

	const std::vector<ConstraintStmt *> &constraints() const {
		return m_constraints;
	}

	void addSoftConstraint(ConstraintSoft *c) {
		m_soft_constraints.push_back(c);
	}

	void addConstraint(ConstraintStmt *c) {
		m_constraints.push_back(c);
	}

	bool addField(Field *f);

private:
	std::set<Field *>				m_field_s;
	std::vector<Field *>			m_rand_fields;
	// regular hard constraints
	std::vector<ConstraintStmt *>	m_constraints;
	// soft constraints, arranged in priority order (low..high)
	std::vector<ConstraintSoft *>	m_soft_constraints;
};

typedef std::unique_ptr<SolveGroup> SolveGroupUP;

} /* namespace vsc */

#endif /* SRC_SOLVER_SOLVEGROUP_H_ */
