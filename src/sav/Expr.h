
/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/*
 * Expr.h
 *
 *  Created on: Jul 3, 2020
 *      Author: ballance
 */

#ifndef SRC_EXPR_EXPR_H_
#define SRC_EXPR_EXPR_H_
#include <memory>

#include "../IVisitor.h"

namespace vsc {

class Expr {
public:
	Expr();

	virtual ~Expr();

	virtual void accept(IVisitor *v) = 0;

};

typedef std::shared_ptr<Expr> ExprSP;

} /* namespace vsc */

#endif /* SRC_EXPR_EXPR_H_ */
