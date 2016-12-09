#-------------------------------------------------
#
# Project created by QtCreator 2016-12-03T15:18:08
#
#-------------------------------------------------

QT       += core gui\
         sql

QTPLUGIN += QSQLITE

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MovieApp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    register.cpp \
    forgotpwd.cpp \
    resetpwd.cpp \
    admdialog.cpp \
    booktickets.cpp \
    editablesqlmodel.cpp \
    datepopup.cpp \
    addmovie.cpp \
    addmovieshow.cpp \
    addms.cpp \
    addtheatre.cpp \
    listmovie.cpp \
    editablesqlmodel1.cpp \
    listtheatre.cpp \
    editablesqlmodel2.cpp \
    listmovieshow.cpp \
    editablesqlmodel3.cpp \
    listassignmovie.cpp \
    editablesqlmodel4.cpp \
    listbookings.cpp \
    listbookingbyid.cpp \
    listmoviebyrating.cpp \
    editablesqlmodel5.cpp \
    listtheatrebyname.cpp \
    editablesqlmodel6.cpp \
    listmoviebyname.cpp \
    editablesqlmodel7.cpp \
    listmovieshowbytname.cpp \
    editablesqlmodel8.cpp \
    editablesqlmodel9.cpp \
    editablesqlmodel10.cpp \
    editablesqlmodel11.cpp \
    editablesqlmodel12.cpp \
    searchassignmovie.cpp

HEADERS  += mainwindow.h \
    register.h \
    forgotpwd.h \
    resetpwd.h \
    admdialog.h \
    booktickets.h \
    editablesqlmodel.h \
    datepopup.h \
    addmovie.h \
    addmovieshow.h \
    addms.h \
    addtheatre.h \
    listmovie.h \
    editablesqlmodel1.h \
    listtheatre.h \
    editablesqlmodel2.h \
    listmovieshow.h \
    editablesqlmodel3.h \
    listassignmovie.h \
    editablesqlmodel4.h \
    listbookings.h \
    listbookingbyid.h \
    listmoviebyrating.h \
    editablesqlmodel5.h \
    listtheatrebyname.h \
    editablesqlmodel6.h \
    listmoviebyname.h \
    editablesqlmodel7.h \
    listmovieshowbytname.h \
    editablesqlmodel8.h \
    editablesqlmodel9.h \
    editablesqlmodel10.h \
    editablesqlmodel11.h \
    editablesqlmodel12.h \
    searchassignmovie.h

FORMS    += mainwindow.ui \
    register.ui \
    forgotpwd.ui \
    resetpwd.ui \
    admdialog.ui \
    booktickets.ui \
    addmovie.ui \
    addmovieshow.ui \
    addms.ui \
    addtheatre.ui \
    listmovie.ui \
    listtheatre.ui \
    listmovieshow.ui \
    listassignmovie.ui \
    listbookings.ui \
    listbookingbyid.ui \
    listmoviebyrating.ui \
    listtheatrebyname.ui \
    listmoviebyname.ui \
    listmovieshowbytname.ui \
    searchassignmovie.ui
