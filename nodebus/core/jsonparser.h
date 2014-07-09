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

/**
 * @brief NodeBus : JSON Parser management.
 * 
 * @author <a href="mailto:emericv@openihs.org">Emeric Verschuur</a>
 * @date 2014
 * @copyright Apache License, Version 2.0
 */

#ifndef NODEBUS_JSONPARSER_H
#define NODEBUS_JSONPARSER_H

#include <nodebus/core/exception.h>

#ifndef NODEBUS_EXPORT
#define NODEBUS_EXPORT
#endif

namespace jsonparser {
class Driver;
}

namespace NodeBus {

nodebus_declare_exception(JSONParserException, Exception);
nodebus_declare_exception(ErrorJSONParserException, JSONParserException);
class StreamChannel;

/**
 * @brief JSON Parser management.
 */
class NODEBUS_EXPORT JSONParser {
public:
	typedef char (*fGetc_t)(void *ptr);
	
	/**
	 * @brief JSONParser constructor.
	 */
	JSONParser();
	
	/**
	 * @brief JSONParser constructor.
	 * @param channel Channel pointer
	 */
	JSONParser(fGetc_t getChar, void *ptr);
	
	/**
	 * @brief JSONParser constructor.
	 * @param channel Channel pointer
	 */
	JSONParser(SharedPtr<StreamChannel> channel);
	
	/**
	 * @brief JSONParser destructor.
	 */
	~JSONParser();
	
	/**
	 * @brief Parse a JSON data from a byte array
	 * @return QVariant object
	 * @throw JSONParserException on parsing error
	 */
	QVariant parse();
	
	/**
	 * @brief Parse a JSON data from a byte array
	 * @return QVariant object
	 * @throw JSONParserException on parsing error
	 */
	static QVariant parse(const char *data, uint len);
	
	/**
	 * @brief Parse a JSON data from a byte array
	 * @return QVariant object
	 * @throw JSONParserException on parsing error
	 */
	static QVariant parse(const QString &data);
	
private:
	jsonparser::Driver *m_driver;
};

}

#endif //NODEBUS_JSONPARSER_H