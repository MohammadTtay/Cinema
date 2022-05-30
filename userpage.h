#ifndef USERPAGE_H
#define USERPAGE_H

#include <QMainWindow>

#include<QSet>

#include<movie.h>

namespace Ui {
class UserPage;
}

class UserPage: public QMainWindow {
    Q_OBJECT

public:
    explicit UserPage(QMainWindow * welcome, QString username, QString password, QWidget * parent = nullptr);
    ~UserPage();
private slots:
    void Make_Default_List();

    void Set_TableWidget_At_FirstRun();

    void on_closeBtn_clicked();

    void on_minBtn_clicked();

    void on_comboBox_activated(const QString & arg1);

    void on_addButton_clicked();

    void on_delButton_clicked();

    void on_delAllButton_clicked();

    void on_resButton_clicked();

    void on_Serach_lineEdit_textChanged(const QString & arg1);

    void Update_File();

    void on_LogOutBtn_clicked();

private:
    Ui::UserPage * ui;
    QVector < Movie > movies;
    QSet < QString > Genres_Group;
    QSet < QString > reserved_films;
    QMainWindow * welc;
};

#endif // USERPAGE_H
