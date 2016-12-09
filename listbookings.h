#ifndef LISTBOOKINGS_H
#define LISTBOOKINGS_H

#include <QSqlQueryModel>
#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QSqlQueryModel>
#include <QMessageBox>
#include "DatePopup.h"


namespace Ui {
class ListBookings;
}

class ListBookings : public QDialog
{
    Q_OBJECT

public:
    explicit ListBookings(QWidget *parent = 0);
    ~ListBookings();

private slots:
    void on_btnList_clicked();

    void on_toolButton_clicked();

private:
    Ui::ListBookings *ui;
    bool Emptychk(QString prm, QString prm1);
};

#endif // LISTBOOKINGS_H
