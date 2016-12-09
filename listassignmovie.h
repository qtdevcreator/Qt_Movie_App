#ifndef LISTASSIGNMOVIE_H
#define LISTASSIGNMOVIE_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QStandardItemModel>
#include "editablesqlmodel4.h"


namespace Ui {
class ListAssignMovie;
}

class ListAssignMovie : public QDialog
{
    Q_OBJECT

public:
    explicit ListAssignMovie(QWidget *parent = 0);
    ~ListAssignMovie();

private slots:
    void on_btnDel_clicked();

private:
    Ui::ListAssignMovie *ui;
    void initializeModel(QStandardItemModel *model1);
    void createView(QStandardItemModel *model4);
    int r;
    EditableSqlModel4 *editableModel;
};

#endif // LISTASSIGNMOVIE_H
