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


#include "editablesqlmodel.h"

EditableSqlModel::EditableSqlModel(QObject *parent)
    : QStandardItemModel(parent)
{
}

//! [0]
Qt::ItemFlags EditableSqlModel::flags(
        const QModelIndex &index) const
{
    Qt::ItemFlags flags = QStandardItemModel::flags(index);
    if (index.column() > 2 )
        flags |= Qt::ItemIsEditable;
    return flags;
}
//! [0]

//! [1]
bool EditableSqlModel::setData(const QModelIndex &index, const QVariant &value, int /* role */)
{
    if (index.column() == 1 || index.column() == 2)
        return false;

//    QModelIndex primaryKeyIndex = QStandardItemModel::index(index.row(), 0);
//    int id = data(primaryKeyIndex).toInt();

//    clear();

//    bool ok;
//    if (index.column() == 1) {
//        ok = setName(id, value.toString());
//    } else if (index.column() == 2) {
//        ok = setCompany(id, value.toString());
//    }
//    else if (index.column() == 3) {
//        ok = setDistName(id, value.toString());
//    }
//    else if (index.column() == 4) {
//        ok = setMfgDt(id, value.toString());
//    }
//    else if (index.column() == 5) {
//        ok = setExpDt(id, value.toString());
//    }
//    else if (index.column() == 6) {
//        ok = setPrc(id, value.toString());
//    }
//    else if (index.column() == 7) {
//        ok = setStkQty(id, value.toString());
//    }
//    refresh(this,getM1(),getYr1());
    return false;
}


QStandardItemModel* EditableSqlModel::refresh(QStandardItemModel *model1,int m, int yr)
{
    model1->setRowCount(9);
    model1->setColumnCount(2);
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
    }
    else
    {
    QSqlQuery query2(db);
    query2.prepare(QString("SELECT MAX(ID) FROM Booking"));
    query2.exec();
    int rsid = 0;
    while (query2.next())
    {
        rsid = query2.value(0).toString().toInt();
    }
    QStandardItem* item1 = new QStandardItem(QString("ReservId"));
    model1->setItem(0, 0, item1);
    QStandardItem* item2 = new QStandardItem(QString::number(rsid));
    model1->setItem(0, 1, item2);

    int row=1;
    QSqlQuery query1(db);
    query1.prepare(QString("SELECT * FROM Booking WHERE ID=:ID"));
    query1.bindValue(":ID", rsid);
    query1.exec();
    QStringList snolst;
    while (query1.next())
    {
        QString fn = query1.value(1).toString();
        QString mn = query1.value(2).toString();
        QString ln = query1.value(3).toString();
        QString sd = query1.value(4).toString();
        QString st = query1.value(5).toString();
        QString nt = query1.value(6).toString();
        QString sn = query1.value(7).toString();
        QString ct = query1.value(8).toString();

        QStandardItem* item3 = new QStandardItem(QString("FirstNm"));
        model1->setItem(1, 0, item3);

        QStandardItem* item4 = new QStandardItem(fn);
        model1->setItem(1, 1, item4);

        QStandardItem* item5 = new QStandardItem(QString("MiddleNm"));
        model1->setItem(2, 0, item5);

        QStandardItem* item6 = new QStandardItem(mn);
        model1->setItem(2, 1, item6);

        QStandardItem* item7 = new QStandardItem(QString("LastNm"));
        model1->setItem(3, 0, item7);

        QStandardItem* item8 = new QStandardItem(ln);
        model1->setItem(3, 1, item8);

        QStandardItem* item9 = new QStandardItem(QString("ShowDt"));
        model1->setItem(4, 0, item9);

        QStandardItem* item10 = new QStandardItem(sd);
        model1->setItem(4, 1, item10);

        QStandardItem* item11 = new QStandardItem(QString("ShowTm"));
        model1->setItem(5, 0, item11);

        QStandardItem* item12 = new QStandardItem(st);
        model1->setItem(5, 1, item12);

        QStandardItem* item13 = new QStandardItem(QString("NoOfTkts"));
        model1->setItem(6, 0, item13);

        QStandardItem* item14 = new QStandardItem(nt);
        model1->setItem(6, 1, item14);

        QStandardItem* item15 = new QStandardItem(QString("SeatNo"));
        model1->setItem(7, 0, item15);

        QStandardItem* item16 = new QStandardItem(sn);
        model1->setItem(7, 1, item16);

        QStandardItem* item17 = new QStandardItem(QString("Cost"));
        model1->setItem(8, 0, item17);

        QStandardItem* item18 = new QStandardItem(ct);
        model1->setItem(8, 1, item18);

    }
    }
}





