#ifndef ADDMS_H
#define ADDMS_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QStandardItemModel>
#include <QMessageBox>
#include "datepopup.h"

namespace Ui {
class AddMS;
}

class AddMS : public QDialog
{
    Q_OBJECT

public:
    explicit AddMS(QWidget *parent = 0);
    ~AddMS();

private slots:
    void on_btnAdd_clicked();

    void on_toolButton_clicked();

private:
    Ui::AddMS *ui;
    bool Emptychk(QString prm, QString prm1);
};

#endif // ADDMS_H
