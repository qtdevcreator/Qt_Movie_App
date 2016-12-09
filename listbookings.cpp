#include "listbookings.h"
#include "ui_listbookings.h"

ListBookings::ListBookings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListBookings)
{
    ui->setupUi(this);
    this->setModal(true);
    ui->btnList->setStyleSheet("background-color: rgb(233,241,255)");
    ui->cmbShow->addItem("Select","0");
    ui->cmbShow->addItem("Morning Show","Morning Show");
    ui->cmbShow->addItem("Afternoon Show","Afternoon Show");
    ui->cmbShow->addItem("Evening Show","Evening Show");
    ui->cmbShow->addItem("Night Show","Night Show");
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
    ui->cmbTheatre->addItem("Select","0");
    while (query.next())
    {
        QString sv = query.value(0).toString();
        ui->cmbTheatre->addItem(query.value(1).toString(), sv);
    }
}

ListBookings::~ListBookings()
{
    delete ui;
}

bool ListBookings::Emptychk(QString prm, QString prm1)
{
    if(prm.isEmpty())
    {
        QMessageBox::warning(this,"List Booked Tickets", "Please enter "+prm1);
        return true;
    }
    else
        return false;
}

void ListBookings::on_btnList_clicked()
{
    QString shid = ui->cmbShow->currentText();
    int thid = 0;
    QString shdt = ui->edtShowDt->text();
    thid = ui->cmbTheatre->itemData(ui->cmbTheatre->currentIndex()).toInt();
    if(Emptychk(shdt, "show date"))
    {
        return;
    }
    else if(shid == QString("Select"))
    {
        QMessageBox::warning(this,"List Booked Tickets", "Please select show time");
        return;
    }
    else if(thid == 0)
    {
        QMessageBox::warning(this,"List Booked Tickets", "Please select theatre");
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
    QString sql =QString("SELECT * FROM Booking WHERE " +QString("TheatreId='"+QString::number(thid)+"'")+QString(" and Showdt='"+shdt+"'")+QString(" and Showtime='"+shid+"'"));

    model->setQuery(sql,db);
    ui->tableView->setModel(model);


}

void ListBookings::on_toolButton_clicked()
{
    DatePopup popup;

    int result = popup.exec();
    if(result == QDialog::Accepted){
        QDate date = popup.selectedDate();

        QString sdt = date.toString("dd-MM-yyyy");
        ui->edtShowDt->setText(sdt);
    }
}
