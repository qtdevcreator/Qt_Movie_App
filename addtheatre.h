#ifndef ADDTHEATRE_H
#define ADDTHEATRE_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QStandardItemModel>
#include <QMessageBox>

namespace Ui {
class AddTheatre;
}

class AddTheatre : public QDialog
{
    Q_OBJECT

public:
    explicit AddTheatre(QWidget *parent = 0);
    ~AddTheatre();

private slots:
    void on_btnAdd_clicked();

private:
    Ui::AddTheatre *ui;
    bool Emptychk(QString prm, QString prm1);
};

#endif // ADDTHEATRE_H
