#include "booktickets.h"
#include "ui_booktickets.h"

BookTickets::BookTickets(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BookTickets)
{
    ui->setupUi(this);
    this->setModal(true);
    bkseats = 0;
    tktcost = 0;
    seatlst = "";
    ui->tableView->hide();
    ui->btnBk->setStyleSheet("background-color: rgb(233,241,255)");
    ui->cmbShow->addItem("Select","0");
    ui->cmbShow->addItem("Morning Show","Morning Show");
    ui->cmbShow->addItem("Afternoon Show","Afternoon Show");
    ui->cmbShow->addItem("Evening Show","Evening Show");
    ui->cmbShow->addItem("Night Show","Night Show");
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
    }
    else
    {
        QSqlQuery query(db);
        query.prepare(QString("SELECT ID,Tname FROM Theatre"));
        query.exec();
        ui->cmbTheatre->addItem("Select","0");
        while (query.next())
        {
            QString sv = query.value(0).toString();
            ui->cmbTheatre->addItem(query.value(1).toString(), sv);
        }
    }
    ui->edtCostPerTkt->setReadOnly(true);
    ui->edtTktCost->setReadOnly(true);
    ui->edtShowDt->setReadOnly(true);
}

BookTickets::~BookTickets()
{
    delete ui;
}

bool BookTickets::Emptychk(QString prm, QString prm1)
{
    if(prm.isEmpty())
    {
        QMessageBox::warning(this,"Book Tickets", "Please enter "+prm1);
        return true;
    }
    else
        return false;
}

void BookTickets::on_btnBk_clicked()
{
    QString fname = ui->edtFname->text();
    QString mname = ui->edtMname->text();
    QString lname = ui->edtLname->text();
    QString shdt = ui->edtShowDt->text();

    QString shid = ui->cmbShow->currentText();
    int thid = 0;
    QString th = "0";

    thid = ui->cmbTheatre->itemData(ui->cmbTheatre->currentIndex()).toInt();
    QString cptkt = ui->edtCostPerTkt->text();
    QString tkc = ui->edtTktCost->text();

    if(Emptychk(fname, "first name"))
    {
        return;
    }
    else if(Emptychk(mname, "middle name"))
    {
        return;
    }
    else if(Emptychk(lname, "last name"))
    {
        return;
    }
    else if(Emptychk(shdt, "show date"))
    {
        return;
    }
    else if(shid == QString("Select"))
    {
        QMessageBox::warning(this,"Book Tickets", "Please select show time");
        return;
    }
    else if(thid == 0)
    {
        QMessageBox::warning(this,"Book Tickets", "Please select theatre");
        return;
    }
    else if(tkc == QString("0"))
    {
        QMessageBox::warning(this,"Book Tickets", "Please select tickets");
        return;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:\\QT_551\\MovieApp\\onlmovie.db");
    bool ok = db.open();
    if (!ok)
    {
      QMessageBox::critical(0, QObject::tr("Database Error"),
                db.lastError().text());
    }
    else
    {
        int notkt = tkc.toInt() / cptkt.toInt();
        QSqlQuery query(db);
        query.prepare(QString("insert into Booking(Uname,Mname,Lname,Showdt,Showtime,TheatreId,Cost,Seatno,Nooftickets) values(:Uname,:Mname,:Lname,:Showdt,:Showtime,:TheatreId,:Cost,:Seatno,:Nooftickets)"));
        query.bindValue(":Uname", fname);
        query.bindValue(":Mname", mname);
        query.bindValue(":Lname", lname);
        query.bindValue(":Showdt", shdt);
        query.bindValue(":Showtime", shid);
        query.bindValue(":TheatreId", thid);
        query.bindValue(":Cost", tkc);
        query.bindValue(":Seatno", seatlst);
        query.bindValue(":Nooftickets", notkt);
        if(query.exec())
        {
            ui->lblStat->setText("Tickets are successfully booked");
        }
        else
        {
            ui->lblStat->setText("Error booking tickets");
        }
        ui->listWidget->clear();
        ui->listWidget->hide();
        editableModel = new EditableSqlModel();
        initializeModel(editableModel);
        createView(editableModel);
    }
}

void BookTickets::initializeModel(QStandardItemModel *model1)
{
    model1->setRowCount(9);
    model1->setColumnCount(2);
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
    }
    else
    {
    QSqlQuery query2(db);
    query2.prepare(QString("SELECT MAX(ID) FROM Booking"));
    query2.exec();
    rsid = 0;
    while (query2.next())
    {
        rsid = query2.value(0).toString().toInt();
    }
    QStandardItem* item1 = new QStandardItem(QString("ReservId"));
    model1->setItem(0, 0, item1);
    QStandardItem* item2 = new QStandardItem(QString::number(rsid));
    model1->setItem(0, 1, item2);

    int row=1;
    QSqlQuery query1(db);
    query1.prepare(QString("SELECT * FROM Booking WHERE ID=:ID"));
    query1.bindValue(":ID", rsid);
    query1.exec();
    QStringList snolst;
    while (query1.next())
    {
        QString fn = query1.value(1).toString();
        QString mn = query1.value(2).toString();
        QString ln = query1.value(3).toString();
        QString sd = query1.value(4).toString();
        QString st = query1.value(5).toString();
        QString nt = query1.value(6).toString();
        QString sn = query1.value(7).toString();
        QString ct = query1.value(8).toString();

        QStandardItem* item3 = new QStandardItem(QString("FirstNm"));
        model1->setItem(1, 0, item3);

        QStandardItem* item4 = new QStandardItem(fn);
        model1->setItem(1, 1, item4);

        QStandardItem* item5 = new QStandardItem(QString("MiddleNm"));
        model1->setItem(2, 0, item5);

        QStandardItem* item6 = new QStandardItem(mn);
        model1->setItem(2, 1, item6);

        QStandardItem* item7 = new QStandardItem(QString("LastNm"));
        model1->setItem(3, 0, item7);

        QStandardItem* item8 = new QStandardItem(ln);
        model1->setItem(3, 1, item8);

        QStandardItem* item9 = new QStandardItem(QString("ShowDt"));
        model1->setItem(4, 0, item9);

        QStandardItem* item10 = new QStandardItem(sd);
        model1->setItem(4, 1, item10);

        QStandardItem* item11 = new QStandardItem(QString("ShowTm"));
        model1->setItem(5, 0, item11);

        QStandardItem* item12 = new QStandardItem(st);
        model1->setItem(5, 1, item12);

        QStandardItem* item13 = new QStandardItem(QString("NoOfTkts"));
        model1->setItem(6, 0, item13);

        QStandardItem* item14 = new QStandardItem(nt);
        model1->setItem(6, 1, item14);

        QStandardItem* item15 = new QStandardItem(QString("SeatNo"));
        model1->setItem(7, 0, item15);

        QStandardItem* item16 = new QStandardItem(sn);
        model1->setItem(7, 1, item16);

        QStandardItem* item17 = new QStandardItem(QString("Cost"));
        model1->setItem(8, 0, item17);

        QStandardItem* item18 = new QStandardItem(ct);
        model1->setItem(8, 1, item18);
    }
    }
}

void BookTickets::createView(QStandardItemModel *model4)
{
    ui->tableView->setModel(model4);
    ui->tableView->show();
}

void BookTickets::on_cmbTheatre_currentIndexChanged(int index)
{
    GetSeatNos(index);
}

void BookTickets::on_listWidget_itemChanged(QListWidgetItem *item)
{

    QString ct = item->text();


    if(item->checkState() == Qt::Checked)
    {
        bkseats++;
        seatlst = seatlst + ct + QString(", ");
    }
    else if(item->checkState() == Qt::Unchecked)
    {
        if(bkseats > 0)
        {
            bkseats--;
            QString sd = ct + QString(", ");
            seatlst.replace(sd, "");
        }
    }

    int tc = bkseats * tktcost;
    ui->edtTktCost->setText(QString::number(tc));
}

void BookTickets::on_cmbShow_currentIndexChanged(int index)
{
    GetSeatNos(ui->cmbTheatre->currentIndex());
}

void BookTickets::on_toolButton_clicked()
{
    DatePopup popup;

    int result = popup.exec();
    if(result == QDialog::Accepted){
        QDate date = popup.selectedDate();

        QString sdt = date.toString("dd-MM-yyyy");
        ui->listWidget->clear();
        ui->edtShowDt->setText(sdt);
    }
    GetSeatNos(ui->cmbTheatre->currentIndex());
}

void BookTickets::GetSeatNos(int index)
{
    QString shid = ui->cmbShow->currentText();
    int thid = 0;
    QString th = "0";
    QString shdt = ui->edtShowDt->text();

    if(index>0 && shid != "Select" && shdt != "")
    {
        thid = ui->cmbTheatre->itemData(index).toInt();

    int seatcnt = 0;
    //QMessageBox::warning(this,"Exp", QString::number(thid));
    //QMessageBox::warning(this,"Exp",th);
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
    }
    else
    {
        QSqlQuery query(db);
        query.prepare(QString("SELECT * FROM Theatre where ID=:ID"));
        query.bindValue(":ID", thid);
        query.exec();
        while (query.next())
        {
            seatcnt = query.value(4).toString().toInt();
            tktcost = query.value(5).toString().toInt();
        }
        ui->edtCostPerTkt->setText(QString::number(tktcost));
        QSqlQuery query1(db);
        query1.prepare(QString("SELECT * FROM Booking WHERE TheatreId=:TheatreId and Showdt=:Showdt and Showtime=:Showtime"));
        query1.bindValue(":TheatreId", thid);
        query1.bindValue(":Showdt", shdt);
        query1.bindValue(":Showtime", shid);
        query1.exec();
        QStringList snolst;
        snolst.clear();
        ui->listWidget->clear();
        while (query1.next())
        {
            QString seatnos = query1.value(7).toString();
            QStringList snolst1 = seatnos.split(", ");
            snolst.append(snolst1);
        }
        int availseats=0;
        for(int i=1;i<=seatcnt;i++)
        {
            if(!snolst.contains(QString::number(i)))
            {
                availseats++;
                QListWidgetItem *listItem = new QListWidgetItem(QString::number(i),ui->listWidget);
                listItem->setCheckState(Qt::Unchecked);
                ui->listWidget->addItem(listItem);
            }
        }
        if(availseats==0)
        {
            ui->lblStat->setText("House Full");
        }
    }
    }
    else
    {
        ui->listWidget->clear();
    }
}
