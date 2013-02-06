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

#ifndef SERVERCONF_H
#define SERVERCONF_H

#include "globals.h"
#include "mythread.h"
#include "lineeditvalidate.h"

// clasa care gestioneaza conexiunea cu serverul
class ServerConf: public QWidget
{
    Q_OBJECT

public:

    // constructor
    ServerConf(QWidget *parent = 0, const int &wid = 1024, const int &hei = 768);

    // destructor
    ~ServerConf();

private:

    ServerConf *serverconf;

    // declar elementele de interfata folosite pentru pagina de configurare server
    QLabel *SLabel, *SAddr, *SPort, *title;
    QWidget *form;

    LineEditValidate *LineEditSAddr, *LineEditSPort;
    QRegExpValidator *ValidSAddr, *ValidSPort;

    QPushButton *ClientCconnect, *Quit;

    QLabel *ServerRememberLabel;
    QCheckBox *ServerRemeberButton;

    // declar aranjarile in pagina folosite la configurarea serverului
    QHBoxLayout *hbox1, *hbox2, *hbox3;
    QVBoxLayout *vbox1, *vbox2, *box, *all;

    // declar pointer-ul catre char pe care il voi trimite la threadul de connect
    char *adr;

    // declar thread-ul folosit pentru conectare

    mythread * connectThread;


signals:
    //semnalul care ii zice parintelui daca m-am conectat cu succes sau nu
    void Connected(int how);

public slots:

    // testarea inputurilor, daca sunt valide (toate) activez butonul de trimitere a comenzii de conectare
    void onInputEdit();

    // tentativa de conectare
    void ConnectAttempt();

    // raspunsul (rez == 1 ===> suces)
    void ConnectAnswer(int rez);
};

#endif // SERVERCONF_H
