#ifndef EDITABLESQLMODEL3_H
#define EDITABLESQLMODEL3_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QStandardItemModel>

class EditableSqlModel3 : public QStandardItemModel
{
    Q_OBJECT

public:
    EditableSqlModel3(QObject *parent = 0);

    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;
    QStandardItemModel* refresh(QStandardItemModel* ,int);
    void setMYr(int);

private:
    EditableSqlModel3 *editableModel;
    int r;
    bool setTheatrename(int personId, const QString &moviename);
    bool setMovie(int personId, const QString &director);
    bool setBookingDt(int personId, const QString &actors);
    bool setShowTime(int personId, const QString &rating);
    bool setNoOfTickets(int personId, const QString &cost);
};


#endif // EDITABLESQLMODEL3_H
