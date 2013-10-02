/*
 * Copyright (c) 2013, Falko Schumann <http://www.muspellheim.de>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   - Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   - Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "columndefinition.h"

QString ColumnDefinition::name() const
{
    return m_name;
}

void ColumnDefinition::setName(const QString &name)
{
    m_name = name;
}

ColumnDefinition::ColumnType ColumnDefinition::type() const
{
    return m_type;
}

void ColumnDefinition::setType(ColumnType type)
{
    m_type = type;
}

bool ColumnDefinition::autoincrement() const
{
    return m_autoincrement;
}

void ColumnDefinition::setAutoincrement(bool autoincrement)
{
    m_autoincrement = autoincrement;
}

QVariant ColumnDefinition::defaultValue() const
{
    return m_defaultValue;
}

void ColumnDefinition::setDefaultValue(const QVariant &defaultValue)
{
    m_defaultValue = defaultValue;
}

bool ColumnDefinition::isRequired() const
{
    return m_required;
}

void ColumnDefinition::setRequired(bool required)
{
    m_required = required;
}

ColumnDefinition::ColumnIndex ColumnDefinition::indexed() const
{
    return m_indexed;
}

void ColumnDefinition::setIndexed(ColumnIndex indexed)
{
    m_indexed = indexed;
}

QString ColumnDefinition::toSql() const
{
    // TODO primary key and/or autoincrement
    QString sql;
    sql = name() + " ";
    switch (type()) {
    case IntegerType:
        sql += "INTEGER";
        if (!defaultValue().isNull())
            sql += " DEFAULT " + defaultValue().toString();
        break;
    case RealType:
        sql += "REAL";
        if (!defaultValue().isNull())
            sql += " DEFAULT " + defaultValue().toString();
        break;
    case TextType:
        sql += "TEXT";
        if (!defaultValue().isNull())
            sql += " DEFAULT '" + defaultValue().toString() + "'";
        break;
    case BlobType:
        sql += "BLOB";
        break;
    }
    if (isRequired())
        sql += " NOT NULL";
    switch (indexed()) {
    case NoIndex:
        break;
    case IndexWithDuplicatesPossible:
        sql += "???";
        break;
    case IndexWithoutDuplicates:
        sql += " UNIQUE";
        break;
    }

    return sql;
}
