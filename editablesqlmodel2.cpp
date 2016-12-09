/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/


#include "EditableSqlModel2.h"

EditableSqlModel2::EditableSqlModel2(QObject *parent)
    : QStandardItemModel(parent)
{
}

//! [0]
Qt::ItemFlags EditableSqlModel2::flags(
        const QModelIndex &index) const
{
    Qt::ItemFlags flags = QStandardItemModel::flags(index);
    if (index.column() >= 1 && index.column() <= 5 )
        flags |= Qt::ItemIsEditable;
    return flags;
}
//! [0]

//! [1]
bool EditableSqlModel2::setData(const QModelIndex &index, const QVariant &value, int /* role */)
{
    if (index.column() == 0)
        return false;

    QModelIndex primaryKeyIndex = QStandardItemModel::index(index.row(), 0);
    int id = data(primaryKeyIndex).toInt();

    clear();

    bool ok;
    if (index.column() == 1) {
        ok = setTheatrename(id, value.toString());
    } else if (index.column() == 2) {
        ok = setAddress(id, value.toString());
    }
    else if (index.column() == 3) {
        ok = setManager(id, value.toString());
    }
    else if (index.column() == 4) {
        ok = setSize(id, value.toString());
    }
    else if (index.column() == 5) {
        ok = setCost(id, value.toString());
    }
    refresh(this,r);
    return false;
}


QStandardItemModel* EditableSqlModel2::refresh(QStandardItemModel *model1, int r)
{
    model1->setRowCount(r);
    model1->setColumnCount(6);
    int row = 0;

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName("D:\\QT_551\\MovieApp\\onlmovie.db");
    db.setUserName("root");
    db.setPassword("root");
    bool ok = db.open();
    if (!ok)
    {
      QMessageBox::critical(0, QObject::tr("Database Error"),
                db.lastError().text());
      //return;
    }
    QSqlQuery query1(db);
    query1.prepare(QString("SELECT * FROM Theatre"));
    query1.exec();

    if(query1.size()!=0)
    {

    while (query1.next())
    {
        for(int c=0;c<=5;c++)
        {
        QString sval = query1.value(c).toString();
        //QMessageBox::warning(this,"Exp", sval);
        QStandardItem* item = new QStandardItem(sval);
        model1->setItem(row, c, item);
        }
        row++;
    }

    }
    model1->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model1->setHeaderData(1, Qt::Horizontal, QObject::tr("Theatre"));
    model1->setHeaderData(2, Qt::Horizontal, QObject::tr("Address"));
    model1->setHeaderData(3, Qt::Horizontal, QObject::tr("Manager"));
    model1->setHeaderData(4, Qt::Horizontal, QObject::tr("Size"));
    model1->setHeaderData(5, Qt::Horizontal, QObject::tr("Cost"));
}

void EditableSqlModel2::setMYr(int a)
{
    r = a;
    return;
}

bool EditableSqlModel2::setTheatrename(int personId, const QString &moviename)
{
    QSqlQuery query;
    query.prepare("update theatre set Tname = ? where id = ?");
    query.addBindValue(moviename);
    query.addBindValue(personId);
    return query.exec();
}
//! [2]

bool EditableSqlModel2::setAddress(int personId, const QString &director)
{
    QSqlQuery query;
    query.prepare("update theatre set Taddress = ? where id = ?");
    query.addBindValue(director);
    query.addBindValue(personId);
    return query.exec();
}

bool EditableSqlModel2::setManager(int personId, const QString &actors)
{
    QSqlQuery query;
    query.prepare("update theatre set Manager = ? where id = ?");
    query.addBindValue(actors);
    query.addBindValue(personId);
    return query.exec();
}

bool EditableSqlModel2::setSize(int personId, const QString &rating)
{
    QSqlQuery query;
    query.prepare("update theatre set Size = ? where id = ?");
    query.addBindValue(rating);
    query.addBindValue(personId);
    return query.exec();
}

bool EditableSqlModel2::setCost(int personId, const QString &cost)
{
    QSqlQuery query;
    query.prepare("update theatre set TicketCost = ? where id = ?");
    query.addBindValue(cost);
    query.addBindValue(personId);
    return query.exec();
}



