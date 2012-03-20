/*
    Copyright (c) 2012, Emeric Verschuur <contact@openihs.org>
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
        * Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.
        * Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.
        * Neither the name of the <organization> nor the
        names of its contributors may be used to endorse or promote products
        derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY Emeric Verschuur <contact@openihs.org> ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL Emeric Verschuur <contact@openihs.org> BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 * @brief JSONBus : JSON serializer management.
 * @file jsonserializer.h
 * @author Emeric VERSCHUUR <contact@openihs.org>, (C) 2012
 */

#ifndef JSONBUS_JSONSERIALIZER_H
#define JSONBUS_JSONSERIALIZER_H

#include <jsonbus/core/exception.h>

#ifndef JSONBUS_EXPORT
#define JSONBUS_EXPORT
#endif

#include <QString>
#include <QVariant>

namespace JSONBus {

jsonbus_declare_exception(JSONSerializerException, Exception);

/**
 * @brief JSON serializer management.
 */
class JSONBUS_EXPORT JSONSerializer: public QObject {
public:
	
	/**
	 * @brief JSONSerializer constructor.
	 * @param parent Parent object
	 */
	JSONSerializer(QObject* parent = 0);
	
	/**
	 * @brief JSONSerializer destructor.
	 */
	~JSONSerializer();
	
	/**
	 * @brief Serialize an object in JSON format
	 * @param variant object to serialize
	 * @return QByteArray object
	 */
	QByteArray serialize(const QVariant &variant);
	
	/**
	 * @brief Serialize a JSON data from a input device
	 * @param variant object to serialize
	 * @param output Device to output the JSON string
	 * @throw JSONSerializerException on error
	 */
	void serialize(const QVariant &variant, QIODevice &output);
private:
	void *m_handle;
};

}

#endif