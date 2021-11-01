/*
 * DataTypeWidthVisitor.h
 *
 *  Created on: Nov 1, 2021
 *      Author: mballance
 */

#pragma once
#include "VisitorBase.h"

namespace vsc {

class DataTypeWidthVisitor : public VisitorBase {
public:
	DataTypeWidthVisitor();

	virtual ~DataTypeWidthVisitor();

	std::pair<bool,int32_t> width(DataType *t);

	virtual void visitDataTypeInt(DataTypeInt *t) override;

private:
	bool					m_is_signed;
	int32_t					m_width;

};

} /* namespace vsc */

