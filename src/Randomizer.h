/*
 * Randomizer.h
 *
 *  Created on: Sep 26, 2021
 *      Author: mballance
 */
#pragma once
#include "vsc/IModelConstraint.h"
#include "ISolverFactory.h"
#include "ModelField.h"
#include "RandState.h"
#include "RNG.h"

namespace vsc {

class Randomizer {
public:
	Randomizer(
			ISolverFactory		*solver_factory,
			RandState			*randstate);

	virtual ~Randomizer();

	bool randomize(
			const std::vector<IModelField *>		&fields,
			const std::vector<IModelConstraint *>	&constraints,
			bool									diagnose_failures
			);

private:
	ISolverFactory		*m_solver_factory;
	RandState			*m_randstate;

};

} /* namespace vsc */

