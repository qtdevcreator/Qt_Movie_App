#ifndef EDITABLESQLMODEL1_H
#define EDITABLESQLMODEL1_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QStandardItemModel>

class EditableSqlModel1 : public QStandardItemModel
{
    Q_OBJECT

public:
    EditableSqlModel1(QObject *parent = 0);

    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;
    QStandardItemModel* refresh(QStandardItemModel* ,int);
    void setMYr(int);

private:
    EditableSqlModel1 *editableModel;
    int r;
    bool setMoviename(int personId, const QString &moviename);
    bool setDirector(int personId, const QString &director);
    bool setActor(int personId, const QString &actors);
    bool setRating(int personId, const QString &rating);
};

#endif // EDITABLESQLMODEL1_H
