#include "listassignmovie.h"
#include "ui_listassignmovie.h"

ListAssignMovie::ListAssignMovie(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListAssignMovie)
{
    ui->setupUi(this);
    this->setModal(true);
    ui->btnDel->setStyleSheet("background-color: rgb(233,241,255)");
    ui->btnDel->setEnabled(false);
    r=0;
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
    query.prepare(QString("SELECT * FROM AssignMovie"));
    query.exec();
    if (query.size()!=0)
    {
        while (query.next())
        {
        r++;
        }
    }
    editableModel = new EditableSqlModel4();
    editableModel->setMYr(r);
    initializeModel(editableModel);
    createView(editableModel);
    ui->btnDel->setEnabled(true);
}

ListAssignMovie::~ListAssignMovie()
{
    delete ui;
}

void ListAssignMovie::initializeModel(QStandardItemModel *model1)
{
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
    query1.prepare(QString("SELECT * FROM AssignMovie"));
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

void ListAssignMovie::createView(QStandardItemModel *model4)
{
    ui->tableView->setModel(model4);
}



void ListAssignMovie::on_btnDel_clicked()
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
        query.prepare("delete from AssignMovie where id = ?");
        query.addBindValue(id);
        query.exec();
        editableModel->removeRows(indexes.last().row(), 1);
        editableModel->submit();
        indexes.removeLast();
    }

    createView(editableModel);
}
