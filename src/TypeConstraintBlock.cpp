/*
 * TypeConstraintBlock.cpp
 *
 *  Created on: Apr 8, 2022
 *      Author: mballance
 */

#include "TypeConstraintBlock.h"

namespace vsc {
namespace dm {

TypeConstraintBlock::TypeConstraintBlock(const std::string &name) :
	m_name(name) {

}

TypeConstraintBlock::~TypeConstraintBlock() {
	// TODO Auto-generated destructor stub
}

void TypeConstraintBlock::addConstraint(ITypeConstraint *c) {
	m_constraints.push_back(ITypeConstraintUP(c));
}

}
} /* namespace vsc */

