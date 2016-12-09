#include "listmoviebyname.h"
#include "ui_listmoviebyname.h"

ListMovieByName::ListMovieByName(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListMovieByName)
{
    ui->setupUi(this);
    this->setModal(true);
    ui->btnDel->setStyleSheet("background-color: rgb(233,241,255)");
    ui->btnDel->setEnabled(false);
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
    query.prepare(QString("SELECT ID,Moviename FROM Movie"));
    query.exec();
    ui->cmbMov->addItem("Select","0");
    while (query.next())
    {
        QString sv = query.value(0).toString();
        ui->cmbMov->addItem(query.value(1).toString(), sv);
    }
}

ListMovieByName::~ListMovieByName()
{
    delete ui;
}

void ListMovieByName::on_btnList_clicked()
{
    QString thid = "";
    thid = ui->cmbMov->currentText();
    if(thid == "Select")
    {
        QMessageBox::warning(this,"List Movie By Name", "Please select movie");
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
    query.prepare(QString("SELECT * FROM Movie where Moviename=:Moviename"));
    query.bindValue(":Moviename", thid);
    query.exec();

    if(query.size()!=0)
    {

    while (query.next())
    {

    r++;
    }

    }
    editableModel = new EditableSqlModel7();
    editableModel->setMYr(r,thid);
    initializeModel(editableModel);
    createView(editableModel);
    if(r>0)
        ui->btnDel->setEnabled(true);
}

void ListMovieByName::initializeModel(QStandardItemModel *model1)
{
    QString thid = "";
    thid = ui->cmbMov->currentText();

    model1->setRowCount(r);
    model1->setColumnCount(5);
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
    query1.prepare(QString("SELECT * FROM Movie where Moviename=:Moviename"));
    query1.bindValue(":Moviename", thid);
    query1.exec();

    if(query1.size()!=0)
    {

    while (query1.next())
    {
        for(int c=0;c<=4;c++)
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
    model1->setHeaderData(1, Qt::Horizontal, QObject::tr("Movie"));
    model1->setHeaderData(2, Qt::Horizontal, QObject::tr("Director"));
    model1->setHeaderData(3, Qt::Horizontal, QObject::tr("Actor"));
    model1->setHeaderData(4, Qt::Horizontal, QObject::tr("Rating"));


}

void ListMovieByName::createView(QStandardItemModel *model4)
{
    ui->tableView->setModel(model4);
}



void ListMovieByName::on_btnDel_clicked()
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
        query.prepare("delete from Movie where id = ?");
        query.addBindValue(id);
        query.exec();
        editableModel->removeRows(indexes.last().row(), 1);
        editableModel->submit();
        indexes.removeLast();
    }

    createView(editableModel);
}
