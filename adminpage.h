#ifndef ADMINPAGE_H
#define ADMINPAGE_H

#include <QMainWindow>

#include<QSet>

#include<movie.h>

namespace Ui {
class AdminPage;
}

class AdminPage: public QMainWindow {
    Q_OBJECT

public:
    explicit AdminPage(QMainWindow * welcome, QWidget * parent = nullptr);
    ~AdminPage();

private slots:
    void Make_Default_List();

    void Set_TableWidget_At_FirstRun();

    void on_comboBox_activated(const QString & arg1);

    void on_closeBtn_clicked();

    void on_minBtn_clicked();

    void on_addButton_clicked();

    void Update_File();

    int Count_Users();

    void on_DelButton_clicked();

    void Update_DelComboBox();

    void Update_EditComboBox();

    void on_EditcomboBox_activated(const QString & arg1);

    void on_EditButton_clicked();

    void on_LogOutBtn_clicked();

    void UP_Table();

    void Update_Combobox();

private:
    QVector < Movie > movies;
    Ui::AdminPage * ui;
    QMainWindow * welc;
};

#endif // ADMINPAGE_H
