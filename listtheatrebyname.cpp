#include "listtheatrebyname.h"
#include "ui_listtheatrebyname.h"

ListTheatreByName::ListTheatreByName(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListTheatreByName)
{
    ui->setupUi(this);
    this->setModal(true);
    ui->btnList->setStyleSheet("background-color: rgb(233,241,255)");
    QSqlDatabase db1 = QSqlDatabase::addDatabase("QSQLITE");
    db1.setHostName("localhost");
    db1.setDatabaseName("D:\\QT_551\\MovieApp\\onlmovie.db");
    db1.setUserName("root");
    db1.setPassword("root");
    bool ok1 = db1.open();
    if (!ok1)
    {
      QMessageBox::critical(0, QObject::tr("Database Error"),
                db1.lastError().text());
      return;
    }
    QSqlQuery query(db1);
    query.prepare(QString("SELECT ID,Tname FROM Theatre"));
    query.exec();
    ui->cmbTh->addItem("Select","0");
    while (query.next())
    {
        QString sv = query.value(0).toString();
        ui->cmbTh->addItem(query.value(1).toString(), sv);
    }
}

ListTheatreByName::~ListTheatreByName()
{
    delete ui;
}

void ListTheatreByName::on_btnList_clicked()
{
    QString thid = "";
    thid = ui->cmbTh->currentText();
    if(thid == "Select")
    {
        QMessageBox::warning(this,"List Theatre By Name", "Please select theatre");
        return;
    }
    r= 0;
    QSqlDatabase db1 = QSqlDatabase::addDatabase("QSQLITE");
    db1.setHostName("localhost");
    db1.setDatabaseName("D:\\QT_551\\MovieApp\\onlmovie.db");
    db1.setUserName("root");
    db1.setPassword("root");
    bool ok = db1.open();
    if (!ok)
    {
      QMessageBox::critical(0, QObject::tr("Database Error"),
                db1.lastError().text());
      return;
    }
    QSqlQuery query(db1);
    query.prepare(QString("SELECT * FROM Theatre where Tname=:Tname"));
    query.bindValue(":Tname", thid);
    query.exec();

    if(query.size()!=0)
    {

    while (query.next())
    {

    r++;
    }

    }
    editableModel = new EditableSqlModel6();
    editableModel->setMYr(r,thid);
    initializeModel(editableModel);
    createView(editableModel);
    if(r>0)
        ui->btnDel->setEnabled(true);
}

void ListTheatreByName::initializeModel(QStandardItemModel *model1)
{
    QString thid = "";
    thid = ui->cmbTh->currentText();

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
      return;
    }
    QSqlQuery query1(db);
    query1.prepare(QString("SELECT * FROM Theatre where Tname=:Tname"));
    query1.bindValue(":Tname", thid);
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
    model1->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
    model1->setHeaderData(2, Qt::Horizontal, QObject::tr("Address"));
    model1->setHeaderData(3, Qt::Horizontal, QObject::tr("Manager"));
    model1->setHeaderData(4, Qt::Horizontal, QObject::tr("Size"));
    model1->setHeaderData(5, Qt::Horizontal, QObject::tr("Cost"));

}

void ListTheatreByName::createView(QStandardItemModel *model4)
{
    ui->tableView->setModel(model4);
}

void ListTheatreByName::on_btnDel_clicked()
{
    QModelIndexList indexes = ui->tableView->selectionModel()->selectedRows();
    while (!indexes.isEmpty())
    {
        QModelIndex primaryKeyIndex = indexes.last();
        int id = editableModel->data(primaryKeyIndex).toInt();
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
          return;
        }
        QSqlQuery query(db);
        query.prepare("delete from Theatre where id = ?");
        query.addBindValue(id);
        query.exec();
        editableModel->removeRows(indexes.last().row(), 1);
        editableModel->submit();
        indexes.removeLast();
    }

    createView(editableModel);
}
