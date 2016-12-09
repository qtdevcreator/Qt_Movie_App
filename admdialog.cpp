#include "admdialog.h"
#include "ui_admdialog.h"

AdmDialog::AdmDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdmDialog)
{
    ui->setupUi(this);
    this->setModal(true);
    bFlg = false;
    bFlg1 = false;
    bFlg2 = false;
    bFlg3 = false;
    bFlg4 = false;
    bFlg5 = false;
    bFlg6 = false;
    bFlg7 = false;
    bFlg8 = false;
    bFlg9 = false;
    bFlg10 = false;
    bFlg11 = false;
    bFlg12 = false;
    bFlg13 = false;
    bFlg14 = false;
    bFlg15 = false;
    ui->cmbCat->addItem("Select", "0");
    ui->cmbCat->addItem("AssignMovie", "AssignMovie");
    ui->cmbCat->addItem("Booking", "Booking");
    ui->cmbCat->addItem("Movie", "Movie");
    ui->cmbCat->addItem("MovieShow", "MovieShow");
    ui->cmbCat->addItem("Theatre", "Theatre");
}

AdmDialog::~AdmDialog()
{
    delete ui;
}

void AdmDialog::on_btnAddMov_3_clicked()
{
    if(!bFlg || !bktkt->isVisible())
    {
        bFlg = true;
        bktkt = new BookTickets();
        bktkt->show();
    }
}

void AdmDialog::on_btnAddMov_clicked()
{
    if(!bFlg1 || !amov->isVisible())
    {
        bFlg1 = true;
        amov = new AddMovie();
        amov->show();
    }
}

void AdmDialog::on_btnAddMov_2_clicked()
{
    if(!bFlg3 || !ams->isVisible())
    {
        bFlg3 = true;
        ams = new AddMS();
        ams->show();
    }
}

void AdmDialog::on_pushButton_clicked()
{
    if(!bFlg2 || !amovs->isVisible())
    {
        bFlg2 = true;
        amovs = new AddMovieShow();
        amovs->show();
    }
}

void AdmDialog::on_btnAddTh_clicked()
{
    if(!bFlg4 || !ath->isVisible())
    {
        bFlg4 = true;
        ath = new AddTheatre();
        ath->show();
    }
}

void AdmDialog::on_btnLstMov_clicked()
{
    if(!bFlg5 || !lmov->isVisible())
    {
        bFlg5 = true;
        lmov = new ListMovie();
        lmov->show();
    }
}

void AdmDialog::on_btnLstMov_2_clicked()
{
    if(!bFlg6 || !lth->isVisible())
    {
        bFlg6 = true;
        lth = new ListTheatre();
        lth->show();
    }
}

void AdmDialog::on_btnLstAsMov_2_clicked()
{
    if(!bFlg7 || !lms->isVisible())
    {
        bFlg7 = true;
        lms = new ListMovieShow();
        lms->show();
    }
}

void AdmDialog::on_btnLstAsMov_clicked()
{
    if(!bFlg8 || !lam->isVisible())
    {
        bFlg8 = true;
        lam = new ListAssignMovie();
        lam->show();
    }
}

void AdmDialog::on_btnLstMov_3_clicked()
{
    if(!bFlg9 || !lbk->isVisible())
    {
        bFlg9 = true;
        lbk = new ListBookings();
        lbk->show();
    }
}

void AdmDialog::on_btnBkById_clicked()
{
    if(!bFlg10 || !lbkid->isVisible())
    {
        bFlg10 = true;
        lbkid = new ListBookingById();
        lbkid->show();
    }
}

void AdmDialog::on_btnMovRt_clicked()
{
    if(!bFlg11 || !lmrt->isVisible())
    {
        bFlg11 = true;
        lmrt = new ListMovieByRating();
        lmrt->show();
    }
}

void AdmDialog::on_btnThByNm_clicked()
{
    if(!bFlg12 || !ltbn->isVisible())
    {
        bFlg12= true;
        ltbn = new ListTheatreByName();
        ltbn->show();
    }
}

void AdmDialog::on_btnMovByNamr_clicked()
{
    if(!bFlg13 || !lmbn->isVisible())
    {
        bFlg13= true;
        lmbn = new ListMovieByName();
        lmbn->show();
    }
}

void AdmDialog::on_btnLstMov_4_clicked()
{
    if(!bFlg14 || !lmsbt->isVisible())
    {
        bFlg14= true;
        lmsbt = new ListMovieShowByTName();
        lmsbt->show();
    }
}

void AdmDialog::on_btnGo_clicked()
{
    QString keyword = ui->edtKeword->text();
    QString cat = ui->cmbCat->currentText();
    if(keyword == "")
    {
        QMessageBox::warning(this,"Search", "Please enter keyword");
        return;
    }
    else if(cat == "Select")
    {
        QMessageBox::warning(this,"Search", "Please select category");
        return;
    }

    QSqlDatabase db1 = QSqlDatabase::addDatabase("QSQLITE");
    db1.setHostName("localhost");
    db1.setDatabaseName("D:\\QT_551\\MovieApp\\onlmovie.db");
    db1.setUserName("root");
    db1.setPassword("root");
    bool ok1 = db1.open();
    if (!ok1)
    {
      QMessageBox::critical(0, QObject::tr("Database Error"),
                db1.lastError().text());
      return;
    }
    if(cat == "AssignMovie")
    {
        r1=0;
        sql1 = QString("SELECT * FROM AssignMovie WHERE " +
                            QString("(Moviename LIKE '%" + keyword + "%') OR ") +
                            QString("(Theatrename LIKE '%" + keyword + "%')"));
        QSqlQuery query(db1);
        query.prepare(sql1);
        query.exec();
        r1=query.size();
//            QString sql = "SELECT * FROM Medicines WHERE Name LIKE '%"+keywd+"%'";
//            QStandardItemModel *model = new QStandardItemModel();
//            model->setQuery(sql, db);
//            ui->tableView->setModel(model);
//            ui->tableView->show();
        editableModel1 = new EditableSqlModel9();
        initializeModel1(editableModel1);
        editableModel1->setQl(sql1);
        editableModel1->setMR1(r1);
        createView(editableModel1);
        ui->btnDelete->setEnabled(true);
    }
    else if(cat == "Booking")
    {
        sql2 = QString("SELECT * FROM Booking WHERE " +
                            QString("(Uname LIKE '%" + keyword + "%') OR ") +
                            QString("(Mname LIKE '%" + keyword + "%') OR ") +
                            QString("(Lname LIKE '%" + keyword + "%')"));
        initializeModel2();
        ui->btnDelete->setEnabled(false);
    }
    else if(cat == "Movie")
    {
        r3=0;
        sql3 = QString("SELECT * FROM Movie WHERE " +
                QString("Moviename LIKE '%" + keyword + "%'"));
        QSqlQuery query(db1);
        query.prepare(sql3);
        query.exec();
        r3=query.size();
        editableModel3 = new EditableSqlModel10();
        initializeModel3(editableModel3);
        editableModel3->setQl(sql3);
        editableModel3->setMR1(r3);
        createView(editableModel3);
        ui->btnDelete->setEnabled(true);
    }
    else if(cat == "MovieShow")
    {
        r4=0;
        sql4 = QString("SELECT * FROM MovieShow WHERE " +
                       QString("(Theatrename LIKE '%" + keyword + "%') OR ") +
                       QString("(Moviename LIKE '%" + keyword + "%')"));
        QSqlQuery query(db1);
        query.prepare(sql4);
        query.exec();
        r4=query.size();
        editableModel4 = new EditableSqlModel11();
        initializeModel4(editableModel4);
        editableModel4->setQl(sql4);
        editableModel4->setMR1(r4);
        createView(editableModel4);
        ui->btnDelete->setEnabled(true);
    }
    else if(cat == "Theatre")
    {
        r5=0;
        sql5 = QString("SELECT * FROM Theatre WHERE Tname LIKE '%" + keyword + "%'");
        QSqlQuery query(db1);
        query.prepare(sql5);
        query.exec();
        r5=query.size();
        editableModel5 = new EditableSqlModel12();
        initializeModel5(editableModel5);
        editableModel5->setQl(sql5);
        editableModel5->setMR1(r5);
        createView(editableModel5);
        ui->btnDelete->setEnabled(true);
    }

}

void AdmDialog::createView(QStandardItemModel *model4)
{
    ui->tableView->setModel(model4);
    ui->tableView->show();
}

void AdmDialog::initializeModel1(QStandardItemModel *model1)
{
    model1->setRowCount(r1);
    model1->setColumnCount(4);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName("D:\\QT_551\\MovieApp\\onlmovie.db");
    db.setUserName("root");
    db.setPassword("root");
    bool ok = db.open();
    if (!ok)
    {
      QMessageBox::critical(0, QObject::tr("Database Error"),
                db.lastError().text());
      return;
    }
    QSqlQuery query1(db);
    query1.prepare(sql1);
    query1.exec();
    int row = 0;
    if(query1.size()!=0)
    {

    while (query1.next())
    {
        for(int c=0;c<=3;c++)
        {
        QString sval = query1.value(c).toString();

        QStandardItem* item = new QStandardItem(sval);
        model1->setItem(row, c, item);

        }
    row++;
    }

    }
    model1->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model1->setHeaderData(1, Qt::Horizontal, QObject::tr("Theatre"));
    model1->setHeaderData(2, Qt::Horizontal, QObject::tr("Movie"));
    model1->setHeaderData(3, Qt::Horizontal, QObject::tr("AvailableDt"));
}

void AdmDialog::initializeModel2()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName("D:\\QT_551\\MovieApp\\onlmovie.db");
    db.setUserName("root");
    db.setPassword("root");
    bool ok = db.open();
    if (!ok)
    {
      QMessageBox::critical(0, QObject::tr("Database Error"),
                db.lastError().text());
      return;
    }
    QSqlQueryModel *model = new QSqlQueryModel(this);
    //QString sql =QString("SELECT * FROM Booking WHERE " +QString("TheatreId='"+QString::number(thid)+"'")+QString(" and Showdt='"+shdt+"'")+QString(" and Showtime='"+shid+"'"));

    model->setQuery(sql2,db);
    ui->tableView->setModel(model);

}


void AdmDialog::initializeModel3(QStandardItemModel *model1)
{
    model1->setRowCount(r3);
    model1->setColumnCount(5);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName("D:\\QT_551\\MovieApp\\onlmovie.db");
    db.setUserName("root");
    db.setPassword("root");
    bool ok = db.open();
    if (!ok)
    {
      QMessageBox::critical(0, QObject::tr("Database Error"),
                db.lastError().text());
      return;
    }
    QSqlQuery query1(db);
    query1.prepare(sql3);
    query1.exec();
    int row = 0;
    if(query1.size()!=0)
    {

    while (query1.next())
    {
        for(int c=0;c<=4;c++)
        {
        QString sval = query1.value(c).toString();

        QStandardItem* item = new QStandardItem(sval);
        model1->setItem(row, c, item);

        }
    row++;
    }

    }
    model1->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model1->setHeaderData(1, Qt::Horizontal, QObject::tr("Movie"));
    model1->setHeaderData(2, Qt::Horizontal, QObject::tr("Director"));
    model1->setHeaderData(3, Qt::Horizontal, QObject::tr("Actor"));
    model1->setHeaderData(4, Qt::Horizontal, QObject::tr("Rating"));
}

void AdmDialog::initializeModel4(QStandardItemModel *model1)
{
    model1->setRowCount(r4);
    model1->setColumnCount(6);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName("D:\\QT_551\\MovieApp\\onlmovie.db");
    db.setUserName("root");
    db.setPassword("root");
    bool ok = db.open();
    if (!ok)
    {
      QMessageBox::critical(0, QObject::tr("Database Error"),
                db.lastError().text());
      return;
    }
    QSqlQuery query1(db);
    query1.prepare(sql4);
    query1.exec();
    int row = 0;
    if(query1.size()!=0)
    {

    while (query1.next())
    {
        for(int c=0;c<=5;c++)
        {
        QString sval = query1.value(c).toString();

        QStandardItem* item = new QStandardItem(sval);
        model1->setItem(row, c, item);

        }
    row++;
    }

    }
    model1->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model1->setHeaderData(1, Qt::Horizontal, QObject::tr("Theatre"));
    model1->setHeaderData(2, Qt::Horizontal, QObject::tr("Movie"));
    model1->setHeaderData(3, Qt::Horizontal, QObject::tr("BookingDt"));
    model1->setHeaderData(4, Qt::Horizontal, QObject::tr("Showtime"));
    model1->setHeaderData(5, Qt::Horizontal, QObject::tr("NoOfTickets"));

}

void AdmDialog::initializeModel5(QStandardItemModel *model1)
{
    model1->setRowCount(r5);
    model1->setColumnCount(6);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName("D:\\QT_551\\MovieApp\\onlmovie.db");
    db.setUserName("root");
    db.setPassword("root");
    bool ok = db.open();
    if (!ok)
    {
      QMessageBox::critical(0, QObject::tr("Database Error"),
                db.lastError().text());
      return;
    }
    QSqlQuery query1(db);
    query1.prepare(sql5);
    query1.exec();
    int row = 0;
    if(query1.size()!=0)
    {

    while (query1.next())
    {
        for(int c=0;c<=5;c++)
        {
        QString sval = query1.value(c).toString();

        QStandardItem* item = new QStandardItem(sval);
        model1->setItem(row, c, item);

        }
    row++;
    }

    }
    model1->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model1->setHeaderData(1, Qt::Horizontal, QObject::tr("Theatre"));
    model1->setHeaderData(2, Qt::Horizontal, QObject::tr("Address"));
    model1->setHeaderData(3, Qt::Horizontal, QObject::tr("Manager"));
    model1->setHeaderData(4, Qt::Horizontal, QObject::tr("Size"));
    model1->setHeaderData(5, Qt::Horizontal, QObject::tr("Cost"));
}



void AdmDialog::on_btnDelete_clicked()
{
    QString cat = ui->cmbCat->currentText();
    QModelIndexList indexes = ui->tableView->selectionModel()->selectedRows();
    while (!indexes.isEmpty())
    {
        QModelIndex primaryKeyIndex = indexes.last();
        int id = 0;
        if(cat == "AssignMovie")
        {
            id = editableModel1->data(primaryKeyIndex).toInt();
        }
        else if(cat == "Movie")
        {
            id = editableModel3->data(primaryKeyIndex).toInt();
        }
        else if(cat == "MovieShow")
        {
            id = editableModel4->data(primaryKeyIndex).toInt();
        }
        else if(cat == "Theatre")
        {
            id = editableModel5->data(primaryKeyIndex).toInt();
        }
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setHostName("localhost");
        db.setDatabaseName("D:\\QT_551\\Test3\\onlmedicine.db");
        db.setUserName("root");
        db.setPassword("root");
        bool ok = db.open();
        if (!ok)
        {
          QMessageBox::critical(0, QObject::tr("Database Error"),
                    db.lastError().text());
          return;
        }
        QString s1 = "";
        if(cat == "AssignMovie")
        {
            s1 = "delete from AssignMovie where id = ?";
        }
        else if(cat == "Movie")
        {
            s1 = "delete from Movie where id = ?";
        }
        else if(cat == "MovieShow")
        {
            s1 = "delete from MovieShow where id = ?";
        }
        else if(cat == "Theatre")
        {
            s1 = "delete from Theatre where id = ?";
        }

        QSqlQuery query(db);
        query.prepare(s1);
        query.addBindValue(id);
        query.exec();
        //editableModel->beginRemoveRows(primaryKeyIndex, indexes.last().row(), indexes.last().row()+1);
        if(cat == "AssignMovie")
        {
            editableModel1->removeRows(indexes.last().row(), 1);
        }
        else if(cat == "Movie")
        {
            editableModel3->removeRows(indexes.last().row(), 1);
        }
        else if(cat == "MovieShow")
        {
            editableModel4->removeRows(indexes.last().row(), 1);
        }
        else if(cat == "Theatre")
        {
            editableModel5->removeRows(indexes.last().row(), 1);
        }

        //editableModel->endRemoveRows();

        indexes.removeLast();
    }
    if(cat == "AssignMovie")
    {
        editableModel1->submit();
        createView(editableModel1);
        editableModel1->setMR1(r1);
    }
    else if(cat == "Movie")
    {
        editableModel3->submit();
        createView(editableModel3);
        editableModel3->setMR1(r3);
    }
    else if(cat == "MovieShow")
    {
        editableModel4->submit();
        createView(editableModel4);
        editableModel4->setMR1(r4);
    }
    else if(cat == "Theatre")
    {
        editableModel5->submit();
        createView(editableModel5);
        editableModel5->setMR1(r5);
    }
}

void AdmDialog::on_btnSrcMov_clicked()
{
    if(!bFlg15 || !sam->isVisible())
    {
        bFlg15= true;
        sam = new SearchAssignMovie();
        sam->show();
    }
}
