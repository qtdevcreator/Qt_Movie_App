#include "forgotpwd.h"
#include "ui_forgotpwd.h"

ForgotPwd::ForgotPwd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ForgotPwd)
{
    ui->setupUi(this);
    this->setModal(true);
    ui->edtGo->setStyleSheet("background-color: rgb(233,241,255)");
    bFlg = false;
}

ForgotPwd::~ForgotPwd()
{
    delete ui;
}

void ForgotPwd::on_edtGo_clicked()
{
    QString em = ui->edtEmail->text();
    if(!em.isEmpty())
    {
//        if(!validaEmail(em))
//        {
//            QMessageBox::warning(this,"Register", "Entered email is invalid");
//            return;
//        }
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
        query.prepare(QString("select stemail from Reg where stemail = :stemail"));
        query.bindValue(":stemail", em);
        query.exec();
        QString sps = "";
        if(query.size()!=0)
        {

        if (query.next())
        {
            sps = query.value(0).toString();
        }
        }
        if (sps!="")
        {
            if(!bFlg || !respwd->isVisible())
            {
                bFlg = true;
                respwd = new ResetPwd(NULL,em);
                respwd->show();
            }
        }
        else
        {
            QMessageBox::warning(this,"Forgot Pwd", "Email does not exist!");
        }
    }
    else
    {
        QMessageBox::warning(this,"Forgot Pwd", "Please enter email");
    }
}
