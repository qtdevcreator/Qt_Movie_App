#ifndef LISTTHEATREBYNAME_H
#define LISTTHEATREBYNAME_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QStandardItemModel>
#include "editablesqlmodel6.h"

namespace Ui {
class ListTheatreByName;
}

class ListTheatreByName : public QDialog
{
    Q_OBJECT

public:
    explicit ListTheatreByName(QWidget *parent = 0);
    ~ListTheatreByName();

private slots:
    void on_btnList_clicked();

    void on_btnDel_clicked();

private:
    Ui::ListTheatreByName *ui;
    void initializeModel(QStandardItemModel *model1);
    void createView(QStandardItemModel *model4);
    int r;
    EditableSqlModel6 *editableModel;
};

#endif // LISTTHEATREBYNAME_H
