/*
 * ExprValEnum.cpp
 *
 *  Created on: Jul 31, 2020
 *      Author: ballance
 */

#include "sav/ExprValEnum.h"

namespace vsc {

ExprValEnum::ExprValEnum(
		EnumTypeInfo		*info,
		int64_t				val) : ExprVal(ValType_Enum),
				m_info(info), m_val(val) {

}

ExprValEnum::~ExprValEnum() {
	// TODO Auto-generated destructor stub
}

std::string ExprValEnum::toString() const {
	// TODO:
//	return m_info->;
	return "unknown";
}

} /* namespace vsc */
