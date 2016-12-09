#ifndef LISTMOVIEBYNAME_H
#define LISTMOVIEBYNAME_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QStandardItemModel>
#include "editablesqlmodel7.h"

namespace Ui {
class ListMovieByName;
}

class ListMovieByName : public QDialog
{
    Q_OBJECT

public:
    explicit ListMovieByName(QWidget *parent = 0);
    ~ListMovieByName();

private slots:
    void on_btnList_clicked();

    void on_btnDel_clicked();

private:
    Ui::ListMovieByName *ui;
    void initializeModel(QStandardItemModel *model1);
    void createView(QStandardItemModel *model4);
    int r;
    EditableSqlModel7 *editableModel;
};

#endif // LISTMOVIEBYNAME_H
