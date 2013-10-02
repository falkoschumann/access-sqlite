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

#include "addcolumndialog.h"
#include "ui_addcolumndialog.h"

#include "columndefinition.h"

#include <QPushButton>

AddColumnDialog::AddColumnDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddColumnDialog)
{
    ui->setupUi(this);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Add column");

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

AddColumnDialog::~AddColumnDialog()
{
    delete ui;
}

ColumnDefinition AddColumnDialog::columnDefinition()
{
    ColumnDefinition d;
    d.setName(ui->name->text());
    switch (ui->type->currentIndex()) {
    case ColumnDefinition::IntegerType:
        d.setType(ColumnDefinition::IntegerType);
        break;
    case ColumnDefinition::RealType:
        d.setType(ColumnDefinition::RealType);
        break;
    case ColumnDefinition::TextType:
        d.setType(ColumnDefinition::TextType);
        break;
    case ColumnDefinition::BlobType:
        d.setType(ColumnDefinition::BlobType);
        break;
    }
    d.setRequired(ui->required->isChecked());
    d.setDefaultValue(ui->defaultValue->text());
    switch (ui->indexed->currentIndex()) {
    case ColumnDefinition::NoIndex:
        d.setIndexed(ColumnDefinition::NoIndex);
        break;
    case ColumnDefinition::IndexWithDuplicatesPossible:
        d.setIndexed(ColumnDefinition::IndexWithDuplicatesPossible);
        break;
    case ColumnDefinition::IndexWithoutDuplicates:
        d.setIndexed(ColumnDefinition::IndexWithoutDuplicates);
        break;
    }
    d.setAutoincrement(ui->autoincrement->isChecked());
    return d;
}
