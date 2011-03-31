#include "puser.h"
#include "edbconnection.h"

PUser::PUser(long id, QObject *parent) :
    QObject(parent)
{
    QString query = QString("SELECT login, lastname, name, address, phone, email FROM users WHERE id = %1").arg(id);
    QList<QStringList> List = EDBconnection::getInstance()->get(query);
    if (List.isEmpty()) {
        qDebug("error in PUser constructor");
    } else {
        login = List[0].at(0);
        lastname = List[1].at(0);
        name = List[2].at(0);
        address = List[3].at(0);
        phone = List[4].at(0);
        email = List[5].at(0);
    }
}
