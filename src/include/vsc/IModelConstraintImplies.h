/*
 * IModelConstraintImplies.h
 *
 *  Created on: Feb 3, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelConstraint.h"
#include "vsc/IModelExpr.h"

namespace vsc {

class IModelConstraintImplies;
using IModelConstraintImpliesUP=std::unique_ptr<IModelConstraintImplies>;
class IModelConstraintImplies : public virtual IModelConstraint {
public:

	virtual ~IModelConstraintImplies() { }

	virtual IModelExpr *getCond() const = 0;

	virtual IModelConstraint *getBody() const = 0;

};

}
