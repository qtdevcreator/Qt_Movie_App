#ifndef DATEPOPUP_H
#define DATEPOPUP_H

#include <QDialog>
#include <QDate>
#include <QCalendarWidget>
#include <QDialogButtonBox>
#include <QVBoxLayout>
//class QCalendarWidget;
//class QDialogButtonBox;
//class QVBoxLayout;

class DatePopup : public QDialog{
    Q_OBJECT
public:
    DatePopup(QWidget *parent=0);
    QDate selectedDate() const;

private:
    QWidget *widget;
    QCalendarWidget *calendarWidget;
    QDialogButtonBox* buttonBox;
    QVBoxLayout *verticalLayout;

};


#endif // DATEPOPUP_H
