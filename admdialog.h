#ifndef ADMDIALOG_H
#define ADMDIALOG_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QStandardItemModel>
#include <QMessageBox>
#include "booktickets.h"
#include "addmovie.h"
#include "addmovieshow.h"
#include "addms.h"
#include "addtheatre.h"
#include "listmovie.h"
#include "listtheatre.h"
#include "listmovieshow.h"
#include "listassignmovie.h"
#include "listbookings.h"
#include "listbookingbyid.h"
#include "listmoviebyrating.h"
#include "listtheatrebyname.h"
#include "listmoviebyname.h"
#include "listmovieshowbytname.h"
#include "searchassignmovie.h"
#include "editablesqlmodel9.h"
#include "editablesqlmodel10.h"
#include "editablesqlmodel11.h"
#include "editablesqlmodel12.h"


namespace Ui {
class AdmDialog;
}

class AdmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AdmDialog(QWidget *parent = 0);
    ~AdmDialog();

private slots:
    void on_btnAddMov_3_clicked();

    void on_btnAddMov_clicked();

    void on_btnAddMov_2_clicked();

    void on_pushButton_clicked();

    void on_btnAddTh_clicked();

    void on_btnLstMov_clicked();

    void on_btnLstMov_2_clicked();

    void on_btnLstAsMov_2_clicked();

    void on_btnLstAsMov_clicked();

    void on_btnLstMov_3_clicked();

    void on_btnBkById_clicked();

    void on_btnMovRt_clicked();

    void on_btnThByNm_clicked();

    void on_btnMovByNamr_clicked();

    void on_btnLstMov_4_clicked();

    void on_btnGo_clicked();

    void on_btnDelete_clicked();

    void on_btnSrcMov_clicked();

private:
    Ui::AdmDialog *ui;
    bool bFlg;
    bool bFlg1;
    bool bFlg2;
    bool bFlg3;
    bool bFlg4;
    bool bFlg5;
    bool bFlg6;
    bool bFlg7;
    bool bFlg8;
    bool bFlg9;
    bool bFlg10;
    bool bFlg11;
    bool bFlg12;
    bool bFlg13;
    bool bFlg14;
    bool bFlg15;
    BookTickets *bktkt;
    AddMovie *amov;
    AddMovieShow *amovs;
    AddMS *ams;
    AddTheatre *ath;
    ListMovie *lmov;
    ListTheatre *lth;
    ListMovieShow *lms;
    ListAssignMovie *lam;
    ListBookings *lbk;
    ListBookingById *lbkid;
    ListMovieByRating *lmrt;
    ListTheatreByName *ltbn;
    ListMovieByName *lmbn;
    ListMovieShowByTName *lmsbt;
    SearchAssignMovie *sam;

    void initializeModel1(QStandardItemModel *);
    void initializeModel2();
    void initializeModel3(QStandardItemModel *);
    void initializeModel4(QStandardItemModel *);
    void initializeModel5(QStandardItemModel *);
    void createView(QStandardItemModel *model4);
    QString sql1;
    QString sql2;
    QString sql3;
    QString sql4;
    QString sql5;
    int r1;
    int r2;
    int r3;
    int r4;
    int r5;
    EditableSqlModel9 *editableModel1;
    EditableSqlModel10 *editableModel3;
    EditableSqlModel11 *editableModel4;
    EditableSqlModel12 *editableModel5;
};

#endif // ADMDIALOG_H
