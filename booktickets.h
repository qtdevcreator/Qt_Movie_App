#ifndef BOOKTICKETS_H
#define BOOKTICKETS_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QStandardItemModel>
#include "editablesqlmodel.h"
#include <QStringList>
#include <QListWidgetItem>
#include "DatePopup.h"

namespace Ui {
class BookTickets;
}

class BookTickets : public QDialog
{
    Q_OBJECT

public:
    explicit BookTickets(QWidget *parent = 0);
    ~BookTickets();

private slots:

    void on_btnBk_clicked();

    void on_cmbTheatre_currentIndexChanged(int index);

    void on_listWidget_itemChanged(QListWidgetItem *item);

    void on_cmbShow_currentIndexChanged(int index);

    void on_toolButton_clicked();

private:
    Ui::BookTickets *ui;
    QStringList sl;
    QString seatlst;
    int bkseats;
    int tktcost;
    int rsid;
    bool Emptychk(QString prm, QString prm1);
    void initializeModel(QStandardItemModel *model1);
    void createView(QStandardItemModel *model4);
    EditableSqlModel *editableModel;
    void GetSeatNos(int index);
};

#endif // BOOKTICKETS_H
