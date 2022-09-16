/*
 * IModelFieldRef.h
 *
 *  Created on: May 9, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "vsc/IModelField.h"

namespace vsc {

class IModelFieldRef;
using IModelFieldRefUP=std::unique_ptr<IModelFieldRef>;
class IModelFieldRef : public virtual IModelField {
public:

	virtual ~IModelFieldRef() { }

	virtual void setRef(IModelField *ref) = 0;

	virtual IModelField *getRef() const = 0;

};

}
