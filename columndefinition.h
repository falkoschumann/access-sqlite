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

#ifndef COLUMNDEFINITION_H
#define COLUMNDEFINITION_H

#include <QVariant>

class ColumnDefinition
{
public:
    enum ColumnType { IntegerType, RealType, TextType, BlobType };
    enum ColumnIndex { NoIndex, IndexWithoutDuplicates, IndexWithDuplicatesPossible };
    
    QString name() const;
    void setName(const QString &name);
    ColumnType type() const;
    void setType(ColumnType type);
    bool autoincrement() const;
    void setAutoincrement(bool autoincrement);
    QVariant defaultValue() const;
    void setDefaultValue(const QVariant &defaultValue);
    bool isRequired() const;
    void setRequired(bool isRequired);
    ColumnIndex indexed() const;
    void setIndexed(ColumnIndex indexed);
    QString toSql() const;

private:
    QString m_name;
    ColumnType m_type;
    bool m_autoincrement;
    QVariant m_defaultValue;
    bool m_required;
    ColumnIndex m_indexed;
};

#endif // COLUMNDEFINITION_H
