#ifndef ADDMOVIESHOW_H
#define ADDMOVIESHOW_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QStandardItemModel>
#include <QMessageBox>
#include "datepopup.h"

namespace Ui {
class AddMovieShow;
}

class AddMovieShow : public QDialog
{
    Q_OBJECT

public:
    explicit AddMovieShow(QWidget *parent = 0);
    ~AddMovieShow();

private slots:
    void on_toolButton_clicked();

    void on_btnAdd_clicked();

private:
    Ui::AddMovieShow *ui;
    bool Emptychk(QString prm, QString prm1);
};

#endif // ADDMOVIESHOW_H
