#ifndef EDITABLESQLMODEL6_H
#define EDITABLESQLMODEL6_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QStandardItemModel>

class EditableSqlModel6 : public QStandardItemModel
{
    Q_OBJECT

public:
    EditableSqlModel6(QObject *parent = 0);

    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;
    QStandardItemModel* refresh(QStandardItemModel* ,int);
    void setMYr(int,QString);

private:
    EditableSqlModel6 *editableModel;
    int r;
    QString thid;
    bool setTheatrename(int personId, const QString &moviename);
    bool setAddress(int personId, const QString &director);
    bool setManager(int personId, const QString &actors);
    bool setSize(int personId, const QString &rating);
    bool setCost(int personId, const QString &cost);
};


#endif // EDITABLESQLMODEL6_H
