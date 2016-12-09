#ifndef EDITABLESQLMODEL5_H
#define EDITABLESQLMODEL5_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QStandardItemModel>

class EditableSqlModel5 : public QStandardItemModel
{
    Q_OBJECT

public:
    EditableSqlModel5(QObject *parent = 0);

    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;
    QStandardItemModel* refresh(QStandardItemModel* ,int);
    void setMYr(int,QString);

private:
    EditableSqlModel5 *editableModel;
    int r;
    QString rt;
    bool setMoviename(int personId, const QString &moviename);
    bool setDirector(int personId, const QString &director);
    bool setActor(int personId, const QString &actors);
    bool setRating(int personId, const QString &rating);
};

#endif // EDITABLESQLMODEL5_H
