#include "addms.h"
#include "ui_addms.h"

AddMS::AddMS(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMS)
{
    ui->setupUi(this);
    this->setModal(true);
    ui->btnAdd->setStyleSheet("background-color: rgb(233,241,255)");
    ui->toolButton->setStyleSheet("background-color: rgb(233,241,255)");
    ui->edtBdt->setReadOnly(true);
    ui->cmbShow->addItem("Select","0");
    ui->cmbShow->addItem("Morning Show","Morning Show");
    ui->cmbShow->addItem("Afternoon Show","Afternoon Show");
    ui->cmbShow->addItem("Evening Show","Evening Show");
    ui->cmbShow->addItem("Night Show","Night Show");
    ui->edtNo->setValidator( new QIntValidator);
}

AddMS::~AddMS()
{
    delete ui;
}

bool AddMS::Emptychk(QString prm, QString prm1)
{
    if(prm.isEmpty())
    {
        QMessageBox::warning(this,"AddMovieShow", "Please enter "+prm1);
        return true;
    }
    else
        return false;
}

void AddMS::on_btnAdd_clicked()
{
    QString movnm = ui->edtMov->text();
    QString th = ui->edtTh->text();
    QString bdt = ui->edtBdt->text();
    QString sh = ui->cmbShow->currentText();
    QString no = ui->edtNo->text();
    if(Emptychk(movnm, "movie"))
    {
        return;
    }
    else if(Emptychk(th, "theatre"))
    {
        return;
    }
    else if(Emptychk(bdt, "booking date"))
    {
        return;
    }
    else if(sh == "Select")
    {
        QMessageBox::warning(this,"AddMovieShow", "Please select movie show");
        return;
    }
    else if(Emptychk(no, "no of tickets"))
    {
        return;
    }
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setHostName("localhost");
    db.setDatabaseName("D:\\QT_551\\MovieApp\\onlmovie.db");
    //db.setUserName("root");
    //db.setPassword("root");
    bool ok = db.open();
    if (!ok)
    {
      QMessageBox::critical(0, QObject::tr("Database Error"),
                db.lastError().text());
      return;
    }
    QSqlQuery query(db);
    query.prepare(QString("insert into MovieShow(Theatrename,Moviename,BookingDt,Showtime,Nooftickets) values(:Theatrename,:Moviename,:BookingDt,:Showtime,:Nooftickets)"));
    query.bindValue(":Theatrename", th);
    query.bindValue(":Moviename", movnm);
    query.bindValue(":BookingDt", bdt);
    query.bindValue(":Showtime", sh);
    query.bindValue(":Nooftickets", no);


    if(query.exec())
    {
        ui->lblStat->setText("Movie Show has been successfully added");
    }
    else
    {
        ui->lblStat->setText("Error adding movie show");
    }
}

void AddMS::on_toolButton_clicked()
{
    DatePopup popup;

    int result = popup.exec();
    if(result == QDialog::Accepted){
        QDate date = popup.selectedDate();

        QString sdt = date.toString("dd-MM-yyyy");
        ui->edtBdt->setText(sdt);
    }
}
