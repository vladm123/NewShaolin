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

#ifndef USERADDCAT_H
#define USERADDCAT_H

#include "globals.h"
#include "communicationthread.h"
#include "lineeditvalidate.h"

// clasa element a interfetei utilizator care reprezinta butonul de adaugare a unei noi categorii, permisiunea pentru el >=3

class AddCatButton: public QPushButton
{
    Q_OBJECT

 public:

   static QWidget * CreateAddCatButton(QWidget *parent = 0);

    AddCatButton(QString &text, QWidget *parent = 0);
    ~AddCatButton();

};

// clasa element a interfetei utilizator care reprezinta butonul de modificare categorii, permisiunea pentru el >=3

class ModCatButton: public QPushButton
{
    Q_OBJECT

 public:

   static QWidget * CreateModCatButton(QWidget *parent = 0);

    ModCatButton(QString &text, QWidget *parent = 0);
    ~ModCatButton();

};

// clasa element a interfetei utilizator care reprezinta butonul de modificare categorii, permisiunea pentru el >=3

class DelCatButton: public QPushButton
{
    Q_OBJECT

 public:

   static QWidget * CreateDelCatButton(QWidget *parent = 0);

    DelCatButton(QString &text, QWidget *parent = 0);
    ~DelCatButton();

};


// clasa element in clasa privata User, Dialogul pentru modificarea de parola a contului user-ului
class UserAddModCatDialog: public QDialog
{
    Q_OBJECT

public:

    // constructor
    UserAddModCatDialog(QWidget *parent = 0, int Mode = 0);

    // destructor
    ~UserAddModCatDialog();

private:

    // elementele de interfata folosite aici;
    QPushButton *Modify, *Cancel;
    LineEditValidate *InputId, *InputName, *InputParent;
    QRegExpValidator *ValidIdANDParent, *ValidName;
    QLabel *CatId, *CatName, *CatParent;
    QVBoxLayout *Labels, *LineEdits, *All;
    QHBoxLayout *Content, *Buttons;

    // creare sau modificare?
    int mode;

    // threadul de comunicare cu serverul
     CommunicationThread *AddModCatThread;

signals:

    // definesc semnalul de modifica a unei categorii, (sa il trimit parintelui si sa updatez categoriile?)
    void UserSignalModifyCat(int how);

public slots:

    // slotul care se executa la apasarea butonului de deconectare
    void UserAddModCatAttempt();

    // slotul care se executa la terminarea threadului care ii comunica serverului dorinta de deconectare a utilizatorului
    void ServerAddModCatAnswer(int how);

    // slotul care imi activeaza/dezactiveaza butonul de modificare al parolei
    void onInputEdit();

    // care se executa la apasarea butonului de close
    void onCloseDialog();

};

// // clasa element in clasa privata User, Dialogul pentru stergerea unei categorii
class UserDelCatDialog: public QDialog
{
    Q_OBJECT

public:

    // constructor
    UserDelCatDialog(QWidget *parent = 0);

    // destructor
    ~UserDelCatDialog();

private:

    // elementele de interfata folosite aici;
    QPushButton *Modify, *Cancel;
    LineEditValidate *InputId;
    QRegExpValidator *ValidId;
    QLabel *CatId;
    QVBoxLayout *All;
    QHBoxLayout *Content, *Buttons;

    // threadul de comunicare cu serverul
     CommunicationThread *DelCatThread;

signals:

    // definesc semnalul de modificare a parolei
    void UserSignalDelCat(int how);

public slots:

    // slotul care se executa la apasarea butonului de deconectare
    void UserDelCatAttempt();

    // slotul care se executa la terminarea threadului care ii comunica serverului dorinta de deconectare a utilizatorului
    void ServerDelCatAnswer(int how);

    // slotul care imi activeaza/dezactiveaza butonul de modificare al parolei
    void onInputEdit();

    // care se executa la apasarea butonului de close
    void onCloseDialog();
};

#endif // USERADDCAT_H
