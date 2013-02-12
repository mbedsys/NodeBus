/*
 *   Copyright 2012-2013 Emeric Verschuur <emericv@openihs.org>
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

#include <common.h>
#include <jsonserializer.h>

#define JSON_NULL "null"
#define JSON_TRUE "true"
#define JSON_FALSE "false"
#define JSON_OBJECT_BEGIN "{"
#define JSON_OBJECT_END "}"
#define JSON_MEMBER_SEP ":"
#define JSON_ELEMENT_SEP ","
#define JSON_ARRAY_BEGIN "["
#define JSON_ARRAY_END "]"

using namespace std;

namespace JSONBus {

static QString sanitizeString( QString str )
{
  str.replace( QLatin1String( "\\" ), QLatin1String( "\\\\" ) );
  str.replace( QLatin1String( "\"" ), QLatin1String( "\\\"" ) );
  str.replace( QLatin1String( "\b" ), QLatin1String( "\\b" ) );
  str.replace( QLatin1String( "\f" ), QLatin1String( "\\f" ) );
  str.replace( QLatin1String( "\n" ), QLatin1String( "\\n" ) );
  str.replace( QLatin1String( "\r" ), QLatin1String( "\\r" ) );
  str.replace( QLatin1String( "\t" ), QLatin1String( "\\t" ) );
  return QString( QLatin1String( "\"%1\"" ) ).arg( str );
}

JSONSerializer::JSONSerializer(QObject *parent)
: QObject(parent), m_stream(*new StdStream(cout)) {
	
}

JSONSerializer::JSONSerializer(ostream& stream, QObject* parent)
: QObject(parent), m_stream(*new StdStream(stream)) {
	
}

JSONSerializer::JSONSerializer(const JSONBus::JSONSerializer::Stream& stream, QObject* parent)
: QObject(parent), m_stream(*stream.clone()) {
	
}

JSONSerializer::~JSONSerializer() {
	delete &m_stream;
}

void JSONSerializer::serialize(const QVariant &variant) {
	if (!variant.isValid()) { // Case of JSON null/undefined
		// TODO:find a way to differenciate null/undefined
		m_stream << JSON_NULL;
	} else if (variant.type() == QVariant::Bool) { // Case of JSON boolean
		m_stream << (variant.toBool() ? JSON_TRUE: JSON_FALSE);
	} else if (variant.type() == QVariant::Map) { // Case of JSON object
		m_stream << JSON_OBJECT_BEGIN;
		const QVariantMap elements = variant.toMap();
		auto it = elements.begin();
		if (it != elements.end()) {
			m_stream << sanitizeString(it.key()) << JSON_MEMBER_SEP;
			serialize(it.value());
			it++;
		}
		while (it != elements.end()) {
			m_stream << JSON_ELEMENT_SEP << sanitizeString(it.key()) << JSON_MEMBER_SEP;
			serialize(it.value());
			it++;
		}
		m_stream << JSON_OBJECT_END;
	} else if (variant.type() == QVariant::List) { // Case of JSON array
		m_stream << JSON_ARRAY_BEGIN;
		const QVariantList elements = variant.toList();
		auto it = elements.begin();
		if (it != elements.end()) {
			serialize(*it);
			it++;
		}
		while (it != elements.end()) {
			m_stream << JSON_MEMBER_SEP;
			serialize(*it);
			it++;
		}
		m_stream << JSON_ARRAY_END;
	} else if ((variant.type() == QVariant::String) 
		|| (variant.type() == QVariant::ByteArray)) { // Case of JSON string
		m_stream << sanitizeString(variant.toString());
	} else if ((variant.type() == QVariant::Double) || variant.canConvert<double>()) {
		m_stream << QString::number(variant.toDouble()).replace("inf", "infinity");
	} else if ((variant.type() == QVariant::String) || variant.canConvert<QString>()) {
		m_stream << variant.toString();
	} else {
		throw JSONSerializerException("Fatal: QVariant type not managed.");
	}
}

}
