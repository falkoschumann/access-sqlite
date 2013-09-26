/*
 * Access SQLite
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

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->databaseView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenuForDatabaseView(QPoint)));
    connect(ui->actionCreateDatabase, SIGNAL(triggered()), this, SLOT(createDatabase()));
    connect(ui->actionOpenDatabase, SIGNAL(triggered()), this, SLOT(openDatabase()));
    connect(ui->actionCloseDatabase, SIGNAL(triggered()), this, SLOT(closeDatabase()));
    connect(ui->actionRenameTable, SIGNAL(triggered()), this, SLOT(renameTable()));
    connect(ui->actionDeleteTable, SIGNAL(triggered()), this, SLOT(deleteTable()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showContextMenuForDatabaseView(const QPoint &positionAtWidget)
{
    if (ui->databaseView->selectedItems().size() > 0) {
        QMenu menu(this);
        menu.addAction(ui->actionRenameTable);
        menu.addAction(ui->actionDeleteTable);
        menu.exec(ui->databaseView->viewport()->mapToGlobal(positionAtWidget));
    }
}

void MainWindow::createDatabase()
{
    QString fileName = QFileDialog::getSaveFileName(
                this,
                tr("Create SQLite database"),
                QDir::homePath(),
                tr("SQLite database (*.sqlite *.db);;All files (*.*)"));
    if (!fileName.isNull())
        connectDatabase(fileName);
}

void MainWindow::openDatabase()
{
    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Open SQLite database"),
                QDir::homePath(),
                tr("SQLite database (*.sqlite *.db);;All files (*.*)"));
    if (!fileName.isNull())
        connectDatabase(fileName);
}

void MainWindow::connectDatabase(QString &fileName)
{
    closeDatabase();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(fileName);
    if (db.open()) {
        setWindowTitle(QFile(fileName).fileName() + " - Access SQLite");
        ui->actionCloseDatabase->setEnabled(true);
        refreshDatabaseView();
    } else {
        QMessageBox::critical(this, tr("Error opening database"), db.lastError().text());
    }
}

void MainWindow::closeDatabase()
{
    QString connectionName;
    {
        QSqlDatabase db = QSqlDatabase::database();
        if (db.isValid()) {
            db.close();
            connectionName = db.connectionName();
        }
    }
    if (!connectionName.isNull()) {
        QSqlDatabase::removeDatabase(connectionName);
        setWindowTitle("Access SQLite");
        ui->actionCloseDatabase->setEnabled(false);
        refreshDatabaseView();
    }
}

void MainWindow::refreshDatabaseView()
{
    ui->databaseView->clear();

    if (!QSqlDatabase::database().isValid())
        return;

    QSqlQuery query;
    if (query.exec("SELECT name FROM sqlite_master WHERE type='table' ORDER BY name")) {
        while (query.next()) {
            new QListWidgetItem(query.value(0).toString(), ui->databaseView);
        }
    } else {
        QMessageBox::critical(this, tr("Error querying database"), query.lastError().text());
    }
}

void MainWindow::renameTable()
{
    QString oldTableName = ui->databaseView->selectedItems().at(0)->text();
    QString newTableName = QInputDialog::getText(this, "Rename table", "Please give the new table name", QLineEdit::Normal, oldTableName);
    // TODO: check newTableName for empty string if Ok pressed
    // TODO: rename "Ok" button to "Rename"
    if (newTableName.isNull())
        return;

    QSqlQuery query;
    if (query.exec("ALTER TABLE " + oldTableName + " RENAME TO " + newTableName)) {
        refreshDatabaseView();
    } else {
        QMessageBox::critical(this, tr("Error renaming table"), query.lastError().text());
    }
}

void MainWindow::deleteTable()
{
    QString tableName = ui->databaseView->selectedItems().at(0)->text();
    QMessageBox::StandardButton result = QMessageBox::question(this, "Delete table", "Do you really want to delete the table " + tableName + "?");
    if (result == QMessageBox::No)
        return;

    QSqlQuery query;
    if (query.exec("DROP TABLE " + tableName)) {
        refreshDatabaseView();
    } else {
        QMessageBox::critical(this, tr("Error deleting table"), query.lastError().text());
    }
}
