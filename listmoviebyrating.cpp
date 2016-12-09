#include "listmoviebyrating.h"
#include "ui_listmoviebyrating.h"

ListMovieByRating::ListMovieByRating(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListMovieByRating)
{
    ui->setupUi(this);
    this->setModal(true);
    ui->btnDel->setStyleSheet("background-color: rgb(233,241,255)");
    ui->btnDel->setEnabled(false);
    ui->cmbRating->addItem("Select","Select");
    ui->cmbRating->addItem("1 Star","1 Star");
    ui->cmbRating->addItem("2 Stars","2 Stars");
    ui->cmbRating->addItem("3 Stars","3 Stars");
    ui->cmbRating->addItem("4 Stars","4 Stars");
    ui->cmbRating->addItem("5 Stars","5 Stars");

}

ListMovieByRating::~ListMovieByRating()
{
    delete ui;
}

void ListMovieByRating::on_btnList_clicked()
{
    QString rt = ui->cmbRating->currentText();
    if(rt == "Select")
    {
        QMessageBox::warning(this,"List Movie By Rating", "Please select rating");
        return;
    }
    editableModel = new EditableSqlModel5();
    editableModel->setMYr(r,rt);
    initializeModel(editableModel);
    createView(editableModel);
}

void ListMovieByRating::initializeModel(QStandardItemModel *model1)
{
    QString rt = ui->cmbRating->currentText();
    if(rt == "Select")
    {
        QMessageBox::warning(this,"List Movie By Rating", "Please select rating");
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
    query.prepare(QString("SELECT * FROM Movie where Rating=:Rating"));
    query.bindValue(":Rating", rt);
    query.exec();

    if(query.size()!=0)
    {

    while (query.next())
    {

    r++;
    }

    }

    model1->setRowCount(r);
    model1->setColumnCount(5);
    int row = 0;

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName("D:\\QT_551\\MovieApp\\onlmovie.db");
    db.setUserName("root");
    db.setPassword("root");
    ok = db.open();
    if (!ok)
    {
      QMessageBox::critical(0, QObject::tr("Database Error"),
                db.lastError().text());
      return;
    }
    QSqlQuery query1(db);
    query1.prepare(QString("SELECT * FROM Movie where Rating=:Rating"));
    query1.bindValue(":Rating", rt);
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

void ListMovieByRating::createView(QStandardItemModel *model4)
{
    ui->tableView->setModel(model4);
}

void ListMovieByRating::on_btnDel_clicked()
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
