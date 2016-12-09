#ifndef EDITABLESQLMODEL8_H
#define EDITABLESQLMODEL8_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QStandardItemModel>

class EditableSqlModel8 : public QStandardItemModel
{
    Q_OBJECT

public:
    EditableSqlModel8(QObject *parent = 0);

    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;
    QStandardItemModel* refresh(QStandardItemModel* ,int);
    void setMYr(int,QString,QString,QString);

private:
    EditableSqlModel8 *editableModel;
    int r;
    QString thid,bdt,shid;
    bool setTheatrename(int personId, const QString &moviename);
    bool setMovie(int personId, const QString &director);
    bool setBookingDt(int personId, const QString &actors);
    bool setShowTime(int personId, const QString &rating);
    bool setNoOfTickets(int personId, const QString &cost);
};

#endif // EDITABLESQLMODEL8_H
