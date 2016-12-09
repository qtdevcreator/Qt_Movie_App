#ifndef EDITABLESQLMODEL9_H
#define EDITABLESQLMODEL9_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QStandardItemModel>

class EditableSqlModel9 : public QStandardItemModel
{
    Q_OBJECT

public:
    EditableSqlModel9(QObject *parent = 0);

    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;
    QStandardItemModel* refresh(QStandardItemModel* ,int);
    void setQl(QString s);
    void setMR1(int c);


private:
    EditableSqlModel9 *editableModel;
    QString sql;
    int r;
    bool setTheatrename(int personId, const QString &moviename);
    bool setMovie(int personId, const QString &director);
    bool setAvailDt(int personId, const QString &actors);
};


#endif // EDITABLESQLMODEL9_H
