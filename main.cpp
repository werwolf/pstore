#include <QtGui/QApplication>
#include "mainwindow.h"
#include "loginform.h"
#include "padmin.h"
#include "pmanager.h"
#include "edbconnection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EDBconnection* m_db;

    try {
        m_db = EDBconnection::getInstance();
    }
    catch (int error) {
        qDebug("error %d (main) when try connect to DB", error);
        return error;
    }
    catch (...) {
        qDebug("unknown error (main) when try connect to DB");
        return 1;
    }

    LoginForm loginform;
//    loginform.show();

    MainWindow w;
    PAdmin padmin;
//    PManager pmanager;
    PManager pmanager;
    pmanager.show();

    QObject::connect(&loginform, SIGNAL(loginningUser( long )), &w, SLOT(startP( long )));
    QObject::connect(&loginform, SIGNAL(loginningAdmin()), &padmin, SLOT(show()));
    QObject::connect(&loginform, SIGNAL(loginningManager()), &pmanager, SLOT(startP()));

    int error = a.exec();
    m_db->destroyInstance();
    return error;
}
