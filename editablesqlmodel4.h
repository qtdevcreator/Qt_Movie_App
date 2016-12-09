#ifndef EDITABLESQLMODEL4_H
#define EDITABLESQLMODEL4_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QStandardItemModel>

class EditableSqlModel4 : public QStandardItemModel
{
    Q_OBJECT

public:
    EditableSqlModel4(QObject *parent = 0);

    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;
    QStandardItemModel* refresh(QStandardItemModel* ,int);
    void setMYr(int);

private:
    EditableSqlModel4 *editableModel;
    int r;
    bool setTheatrename(int personId, const QString &moviename);
    bool setMovie(int personId, const QString &director);
    bool setAvailDt(int personId, const QString &actors);
};

#endif // EDITABLESQLMODEL4_H
