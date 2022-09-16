
#pragma once
#include "vsc/IContext.h"
#include "vsc/IModelField.h"
#include "vsc/impl/VisitorBase.h"
#include "vsc/impl/TaskResolveModelExprVal.h"

namespace vsc {

/**
 * @brief Resolve a field-reference expression to a field
 * 
 */
class TaskResolveModelExprFieldRef : public virtual VisitorBase {
public:

    TaskResolveModelExprFieldRef(IContext *ctx) : m_ctx(ctx) { }

    virtual ~TaskResolveModelExprFieldRef() { }

    IModelField *resolve(IModelField *base, IModelExpr *e) {
        m_field = base;
        e->accept(m_this);
        return m_field;
    }

    template <class T> T *resolveT(IModelField *base, IModelExpr *e) {
        return dynamic_cast<T *>(resolve(base, e));
    }

	virtual void visitModelExprBin(IModelExprBin *e) override {
        m_field = 0;
    }

	virtual void visitModelExprCond(IModelExprCond *e) override {
        m_field = 0;
    }

	virtual void visitModelExprFieldRef(IModelExprFieldRef *e) override {
        m_field = e->field();
    }

	virtual void visitModelExprIn(IModelExprIn *e) override {
        m_field = 0;
    }

	virtual void visitModelExprIndexedFieldRef(IModelExprIndexedFieldRef *e) override {
        fprintf(stdout, "ResolveFieldRef::visitModelExprIndexedFieldRef\n");
        fflush(stdout);
        IModelField *field = m_field;

        for (std::vector<ModelExprIndexedFieldRefElem>::const_iterator
            it=e->getPath().begin();
            it!=e->getPath().end(); it++) {
            fprintf(stdout, "IT: %d\n", it->kind);
            fflush(stdout);
            switch (it->kind) {
            case ModelExprIndexedFieldRefKind::Field:
                field = it->field;
                fprintf(stdout, "field=%p\n", field);
                fflush(stdout);
                break;
            case ModelExprIndexedFieldRefKind::FieldIndex:
                field = field->getField(it->offset);
                break;
            case ModelExprIndexedFieldRefKind::VecIndex: {
                IModelFieldVec *vec = dynamic_cast<IModelFieldVec *>(field);
                if (!m_val) {
                    m_val = IModelValUP(m_ctx->mkModelVal());
                    m_val->setBits(32);
                }
                fprintf(stdout, "vec=%p\n", vec);
                if (!vec) {
                    field = 0;
                    break;
                }

                TaskResolveModelExprVal(m_ctx).eval(m_val.get(), it->idx_e);

                fprintf(stdout, "Index: %lld\n", m_val->val_u());

                field = vec->getField(m_val->val_u());
            } break;

            }

            if (!field) {
                break;
            }
        }

        m_field = field;
    }

	virtual void visitModelExprPartSelect(IModelExprPartSelect *e) override {
        m_field = 0;
    }

	virtual void visitModelExprRange(IModelExprRange *e) override {
        m_field = 0;
    }

	virtual void visitModelExprRangelist(IModelExprRangelist *e) override {
        m_field = 0;
    }

	virtual void visitModelExprRef(IModelExprRef *e) override {
        m_field = 0;
    }

	virtual void visitModelExprUnary(IModelExprUnary *e) override {
        m_field = 0;
    }

	virtual void visitModelExprVal(IModelExprVal *e) override {
        m_field = 0;
    }


private:
    IContext                        *m_ctx;
    IModelField                     *m_field;
    IModelValUP                     m_val;

};

}