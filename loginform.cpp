#include "loginform.h"
#include "ui_loginform.h"

#include <QDebug>
#include <QMessageBox>
#include "edbconnection.h"

LoginForm::LoginForm(QDialog *parent) : QDialog(parent), ui(new Ui::LoginForm)
{
    ui->setupUi(this);
    loadStyleSheets();
    user_id = -1;
    ui->loginEdit->setFocus();

    // my: "+38 (ddd) ddd dd dd"
    QRegExp regexPhone("^\\+\\d{1,2}\\s\\(\\d{3}\\)\\s\\d{3}\\s\\d{2}\\s\\d{2}$");
    QValidator *phone_validator = new QRegExpValidator(regexPhone, 0);
    ui->phoneEdit->setValidator(phone_validator);

    // validate username
    QRegExp regexVal("^[\\w_]{6,18}$");
    QValidator *username_validator = new QRegExpValidator(regexVal, 0);
    ui->regLoginEdit->setValidator(username_validator);

    // validate username and password
    QValidator *password_validator = new QRegExpValidator(regexVal, 0);
    ui->regPwdEdit->setValidator(password_validator);

    ui->lastnameEdit->setValidator(new QRegExpValidator(QRegExp("^[a-zA-Z]{3,12}$"), 0));
    ui->nameEdit->setValidator(new QRegExpValidator(QRegExp("^[a-zA-Z]{3,12}$"), 0));

    QObject::connect(this, SIGNAL(checkUser(QString, QString)), EDBconnection::getInstance(), SLOT(checkUser(QString, QString)));
    QObject::connect(EDBconnection::getInstance(), SIGNAL(setUserId(long)), this, SLOT(setUserId(long)));

    QObject::connect(this, SIGNAL(newUser(QString,QString,QString,QString,QString,QString,QString)),
                     EDBconnection::getInstance(), SLOT(newUser(QString,QString,QString,QString,QString,QString,QString)));

    QSettings settings("config.ini", QSettings::IniFormat);
    admin_login = settings.value("admin/login", "").toString();
    admin_pwd  = settings.value("admin/password", "").toString();
    manager_login = settings.value("manager/login", "").toString();
    manager_pwd  = settings.value("manager/password", "").toString();
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::loadStyleSheets(void)
{
    QFile file_imp_field(":/loginform/qss/imp_field.qss");
    file_imp_field.open(QFile::ReadOnly);
    imp_field = QLatin1String(file_imp_field.readAll());

    QFile file_non_imp_field(":/loginform/qss/non_imp_field.qss");
    file_non_imp_field.open(QFile::ReadOnly);
    non_imp_field = QLatin1String(file_non_imp_field.readAll());

    QFile file_error_imp_field(":/loginform/qss/error_imp_field.qss");
    file_error_imp_field.open(QFile::ReadOnly);
    error_imp_field = QLatin1String(file_error_imp_field.readAll());

    QFile file_error_non_imp_field(":/loginform/qss/error_non_imp_field.qss");
    file_error_non_imp_field.open(QFile::ReadOnly);
    error_non_imp_field = QLatin1String(file_error_non_imp_field.readAll());
}

void LoginForm::on_toolBox_currentChanged(int index)
{
    switch(index) {
    case 0 : resize(235,210); break;        // login tab
    case 1 : resize(235,280); break;        // registration tab
    }
}

int LoginForm::on_enterButton_clicked()
{
    qDebug()<<"authorization:";

    // highlighting empty fields on enter
    ui->loginEdit->setStyleSheet("* {background: rgb(255,255,255)}");
    ui->pwdEdit->setStyleSheet("* {background: rgb(255,255,255)}");

    if (ui->loginEdit->text().isEmpty()) {
        qDebug("login is empty\n");
        ui->loginEdit->setStyleSheet("* {background: rgb(240,0,0,80)}");
        ui->loginEdit->setFocus();
        return -1;
    }

    if (ui->pwdEdit->text().isEmpty()) {
        qDebug("password is empty\n");
        ui->pwdEdit->setStyleSheet("* {background: rgb(240,0,0,80)}");
        ui->pwdEdit->setFocus();
        return -1;
    }

    QString login = ui->loginEdit->text().trimmed();
    QString pwd  = ui->pwdEdit->text().trimmed();

    int user_type = ui->user_typeCBox->currentIndex() ;
    switch (user_type) {
    case 0 :                                                                                                        // USER
        emit checkUser(login, pwd);
        if (user_id == -1) {
            qDebug("bad login or password\n");
            ui->loginEdit->setStyleSheet("* {background: rgb(240,0,0,80)}");
            ui->pwdEdit->setStyleSheet("* {background: rgb(240,0,0,80)}");
            ui->loginEdit->setFocus();
            return -1;
        } else {
            qDebug("login correct\n");
            emit loginningUser(user_id);
        }
        break;
    case 1 :                                                                                                        // MANAGER
        if (login != manager_login) {
            qDebug("bad manager login\n");
            ui->loginEdit->setStyleSheet("* {background: rgb(240,0,0,80)}");
            ui->loginEdit->setFocus();
            return -1;
        } else if (pwd != manager_pwd) {
            qDebug("bad manager password");
            ui->pwdEdit->setStyleSheet("* {background: rgb(240,0,0,80)}");
            ui->pwdEdit->setFocus();
            return -1;
        } else {
            qDebug("manager connected\n");
            emit loginningManager();
        }
        break;
    case 2 :                                                                                                        // ADMIN
        if (login != admin_login) {
            qDebug("bad admin login\n");
            ui->loginEdit->setStyleSheet("* {background: rgb(240,0,0,80)}");
            ui->loginEdit->setFocus();
            return -1;
        } else if (pwd != admin_pwd) {
            qDebug("bad admin password");
            ui->pwdEdit->setStyleSheet("* {background: rgb(240,0,0,80)}");
            ui->pwdEdit->setFocus();
            return -1;
        } else {
            qDebug("admin connected\n");
            emit loginningAdmin();
        }
        break;
    }
    this->close();
    return 0;
}

int LoginForm::on_registrationButton_clicked()
{
    qDebug()<<"registration:";

    // highlighting empty fields on enter
    ui->regLoginEdit->setStyleSheet(imp_field);
    ui->regPwdEdit->setStyleSheet(imp_field);
    ui->lastnameEdit->setStyleSheet(imp_field);
    ui->nameEdit->setStyleSheet(imp_field);

    ui->emailEdit->setStyleSheet(non_imp_field);

    if (ui->regLoginEdit->text().isEmpty()) {
        qDebug("login is empty\n");
        ui->regLoginEdit->setStyleSheet(error_imp_field);
        ui->regLoginEdit->setFocus();
        return -1;
    }

    if (ui->regPwdEdit->text().isEmpty()) {
        qDebug("password is empty\n");
        ui->regPwdEdit->setStyleSheet(error_imp_field);
        ui->regPwdEdit->setFocus();
        return -1;
    }

    if (ui->lastnameEdit->text().isEmpty()) {
        qDebug("lastname is empty\n");
        ui->lastnameEdit->setStyleSheet(error_imp_field);
        ui->lastnameEdit->setFocus();
        return -1;
    }

    if (ui->nameEdit->text().isEmpty()) {
        qDebug("name is empty\n");
        ui->nameEdit->setStyleSheet(error_imp_field);
        ui->nameEdit->setFocus();
        return -1;
    }
    //
    if (!ui->emailEdit->text().isEmpty()) {
        QRegExp regexEmail("^[-a-z0-9!#$%&'*+/=?^_`{|}~]+"
                           "(?:\\.[-a-z0-9!#$%&'*+/=?^_`{|}~]+)*@(?:[a-z0-9]([-a-z0-9]{0,61}[a-z0-9])?\\.)*"
                           "(?:aero|arpa|asia|biz|cat|com|coop|edu|gov|info|int|jobs|mil|mobi|museum|name|net|org|pro|tel|travel|[a-z][a-z])$");
        QRegExpValidator validator(regexEmail, 0);

        int pos = 0;
        QString email = ui->emailEdit->text();
        if( validator.validate(email, pos) != QValidator::Acceptable ) {
            qDebug("error email format\n");
            ui->emailEdit->setStyleSheet(error_non_imp_field);
            ui->emailEdit->setFocus();
            return -1;
        }
    }
    //
    emit checkUser(ui->regLoginEdit->text());
    if (user_id > 0) {
        qDebug("user with this login is already exist\n");
        ui->regLoginEdit->setStyleSheet(error_imp_field);
        ui->regLoginEdit->setFocus();
        return -1;
    } else {
        qDebug("registration data is correc\n");

        QString login = ui->regLoginEdit->text();
        QString pwd = ui->regPwdEdit->text();
        QString lastname = ui->lastnameEdit->text();
        QString name = ui->nameEdit->text();
        QString address = ui->addressEdit->text();
        QString phone = ui->phoneEdit->text();
        QString email = ui->emailEdit->text();

        emit newUser(login, pwd, lastname, name, address, phone, email);
    }
    return 0;
}

void LoginForm::setUserId(long user_id)
{
    this->user_id = user_id;
}
