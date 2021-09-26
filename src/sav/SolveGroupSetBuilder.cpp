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
 * SolveGroupSetBuilder.cpp
 *
 *  Created on: Jul 6, 2020
 *      Author: ballance
 */

#include "sav/SolveGroupSetBuilder.h"

#include <assert.h>

namespace vsc {

SolveGroupSetBuilder::SolveGroupSetBuilder() : m_pass(0), m_depth(0) {
	// TODO Auto-generated constructor stub

}

SolveGroupSetBuilder::~SolveGroupSetBuilder() {
	// TODO Auto-generated destructor stub
}

SolveGroupSet *SolveGroupSetBuilder::build(
		const std::vector<FieldSP>				&fields,
		const std::vector<ConstraintStmtSP>		&constraints) {

	m_active_solvegroup = 0;

	// First, collect all fields
	m_pass = 0;
	m_depth = 0;
	for (std::vector<FieldSP>::const_iterator it=fields.begin();
			it!=fields.end(); it++) {
		(*it)->accept(this);
	}

	// Now, build up the solve groups
	m_pass = 1;
	m_used_rand = true;
	for (std::vector<FieldSP>::const_iterator it=fields.begin();
			it!=fields.end(); it++) {
		(*it)->accept(this);
	}
	for (std::vector<ConstraintStmtSP>::const_iterator it=constraints.begin();
			it!=constraints.end(); it++) {
		(*it)->accept(this);
	}

	SolveGroupSet *ret = new SolveGroupSet();

	for (std::set<SolveGroup *>::const_iterator it=m_solvegroup_s.begin();
			it!=m_solvegroup_s.end(); it++) {
		// Transfers ownership to SolveGroupSet
		ret->addSolveGroup(*it);
	}

	for (std::set<Field *>::const_iterator it=m_field_s.begin();
			it!=m_field_s.end(); it++) {
		ret->addUnconstrained(*it);
	}

	return ret;
}

void SolveGroupSetBuilder::visitConstraintBlock(ConstraintBlock *c) {
	// TODO: check whether block is enabled

	if (m_used_rand) {
		m_active_solvegroup = 0;
		m_constraint_l.push_back(c);
		VisitorBase::visitConstraintBlock(c);
		m_constraint_l.clear();
	}
}

void SolveGroupSetBuilder::visitConstraintExpr(ConstraintExpr *c) {
	visitConstraintStmtEnter(c);
	VisitorBase::visitConstraintExpr(c);
	visitConstraintStmtLeave(c);
}

void SolveGroupSetBuilder::visitConstraintStmtEnter(ConstraintStmt *c) {
	if (m_pass == 1 && m_depth == 0) {
		// Need to make this a UP?
		m_active_solvegroup = 0;
	}
	m_depth++;
	m_constraint_l.push_back(c);
}

void SolveGroupSetBuilder::visitConstraintStmtLeave(ConstraintStmt *c) {
	m_constraint_l.pop_back();
	m_depth--;
	if (m_pass == 1 && m_depth == 0) {
		if (m_active_solvegroup) {
			m_active_solvegroup->addConstraint(c);
		}
	}
}

void SolveGroupSetBuilder::visitExprFieldRef(ExprFieldRef *e) {
	if (m_pass != 1) {
		return;
	}

	// TODO: handle array special case
	process_fieldref(e->field());
}

void SolveGroupSetBuilder::process_fieldref(Field *f) {
	if (m_field_solvegroup_m.find(f) != m_field_solvegroup_m.end()) {
		SolveGroup *ex_group = m_field_solvegroup_m.find(f)->second;

		if (!m_active_solvegroup) {
			m_active_solvegroup = ex_group;
		} else if (m_active_solvegroup != ex_group) {
			for (std::set<Field *>::const_iterator it=m_active_solvegroup->fields().begin();
					it!=m_active_solvegroup->fields().end(); it++) {
				// Relink fields to the new consolidated solvegroup
				ex_group->addField(*it);

				// Update field/solvegroup mapping
				m_field_solvegroup_m.erase(*it);
				m_field_solvegroup_m.insert({*it, ex_group});
			}

			for (std::vector<ConstraintStmt *>::const_iterator it=m_active_solvegroup->constraints().begin();
					it!=m_active_solvegroup->constraints().end(); it++) {
				ex_group->addConstraint(*it);
			}

			// Remove the previous solvegroup
			m_solvegroup_s.erase(m_active_solvegroup);
			delete m_active_solvegroup;
			m_active_solvegroup = ex_group;
		}
	} else {
		// Field isn't currently part of a solvegroup
		if (!m_active_solvegroup) {
			// Create a new solvegroup
			m_active_solvegroup = new SolveGroup();
			m_solvegroup_s.insert(m_active_solvegroup);
		}
		// Register this field/solvegroup mapping
		m_active_solvegroup->addField(f);
		m_field_solvegroup_m.insert({f, m_active_solvegroup});
	}

	if (m_field_s.find(f) != m_field_s.end()) {
		m_field_s.erase(f);
	}
}

void SolveGroupSetBuilder::visitFieldComposite(FieldComposite *f) {
	bool prev_used_rand = m_used_rand;
	m_used_rand = f->used_rand();
	VisitorBase::visitFieldComposite(f);
	m_used_rand = prev_used_rand;
}

void SolveGroupSetBuilder::visitFieldScalar(FieldScalar *f) {
	if (m_pass != 0) {
		return;
	}
	m_field_s.insert(f);
}


} /* namespace vsc */
