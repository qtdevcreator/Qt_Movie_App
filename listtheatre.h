#ifndef LISTTHEATRE_H
#define LISTTHEATRE_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QStandardItemModel>
#include "editablesqlmodel2.h"

namespace Ui {
class ListTheatre;
}

class ListTheatre : public QDialog
{
    Q_OBJECT

public:
    explicit ListTheatre(QWidget *parent = 0);
    ~ListTheatre();

private slots:
    void on_btnDel_clicked();

private:
    Ui::ListTheatre *ui;
    void initializeModel(QStandardItemModel *model1);
    void createView(QStandardItemModel *model4);
    int r;
    EditableSqlModel2 *editableModel;
};

#endif // LISTTHEATRE_H
