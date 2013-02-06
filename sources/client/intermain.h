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

#ifndef INTERMAIN_H
#define INTERMAIN_H

#include "globals.h"
#include "serverconf.h"
#include "userconnreg.h"
#include "userprivatespace.h"


namespace Ui
{
     class InterMain;
}

// interfata principala care contine celelalte clase interfata
class InterMain : public QMainWindow
{
    Q_OBJECT

public:

    // declar functia de setare a stilului
    void setstyle(char sty[], const int &inc);

    // declar variabila care gestioneaza o configurare de server
    ServerConf *confserver;

    // declar variabila care gestioneaza o conectare utilizator
    UserConnReg *connreg;

    // delcar varaibila care gestioneaza spatiul privat
    UserPrivateSpace *userprivatespace;

    // declar imaginea de background
    ImageSetter *imagesetter;

    // declar functia de instantiere
    static InterMain* instance(QWidget *parent = 0, const int &wid = 1024, const int &hei = 768, char sty[] = "");

    // declar functia de redimensionare
    void resizeEvent(QResizeEvent * event);

    // destructor
    ~InterMain();

private:

    // variabila statica
    static InterMain *intermain;

    // declar
    char css[1000];

    // retin o variabila intreaga care imi spune intotdeauna daca sunt conectat sau nu..
    int online;

    // pointer la ui
    Ui::InterMain *ui;

    // constructor
    InterMain(QWidget *parent = 0, const int &wid = 1024, const int &hei = 768, char sty[] = "");

    // constructor de copiere
    InterMain(const InterMain&);

    // operator de atribuire
    InterMain& operator=(const InterMain&);

    // functie care se executa la inchidere
    void closeEvent(QCloseEvent *event);

    // semnale
signals:
    // semnalul pe care il transmit la inchidere, este folosit pentru a inchide toate dialogurile deschise de un utilizator
    void AboutToClose();

    // sloturi publice ( how = 1 => succes)
public slots:

    // conectarea la server
    void SuccessfullServerConnect(int how);

    // conectarea unui utilizator
    void SuccessfullUserConnect(int id, int perm);

    // deconectarea unui utilizator
    void SuccessfullUserDeconnect(int how);

    // deonectarea de la server
    void servershutdown();
};

#endif
