#include "addtheatre.h"
#include "ui_addtheatre.h"

AddTheatre::AddTheatre(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTheatre)
{
    ui->setupUi(this);
    this->setModal(true);
    ui->btnAdd->setStyleSheet("background-color: rgb(233,241,255)");

}

AddTheatre::~AddTheatre()
{
    delete ui;
}

bool AddTheatre::Emptychk(QString prm, QString prm1)
{
    if(prm.isEmpty())
    {
        QMessageBox::warning(this,"AddTheatre", "Please enter "+prm1);
        return true;
    }
    else
        return false;
}


void AddTheatre::on_btnAdd_clicked()
{
    QString th = ui->edtTh->text();
    QString addr = ui->edtAddr->toPlainText();
    QString mgr = ui->edtMgr->text();
    QString sz = ui->edtSz->text();
    QString ct = ui->edtCost->text();
    if(Emptychk(th, "theatre name"))
    {
        return;
    }
    else if(Emptychk(addr, "adddress"))
    {
        return;
    }
    else if(Emptychk(mgr, "manager"))
    {
        return;
    }
    else if(Emptychk(sz, "size"))
    {
        return;
    }
    else if(Emptychk(ct, "cost"))
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
    query.prepare(QString("insert into Theatre(Tname,Taddress,Manager,Size,TicketCost) values(:Tname,:Taddress,:Manager,:Size,:TicketCost)"));
    query.bindValue(":Tname", th);
    query.bindValue(":Taddress", addr);
    query.bindValue(":Manager", mgr);
    query.bindValue(":Size", sz);
    query.bindValue(":TicketCost", ct);

    if(query.exec())
    {
        ui->lblStat->setText("Theatre has been successfully added");
    }
    else
    {
        ui->lblStat->setText("Error adding theatre");
    }
}
