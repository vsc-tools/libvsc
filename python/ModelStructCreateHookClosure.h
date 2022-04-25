/*
 * ModelStructCreateHookClosure.h
 *
 *  Created on: Apr 24, 2022
 *      Author: mballance
 */

#pragma once
#include <Python.h>
#include "vsc/IModelStructCreateHook.h"

namespace vsc {

class ModelStructCreateHookClosure : public IModelStructCreateHook {
public:
	ModelStructCreateHookClosure(PyObject *obj);

	virtual ~ModelStructCreateHookClosure();

	virtual void create(IModelField *field) override;

private:
	PyObject				*m_obj;
};

} /* namespace vsc */

