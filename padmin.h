#ifndef PADMIN_H
#define PADMIN_H

#include <QMainWindow>

namespace Ui {
    class PAdmin;
}

class PAdmin : public QMainWindow
{
    Q_OBJECT

public:
    explicit PAdmin(QWidget *parent = 0);
    ~PAdmin();

private:
    Ui::PAdmin *ui;
};

#endif // PADMIN_H
