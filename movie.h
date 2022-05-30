#ifndef MOVIE_H
#define MOVIE_H
#include<QString>

#include<QVector>

class Movie {
public:
    QString Name;
    QVector < QString > Genre; //Group
    QString Director;
    int ReleaseDate;
    int Rem_Tickets; //Tickets that remain and costumers can reserve
    Movie(QString, QString, QString, int, int);
    Movie(){};

};

#endif // MOVIE_H
