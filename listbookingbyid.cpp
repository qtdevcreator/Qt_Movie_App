#include "listbookingbyid.h"
#include "ui_listbookingbyid.h"

ListBookingById::ListBookingById(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListBookingById)
{
    ui->setupUi(this);
    this->setModal(true);
    ui->btnList->setStyleSheet("background-color: rgb(233,241,255)");
}

ListBookingById::~ListBookingById()
{
    delete ui;
}

bool ListBookingById::Emptychk(QString prm, QString prm1)
{
    if(prm.isEmpty())
    {
        QMessageBox::warning(this,"List Bookings By Id", "Please enter "+prm1);
        return true;
    }
    else
        return false;
}

void ListBookingById::on_btnList_clicked()
{
    QString rid = ui->edtId->text();
    if(Emptychk(rid, "reservation id"))
    {
        return;
    }
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
    QSqlQueryModel *model = new QSqlQueryModel(this);
    QString sql =QString("SELECT * FROM Booking WHERE " +QString("ID="+rid));

    model->setQuery(sql,db);
    ui->tableView->setModel(model);


}
