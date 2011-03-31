#ifndef PUSER_H
#define PUSER_H

#include <QObject>

class PUser : public QObject
{
    Q_OBJECT
public:
    explicit PUser(long id, QObject *parent = 0);

    long getUserID(void) const { return id; };
    QString getLogin(void) const { return login; };
    QString getLastname(void) const { return lastname; };
    QString getName(void) const { return name; };
    QString getAddress(void) const { return address; };
    QString getPhone(void) const { return phone; };
    QString getEmail(void) const { return email; };

signals:

public slots:

private:
    long id;
    QString login;
    QString lastname;
    QString name;
    QString address;
    QString phone;
    QString email;
};

#endif // PUSER_H
