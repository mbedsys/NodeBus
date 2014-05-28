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

#include <globals.h>
#include <parser.hh>
#include "scanner.h"
#include "driver.h"

#ifdef USE_JSONBUS_EXCEPTION
#include <jsonbus/core/jsonparser.h>
#define ErrorException ErrorJSONParserException
using namespace JSONBus;
#else
#include "exception.h"
#endif


namespace jsonparser {

Driver::Driver(getc_t getc, void *stream)
		: scanner(*new Scanner(getc, stream)),
		parser(*new Parser(*this)){
}

Driver::~Driver() {
	delete &parser;
	delete &scanner;
}

QVariant Driver::parse() {
	variant_t ret;
	result = &ret;
	scanner.resetPos();
	if (parser.parse() != 0) {
		throw ErrorException(QString("Line: ") + QString::number(scanner.lineno()) + ", column: " + QString::number(scanner.YYLeng()) + ", " + lastError);
	}
	if (!result) {
		throw EOFException();
	}
	return *result;
}

}

