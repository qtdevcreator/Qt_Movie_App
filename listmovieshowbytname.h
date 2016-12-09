#ifndef LISTMOVIESHOWBYTNAME_H
#define LISTMOVIESHOWBYTNAME_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QStandardItemModel>
#include "editablesqlmodel8.h"
#include "datepopup.h"


namespace Ui {
class ListMovieShowByTName;
}

class ListMovieShowByTName : public QDialog
{
    Q_OBJECT

public:
    explicit ListMovieShowByTName(QWidget *parent = 0);
    ~ListMovieShowByTName();

private slots:
    void on_btnList_clicked();

    void on_btnDel_clicked();

    void on_toolButton_clicked();

private:
    Ui::ListMovieShowByTName *ui;
    void initializeModel(QStandardItemModel *model1);
    void createView(QStandardItemModel *model4);
    int r;
    EditableSqlModel8 *editableModel;
};

#endif // LISTMOVIESHOWBYTNAME_H
