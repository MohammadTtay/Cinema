#ifndef WELCOME_H
#define WELCOME_H

#include <QMainWindow>

#include<QMouseEvent>

#include<userpage.h>

#include<adminpage.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class Welcome;
}
QT_END_NAMESPACE

class Welcome: public QMainWindow {
    Q_OBJECT

public:
    Welcome(QWidget * parent = nullptr);
    ~Welcome();

private slots:
    void mousePressEvent(QMouseEvent * event);

    void mouseMoveEvent(QMouseEvent * event);

    void on_forgetBtn_clicked();

    void on_closeBtn_clicked();

    void on_ShowpassBtn_pressed();

    void on_ShowpassBtn_released();

    void on_loginBtn_clicked();

    void on_usernameInput_textChanged(const QString & arg1);

    void on_passwordInput_textChanged(const QString & arg1);

    void on_signupBtn_clicked();

private:
    Ui::Welcome * ui;
    UserPage * userpage;
    AdminPage * adminpage;
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
};
#endif // WELCOME_H
