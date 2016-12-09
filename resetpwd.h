#ifndef RESETPWD_H
#define RESETPWD_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QMessageBox>

namespace Ui {
class ResetPwd;
}

class ResetPwd : public QDialog
{
    Q_OBJECT

public:
    explicit ResetPwd(QWidget *parent = 0,QString seml = "");
    ~ResetPwd();

private slots:
    void on_btnUpd_clicked();

private:
    Ui::ResetPwd *ui;
    QString sem;
};
#endif // RESETPWD_H
