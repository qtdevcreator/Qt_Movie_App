#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bFlg = false;
    bFlg1 = false;
    bFlg2 = false;
    ui->pushButton->setStyleSheet("background-color: rgb(233,241,255)");
    ui->btnRegister->setStyleSheet("background-color: rgb(233,241,255)");
    ui->edtFpwd->setStyleSheet("background-color: rgb(233,241,255)");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnRegister_clicked()
{
    if(!bFlg1 || !regDlg->isVisible())
    {
        bFlg1 = true;
        regDlg = new Register();
        regDlg->show();
    }
}

void MainWindow::on_edtFpwd_clicked()
{
    if(!bFlg2 || !fPwd->isVisible())
    {
        bFlg2 = true;
        fPwd = new ForgotPwd();
        fPwd->show();
    }
}

void MainWindow::on_pushButton_clicked()
{
    QString username = ui->username->text();
    QString password = ui->password->text();
    if(username.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this,"Login", "Please enter Username / password");
        return;
    }
    if(!bFlg /*|| !secDialog1->isVisible()*/)
    {
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
        }
        else
        {
            QSqlQuery query(db);
            query.prepare(QString("select stemail,stpass from Reg where stemail = :stemail and stpass = :stpass"));
            query.bindValue(":stemail", username);
            query.bindValue(":stpass", password);
            query.exec();
            QString unm = "";
            QString pswd = "";
            /*if(db.isOpen())
            {
                db.close();
            }
            QSqlDatabase::removeDatabase("MyDBConnectionName");*/
            QString sus = "";
            QString sps = "";
            if(query.size()!=0)
            {

            if (query.next())
            {
                sus = query.value(0).toString();
                sps = query.value(1).toString();
            }
            }

            if(username == sus && password == sps) {
                bFlg = true;
                ui->label->setText("Welcome!");
                ui->pushButton->setText("Logout");
                ui->label_2->setVisible(false);
                ui->label_3->setVisible(false);
                ui->username->setVisible(false);
                ui->password->setVisible(false);
                ui->btnRegister->setVisible(false);
                ui->edtFpwd->setVisible(false);
                admDialog1 = new AdmDialog();
                admDialog1->show();
            }
            else
            {
                bFlg = false;
                QMessageBox::warning(this,"Login", "Username and password is not correct");
            }
        }
    }
    else
    {
        bFlg = false;
        ui->label->setText("Login Application");
        ui->pushButton->setText("Login");
        ui->label_2->setVisible(true);
        ui->label_3->setVisible(true);
        ui->username->setVisible(true);
        ui->password->setVisible(true);
        ui->btnRegister->setVisible(true);
        ui->edtFpwd->setVisible(true);
        ui->username->setText("");
        ui->password->setText("");
    }
}
