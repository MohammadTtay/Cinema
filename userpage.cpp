#include "userpage.h"

#include "ui_userpage.h"

#include<movie.h>

#include<QMessageBox>

#include<QFileInfo>

#include<QFile>

#include<QTextStream>

#include<QDebug>

#include<QTableWidgetItem>

UserPage::UserPage(QMainWindow * welcome, QString username, QString password, QWidget * parent):
      QMainWindow(parent),
      ui(new Ui::UserPage) {
    ui -> setupUi(this);
    welc = welcome;
    this -> setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    ui -> username -> setText(username);
    ui->password->setText(password);

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

    for (auto x: movies) {
        for (auto y: x.Genre) {
            Genres_Group.insert(y);
        }
    }

    for (auto x: Genres_Group) { ////////////////////////////////////Add to The Genres Combo box the list of Genres ( Without Duplicate Objects)
        ui -> comboBox -> addItem(x);
    }

    Set_TableWidget_At_FirstRun();///////////////////////////////////Input Obejcts of movies into the table widget at first run
}

UserPage::~UserPage() {
    delete ui;
}

void UserPage::Make_Default_List()
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

    film = new Movie;
    film -> Name = "محمد رسول الله ";
    film -> Genre.push_back("بیوگرافی");
    film -> Genre.push_back("تاریخی");
    film -> Director = "مجید مجیدی";
    film -> ReleaseDate = 1394;
    film -> Rem_Tickets = 46;
    movies.push_back( * film);
}

void UserPage::Set_TableWidget_At_FirstRun()
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

void UserPage::on_closeBtn_clicked() {
    QFile file("Movies.txt");
    QTextStream out( & file);
    QTextStream in ( & file);
    out.setCodec("UTF-8"); in .setCodec("UTF-8");
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

    this -> close();
}

void UserPage::on_minBtn_clicked() {
    this -> showMinimized();
}

void UserPage::on_comboBox_activated(const QString & arg1) {
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

void UserPage::on_addButton_clicked() {
    QList < QTableWidgetItem * > allCells = ui -> tableWidget -> selectedItems();
    bool flag = false;
    bool flag2 = false;
    for (auto x: allCells) {
        for (auto y: movies) {
            if (x -> text() == y.Name) flag = true;
        }

        for (int i = 0; i < ui -> listWidget -> count(); i++) {
            if (x -> text() == ui -> listWidget -> item(i) -> text()) flag2 = true;
        }

        if (flag == true && flag2 == false) {
            for (auto y: movies) {
                if (x -> text() == y.Name && y.Rem_Tickets != 0) {
                    ui -> listWidget -> addItem(x -> text());
                    break;
                } else if (x -> text() == y.Name && y.Rem_Tickets == 0) {
                    QMessageBox::critical(this, " ", "ظرفیت باقیمانده فیلم انتخابی برابر صفر می باشد و قابل رزرو نیست");
                }
            }
        } else if (flag == false) {
            QMessageBox::information(this, " ", "برای اضافه کردن به لیست رزرو لطفا روی نام فیلم کلیک کنید و سپس دکمه اضافه را فشار دهید تا به لیست اضافه شود");
        } else if (flag == true && flag2 == true) {
            QMessageBox::critical(this, " ", "فیلم در لیست وجود دارد");
        }
    }
}

void UserPage::on_delButton_clicked() {
    QList < QListWidgetItem * > items = ui -> listWidget -> selectedItems();
    for (auto item: items) {
        delete ui -> listWidget -> takeItem(ui -> listWidget -> row(item));
    }
}

void UserPage::on_delAllButton_clicked() {
    ui -> listWidget -> clear();
}

void UserPage::on_resButton_clicked() {
    if (ui -> listWidget -> count() == 0) QMessageBox::critical(this, " ", "لطفا فیلم های مورد نظر خود را به لیست رزرو اضافه کنید");
    else {
        bool flag = false;
        for (int i = 0; i < ui -> listWidget -> count(); i++) {
            for (auto x: reserved_films) {
                if (ui -> listWidget -> item(i) -> text() == x) {
                    QMessageBox::critical(this, " ", "یکی از فیلم ها قبلا رزرو شده اند . لطفا آن را از لیست رزرو حذف نمایید و دوباره امتحان کنید");
                    flag = true;
                    break;
                }
                if (flag == true) break;
            }
            if (flag == true) break;
        }
        if (flag == false) {
            for (int i = 0; i < ui -> listWidget -> count(); i++) {
                reserved_films.insert(ui -> listWidget -> item(i) -> text());
                for (auto & x: movies) {
                    if (x.Name == ui -> listWidget -> item(i) -> text()) {
                        x.Rem_Tickets--;
                        UserPage::Update_File();
                    }
                }
            }
            ui -> listWidget -> clear();
            ui -> Reserve_listWidget -> clear();
            for (auto x: reserved_films) {
                ui -> Reserve_listWidget -> addItem(x); //add items in main list widget into "Reserved Tab"
            }
            ui -> count_reserved -> setText(QString::number(reserved_films.size())); //save count of reserved film User tab
            QMessageBox::information(this, " ", "فیلم های موردنظر با موفقیت رزرو شدند");

            UserPage::on_comboBox_activated("همه ژانر ها");

        }

    }
}

void UserPage::on_Serach_lineEdit_textChanged(const QString & arg1) {
    if (arg1.isEmpty()) {
        ui -> comboBox -> setEnabled(true);
        UserPage::on_comboBox_activated("همه ژانر ها");

    } else if (ui -> Name_RButton -> isChecked()) {
        ui -> comboBox -> setEnabled(false);
        int count = 0;
        for (auto x: movies) {
            if (arg1 == x.Name.left(arg1.size())) count++;
        }
        ui -> tableWidget -> setRowCount(count);
        int i = 0;
        QTableWidgetItem * item = new QTableWidgetItem;
        for (auto x: movies) {
            if (arg1 == x.Name.left(arg1.size())) {
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

    } else if (ui -> Genre_RButton -> isChecked()) {
        ui -> comboBox -> setEnabled(false);
        int count = 0;
        for (auto x: movies) {
            for (auto y: x.Genre) {
                if (arg1 == y.left(arg1.size())) {
                    count++;
                    break;
                }
            }
            ui -> tableWidget -> setRowCount(count);
            int i = 0;
            QTableWidgetItem * item = new QTableWidgetItem;
            for (auto x: movies) {
                for (auto y: x.Genre)
                    if (arg1 == y.left(arg1.size())) {
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
                        break;
                    }

            }

        }

    } else if (ui -> Dir_RButton -> isChecked()) {
        ui -> comboBox -> setEnabled(false);
        int count = 0;
        for (auto x: movies) {
            if (arg1 == x.Director.left(arg1.size())) count++;
        }
        ui -> tableWidget -> setRowCount(count);
        int i = 0;
        QTableWidgetItem * item = new QTableWidgetItem;
        for (auto x: movies) {
            if (arg1 == x.Director.left(arg1.size())) {
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
    } else if (ui -> ReleaseDate_RButton -> isChecked()) {
        ui -> comboBox -> setEnabled(false);
        int count = 0;
        for (auto x: movies) {
            if (arg1 == QString::number(x.ReleaseDate).left(arg1.size())) count++;
        }
        ui -> tableWidget -> setRowCount(count);
        int i = 0;
        QTableWidgetItem * item = new QTableWidgetItem;
        for (auto x: movies) {
            if (arg1 == QString::number(x.ReleaseDate).left(arg1.size())) {
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

void UserPage::Update_File() {
    QFile file("Movies.txt");
    QTextStream out( & file);
    QTextStream in ( & file);
    out.setCodec("UTF-8"); in .setCodec("UTF-8");
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

void UserPage::on_LogOutBtn_clicked() {
    this -> close();
    welc -> show();
}
