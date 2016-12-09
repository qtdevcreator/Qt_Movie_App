#include "addmovieshow.h"
#include "ui_addmovieshow.h"

AddMovieShow::AddMovieShow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMovieShow)
{
    ui->setupUi(this);
    this->setModal(true);
    ui->btnAdd->setStyleSheet("background-color: rgb(233,241,255)");
    ui->toolButton->setStyleSheet("background-color: rgb(233,241,255)");
    ui->edtAdt->setReadOnly(true);
}

AddMovieShow::~AddMovieShow()
{
    delete ui;
}

void AddMovieShow::on_toolButton_clicked()
{
    DatePopup popup;

    int result = popup.exec();
    if(result == QDialog::Accepted){
        QDate date = popup.selectedDate();

        QString sdt = date.toString("dd-MM-yyyy");
        ui->edtAdt->setText(sdt);
    }
}

bool AddMovieShow::Emptychk(QString prm, QString prm1)
{
    if(prm.isEmpty())
    {
        QMessageBox::warning(this,"AssignMovie", "Please enter "+prm1);
        return true;
    }
    else
        return false;
}

void AddMovieShow::on_btnAdd_clicked()
{
    QString movnm = ui->edtMov->text();
    QString th = ui->edtTh->text();
    QString dt = ui->edtAdt->text();

    if(Emptychk(movnm, "movie"))
    {
        return;
    }
    else if(Emptychk(th, "theatre"))
    {
        return;
    }
    else if(Emptychk(dt, "available date"))
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
    query.prepare(QString("insert into AssignMovie(Moviename,Theatrename,AvailDt) values(:Moviename,:Theatrename,:AvailDt)"));
    query.bindValue(":Moviename", movnm);
    query.bindValue(":Theatrename", th);
    query.bindValue(":AvailDt", dt);

    if(query.exec())
    {
        ui->lblStat->setText("Movie Show has been successfully assigned");
    }
    else
    {
        ui->lblStat->setText("Error assigning movie show");
    }

}
