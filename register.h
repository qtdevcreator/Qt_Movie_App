#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QMessageBox>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QRegExp>


namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = 0);
    ~Register();

private slots:
    void on_btnReg_clicked();

private:
    Ui::Register *ui;
    bool Emptychk(QString prm, QString prm1);
    bool validaEmail(QString email);
};

#endif // REGISTER_H
