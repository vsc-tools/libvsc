
#pragma once
#include <vector>
#include "vsc/impl/VisitorBase.h"

namespace vsc {

class TaskRollbackConstraintSubst : public VisitorBase {
public:

    void rollback(IModelConstraint *c) {
        c->accept(m_this);
    }

    virtual void visitModelConstraintScope(IModelConstraintScope *c) {
        m_index_s.push_back(0);
        m_scope_s.push_back(c);
        for (std::vector<IModelConstraintUP>::const_iterator
            it=c->constraints().begin();
            it!=c->constraints().end(); it++) {
            (*it)->accept(m_this);
            m_index_s.back() += 1;
        }
        m_scope_s.pop_back();
    }

    virtual void visitModelConstraintSubst(IModelConstraintSubst *c) {
        IModelConstraint *orig = c->releaseOriginal();
        m_scope_s.back()->swapConstraint(
            m_index_s.back(),
            orig);
        delete c;
    }

private:
    std::vector<IModelConstraintScope *>        m_scope_s;
    std::vector<uint32_t>                       m_index_s;
    

};

}
