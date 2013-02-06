/*
    Copyright 2009, 2010 Sebastian Codrin Ditu, Vlad Manea

        This file is part of newshaolin.

        newshaolin is free software: you can redistribute it and/or modify
        it under the terms of the GNU General Public License as published by
        the Free Software Foundation, either version 3 of the License, or
        (at your option) any later version.

        newshaolin is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
        GNU General Public License for more details.

        You should have received a copy of the GNU General Public License
        along with newshaolin.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "intermain.h"
#include "ui_intermain.h"

// declar variabila statica
InterMain* InterMain::intermain = 0;

// definesc functia de instantiere
InterMain* InterMain::instance(QWidget *parent, const int &wid, const int &hei, char sty[])
{
    if (!intermain)
        if (!(intermain = new InterMain(parent, wid, hei, sty)))
            exit(0);

    return intermain;
}

// definesc constructorul interfata principala care contine celelalte clase interfata
InterMain::InterMain(QWidget *parent, const int &wid, const int &hei, char sty[])
    : QMainWindow(parent), confserver(0), connreg(0), userprivatespace(0)
{
    if (!(ui = new Ui::InterMain) || !(imagesetter = new ImageSetter(this, wid, hei))
        || !(confserver = new ServerConf(this, wid, hei)))
        exit(0);
    // setez interfata cu utilizatorul
    ui->setupUi(this);

    // dimensionez obiectul
    this->resize(wid, hei);

    // mut obiectul in centru fata de desktop
    moveToCenter(this, width(), height());

    // setez fereastra principala
    setCentralWidget(confserver);

    // creez pagina de conectare
    if(!(connreg = new UserConnReg(this, wid, hei)))
       exit(0);
    connreg->hide();

    // creez pagina privata a utilizatorului
    if(!(userprivatespace = new UserPrivateSpace(this)))
        exit(0);
    userprivatespace->hide();

    // setez titlul ferestrei
    this->setWindowTitle("newshaolin  |  configurare server");

    // ascociez semnale cu sloturi
    connect(this->confserver, SIGNAL(Connected(int)), this, SLOT(SuccessfullServerConnect(int)));

    // terminare
    connect(this, SIGNAL(AboutToClose()), this->userprivatespace,SLOT(DeleteDialogs()));

    // interzic resize
    this->setFixedSize(width(), height());

}

// definesc destructorul
InterMain::~InterMain()
{
    // eliberez memoria alocata
    delete ui;
    delete confserver;
    delete userprivatespace;
    delete connreg;
    delete imagesetter;
}

// declar functia de setare a stilului
void InterMain::setstyle(char sty[], const int &inc)
{
    if (inc)
        strcpy(css, sty);
    else
        strcat(css, sty);

    if (imagesetter)
        imagesetter->setStyleSheet(css);
}

// schimb dintre ferestre la conectarea serverului
void InterMain::SuccessfullServerConnect(int how)
{
    if(how == 1)
    {
        this->confserver->hide();
        this->connreg->show();
        this->setWindowTitle("newshaolin  |  Conectarea | Inregistrarea utilizatorului");
    }
    else
    {
        // nu fac nimic, il las sa mai incerce o configurare, daca nu poate inchide singur aplicatia :)
    }

}

// realizez schimbul dintre ferestre, incarc / creez interfata utilizatorului in functie de drepturile sale
void InterMain::SuccessfullUserConnect(int id, int perm)
{
    connreg->hide();

    // setez id-ul utilizatorului widget-ului respectiv pentru posibilele modificari pe care le poate face
    userprivatespace->SetUserId(id);

    // creez elementele de interface specifice tipului utizatorului conectat
    userprivatespace->SetUserType(perm);

    // schimb stilul ferestrei intermain
    setstyle("background-color:#fff; background-image:url(images/wall1.jpg); background-repeat:no-repeat;", 0);


    // le afisez pe ecran
    userprivatespace->show();

    setWindowTitle("newshaolin  |  Spatiu privat utilizator");
    QMessageBox::information(this, "newshaolin | info", "    Bine ai venit!      ", QMessageBox::Ok);
}

// apelez functia de deconectare de la server (nu e necesar sa o fac separat in thread)
void InterMain::servershutdown()
{
    // daca inchiderea socketului care comunica cu serverul curent se executa cu succes
     if(!deconectareServer(sd))
        {
            this->connreg->hide();
            this->connreg->clearContents();
            this->confserver->show();
        }
     else
     {
            QMessageBox::information(this, "newshaolin | info","Eroare la deconectare serverului!", QMessageBox::Ok);
     }
}

// deconectarea unui utilizator, schimb intre ferestre si aplic functie din clasa interfata privata cu utilizatorul
// pentru a sterge elementele de interfata care nu mai sunt necesare
// (dialogurile vor ramane desi vor fi setate va invisible)
void InterMain::SuccessfullUserDeconnect(int how)
{
    if(how == 1)
    {
        if(userprivatespace)
        {
            // sterg elementele anterior create pentru a da posibilitatea conectarii unui nou tip de utilizator
            // diferit chiar de precedentul sau
            userprivatespace->DestroyUserInterface();
            userprivatespace->close();

            // schimb stilul ferestrei intermain
            setstyle("background-color:#fff; background-image:url(images/shaolin.jpg); background-repeat:no-repeat;", 0);

            connreg->clearContents();
            connreg->show();
        }
        else
        QMessageBox::information(this, "newshaolin | info", "Stergere!\n",
                                             QMessageBox::Ok);
    }
    else
    {
        // nu fac nimic pentru ca am tratat cazul de eroare in clasa UserPrivateSpace
    }
}

// lla terminare trimit semnalul de AboutToClose pentru a inchide si dialogurile care au ramas deschise
void InterMain::closeEvent(QCloseEvent *event)
 {
    // emit semnalul pentru inchiderea tuturor dialogurilor deschise
    emit AboutToClose();

    // accept evenimentul de inchidere
    event->accept();
 }

// resize event
void InterMain::resizeEvent(QResizeEvent * event)
{
    this->resize(event->size());
}

