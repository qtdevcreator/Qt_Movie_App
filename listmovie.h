#ifndef LISTMOVIE_H
#define LISTMOVIE_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QStandardItemModel>
#include "editablesqlmodel1.h"


namespace Ui {
class ListMovie;
}

class ListMovie : public QDialog
{
    Q_OBJECT

public:
    explicit ListMovie(QWidget *parent = 0);
    ~ListMovie();

private slots:
    void on_btnDel_clicked();

private:
    Ui::ListMovie *ui;
    void initializeModel(QStandardItemModel *model1);
    void createView(QStandardItemModel *model4);
    int r;
    EditableSqlModel1 *editableModel;
};

#endif // LISTMOVIE_H
