#include "resetpwd.h"
#include "ui_resetpwd.h"

ResetPwd::ResetPwd(QWidget *parent,QString seml) :
    QDialog(parent),
    ui(new Ui::ResetPwd)
{
    ui->setupUi(this);
    this->setModal(true);
    sem = seml;
    ui->btnUpd->setStyleSheet("background-color: rgb(233,241,255)");
}

ResetPwd::~ResetPwd()
{
    delete ui;
}

void ResetPwd::on_btnUpd_clicked()
{
    QString pwd = ui->edtPwd->text();
    QString cpwd = ui->edtCpwd->text();
    if(!pwd.isEmpty() && !cpwd.isEmpty())
    {
        if(pwd == cpwd)
        {
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
            query.prepare(QString("update Reg set stpass=:stpass,stcpass=:stcpass where stemail=:stemail"));
            query.bindValue(":stpass", pwd);
            query.bindValue(":stcpass", cpwd);
            query.bindValue(":stemail", sem);
            if(query.exec())
            {
                ui->lblStat->setText("Password has been successfully resetted");
            }
            else
            {
                ui->lblStat->setText("Error resetting password");
            }
        }
        else
        {
            QMessageBox::warning(this,"Reset Pwd", "Passowd & Confirm Password must match");
        }
    }
    else
    {
        QMessageBox::warning(this,"Reset Pwd", "Please enter Passowd/Confirm Password");
    }
}
