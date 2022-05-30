#include "adminpage.h"

#include "ui_adminpage.h"

#include<QFile>

#include<QFileInfo>

#include<QTextStream>

#include<QMessageBox>

#include<QDebug>

AdminPage::AdminPage(QMainWindow * welcome, QWidget * parent):
      QMainWindow(parent),
      ui(new Ui::AdminPage) {
    ui -> setupUi(this);
    this -> setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    welc = welcome;

    ui -> count_users -> setText(QString::number(Count_Users())); ///////set the count of users in Tab 4
    UP_Table();//////////////////////////////////////////////////////////set the Database of usernames and passwords in Tab4
    connect(ui -> Name_checkBox, SIGNAL(toggled(bool)), ui -> lineEdit_Name, SLOT(setEnabled(bool)));
    connect(ui -> Genre_checkBox, SIGNAL(toggled(bool)), ui -> lineEdit_Genre, SLOT(setEnabled(bool)));
    connect(ui -> Director_checkBox, SIGNAL(toggled(bool)), ui -> lineEdit_Director, SLOT(setEnabled(bool)));
    connect(ui -> ReleaseD_checkBox, SIGNAL(toggled(bool)), ui -> lineEdit_ReleaseD, SLOT(setEnabled(bool)));
    connect(ui -> RemainT_checkBox, SIGNAL(toggled(bool)), ui -> spinBox_RemainT, SLOT(setEnabled(bool)));


    Make_Default_List();/////////////////////////////////////////////////////////MAKE OUR DEFAULT LIST At the first run


    QFile file("Movies.txt");
    QTextStream out( & file);
    QTextStream in ( & file);
    out.setCodec("UTF-8"); in .setCodec("UTF-8");
    if (QFileInfo::exists("Movies.txt")) {///////////////Load OUR Movie LIST At the first run from Movies.txt
        movies.clear();
        QString Temp;
        int Temp_GNum;
        Movie * film = new Movie;
        file.open(QFile::ReadWrite | QFile::Text);
        while (! in .atEnd()) {
            film = new Movie;
            Temp = in .readLine();
            if (Temp == "Name") {
                film -> Name = in .readLine();
            }
            Temp = in .readLine();
            if (Temp == "Genre") {
                Temp_GNum = in .readLine().toInt();
                for (int i = 0; i < Temp_GNum; i++) {
                    film -> Genre.push_back( in .readLine());
                }
            }
            Temp = in .readLine();
            if (Temp == "Director") {
                film -> Director = in .readLine();
            }
            Temp = in .readLine();
            if (Temp == "ReleaseDate") {
                film -> ReleaseDate = in .readLine().toInt();
            }
            Temp = in .readLine();
            if (Temp == "Rem_Tickets") {
                film -> Rem_Tickets = in .readLine().toInt();
            }
            movies.push_back( * film);

        }
        file.close();

    } else {/////////////////////////////////////////////////////////Save OUR DEFAULT LIST At the first run in the Movies.txt
        file.open(QFile::ReadWrite | QFile::Text);
        for (auto x: movies) {
            out << "Name" << "\n" << x.Name << "\n";
            out << "Genre" << "\n";
            out << x.Genre.size() << "\n";
            for (auto y: x.Genre) {
                out << y << "\n";
            }
            out << "Director" << "\n" << x.Director << "\n";
            out << "ReleaseDate" << "\n" << x.ReleaseDate << "\n";
            out << "Rem_Tickets" << "\n" << x.Rem_Tickets << "\n";
        }
        file.close();
    }


    Update_Combobox();//////////////////////////////////////Add to The Genres Combo box the list of Genres ( Without Duplicate Objects)
    Update_DelComboBox(); //////////////////////////////////add items into the DelComboBox in Tab 2 at the first
    Update_EditComboBox();//////////////////////////////////add items into the EditComboBox in Tab 3 at the first
    Set_TableWidget_At_FirstRun();//////////////////////////Input Obejcts of movies into the table widget at first run
}

AdminPage::~AdminPage() {
    delete ui;
}

void AdminPage::Make_Default_List()
{

    Movie * film = new Movie;
    film -> Name = "مطرب";
    film -> Genre.push_back("کمدی");
    film -> Genre.push_back("اجتماعی");
    film -> Director = "مصطفی کیایی";
    film -> ReleaseDate = 1398;
    film -> Rem_Tickets = 17;
    movies.push_back( * film);

    film = new Movie;
    film -> Name = "هزارپا";
    film -> Genre.push_back("کمدی");
    film -> Director = "ابوالحسن داوودی";
    film -> ReleaseDate = 1397;
    film -> Rem_Tickets = 14;
    movies.push_back( * film);

    film = new Movie;
    film -> Name = "متری شیش و نیم";
    film -> Genre.push_back("اکشن");
    film -> Genre.push_back("جنایی");
    film -> Director = "سعید روستایی";
    film -> ReleaseDate = 1398;
    film -> Rem_Tickets = 35;
    movies.push_back( * film);

    film = new Movie;
    film -> Name = "بادیگارد";
    film -> Genre.push_back("اکشن");
    film -> Genre.push_back("درام");
    film -> Director = "ابراهیم حاتمی کیا";
    film -> ReleaseDate = 1395;
    film -> Rem_Tickets = 84;
    movies.push_back( * film);

    film = new Movie();
    film -> Name = "محمد رسول الله ";
    film -> Genre.push_back("بیوگرافی");
    film -> Genre.push_back("تاریخی");
    film -> Director = "مجید مجیدی";
    film -> ReleaseDate = 1394;
    film -> Rem_Tickets = 46;
    movies.push_back( * film);
}

void AdminPage::Set_TableWidget_At_FirstRun()
{

    QTableWidgetItem * item = new QTableWidgetItem;
    ui -> tableWidget -> setRowCount(movies.size());
    for (int i = 0; i < ui -> tableWidget -> rowCount(); i++) {
        item = new QTableWidgetItem(movies[i].Name);
        ui -> tableWidget -> setItem(i, 0, item);

        QString genres;
        for (auto x: movies[i].Genre) {
            genres += x + ",";
        }
        genres = genres.left(genres.size() - 1);

        item = new QTableWidgetItem(genres);
        ui -> tableWidget -> setItem(i, 1, item);

        item = new QTableWidgetItem(movies[i].Director);
        ui -> tableWidget -> setItem(i, 2, item);

        item = new QTableWidgetItem(QString::number(movies[i].ReleaseDate));
        ui -> tableWidget -> setItem(i, 3, item);

        item = new QTableWidgetItem(QString::number(movies[i].Rem_Tickets));
        ui -> tableWidget -> setItem(i, 4, item);
    }
}

void AdminPage::on_comboBox_activated(const QString & arg1) {
    QTableWidgetItem * item = new QTableWidgetItem;
    if (arg1 == "همه ژانر ها") {
        ui -> tableWidget -> setRowCount(movies.size());
        for (int i = 0; i < ui -> tableWidget -> rowCount(); i++) {
            item = new QTableWidgetItem(movies[i].Name);
            ui -> tableWidget -> setItem(i, 0, item);

            QString genres;
            for (auto x: movies[i].Genre) {
                genres += x + ",";
            }
            genres = genres.left(genres.size() - 1);

            item = new QTableWidgetItem(genres);
            ui -> tableWidget -> setItem(i, 1, item);

            item = new QTableWidgetItem(movies[i].Director);
            ui -> tableWidget -> setItem(i, 2, item);

            item = new QTableWidgetItem(QString::number(movies[i].ReleaseDate));
            ui -> tableWidget -> setItem(i, 3, item);

            item = new QTableWidgetItem(QString::number(movies[i].Rem_Tickets));
            ui -> tableWidget -> setItem(i, 4, item);
        }

    } else {
        int count = 0;
        for (auto x: movies) {
            for (auto y: x.Genre) {
                if (arg1 == y) count++;
            }
        }
        ui -> tableWidget -> setRowCount(count);
        int i = 0;
        QTableWidgetItem * item = new QTableWidgetItem;
        for (auto x: movies) {
            for (auto y: x.Genre) {
                if (arg1 == y) {
                    item = new QTableWidgetItem(x.Name);
                    ui -> tableWidget -> setItem(i, 0, item);

                    QString genres;
                    for (auto z: x.Genre) {
                        genres += z + ",";
                    }
                    genres = genres.left(genres.size() - 1);
                    item = new QTableWidgetItem(genres);
                    ui -> tableWidget -> setItem(i, 1, item);

                    item = new QTableWidgetItem(x.Director);
                    ui -> tableWidget -> setItem(i, 2, item);

                    item = new QTableWidgetItem(QString::number(x.ReleaseDate));
                    ui -> tableWidget -> setItem(i, 3, item);

                    item = new QTableWidgetItem(QString::number(x.Rem_Tickets));
                    ui -> tableWidget -> setItem(i, 4, item);
                    i++;
                }
            }
        }

    }

}

void AdminPage::on_closeBtn_clicked() {
    this -> close();
}

void AdminPage::on_minBtn_clicked() {
    this -> showMinimized();
}

void AdminPage::on_addButton_clicked() {
    if (ui -> Name_lineEdit -> text().isEmpty() || ui -> Genre_lineEdit_1 -> text().isEmpty() || ui -> Dir_lineEdit -> text().isEmpty() || ui -> ReleaseD_lineEdit -> text().isEmpty() || ui -> RemainT_lineEdit -> text().isEmpty()) {
        QMessageBox::warning(this, " ", "لطفا تمام مقادیر مورد نیاز را وارد نمایید");
    } else {
        Movie * New_Movie = new Movie;
        New_Movie -> Name = ui -> Name_lineEdit -> text();
        New_Movie -> Genre.push_back(ui -> Genre_lineEdit_1 -> text());
        if (!ui -> Genre_lineEdit_2 -> text().isEmpty()) {
            New_Movie -> Genre.push_back(ui -> Genre_lineEdit_2 -> text());
        }
        if (!ui -> Genre_lineEdit_3 -> text().isEmpty()) {
            New_Movie -> Genre.push_back(ui -> Genre_lineEdit_3 -> text());
        }
        if (!ui -> Genre_lineEdit_4 -> text().isEmpty()) {
            New_Movie -> Genre.push_back(ui -> Genre_lineEdit_4 -> text());
        }
        New_Movie -> Director = ui -> Dir_lineEdit -> text();
        New_Movie -> ReleaseDate = ui -> ReleaseD_lineEdit -> text().toInt();
        New_Movie -> Rem_Tickets = ui -> RemainT_lineEdit -> text().toInt();
        movies.push_back( * New_Movie);

        Update_DelComboBox();
        Update_EditComboBox();
        Update_Combobox();
        on_comboBox_activated("همه ژانر ها");
        Update_File();
}
}

void AdminPage::on_DelButton_clicked() {
    QString temp = ui -> DelcomboBox -> currentText();

    for (int i = 0; i < movies.size(); i++) {
        if (temp == movies[i].Name) {
            movies.erase(movies.begin() + i);
            break;
        }
    }
    Update_DelComboBox();
    Update_EditComboBox();
    Update_Combobox();
    on_comboBox_activated("همه ژانر ها");
    Update_File();

}

void AdminPage::on_EditcomboBox_activated(const QString & arg1) {
    if (arg1 == "--") {
        ui -> label_name -> setText("");
        ui -> label_genre -> setText("");
        ui -> label_director -> setText("");
        ui -> label_releaseDate -> setText("");
    } else {
        for (auto x: movies) {
            if (arg1 == x.Name) {
                ui -> label_name -> setText(x.Name);
                QString genres;
                for (auto z: x.Genre) {
                    genres += z + ",";
                }
                genres = genres.left(genres.size() - 1);
                ui -> label_genre -> setText(genres);
                ui -> label_director -> setText(x.Director);
                ui -> label_releaseDate -> setText(QString::number(x.ReleaseDate));
                break;
            }
        }
        Update_File();
    }
}

void AdminPage::Update_DelComboBox() {
    QSet < QString > list;
    for (auto x: movies) {
        list.insert(x.Name);
    }
    ui -> DelcomboBox -> clear();
    ui -> DelcomboBox -> addItems(list.toList());
}

void AdminPage::Update_EditComboBox() {
    QSet < QString > list;
    for (auto x: movies) {
        list.insert(x.Name);
    }
    ui -> EditcomboBox -> clear();
    ui -> EditcomboBox -> addItem("--");
    ui -> EditcomboBox -> addItems(list.toList());
}

void AdminPage::Update_File() {
    QFile file("Movies.txt");
    QTextStream out( & file);
    out.setCodec("UTF-8");
    file.open(QFile::WriteOnly | QFile::Text);
    for (auto x: movies) {
        out << "Name" << "\n" << x.Name << "\n";
        out << "Genre" << "\n";
        out << x.Genre.size() << "\n";
        for (auto y: x.Genre) {
            out << y << "\n";
        }
        out << "Director" << "\n" << x.Director << "\n";
        out << "ReleaseDate" << "\n" << x.ReleaseDate << "\n";
        out << "Rem_Tickets" << "\n" << x.Rem_Tickets << "\n";
    }
    file.close();
}

int AdminPage::Count_Users() {
    QFile file("UP.txt");
    QTextStream in ( & file); in .setCodec("UTF-8");
    int counter = 0;
    QString temp_user, temp_password;

    if (QFileInfo::exists("UP.txt")) {
        file.open(QFile::ReadWrite | QFile::Text);
        do {
            temp_user = in .readLine();
            temp_password = in .readLine();
            counter++;
        } while (!temp_user.isNull());
        file.close();
        return counter - 1;
    } else {
        return 0;
    }

}

void AdminPage::on_EditButton_clicked() {
    QString temp = ui -> EditcomboBox -> currentText();

    for (auto & x: movies) {
        if (temp == x.Name) {
            if (ui -> Name_checkBox -> isChecked()) {
                x.Name = ui -> lineEdit_Name -> text();
            }
            if (ui -> Genre_checkBox -> isChecked()) {
                x.Genre.clear();
                QStringList input_genre;
                input_genre = ui -> lineEdit_Genre -> text().split("،");
                for (auto y: input_genre) {
                    x.Genre.push_back(y);
                }
            }
            if (ui -> Director_checkBox -> isChecked()) {
                x.Director = ui -> lineEdit_Director -> text();
            }
            if (ui -> ReleaseD_checkBox -> isChecked()) {
                x.ReleaseDate = ui -> lineEdit_ReleaseD -> text().toInt();
            }
            if (ui -> RemainT_checkBox -> isChecked()) {
                x.Rem_Tickets = ui -> spinBox_RemainT -> value();
            }
            break;
        }

    }
    Update_DelComboBox();
    Update_EditComboBox();
    Update_Combobox();
    on_comboBox_activated("همه ژانر ها");
    Update_File();

}

void AdminPage::on_LogOutBtn_clicked() {
    this -> close();
    welc -> show();
}

void AdminPage::UP_Table() {
    QTableWidgetItem * item = new QTableWidgetItem;
    ui -> tableWidget_UP -> setRowCount(Count_Users());
    QFile file("UP.txt");
    QTextStream in ( & file); in .setCodec("UTF-8");

    QString temp_user, temp_password;
    file.open(QFile::ReadOnly | QFile::Text);
    for (int i = 0; i < Count_Users(); i++) {
        temp_user = in .readLine();
        temp_password = in .readLine();

        item = new QTableWidgetItem(temp_user);
        ui -> tableWidget_UP -> setItem(i, 0, item);

        item = new QTableWidgetItem(temp_password);
        ui -> tableWidget_UP -> setItem(i, 1, item);

    }

}

void AdminPage::Update_Combobox()
{
    QSet < QString > Genres_Group;
    ui->comboBox->clear();
    ui->comboBox->addItem("همه ژانر ها");
    for (auto x: movies) {
        for (auto y: x.Genre) {
            Genres_Group.insert(y);
        }
    }

    for (auto x: Genres_Group) {
        ui -> comboBox -> addItem(x);
    }
}
