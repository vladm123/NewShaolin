/*
    Copyright 2009, 2010 Sebastian Codrin Ditu, Vlad Manea

        This file is part of newshaolin.

        newshaolin is free software: you can redistribute it and/or modify
        it under the terms of the GNU General Public License as published by
        the Free Software Foundation, either version 3 of the License, or
        (at your option) any later version.

        newshaolin is distributed in the h that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
        GNU General Public License for more details.

        You should have received a copy of the GNU General Public License
        along with newshaolin.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GLOBALS_H
#define GLOBALS_H

#include "QApplication"
#include "QCheckBox"
#include "QThread"
#include "QLineEdit"
#include "QLabel"
#include "QWidget"
#include "QPushButton"
#include "QHBoxLayout"
#include "QVBoxLayout"
#include "QRegExpValidator"
#include "QRegExp"
#include "QMainWindow"
#include "QMessageBox"
#include "QFile"
#include "QTextStream"
#include "QDesktopWidget"
#include "QStyleOption"
#include "QPainter"
#include "QStyle"
#include "QEvent"
#include "QResizeEvent"
#include "source.h"
#include "imagesetter.h"
#include "QMap"
#include "QScrollArea"
#include "QTextEdit"
#include "QScrollArea"
#include "QDateTime"
#include "QMutex"

// declar QAlicatia
extern QApplication *myapp;


// definesc tipul functiei de crearea a unui obiect
typedef QWidget * (*CreateWidget)(QWidget *);

// definesc structura in care voi retine un id si un permision pentru un Widget
struct nod
{
    int perm;
    CreateWidget functie;
};

// redenumesc tipul struct nod in Nod
typedef struct nod Nod;

// definesc structura in care voi retine informatia despre categorie
struct catinfo
{
    // nivelul in arbore
    int level;

    // identificator
    int id;

    // nume
    QString name;

    // data ultimei actualizari
    QString Date;

    // vreau parinte
    // int parentId

    // id -ul utilizatorului care a creat-o
    int owner;
};

// redenumesc tipul struct catinfo in CatInfo
typedef struct catinfo CatInfo;

// declar lista categoriilor
extern QList<CatInfo> CatsList;

// definesc structura in care voi retine informatia despre stire
struct newsinfo
{
    // nivel
    int level;

    // identificator
    int id;

    // titlu
    QString name;

    // data (ultimei actualizari)
    QString Date;

    // continut
    QString Content;

    // parinte id
    int parent;

    // propunator
    int owner;

};

// redenumesc tipul struct catinfo in CatInfo
typedef struct newsinfo NewsInfo;

// declar lista categoriilor
extern QList<NewsInfo> GlobalNewsList;

//
extern QMutex Mutex;

// declar contentul layout-ului categorii
extern QString cats;

// socketul pentru comunicarea cu serverul
extern int *sd;

// lungimea mesajului trimis/primit catre/(de la) server
extern int length;

// mesajul trimis/primit catre/(de la) server
extern char *message;
extern char *comanda, *raspuns;

// declar ca variabila utilizata pentru alte elemente UserId Conectat
extern int UserId;

// pointerul temporar pe care il folosesc la (re)alocarea de memorie
extern char *tmp;
extern char *data;

// muta widgetul la centru raportat la desktop
void moveToCenter(QWidget *w, const int &width, const int &height);

// muta widgetul raportat la parinte
void moveWidgetToCenter(QWidget *w, const int &pwidth, const int &pheight, const int &width, const int &height);

// declar functia care se ocupa cu incarcarea unui layout vertical cu parametri
//void handleVlabel(QVBoxLayout *id, QLabel *name, QLabel *user, QLineEdit *line1, QLabel *pass, QLineEdit *line2, QHBoxLayout *rc);
void handleHLabel(QVBoxLayout *hbox, QLabel *label, QHBoxLayout *hbox1, QHBoxLayout *hbox2, QVBoxLayout *vbox1, QVBoxLayout *vbox2, QLabel *label1, QLabel *label2, QLineEdit *line1, QLineEdit *line2, QPushButton *button, QLabel *remember, QCheckBox * rem);

void handleHLabelR(QVBoxLayout *hbox, QLabel *label, QHBoxLayout *hbox1, QHBoxLayout *hbox2, QVBoxLayout *vbox1, QVBoxLayout *vbox2, QLabel *label1, QLabel *label2, QLineEdit *line1, QLineEdit *line2, QPushButton *button);

// declar functia de incarcare a comenzii, inc = 1 .. concatenez la comanda text, altfel suprascriu
void handle_string(char *comanda, QString text, int inc);

// parcurg in preordine si fac arborele de categorii
void Preorder();

#endif // GLOBALS_H
