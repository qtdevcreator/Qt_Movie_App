#ifndef ADDMOVIE_H
#define ADDMOVIE_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QStandardItemModel>
#include <QMessageBox>

namespace Ui {
class AddMovie;
}

class AddMovie : public QDialog
{
    Q_OBJECT

public:
    explicit AddMovie(QWidget *parent = 0);
    ~AddMovie();

private slots:
    void on_btnAdd_clicked();

private:
    Ui::AddMovie *ui;
    bool Emptychk(QString prm, QString prm1);
};

#endif // ADDMOVIE_H
