/*
 * CompoundSolverDefault.h
 *
 *  Created on: Mar 23, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IContext.h"
#include "vsc/ICompoundSolver.h"

namespace vsc {

class CompoundSolverDefault : public ICompoundSolver {
public:
	CompoundSolverDefault(IContext *ctxt);

	virtual ~CompoundSolverDefault();

	virtual bool solve(
			IRandState								*randstate,
			const std::vector<IModelField *>		&fields,
			const std::vector<IModelConstraint *>	&constraints,
			SolveFlags								flags) override;

private:
	IContext							*m_ctxt;
};

} /* namespace vsc */

