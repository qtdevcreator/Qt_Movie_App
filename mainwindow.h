#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "register.h"
#include "forgotpwd.h"
#include "admdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnRegister_clicked();

    void on_edtFpwd_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Register *regDlg;
    ForgotPwd *fPwd;
    AdmDialog *admDialog1;
    bool bFlg;
    bool bFlg1;
    bool bFlg2;
};

#endif // MAINWINDOW_H
