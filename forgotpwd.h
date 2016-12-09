#ifndef FORGOTPWD_H
#define FORGOTPWD_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QMessageBox>
#include "resetpwd.h"


namespace Ui {
class ForgotPwd;
}

class ForgotPwd : public QDialog
{
    Q_OBJECT

public:
    explicit ForgotPwd(QWidget *parent = 0);
    ~ForgotPwd();

private slots:
    void on_edtGo_clicked();

private:
    Ui::ForgotPwd *ui;
    ResetPwd *respwd;
    bool bFlg;
};

#endif // FORGOTPWD_H
