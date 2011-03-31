#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QDialog>
#include <QtSql>

namespace Ui {
    class LoginForm;
}

class LoginForm : public QDialog
{
    Q_OBJECT

public:
    explicit LoginForm(QDialog *parent = 0);
    ~LoginForm();

private:
    Ui::LoginForm *ui;
    long user_id;
    QValidator *phone_validator;
    QValidator *username_validator;
    QValidator *password_validator;

    // styles
    QString imp_field;
    QString non_imp_field;
    QString error_imp_field;
    QString error_non_imp_field;

    QString admin_login;
    QString admin_pwd;
    QString manager_login;
    QString manager_pwd  ;

    // private methods
    void loadStyleSheets(void);

private slots:
    int  on_registrationButton_clicked();
    int  on_enterButton_clicked();
    void on_toolBox_currentChanged(int index);

    void setUserId(long);

signals:
    void loginningUser( long );
    void loginningAdmin( void );
    void loginningManager( void );
    void checkUser(const QString login, const QString pwd = "ANY");
    void newUser(QString, QString, QString, QString, QString, QString, QString);
};

#endif // LOGINFORM_H
