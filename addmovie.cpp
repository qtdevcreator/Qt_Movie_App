#include "addmovie.h"
#include "ui_addmovie.h"

AddMovie::AddMovie(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMovie)
{
    ui->setupUi(this);
    this->setModal(true);
    ui->btnAdd->setStyleSheet("background-color: rgb(233,241,255)");
    ui->cmbRating->addItem("Select","Select");
    ui->cmbRating->addItem("1 Star","1 Star");
    ui->cmbRating->addItem("2 Stars","2 Stars");
    ui->cmbRating->addItem("3 Stars","3 Stars");
    ui->cmbRating->addItem("4 Stars","4 Stars");
    ui->cmbRating->addItem("5 Stars","5 Stars");

}

AddMovie::~AddMovie()
{
    delete ui;
}

bool AddMovie::Emptychk(QString prm, QString prm1)
{
    if(prm.isEmpty())
    {
        QMessageBox::warning(this,"AddMovie", "Please enter "+prm1);
        return true;
    }
    else
        return false;
}



void AddMovie::on_btnAdd_clicked()
{
    QString movnm = ui->edtName->text();
    QString act = ui->edtActor->text();
    QString dr = ui->edtDirector->text();
    QString rt = ui->cmbRating->currentText();
    if(Emptychk(movnm, "movie name"))
    {
        return;
    }
    else if(Emptychk(act, "actor"))
    {
        return;
    }
    else if(Emptychk(dr, "director"))
    {
        return;
    }
    else if(rt == "Select")
    {
        QMessageBox::warning(this,"AddMovie", "Please select rating");
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
    query.prepare(QString("insert into Movie(Moviename,Director,Actors,Rating) values(:Moviename,:Director,:Actors,:Rating)"));
    query.bindValue(":Moviename", movnm);
    query.bindValue(":Director", dr);
    query.bindValue(":Actors", act);
    query.bindValue(":Rating", rt);
    if(query.exec())
    {
        ui->lblStat->setText("Movie has been successfully added");
    }
    else
    {
        ui->lblStat->setText("Error adding movie");
    }
}
