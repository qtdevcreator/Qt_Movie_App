#ifndef EDITABLESQLMODEL10_H
#define EDITABLESQLMODEL10_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QStandardItemModel>

class EditableSqlModel10 : public QStandardItemModel
{
    Q_OBJECT

public:
    EditableSqlModel10(QObject *parent = 0);

    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;
    QStandardItemModel* refresh(QStandardItemModel* ,int);
    void setQl(QString s);
    void setMR1(int c);

private:
    EditableSqlModel10 *editableModel;
    int r;
    QString sql;
    bool setMoviename(int personId, const QString &moviename);
    bool setDirector(int personId, const QString &director);
    bool setActor(int personId, const QString &actors);
    bool setRating(int personId, const QString &rating);
};


#endif // EDITABLESQLMODEL10_H
