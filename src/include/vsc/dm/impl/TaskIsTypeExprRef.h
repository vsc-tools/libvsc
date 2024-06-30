/**
 * TaskIsTypeExprFieldRef.h
 *
 * Copyright 2023 Matthew Ballance and Contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may 
 * not use this file except in compliance with the License.  
 * You may obtain a copy of the License at:
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" BASIS, 
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  
 * See the License for the specific language governing permissions and 
 * limitations under the License.
 *
 * Created on:
 *     Author: 
 */
#pragma once
#include "vsc/dm/impl/VisitorBase.h"

namespace vsc {
namespace dm {



class TaskIsTypeExprFieldRef : 
    public virtual vsc::dm::VisitorBase {
public:

    virtual ~TaskIsTypeExprFieldRef() { }

    bool eval(ITypeExpr *e) {
        m_ref = false;
        e->accept(m_this);
        return m_ref; 
    }

	virtual void visitTypeExprArrIndex(ITypeExprArrIndex *e) override { }

	virtual void visitTypeExprBin(ITypeExprBin *e) override { }

	virtual void visitTypeExprRange(ITypeExprRange *e) override { }

	virtual void visitTypeExprRangelist(ITypeExprRangelist *e) override { }

	virtual void visitTypeExprRefBottomUp(ITypeExprRefBottomUp *e) override { 
        m_ref = true;
    }

	virtual void visitTypeExprRefTopDown(ITypeExprRefTopDown *e) override { 
        m_ref = true;
    }

	virtual void visitTypeExprUnary(ITypeExprUnary *e) override { }

	virtual void visitTypeExprVal(ITypeExprVal *e) override { }

private:
    bool            m_ref;

};

} /* namespace dm */
} /* namespace vsc */


