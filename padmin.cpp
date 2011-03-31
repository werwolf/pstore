#include "padmin.h"
#include "ui_padmin.h"

PAdmin::PAdmin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PAdmin)
{
    ui->setupUi(this);
}

PAdmin::~PAdmin()
{
    delete ui;
}
