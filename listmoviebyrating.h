#ifndef LISTMOVIEBYRATING_H
#define LISTMOVIEBYRATING_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QStandardItemModel>
#include "editablesqlmodel5.h"

namespace Ui {
class ListMovieByRating;
}

class ListMovieByRating : public QDialog
{
    Q_OBJECT

public:
    explicit ListMovieByRating(QWidget *parent = 0);
    ~ListMovieByRating();

private slots:
    void on_btnList_clicked();

    void on_btnDel_clicked();

private:
    Ui::ListMovieByRating *ui;
    void initializeModel(QStandardItemModel *model1);
    void createView(QStandardItemModel *model4);
    int r;
    EditableSqlModel5 *editableModel;
};

#endif // LISTMOVIEBYRATING_H
