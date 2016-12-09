#ifndef LISTMOVIESHOW_H
#define LISTMOVIESHOW_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QStandardItemModel>
#include "editablesqlmodel3.h"

namespace Ui {
class ListMovieShow;
}

class ListMovieShow : public QDialog
{
    Q_OBJECT

public:
    explicit ListMovieShow(QWidget *parent = 0);
    ~ListMovieShow();

private slots:
    void on_btnDel_clicked();

private:
    Ui::ListMovieShow *ui;
    void initializeModel(QStandardItemModel *model1);
    void createView(QStandardItemModel *model4);
    int r;
    EditableSqlModel3 *editableModel;
};

#endif // LISTMOVIESHOW_H
