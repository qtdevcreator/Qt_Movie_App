#include "searchassignmovie.h"
#include "ui_searchassignmovie.h"

SearchAssignMovie::SearchAssignMovie(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchAssignMovie)
{
    ui->setupUi(this);
    this->setModal(true);
    ui->btnSearch->setStyleSheet("background-color: rgb(233,241,255)");
    ui->btnDel->setStyleSheet("background-color: rgb(233,241,255)");
    ui->btnDel->setEnabled(false);
}

SearchAssignMovie::~SearchAssignMovie()
{
    delete ui;
}

void SearchAssignMovie::initializeModel(QStandardItemModel *model1)
{
    QString Mname = ui->edtMov->text();
    QString Tname = ui->edtTh->text();

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
    query.prepare(QString("SELECT * FROM AssignMovie WHERE " +
                          QString("(Moviename LIKE '%" + Mname + "%') AND ") +
                          QString("(Theatrename LIKE '%" + Tname + "%')")));
    query.exec();
    if (query.size()!=0)
    {
        while (query.next())
        {
        r++;
        }
    }

    model1->setRowCount(r);
    model1->setColumnCount(4);
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
    query1.prepare(QString("SELECT * FROM AssignMovie WHERE " +
                           QString("(Moviename LIKE '%" + Mname + "%') AND ") +
                           QString("(Theatrename LIKE '%" + Tname + "%')")));
    query1.exec();

    if(query1.size()!=0)
    {

    while (query1.next())
    {
        for(int c=0;c<=3;c++)
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
    model1->setHeaderData(2, Qt::Horizontal, QObject::tr("Movie"));
    model1->setHeaderData(3, Qt::Horizontal, QObject::tr("AvailableDt"));
}

void SearchAssignMovie::createView(QStandardItemModel *model4)
{
    ui->tableView->setModel(model4);
}



void SearchAssignMovie::on_btnSearch_clicked()
{
     QString Mname = ui->edtMov->text();
     QString Tname = ui->edtTh->text();

     if(Mname == "" && Tname == "")
     {
        QMessageBox::warning(this,"Search Assign Movie", "Please provide search criteria");
        return;
     }

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

         r=0;
         sql1 = QString("SELECT * FROM AssignMovie WHERE " +
                        QString("(Moviename LIKE '%" + Mname + "%') AND ") +
                        QString("(Theatrename LIKE '%" + Tname + "%')"));
         QSqlQuery query(db1);
         query.prepare(sql1);
         query.exec();
         r=query.size();
 //            QString sql = "SELECT * FROM Medicines WHERE Name LIKE '%"+keywd+"%'";
 //            QStandardItemModel *model = new QStandardItemModel();
 //            model->setQuery(sql, db);
 //            ui->tableView->setModel(model);
 //            ui->tableView->show();
         editableModel1 = new EditableSqlModel9();
         initializeModel(editableModel1);
         editableModel1->setQl(sql1);
         editableModel1->setMR1(r);
         createView(editableModel1);
         ui->btnDel->setEnabled(true);


}

void SearchAssignMovie::on_btnDel_clicked()
{
    QModelIndexList indexes = ui->tableView->selectionModel()->selectedRows();
    while (!indexes.isEmpty())
    {
        QModelIndex primaryKeyIndex = indexes.last();
        int id = editableModel1->data(primaryKeyIndex).toInt();
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
        query.prepare("delete from AssignMovie where id = ?");
        query.addBindValue(id);
        query.exec();
        editableModel1->removeRows(indexes.last().row(), 1);
        editableModel1->submit();
        indexes.removeLast();
    }

    createView(editableModel1);
}
