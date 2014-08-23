/*
 *   Copyright 2012-2014 Emeric Verschuur <emericv@openihs.org>
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *		   http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

#ifndef IDLPARSER_NODEVARIANT_H
#define IDLPARSER_NODEVARIANT_H

#include "ltype.h"
#include "node.h"

namespace idlparser {

class NodeVariant: public Node {
private:
	QVariant m_var;
public:
	NodeVariant(const QVariant &value);
	virtual QString str();
	virtual QVariant &val();
};

inline NodeVariant::NodeVariant(const QVariant& value): m_var(value) {
}

inline QString NodeVariant::str() {
	return m_var.toString();
}

inline QVariant& NodeVariant::val() {
	return m_var;
}

}

#endif // IDLPARSER_NODEVARIANT_H