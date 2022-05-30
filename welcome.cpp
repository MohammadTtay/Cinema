#include "welcome.h"

#include "ui_welcome.h"

#include<QMessageBox>

#include<QFileInfo>

#include<QDebug>

Welcome::Welcome(QWidget * parent): QMainWindow(parent), ui(new Ui::Welcome) {
    ui -> setupUi(this);
    this -> setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
}

Welcome::~Welcome() {
    delete ui;
}

void Welcome::mousePressEvent(QMouseEvent * event) {
    m_nMouseClick_X_Coordinate = event -> x();
    m_nMouseClick_Y_Coordinate = event -> y();
}

void Welcome::mouseMoveEvent(QMouseEvent * event) {
    move(event -> globalX() - m_nMouseClick_X_Coordinate, event -> globalY() - m_nMouseClick_Y_Coordinate);
}

void Welcome::on_closeBtn_clicked() {
    this -> close();
}

void Welcome::on_forgetBtn_clicked() {
    QMessageBox::information(this, "بازیابی رمز عبور", "در صورتی که رمز عبور خود را فراموش کرده اید ، نام کاربری خود را به شماره 09215710143 پیامک بفرمایید.");
}

void Welcome::on_ShowpassBtn_pressed() {
    ui -> passwordInput -> setEchoMode(QLineEdit::Normal);
}

void Welcome::on_ShowpassBtn_released() {
    ui -> passwordInput -> setEchoMode(QLineEdit::Password);
}

void Welcome::on_signupBtn_clicked() {
    QString user = ui -> usernameInput -> text();
    QString pass = ui -> passwordInput -> text();
    if (user.isEmpty() || pass.isEmpty()) {
        if (user.isEmpty() && pass.isEmpty()) {
            QMessageBox::warning(this, " ", "لطفا نام کاربری و رمزعبور را وارد نمایید ");

        } else if (user.isEmpty()) {
            QMessageBox::warning(this, " ", "لطفا نام کاربری را وارد نمایید");

        } else if (pass.isEmpty()) {
            QMessageBox::warning(this, " ", "لطفا رمز عبور را وارد نمایید");

        }
    } else if (user == "admin") {
        QMessageBox::critical(this, " ", "نام کاربری تکراری است . لطفا نام کاربری دیگری انتخاب کنید");
    } else {
        QFile file("UP.txt");
        QTextStream in ( & file);
        QTextStream out( & file);
        out.setCodec("UTF-8"); in .setCodec("UTF-8");
        bool flag = true;
        QString temp_user, temp_password;

        if (QFileInfo::exists("UP.txt")) {
            file.open(QFile::ReadWrite | QFile::Text);
            do {
                temp_user = in .readLine();
                temp_password = in .readLine();
                if (temp_user == user) {
                    flag = false;
                    QMessageBox::critical(this, " ", "نام کاربری تکراری است . لطفا نام کاربری دیگری انتخاب کنید");
                }
            } while (!temp_user.isNull());
            if (flag == true) {
                out << "\n" << user << "\n" << pass;
                QMessageBox::information(this, " ", "ثبت نام با موفقیت انجام شد");
                ui -> usernameInput -> clear();
                ui -> passwordInput -> clear();
            }
            file.close();
        } else {
            file.open(QFile::ReadWrite | QFile::Text);
            out << user << "\n" << pass;
            QMessageBox::information(this, " ", "ثبت نام با موفقیت انجام شد");
            ui -> usernameInput -> clear();
            ui -> passwordInput -> clear();

            file.close();
        }
    }
}

void Welcome::on_loginBtn_clicked() {
    QString user = ui -> usernameInput -> text();
    QString pass = ui -> passwordInput -> text();
    if (user.isEmpty() || pass.isEmpty()) {
        if (user.isEmpty() && pass.isEmpty()) {
            QMessageBox::warning(this, " ", "لطفا نام کاربری و رمزعبور را وارد نمایید ");

        } else if (user.isEmpty()) {
            QMessageBox::warning(this, " ", "لطفا نام کاربری را وارد نمایید");

        } else if (pass.isEmpty()) {
            QMessageBox::warning(this, " ", "لطفا رمز عبور را وارد نمایید");

        }
    } else if (user == "admin") {
        if (pass == "admin") { //Go To The Admin Page
            ui -> usernameInput -> clear();
            ui -> passwordInput -> clear();
            this -> close();
            adminpage = new AdminPage(this);
            adminpage -> show();

        } else {
            QMessageBox::critical(this, " ", "رمزعبور اشتباه است");
        }
    } else {
        QFile file("UP.txt");
        if (QFileInfo::exists("UP.txt")) {
            file.open(QFile::ReadWrite | QFile::Text);
            QTextStream in ( & file); in .setCodec("UTF-8");
            bool flag = true;
            QString temp_user, temp_password;
            do {
                temp_user = in .readLine();
                temp_password = in .readLine();
                if (temp_user == user) {
                    flag = false;
                    if (temp_password == pass) { //Go To The User Page
                        ui -> usernameInput -> clear();
                        ui -> passwordInput -> clear();
                        this -> hide();
                        userpage = new UserPage(this, user, pass);
                        userpage -> show();
                        break;
                    } else {
                        QMessageBox::critical(this, " ", "رمزعبور اشتباه است");
                        break;
                    }
                }
            } while (!temp_user.isNull());

            if (flag == true) {
                QMessageBox::critical(this, " ", "نام کاربری وجود ندارد . لطفا ثبت نام کنید");
            }
            file.close();

        } else {
            QMessageBox::critical(this, " ", "نام کاربری وجود ندارد . لطفا ثبت نام کنید");
        }
    }

}

void Welcome::on_usernameInput_textChanged(const QString & arg1) {
    QFont font1("Arial", 14);
    QFont font2("Nazanin", 11);
    if (!arg1.isEmpty()) ui -> usernameInput -> setFont(font1);
    else {
        ui -> usernameInput -> setFont(font2);
    }
}

void Welcome::on_passwordInput_textChanged(const QString & arg1) {
    QFont font1("Arial", 14);
    QFont font2("Nazanin", 11);
    if (!arg1.isEmpty()) ui -> passwordInput -> setFont(font1);
    else {
        ui -> passwordInput -> setFont(font2);
    }
}
