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



#ifndef USERCONNREG_H
#define USERCONNREG_H

#include "globals.h"
#include "lineeditvalidate.h"
#include "communicationthread.h"

// clasa interfata de conectare utilizator
class UserConnReg: public QWidget
{
    Q_OBJECT

public:

    // constructor
    UserConnReg(QWidget *parent = 0, const int &wid = 1024, const int &hei = 768);

    // destructor
    ~UserConnReg();

    void clearContents();

private:

    UserConnReg *userconnreg;

    // declar elementele de interfata folosite pentru pagina de conectare/inregistrare
    QLabel *Conn, *UserC, *PassC, *Reg, *UserR, *PassR, *title;
    QWidget *form;
    QRegExpValidator *ValidUserC, *ValidPassC, *ValidUserR, *ValidPassR;
    LineEditValidate *LineEditUserC, *LineEditPassC, *LineEditUserR, *LineEditPassR;
    QPushButton *ClientDconnect, *uconnect, *uregister;
    QLabel *ConnectRememberLabel;
    QCheckBox *ConnectRemeberButton;

    //declar asezarile in pagina a elementelor
    QHBoxLayout *hbox, *chbox1, *chbox2, *rhbox1, *rhbox2;
    QVBoxLayout *box1, *box2, *all, *cvbox1, *cvbox2, *rvbox1, *rvbox2;

    // declar threadul de comunicare
    CommunicationThread *cThread;


    signals:
    void User(int id, int perm);

    public slots:

    void onConnectInputEdit();
    void onRegisterInputEdit();
    void UserConnectAttempt();
    void UserRegisterAttempt();
    void ServerConnectAnswer(int how);
    void ServerRegisterAnswer(int how);

};

#endif // USERCONNREG_H

