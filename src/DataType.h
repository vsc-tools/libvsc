/*
 * DataType.h
 *
 *  Created on: Sep 23, 2021
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "vsc/dm/IContext.h"
#include "vsc/dm/IDataType.h"
#include "vsc/dm/IModelBuildContext.h"
#include "ModelVal.h"

namespace vsc {
namespace dm {

class DataType;
typedef std::unique_ptr<DataType> DataTypeUP;
class DataType : public virtual IDataType {
public:
	DataType();

	virtual ~DataType();

    virtual void setAssociatedData(IAssociatedData *data) override {
        m_associated_data = IAssociatedDataUP(data);
    }

    virtual IAssociatedData *getAssociatedData() const override {
        return m_associated_data.get();
    }

protected:
    IAssociatedDataUP           m_associated_data;

};

}
} /* namespace vsc */

