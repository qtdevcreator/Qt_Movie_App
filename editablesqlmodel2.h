#ifndef EDITABLESQLMODEL2_H
#define EDITABLESQLMODEL2_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QStandardItemModel>

class EditableSqlModel2 : public QStandardItemModel
{
    Q_OBJECT

public:
    EditableSqlModel2(QObject *parent = 0);

    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;
    QStandardItemModel* refresh(QStandardItemModel* ,int);
    void setMYr(int);

private:
    EditableSqlModel2 *editableModel;
    int r;
    bool setTheatrename(int personId, const QString &moviename);
    bool setAddress(int personId, const QString &director);
    bool setManager(int personId, const QString &actors);
    bool setSize(int personId, const QString &rating);
    bool setCost(int personId, const QString &cost);
};


#endif // EDITABLESQLMODEL2_H
