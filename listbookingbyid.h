#ifndef LISTBOOKINGBYID_H
#define LISTBOOKINGBYID_H

#include <QSqlQueryModel>
#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QSqlQueryModel>
#include <QMessageBox>


namespace Ui {
class ListBookingById;
}

class ListBookingById : public QDialog
{
    Q_OBJECT

public:
    explicit ListBookingById(QWidget *parent = 0);
    ~ListBookingById();

private slots:
    void on_btnList_clicked();

private:
    Ui::ListBookingById *ui;
    bool Emptychk(QString prm, QString prm1);
};

#endif // LISTBOOKINGBYID_H
