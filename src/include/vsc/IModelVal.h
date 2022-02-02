/*
 * IModelVal.h
 *
 *  Created on: Jan 27, 2022
 *      Author: mballance
 */

#pragma once
#include <stdint.h>

namespace vsc {

class IModelVal {
public:
	union val_t {
		uint64_t		v;
		uint64_t		*vp;
	};

public:
	virtual ~IModelVal() { }

	virtual uint32_t bits() const = 0;

	virtual void bits(uint32_t b) = 0;

	virtual void to_bits(char *bits) const = 0;

	virtual void from_bits(const char *bits, int32_t width=-1) = 0;

	virtual void val_u(uint64_t v, int32_t width=-1) = 0;

	virtual const val_t &val() const = 0;

	virtual val_t &val() = 0;

	inline int64_t val_i() const {
		uint32_t nb = bits();
		const val_t &v = val();
		if (nb <= 64) {
			int64_t ret = v.v;
			if (nb < 64) { // sign-extend
				ret <<= (64-nb);
				ret >>= (64-nb);
			}
			return ret;
		} else {
			return v.vp[0];
		}
	}

	inline uint64_t val_u() const { return (bits()<=64)?val().v:val().vp[0]; }

};

}

