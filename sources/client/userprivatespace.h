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

#ifndef USERPRIVATESPACE_H
#define USERPRIVATESPACE_H

#include "globals.h"
#include "communicationthread.h"
#include "lineeditvalidate.h"
#include "viewcats.h"
#include "viewnews.h"
#include "useraddcat.h"


// clasa element a interfetei utilizator care reprezinta butonul de adaugare a unei noi stiri, permisiunea pentru el >=2

class UsersViewModifyButton: public QPushButton
{
    Q_OBJECT

 public:

   static QWidget * CreateUsersViewModifyButton(QWidget *parent = 0);

    UsersViewModifyButton(QString &text, QWidget *parent = 0);
    ~UsersViewModifyButton();

};

// clasa element in clasa privata User, Dialogul pentru modificarea de parola a contului user-ului
class UsersViewModifyDialog: public QDialog
{
    Q_OBJECT

public:

    // constructor
    UsersViewModifyDialog(QWidget *parent = 0);

    // destructor
    ~UsersViewModifyDialog();

private:

    // threadul de comunicare cu serverul
     CommunicationThread *UsersModifyThread, *UsersViewThread;

    // elementele de interfata folosite aici;
    QPushButton *Modify, *Cancel;
    LineEditValidate *InputUserId, *InputUserPass, *InputUserPerm;
    QRegExpValidator *ValidPass, *ValidNumber;
    QLabel *UserId, *UserPass, *UserPerm, *AllUsers, *LabelMod;
    QScrollArea *ViewUsersArea;

    QVBoxLayout *Labels, *LineEdits, *Content, *LeftBox, *RightBox, *LeftContent, *RightContent;
    QHBoxLayout *Buttons, *All, *HContent;

signals:

    // definesc semnalul de modificare a unui user, voi apela din nou threadul de vizualizare
    void UsersSignalModify(int how);

public slots:

    // slotul care se executa la apasarea inceput sau la orice modificare
    void UserViewUsersAttempt();

    // slotul care se executa la terminarea threadului de vizualizare
    void ServerViewUsersAnswer(int how);

    // slotul care se executa la apasarea butonului de deconectare
    void UserModifyAttempt();

    // slotul care se executa la terminarea threadului care ii comunica serverului dorinta de deconectare a utilizatorului
    void ServerModifyUsersAnswer(int how);

    // slotul care imi activeaza/dezactiveaza butonul de modificare al parolei
    void onInputEdit();

    // slotul care se executa la apasarea butonului de anulare
    void onCloseDialog();

};
//----
// clasa element a interfetei utilizator care reprezinta butonul de adaugare a unei noi stiri, permisiunea pentru el >=2
class AddNewsButton: public QPushButton
{
    Q_OBJECT

 public:

   static QWidget * CreateAddNewButton(QWidget *parent = 0);

    AddNewsButton(QString &text, QWidget *parent = 0);
    ~AddNewsButton();

};

// clasa element in clasa privata User, Dialogul pentru modificarea de parola a contului user-ului
class UserModifyPassDialog: public QDialog
{
    Q_OBJECT

public:

    // constructor
    UserModifyPassDialog(QWidget *parent = 0);

    // functia de creare creare al carei pointer o voi da pentru apelarea in crearea de interfata
    //QWidget *CreateFunction(QWidget * parent);

    // destructor
    ~UserModifyPassDialog();

private:

    // elementele de interfata folosite aici;
    QPushButton *Modify, *Cancel;
    LineEditValidate *InputNewPass, *InputConfPass;
    QRegExpValidator *ValidPass;
    QLabel *NewPass, *ConfPass;
    QVBoxLayout *Labels, *LineEdits, *All;
    QHBoxLayout *Content, *Buttons;

    // threadul de comunicare cu serverul
     CommunicationThread *ModifyPassThread;

signals:

    // definesc semnalul de modificare a parolei
    void UserSignalModifyPass(int how);

public slots:

    // slotul care se executa la apasarea butonului de deconectare
    void UserModifyPassAttempt();

    // slotul care se executa la terminarea threadului care ii comunica serverului dorinta de deconectare a utilizatorului
    void ServerModifyPassAnswer(int how);

    // slotul care imi activeaza/dezactiveaza butonul de modificare al parolei
    void onPassInputEdit();

    // slotul care se executa la apasarea butonului de anulare
    void onCloseDialog();

};

// clasa element in clasa privata User, Dialogul pentru crearea,modificarea de stire
class UserAddNewsDialog: public QDialog
{
    Q_OBJECT

public:

    // constructor
    UserAddNewsDialog(QWidget *parent = 0, int id = -1, QString *title = 0, QString * content = 0, int cat = -1);

    // functia de incarcare a continutului
    void LoadData(int id, QString title, QString content, int cat);

    // settter pentru widgetul de la primesc cereri de modificare
    void setWidgetModifyRequest(QWidget * backto);

    // destructor
    ~UserAddNewsDialog();

private:

    // raspunsul cand modific o stire il trimit catre
    QWidget *BackTo;

    // stirea pentru care vreau sa modific
    int NewId;

    // elementele de interfata folosite aici;
    QLabel *Title, *Cat, *Description;
    LineEditValidate *InputTitle, *InputCatId;
    QTextEdit *InputContent;
    QPushButton *Modify, *Cancel;

    QRegExpValidator *ValidCatId, *ValidTitle;

    QVBoxLayout * LeftVBox, *RightVBox, *All;
    QHBoxLayout *Top, *Bottom;

    // threaduri de comunicare cu serverul
     CommunicationThread *AddNewsThread;

 signals:

     // semnalul care ii spune parintelui ca am terminat, deci ma poate sterge
     void Done();

     // semnalul prin care ii spun requester-ului meu ca am updatat cu succes stirea si ii trimit continul noii stiri
     void Updated(int id, QString title, QString Date, QString content, int cat);

public slots:

    // slotul care se executa la apasarea butonului de creare/modificare
    void UserAddNewsAttempt();

    // slotul care se executa la terminarea threadului care ii comunica serverului dorinta de deconectare a utilizatorului
    void ServerAddNewsAnswer(int how);

    // slotul care imi activeaza/dezactiveaza butonul de crearea/modificare
    void onNewsInputEdit();

    // slotul care se executa la apasarea butonului de anulare
    void onCloseDialog();
};

// clasa interata a spatiului privat
class UserPrivateSpace: public QWidget
{
    Q_OBJECT

public:
    // declar map-ul in care voi retine id-ul unui Widget, permisiunea lui precum si sa de functia de creare
    QMap<int, Nod> WidgetMap;

    // declar Lista in care voi retine obiectele ce vor fi create pentru a le sterge la deconectare
    QList<QWidget*> WidgetList;

    // constructor
    UserPrivateSpace(QWidget *parent = 0);

    // setter pentru id
    void SetUserId(int id);

    // getter pentru id
    int GetUserId();

    // declar functia care imi adauga la lista mea de Widget-uri din interfata utilizatorului, cu un id si pentu o anume permisiune
    bool AddWidget(int WidgetId, int WidgetPerm, CreateWidget function);

    // declar functia de eliminare a unui Widget din interfata
    bool RemoveWidget(int WidgetId);

    // declar functia care imi permite creeaza interfata in functie de permisiunile utilizatorului curent
    void SetUserType(int perm);

    // declar functia care imi distruge interfata creata pentru utlizatorul care se deconecteaza
    void DestroyUserInterface();

    // destructor
    ~UserPrivateSpace();

private:

    // declar id-ul utilizatorului
    int id;

    // declar thread-urile folosite
    CommunicationThread *DeconnectThread;

    // declar elementele de interfata folosite
    QPushButton *UserButtonDeconnect, *UserButtonModifyPass;

    QLabel *title;

    // dialogurile pentru comunicarea cu utilizatorul
    UserModifyPassDialog *ModifyDialog;
    UserAddNewsDialog *AddNewsDialog;
    UserAddModCatDialog *AddCatDialog, *ModCatDialog;
    UserDelCatDialog *DelCatDialog;
    UsersViewModifyDialog *UsersManageDialog;

signals:

    // definesc semnalul de deconectare
    void UserSignalDeconnect(int how);

    // definesc semnalul care anunta modificare utilizatorului
    // va fi conectat cu update stiri, categorii (+ userii daca e admin)
    void UserIdModified(int id);

    // definesc semnalul care receptioneaza dorinta utilizatorului de a crea o noua stire
    void AddNew();

    // definesc semnalul care receptioneaza dorinta utilizatoruui de a modifica o stire curenta
    void ModifyNew(int id, QString title, QString content, int cat, QWidget *from);

    // definesc semnalul care receptioneaza dorinta utilizatorului de a crea o noua categorie
    void AddNewCat();

    // definesc semnalul care receptioneaza dorinta utilizatorului de a modifica o categorie
    void ModifyCat();

    // definesc semnalul care receptioneaza dorinta utilizatorului de a sterge o categorie
    void RemoveCat();

    // definesc semnalul ADMIN
    void ViewUsers();

public slots:

    // slotul care se executa la apasarea butonului de deconectare
    void UserDeconnectAttempt();

    // slotul care se executa la terminarea threadului care ii comunica serverului dorinta de deconectare a utilizatorului
    void ServerDeconnectAnswer(int how);

    // slotul care imi creeaza Dialogul pentru adaugarea de stiri, nu are nevoie de parametrii
    void CreateAddNewsDialog();

    // slotul care imi creeaza Dialogul pentru mofificarea unei stiri, are nevoie de parametrii
    void CreateModNewsDialog(int id, QString title, QString content, int cat, QWidget *from);

    // slotul care imi creeaza Dialogul pentru adaugarea de categorii, nu are nevoie de parametrii
    void CreateAddCatDialog();

    // slotul care imi creeaza Dialogul pentru modificarea de categorii, nu are nevoie de parametrii
    void CreateModCatDialog();

    // slotul care imi creeaza Dialogul pentru stergerea de categorii, nu are nevoie de parametrii
    void CreateDelCatDialog();

     // slotul care imi creeaza user manage dialog
    void CreateUsersManageDialog();


    // slotul care imi sterge Dialogurile create, sau inca deschise
    void DeleteDialogs();


};

#endif // USERPRIVATESPACE_H

