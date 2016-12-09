#include "listmovieshowbytname.h"
#include "ui_listmovieshowbytname.h"

ListMovieShowByTName::ListMovieShowByTName(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListMovieShowByTName)
{
    ui->setupUi(this);
    this->setModal(true);
    ui->btnDel->setEnabled(false);
    ui->toolButton->setStyleSheet("background-color: rgb(233,241,255)");
    ui->btnDel->setStyleSheet("background-color: rgb(233,241,255)");
    ui->btnList->setStyleSheet("background-color: rgb(233,241,255)");
    ui->cmbShow->addItem("Select","0");
    ui->cmbShow->addItem("Morning Show","Morning Show");
    ui->cmbShow->addItem("Afternoon Show","Afternoon Show");
    ui->cmbShow->addItem("Evening Show","Evening Show");
    ui->cmbShow->addItem("Night Show","Night Show");
    ui->edtBdt->setReadOnly(true);
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

ListMovieShowByTName::~ListMovieShowByTName()
{
    delete ui;
}

void ListMovieShowByTName::on_btnList_clicked()
{
    QString thid = "";
    thid = ui->cmbTh->currentText();
    QString shid = ui->cmbShow->currentText();
    QString bdt = ui->edtBdt->text();
    if(thid == "Select")
    {
        QMessageBox::warning(this,"List Movie By Theatre", "Please select theatre");
        return;
    }
    else if(bdt == "")
    {
        QMessageBox::warning(this,"List Movie By Theatre", "Please select booking date");
        return;
    }
    else if(shid == "Select")
    {
        QMessageBox::warning(this,"List Movie By Theatre", "Please select show");
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
    query.prepare(QString("SELECT * FROM MovieShow where Theatrename=:Theatrename  and BookingDt=:BookingDt and Showtime=:Showtime"));
    query.bindValue(":Theatrename", thid);
    query.bindValue(":BookingDt", bdt);
    query.bindValue(":Showtime", shid);
    query.exec();

    if(query.size()!=0)
    {

    while (query.next())
    {

    r++;
    }

    }
    editableModel = new EditableSqlModel8();
    editableModel->setMYr(r,thid, bdt, shid);
    initializeModel(editableModel);
    createView(editableModel);
    if(r>0)
        ui->btnDel->setEnabled(true);
}

void ListMovieShowByTName::initializeModel(QStandardItemModel *model1)
{
    QString thid = "";
    thid = ui->cmbTh->currentText();
    QString shid = ui->cmbShow->currentText();
    QString bdt = ui->edtBdt->text();

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
    query1.prepare(QString("SELECT * FROM MovieShow where Theatrename=:Theatrename  and BookingDt=:BookingDt and Showtime=:Showtime"));
    query1.bindValue(":Theatrename", thid);
    query1.bindValue(":BookingDt", bdt);
    query1.bindValue(":Showtime", shid);
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
    model1->setHeaderData(2, Qt::Horizontal, QObject::tr("Movie"));
    model1->setHeaderData(3, Qt::Horizontal, QObject::tr("BookingDt"));
    model1->setHeaderData(4, Qt::Horizontal, QObject::tr("Showtime"));
    model1->setHeaderData(5, Qt::Horizontal, QObject::tr("NoOfTickets"));


}

void ListMovieShowByTName::createView(QStandardItemModel *model4)
{
    ui->tableView->setModel(model4);
}

void ListMovieShowByTName::on_btnDel_clicked()
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
        query.prepare("delete from MovieShow where id = ?");
        query.addBindValue(id);
        query.exec();
        editableModel->removeRows(indexes.last().row(), 1);
        editableModel->submit();
        indexes.removeLast();
    }

    createView(editableModel);
}

void ListMovieShowByTName::on_toolButton_clicked()
{
    DatePopup popup;

    int result = popup.exec();
    if(result == QDialog::Accepted){
        QDate date = popup.selectedDate();

        QString sdt = date.toString("dd-MM-yyyy");
        ui->edtBdt->setText(sdt);
    }
}
