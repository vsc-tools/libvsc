/*
 * ModelExprFieldRef.h
 *
 *  Created on: Oct 4, 2021
 *      Author: mballance
 */

#pragma once
#include "ModelExpr.h"
#include "ModelField.h"

namespace vsc {

class ModelExprFieldRef : public ModelExpr {
public:
	ModelExprFieldRef(IModelField *field);

	virtual ~ModelExprFieldRef();

	virtual int32_t width() const override {
		return m_field->val()->bits();
	}

	IModelField *field() const { return m_field; }

	virtual void eval(IModelVal *dst) override;

	virtual void accept(IVisitor *v) { v->visitModelExprFieldRef(this); }

private:
	IModelField					*m_field;

};

} /* namespace vsc */

