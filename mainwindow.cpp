#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    puser = 0;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete puser;
    delete ui;
}

void MainWindow::startP(long user_id)
{
    PUser *puser = new PUser(user_id);
    QString u_lastname = puser->getLastname();
    QString u_name = puser->getName();
    this->setWindowTitle("Пользователь: \""+u_lastname.toUtf8()+" "+u_name+"\"");
    show();
}
