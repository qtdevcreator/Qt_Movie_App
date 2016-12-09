#ifndef SEARCHASSIGNMOVIE_H
#define SEARCHASSIGNMOVIE_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QStandardItemModel>
#include <QMessageBox>
#include "editablesqlmodel9.h"


namespace Ui {
class SearchAssignMovie;
}

class SearchAssignMovie : public QDialog
{
    Q_OBJECT

public:
    explicit SearchAssignMovie(QWidget *parent = 0);
    ~SearchAssignMovie();

private slots:
    void on_btnSearch_clicked();

    void on_btnDel_clicked();

private:
    Ui::SearchAssignMovie *ui;
    void initializeModel(QStandardItemModel *);
    void createView(QStandardItemModel *model4);
    QString sql1;
    int r;
    EditableSqlModel9 *editableModel1;

};

#endif // SEARCHASSIGNMOVIE_H
