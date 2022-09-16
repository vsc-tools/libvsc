/*
 * VisitorTaskSetUsedRand.h
 *
 *  Created on: Mar 23, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "vsc/ITask.h"
#include "vsc/impl/VisitorBase.h"

namespace vsc {

class TaskSetUsedRand : public VisitorBase {
public:
	TaskSetUsedRand() {}

	virtual ~TaskSetUsedRand() {}

	virtual void apply(IAccept *item, bool set_root, int32_t max_depth=-1) {
		m_used_rand.clear();
		m_set_root = set_root;
		m_max_depth = max_depth;
		item->accept(this);
	}

	virtual void visitModelField(IModelField *f) override {
		if (is_used_rand()) {
			f->setFlag(ModelFieldFlag::UsedRand);
		}

		if (f->fields().size() > 0) {
			m_used_rand.push_back(is_used_rand());
			for (auto fi=f->fields().begin(); fi!=f->fields().end(); fi++) {
				(*fi)->accept(this);
			}
			m_used_rand.pop_back();
		}
	}

protected:

	bool is_used_rand() {
		if (m_used_rand.size() > 0) {
			return ((m_max_depth == -1 || m_max_depth < m_used_rand.size()) &&
					m_used_rand.at(m_used_rand.size()-1));
		} else {
			return m_set_root;
		}
	}

protected:
	bool							m_set_root;
	int32_t							m_max_depth;
	std::vector<bool>				m_used_rand;


};

} /* namespace vsc */

