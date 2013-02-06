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

#include "userprivatespace.h"

UserPrivateSpace::UserPrivateSpace(QWidget *parent): ModifyDialog(0), AddNewsDialog(0),
AddCatDialog(0), ModCatDialog(0), DelCatDialog(0), UsersManageDialog(0)
{

    // setez parintele
    this->setParent(parent);

    // modific dimensiunile obiectului
    //this->setGeometry(0,0, parent->width(), parent->height());
    this->resize(parent->width(), parent->height());

    // creez interfata privata a utilizatorului, partile comune tuturor tipurilor de utilizator

    if(!(title = new QLabel("<h1>new<font color='#ff6600'>shaolin</font></h1><hr />", this)))
        exit(0);

    title->setGeometry(40,40, title->width()*1.85, title->height()*2);

     // creez butonul de deconectare ca utilizator
    if (!(UserButtonModifyPass = new QPushButton(" Cont/Parola", this)))
        exit(0);

    // setez butonului petrnu cont un tooltip
    UserButtonModifyPass->setToolTip("modificarea contului");

    // il pozitionez pe ecran
    UserButtonModifyPass->move(width() - 100, 60);

    if(!(ModifyDialog = new UserModifyPassDialog()))
        exit(0);

    // ii asociez semnalul la click
    connect(UserButtonModifyPass, SIGNAL(clicked()), ModifyDialog, SLOT(show()));

    // il afisez pe ecran
    UserButtonModifyPass->show();


    // creez butonul de deconectare ca utilizator
    if (!(UserButtonDeconnect = new QPushButton("deconectare", this)))
        exit(0);

    // setez un tooltip
    UserButtonDeconnect->setToolTip("deconectare ca utilizator");

    // il pozitionez pe ecran
    UserButtonDeconnect->move(width() - 100, 20);

    // ii asociez semnalul la click
    connect(UserButtonDeconnect, SIGNAL(clicked()), this, SLOT(UserDeconnectAttempt()));

    // asociez semnalului de primire al deconectarii pentru a asigura comunicarea intre parinte si fiu
    connect(this, SIGNAL(UserSignalDeconnect(int)), parent, SLOT(SuccessfullUserDeconnect(int)));

    // il afisez pe ecran
    UserButtonDeconnect->show();

    // asociez semnalului de primire a dorintei de introducere a unei noi stiri, cu slotul care imi creeaza widget
    connect(this, SIGNAL(AddNew()), this, SLOT(CreateAddNewsDialog()));

    // asociez semanlul de creare a unui dialog de modificare a unei stiri
    connect(this, SIGNAL(ModifyNew(int, QString, QString, int, QWidget*)),
            this, SLOT(CreateModNewsDialog(int, QString, QString ,int, QWidget *)));

    // asociez semnalului de primire a dorintei de introducere a unei noi categorii, cu slotul care imi creeaza widget
    connect(this, SIGNAL(AddNewCat()), this, SLOT(CreateAddCatDialog()));

    // asociez semnalului de primire a dorintei de modificare a unei categorii, cu slotul care imi creeaza widget
    connect(this, SIGNAL(ModifyCat()), this, SLOT(CreateModCatDialog()));

    // asociez semnalului de primire a dorintei de stergere a unei categorii, cu slotul care imi creeaza widget
    connect(this, SIGNAL(RemoveCat()), this, SLOT(CreateDelCatDialog()));

    // asociez semanlul de primire a dorintei de vizul
    connect(this, SIGNAL(ViewUsers()), this, SLOT(CreateUsersManageDialog()));

    // - deconectez ca utilizator
    connect(UserButtonDeconnect, SIGNAL(clicked()), this, SLOT(DeleteDialogs()));

    // asociez creearea butoane in functie de permisiuni

    // cititor
    AddWidget(1, 1, ViewCats::CreateWiewCats);
    AddWidget(2, 1, ViewNews::CreateViewNews);

    // cititor - publicator stiri
    AddWidget(3, 2, AddNewsButton::CreateAddNewButton);

    // cititor -publicator stiri si categorii
    AddWidget(4, 3, AddCatButton::CreateAddCatButton);
    AddWidget(5, 3, ModCatButton::CreateModCatButton);
    AddWidget(6, 3, DelCatButton::CreateDelCatButton);

    // admin
    AddWidget(7, 4, UsersViewModifyButton::CreateUsersViewModifyButton);
}

// slotul care se executa la apasarea butonului de deconectare
void UserPrivateSpace::UserDeconnectAttempt()
{
    char *comanda = 0;

    fprintf(stdout, "attept to disconnect\n");
    fflush(stdout);


    QString aux("dconnuser");
    handle_string(comanda, aux, 0);
    comanda = tmp;

    fprintf(stdout, "\n[UserPrivateSpace] Creez thread de deconectare\n");
         fflush(stdout);

    DeconnectThread = new CommunicationThread(sd, comanda, this);

    connect(DeconnectThread, SIGNAL(Over(int)), this, SLOT(ServerDeconnectAnswer(int)));

    fprintf(stdout, "\n[UserPrivateSpace] incep executia threadului\n");
         fflush(stdout);

    DeconnectThread->start();

    }

// slotul care se executa la terminarea threadului
void UserPrivateSpace::ServerDeconnectAnswer(int how)
{
    if (how == 1)
    {
        QString message = DeconnectThread->getResponse();

        if (QString::compare(message, "success") == 0)
        {

            // sterg identitatea userului
            UserId = -1;

            QMessageBox::information(this, "newshaolin | info", "Te-ai deconectat cu succes!\n",
                                             QMessageBox::Ok);
        }
        else
        {
             QMessageBox::information(this, "newshaolin | info", "Eroare de tipul:\n" + message,
                                             QMessageBox::Ok);
        }

    }
    else
    {
         QMessageBox::information(this, "newshaolin | info", "Eroare fatala!  Comunicarea cu serverul s-a pierdut!",
                                             QMessageBox::Ok);
    }

    // inchid threadul
    DeconnectThread->quit();


    emit UserSignalDeconnect(how);
}

// destructorul
UserPrivateSpace::~UserPrivateSpace()
{
}

// setez id-ul utilizatorului conectat
void UserPrivateSpace::SetUserId(int id)
{
     // updatez id-ul si imi trimit semnal de modificare pentru ca elementele respective sa isi modifice si ele continutul
    this->id = id;
    UserId = id;

    emit UserIdModified(id);
}

// definesc getter-ul pentru id
int UserPrivateSpace::GetUserId()
{
     return this->id;
}

// definesc slotul care imi creeaza Dialogul pentru adaugarea de stiri, nu are nevoie de parametrii
void UserPrivateSpace::CreateAddNewsDialog()
{
    // nu trebuie sa fie copilul meu pentru ca vreau sa fie o fereastra proprie
    if(!AddNewsDialog)
        AddNewsDialog = new UserAddNewsDialog();

    // afisez dialogul
    AddNewsDialog->show();

}

// definesc slotul care se executa la dorinta de a mofificarea o stire, are nevoie de parametrii
void UserPrivateSpace::CreateModNewsDialog(int id, QString title, QString content, int cat, QWidget *from)
{
    // nu trebuie sa fie copilul meu pentru ca vreau sa fie o fereastra proprie
    if(!AddNewsDialog)
    {
        AddNewsDialog = new UserAddNewsDialog(0, id, &title, &content, cat);

        // pentru a sti cui trimit inapoi
        AddNewsDialog->setWidgetModifyRequest(from);
    }
    else
    {
        // ii incarc datele corespunzatoare
        AddNewsDialog->LoadData(id, title, content, cat);

        // pentru a sti cui sa ii trimit inapoi
        AddNewsDialog->setWidgetModifyRequest(from);
    }
    // afisez dialogul
    AddNewsDialog->show();

}

// definesc slotul care se executa la dorinta utilizatorului de a crea o noua categorie
void UserPrivateSpace::CreateAddCatDialog()
{
    // nu trebuie sa fie copilul meu pentru ca vreau sa fie o fereastra proprie
    if(!AddCatDialog)
        AddCatDialog = new UserAddModCatDialog();

    // afisez dialogul
    AddCatDialog->show();

}

void UserPrivateSpace::CreateModCatDialog()
{
    // nu trebuie sa fie copilul meu pentru ca vreau sa fie o fereastra proprie
    if(!ModCatDialog)
        ModCatDialog = new UserAddModCatDialog(0,1);

    // afisez dialogul
    ModCatDialog->show();
}

void UserPrivateSpace::CreateDelCatDialog()
{
    // nu trebuie sa fie copilul meu pentru ca vreau sa fie o fereastra proprie
    if(!DelCatDialog)
        DelCatDialog = new UserDelCatDialog();

    // afisez dialogul
    DelCatDialog->show();
}

void UserPrivateSpace::CreateUsersManageDialog()
{
    // nu trebuie sa fie copilul meu pentru ca vreau sa fie o fereastra proprie
    if(!UsersManageDialog)
    {
        // creez
        UsersManageDialog = new UsersViewModifyDialog();

        // afisez
        UsersManageDialog->show();

    }
    else
    {
         // fac update la utilizatori
        UsersManageDialog->UserViewUsersAttempt();

        // afisez
        UsersManageDialog->show();
    }
}

void UserPrivateSpace::DeleteDialogs()
{
    // optimizare .. la deconectare aceste dialoguri nu vor fi sterse propriu zis
    // ci ele vor fi ascunse, iar pentru un alt doritor ele vor fi din nou reafisate
    if(AddNewsDialog)
    {
        AddNewsDialog->onCloseDialog();
    }

    if(ModifyDialog)
    {
        ModifyDialog->onCloseDialog();
    }

    if(AddCatDialog)
    {
        AddCatDialog->onCloseDialog();
    }

    if(ModCatDialog)
    {
        ModCatDialog->onCloseDialog();
    }

    if(DelCatDialog)
    {
        DelCatDialog->onCloseDialog();     
    }

    if(UsersManageDialog)
    {
        UsersManageDialog->onCloseDialog();

    }
}

// definesc functia care imi adauga la lista mea de Widget-uri din interfata utilizatorului, cu un id si pentu o anume permisiune
 bool UserPrivateSpace::AddWidget(int WidgetId, int WidgetPerm, CreateWidget function)
 {
     // creez nodul nou in care voi pune permisiunea si functia de crearea a obiectului
     Nod newNod;
     newNod.perm = WidgetPerm;
     newNod.functie = function;

     // daca inserarea se face cu succes intorc true, altfel false

     QTextStream out(stdout);
     out << " sunt in AddWidget\n apelez insert..." << endl;

    // declar iteratorul pentru a cauta in Map
    QMutableMapIterator<int, Nod> i(WidgetMap);

    // declar variabila (logica 0 - nu se gaseste, 1 - se gaseste)
    int ok = 0;

    for(i.toFront(); i.hasNext();)
    {
        i.next();

        if((i.key() == WidgetId))
        {
            ok = 1;
            break;
        }
    }

    if(!ok)
    {
        if(WidgetMap.insert(WidgetId, newNod) != WidgetMap.end())
        {
            out << "am apelat cu succes insert si intorc true..." << endl;
            return true;
        }
        else
        {
            out << "am apelat cu succes insert dar intorc false..." << endl;
            return false;
        }

    }
    else
    {
        out << "id existent, nu pot crea..." << endl;
        return false;
    }

}

// definesc functia de eliminare a unui Widget din interfata
bool UserPrivateSpace::RemoveWidget(int WidgetId)
{
    QTextStream out(stdout);
    out << " sunt in RemoveWidget\n apelez erase(find)..." << endl;

    WidgetMap.erase(WidgetMap.find(WidgetId));

    out << " am apelat cu succes, intorc true..." << endl;

    return true;
}

// definesc functia care imi permite creeaza interfata in functie de permisiunile utilizatorului curent
void UserPrivateSpace::SetUserType(int perm)
{
    QTextStream out(stdout);

    out << "apel setUserType" << endl;

    QMutableMapIterator<int, Nod> i(WidgetMap);

    for(i.toFront(); i.hasNext();)
    {
        i.next();

        out << "Elementul (id, perm): (" << i.key() << ", " << i.value().perm << ") ";

        if(i.value().perm <= perm)
        {
            out << "e creat!" << endl;

            // creez elementele care sunt valide pentru tipul de user care tocmai s-a conectat
            QWidget * newWidget = i.value().functie(this);

            // afisez elementul pe ecran
            newWidget->show();

            // il adaug la lista de pointeri pe care ii voi sterge la sfarsit;
            WidgetList.append(newWidget);
        }
        else
        {
            out << "NU e creat!" << endl;
        }
    }
}

// definesc functia care imi distruge interfata creata pentru utlizatorul care se deconecteaza
 void UserPrivateSpace::DestroyUserInterface()
 {

    QTextStream out(stdout);

      out << "\napel de DestroyUserInterface" << endl;


//    QMutableListIterator<QWidget*> i(WidgetList);
//    for(i.toFront(); i.hasNext();)
//    {
//        // pozitionez corect pozitia in lista a iteratorului
//        i.next();
//
//        out << "sterg widget-ul cu id-ul: " << WidgetList.at<< endl;
//        QWidget * removeWidget = i.value();
//
//        if(removeWidget)
//           delete removeWidget;
//    }

      for(int i = 0; i <WidgetList.count(); i++)
      {
          out << "sterg widget-ul: " << WidgetList.at(i) << endl;
          QWidget * removeWidget = WidgetList.at(i);

          if(removeWidget)
             delete removeWidget;
      }

    //golesc lista de pointerii care deja i-am sters mai sus
     WidgetList.clear();
 }
// ---------------------------END---------------------------------------------------------------


// -------------------------BEGIN---------------------------------------------------------------
// constructorul si medodele clasei de modificare a contului curent
UserModifyPassDialog::UserModifyPassDialog(QWidget *parent)
{
    // setez parintele
    this->setParent(parent);

    this->setWindowTitle("Newshaolin | Modificare cont");

    // incep crearea elementelor de interfata

    //label-ul si line editul pentru Parola curenta
    if(!(NewPass = new QLabel("<b>Noua parola: </b>")))
        exit(0);

    // label-ul si line editul pentru reconfirmarea Parolei curente
    if(!(ConfPass = new QLabel("<b>Confirma: </b>")))
        exit(0);

    // validatorul pentru inputul parolei la conectare
    if(!(ValidPass = new QRegExpValidator(QRegExp("^[a-zA-Z0-9_]{1,64}$"), this)))
        exit(0);

    //  LineEditValidate
     if (!(InputNewPass = new LineEditValidate(ValidPass, this)))
        exit(0);

     if (!(InputConfPass = new LineEditValidate(ValidPass, this)))
        exit(0);

    // butonul de trimitere a comnezii
    if(!(Modify = new QPushButton("modifica", this)))
        exit(0);

    // il fac disabled pentur a permite apoi enable
    Modify->setEnabled(0);

    // butonul de inchidere al dialogului
    if(!(Cancel = new QPushButton("anuleaza", this)))
        exit(0);

    //setez tipului de afisarea al textului din line-editurile mele ca tip de parola
    InputNewPass->setEchoMode(QLineEdit::Password);
    InputConfPass->setEchoMode(QLineEdit::Password);

    // asociez functionalitatea butoanelor create
    connect(Modify, SIGNAL(clicked()), this, SLOT(UserModifyPassAttempt()));
    connect(Cancel, SIGNAL(clicked()), this, SLOT(onCloseDialog()));

    // asociez modificarile asupra lineediturile cu slotul crea de mine si deci cu activarea/dezactivarea butonului de modify
    connect(InputNewPass,SIGNAL(textChanged(QString)), this, SLOT(onPassInputEdit()));
    connect(InputConfPass,SIGNAL(textChanged(QString)), this, SLOT(onPassInputEdit()));

    // creez aranjarile in pagina
    if(!(Labels = new QVBoxLayout()))
        exit(0);

    if(!(LineEdits = new QVBoxLayout()))
        exit(0);

    if(!(Buttons = new QHBoxLayout()))
        exit(0);

    if(!(Content = new QHBoxLayout()))
        exit(0);

    if(!(All = new QVBoxLayout()))
        exit(0);

    // pentru fiecare vbox contentul sau
    Labels->addWidget(NewPass);
    Labels->addWidget(ConfPass);

    LineEdits->addWidget(InputNewPass);
    LineEdits->addWidget(InputConfPass);

    // adaugarea butoanelor la
    Buttons->addWidget(Modify);
    Buttons->addSpacing(10);
    Buttons->addWidget(Cancel);

    // contentul prin label-uri si line_edituri
    Content->addLayout(Labels);
    Content->addLayout(LineEdits);

    // continutul
    All->addLayout(Content);
    All->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
    All->addLayout(Buttons);

    // setez aranjarea in pagina pentru obiectul curent
    this->setLayout(All);

}

void UserModifyPassDialog::UserModifyPassAttempt()
{
    char *comanda = 0;

    QString aux("moduser|");
    handle_string(comanda, aux, 0);
    comanda = tmp;

    handle_string(comanda, QString::number(UserId), 1);
    comanda = tmp;

    QString aux2("|");
    handle_string(comanda, aux2, 1);
    comanda = tmp;

    handle_string(comanda, InputNewPass->text(), 1);
    comanda = tmp;

    ModifyPassThread = new CommunicationThread(sd, comanda, this);

    connect(ModifyPassThread, SIGNAL(Over(int)), this, SLOT(ServerModifyPassAnswer(int)));

    ModifyPassThread->start();
}

void UserModifyPassDialog::ServerModifyPassAnswer(int how)
{
    if (how == 1)
    {
        QString message = ModifyPassThread->getResponse();

        if (QString::compare(message, "success") == 0)
        {
            InputConfPass->setText("");
            InputNewPass->setText("");

            QMessageBox::information(this, "newshaolin | info", "Parola modificata cu succes!\n",
                                             QMessageBox::Ok);
        }
        else
        {
             QMessageBox::information(this, "newshaolin | info", "Eroare de tipul:\n" + message,
                                             QMessageBox::Ok);
        }

    }
    else
    {
         QMessageBox::information(this, "newshaolin | info", "Eroare fatala!  Comunicarea cu serverul s-a pierdut!",
                                             QMessageBox::Ok);
    }

    // inchid threadul
        ModifyPassThread->quit();


    emit UserSignalModifyPass(how);
}

void UserModifyPassDialog::onPassInputEdit()
{
    if((InputNewPass->validate(InputNewPass->text(), InputNewPass->text().size()) == QRegExpValidator::Acceptable)
        && (InputConfPass->validate(InputConfPass->text(), InputConfPass->text().size()) == QRegExpValidator::Acceptable)
        && (InputConfPass->text() == InputNewPass->text()))
        {
            this->Modify->setEnabled(1);
        }
    else
        {
            this->Modify->setEnabled(0);
        }
}

void UserModifyPassDialog::onCloseDialog()
{
    this->close();
    InputNewPass->setText("");
    InputConfPass->setText("");
}

UserModifyPassDialog::~UserModifyPassDialog()
{
    delete Labels;
    delete LineEdits;
    delete Buttons;
    delete Content;
    delete All;
}
// ---------------------------END----------------------------------------------------------------

// -------------------------BEGIN----------------------------------------------------------------
// constructorul si metodele butonului de adaugare a unei stiri
AddNewsButton::AddNewsButton(QString &text, QWidget *parent)
{
    // setez parintele obiectului
    this->setParent(parent);

    // setez textul care va apare pe buton, dar ii dau posibilitatea de a-l redenumi
    this->setText(text);

    // il pozitionez pe ecran
    this->move(258, 125);

    // ii dau hide, pentru ca apoi sa ii dau show din WidgetList
    this->hide();

    // realize conectul la apasarea butonului de click
    connect(this, SIGNAL(clicked()), parent, SIGNAL(AddNew()));

}

// functia care imi apeleaza constructorul cu parinte dat de mine si imi returneaza pointer catre elementul nou creat;
QWidget * AddNewsButton::CreateAddNewButton(QWidget *parent)
{
    // ii asociez numele
    QString text("Adauga Stire");

    // apelez constructorul
    return new AddNewsButton(text, parent);
}

// destructor
AddNewsButton::~AddNewsButton()
{
    // nimic
}
// ---------------------------END----------------------------------------------------------------

// -------------------------BEGIN---------------------------------------------------------------
// constructorul si medodele clasei de creare/modificare a unei stiri
UserAddNewsDialog::UserAddNewsDialog(QWidget *parent, int id, QString *title, QString *content, int cat)
{
    // initial nu am nici un requester
    BackTo = 0;

    // setez parintele
    this->setParent(parent);

    // setez titlul
    this->setWindowTitle("Newshaolin | Adaugare stire");

    // incep crearea elementelor de interfata

    //label-ul pentru titlul stirii
    if(!(Title = new QLabel("<b>Titlu: </b>")))
        exit(0);

    // label-ul pentru Categoria stirii
    if(!(Cat = new QLabel("<b>ID Categorie: </b>")))
        exit(0);

    // label-ul pentru Categoria stirii
    if(!(Description = new QLabel("<b>Descriere: </b>")))
        exit(0);

    // validatorul pentru titlul stirii
    if(!(ValidTitle = new QRegExpValidator(QRegExp("^[^|]{1,256}$"), this)))
        exit(0);

    // validatorul pentru Categorie
    if(!(ValidCatId = new QRegExpValidator(QRegExp("^[0-9]+$"), this)))
        exit(0);

    //  LineEditValidate pentru titlul si categorie
     if (!(InputTitle = new LineEditValidate(ValidTitle, this)))
        exit(0);

     if (!(InputCatId = new LineEditValidate(ValidCatId, this)))
        exit(0);

     if (!(InputContent = new QTextEdit(this)))
        exit(0);

     // butonul de trimitere a comnezii
    if(!(Modify = new QPushButton("adauga", this)))
        exit(0);

    // il fac disabled pentur a permite apoi enable
    Modify->setEnabled(0);

    // butonul de inchidere al dialogului
    if(!(Cancel = new QPushButton("anuleaza", this)))
        exit(0);

    // asociez functionalitatea butoanelor create
    connect(Modify, SIGNAL(clicked()), this, SLOT(UserAddNewsAttempt()));
    connect(Cancel, SIGNAL(clicked()), this, SLOT(onCloseDialog()));

    // asociez modificarile asupra lineediturile cu slotul crea de mine si deci cu activarea
    // sau dezactivarea butonului de modify
    connect(InputCatId,SIGNAL(textChanged(QString)), this, SLOT(onNewsInputEdit()));
    connect(InputTitle,SIGNAL(textChanged(QString)), this, SLOT(onNewsInputEdit()));
    connect(InputContent,SIGNAL(textChanged()), this, SLOT(onNewsInputEdit()));

    // creez aranjarile in pagina
    if(!(LeftVBox = new QVBoxLayout()))
        exit(0);

    if(!(RightVBox = new QVBoxLayout()))
        exit(0);

    if(!(Bottom = new QHBoxLayout()))
        exit(0);

    if(!(Top = new QHBoxLayout()))
        exit(0);

    if(!(All = new QVBoxLayout()))
        exit(0);

    // pentru fiecare vbox contentul sau
    LeftVBox->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    LeftVBox->addSpacing(2);
    LeftVBox->addWidget(Title);
    LeftVBox->addSpacing(8);
    LeftVBox->addWidget(Cat);
    LeftVBox->addSpacing(6);
    LeftVBox->addWidget(Description);

    RightVBox->addWidget(InputTitle);
    RightVBox->addWidget(InputCatId);
    RightVBox->addWidget(InputContent);

    // top hbox
    Top->addLayout(LeftVBox);
    Top->addLayout(RightVBox);

    // bottom hbox
    Bottom->setAlignment(Qt::AlignRight| Qt::AlignTop);
    Bottom->addWidget(Modify);
    Bottom->addSpacing(10);
    Bottom->addWidget(Cancel);

    // continutul
    All->addLayout(Top);
    All->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
    All->addLayout(Bottom);

    // setez aranjarea in pagina pentru obiectul curent
    this->setLayout(All);

    NewId = id;

    if(NewId != -1 && cat != -1 && title && content)
    {
        QString category = QString::number(cat), ButtonMeaning = QString("modifica");
        InputCatId->setText(category);
        InputTitle->setText(*title);
        InputContent->setPlainText(*content);
        Modify->setText(ButtonMeaning);
        setWindowTitle("newshaolin | Modificare stire");
    }
}

void UserAddNewsDialog::LoadData(int id, QString title, QString content, int cat)
{
    // setez id-ul stirii curente
    NewId = id;

    QString category = QString::number(cat), ButtonMeaning = QString("modifica");
    InputCatId->setText(category);
    InputTitle->setText(title);
    InputContent->setPlainText(content);
    Modify->setText(ButtonMeaning);
    setWindowTitle("newshaolin | Modificare stire");
}

void UserAddNewsDialog::UserAddNewsAttempt()
{
    char *comanda = 0;
    if( NewId == -1)
    {
        QString aux("addnew|");
        handle_string(comanda, aux, 0);
        comanda = tmp;

        // adaug titlul stirii, name -ul
        handle_string(comanda, InputTitle->text(), 1);
        comanda = tmp;

        // adaug separatorul
        QString aux2("|");
        handle_string(comanda, aux2, 1);
        comanda = tmp;

        // adaug continutul stirii
        handle_string(comanda, InputContent->toPlainText(), 1);
        comanda = tmp;

        // adaug separatorul
        handle_string(comanda, aux2, 1);
        comanda = tmp;

        // adaug categoria
        handle_string(comanda, InputCatId->text(), 1);
        comanda = tmp;

        // creez thread-ul de comunicare cu serverul
        AddNewsThread = new CommunicationThread(sd, comanda, this);

        delete comanda;

        // conectez semnalul de terminare al threadului cu slotul care se va executa apoi
        connect(AddNewsThread, SIGNAL(Over(int)), this, SLOT(ServerAddNewsAnswer(int)));

        // pornesc threadul
        AddNewsThread->start();
    }
    else
    {
        QString aux("modnew|");
        handle_string(comanda, aux, 0);
        comanda = tmp;

        // adaug id-ul stirii
        handle_string(comanda, QString::number(NewId), 1);
        comanda = tmp;

        // adaug separatorul
        QString aux2("|");
        handle_string(comanda, aux2, 1);
        comanda = tmp;

        // adaug titlul stirii, name -ul
        handle_string(comanda, InputTitle->text(), 1);
        comanda = tmp;

        // adaug separatorul
        handle_string(comanda, aux2, 1);
        comanda = tmp;

        // adaug continutul stirii
        handle_string(comanda, InputContent->toPlainText(), 1);
        comanda = tmp;

        // adaug separatorul
        handle_string(comanda, aux2, 1);
        comanda = tmp;

        // adaug categoria
        handle_string(comanda, InputCatId->text(), 1);
        comanda = tmp;

        // creez thread-ul de comunicare cu serverul
        AddNewsThread = new CommunicationThread(sd, comanda, this);

        // pot sa sterg pointerul de comanda facut aici
        delete comanda;

        // conectez semnalul de terminare al threadului cu slotul care se va executa apoi
        connect(AddNewsThread, SIGNAL(Over(int)), this, SLOT(ServerAddNewsAnswer(int)));

        // pornesc threadul
        AddNewsThread->start();
    }
}

void UserAddNewsDialog::ServerAddNewsAnswer(int how)
{
    if (how == 1)
    {
        QString message = AddNewsThread->getResponse();

        if (message.startsWith("success"))
        {
            QMessageBox::information(this, "newshaolin | info", "Operatiune incheiata cu succes!\n",
                                             QMessageBox::Ok);

            if(NewId != -1)
            {
                int id = NewId, i;
                for(i = 0; i < GlobalNewsList.count(); i++)
                    if(GlobalNewsList[i].id == id)
                        break;

                QDateTime time = QDateTime::currentDateTime();
                QString format("yyyy-MM-dd hh:mm:ss");

                // fac update-urile necesare
                GlobalNewsList[i].Date = time.toString(format);
                GlobalNewsList[i].name = InputTitle->text();
                GlobalNewsList[i].Content = InputContent->toPlainText();
                GlobalNewsList[i].parent = InputCatId->text().toInt();

                // trimit semnalul ca am updatat cu succes stirea
                if(BackTo)
                {

                    emit Updated(NewId, InputTitle->text(), time.toString(format),
                             InputContent->toPlainText(), InputCatId->text().toInt());
                }

                // nu mai sunt modificator de stiri
                NewId = -1;

                // am onorat cererea
                BackTo = 0;
            }

            Modify->setText("adauga");
            setWindowTitle("newshaolin | Adaugare stire");
            InputCatId->setText("");
            InputTitle->setText("");
            InputContent->setPlainText("");
        }
        else
        {
             QMessageBox::information(this, "newshaolin | info", "Eroare de tipul:\n" + message,
                                             QMessageBox::Ok);
        }

    }
    else
    {
         QMessageBox::information(this, "newshaolin | info", "Eroare fatala!  Comunicarea cu serverul s-a pierdut!",
                                             QMessageBox::Ok);
    }

    // inchid threadu
    AddNewsThread->quit();
}

void UserAddNewsDialog::onNewsInputEdit()
{
    if((InputCatId->validate(InputCatId->text(), InputCatId->text().size()) == QRegExpValidator::Acceptable)
        && (InputTitle->validate(InputTitle->text(), InputTitle->text().size()) == QRegExpValidator::Acceptable)
        && (!InputContent->toPlainText().contains(QString("|"))) && InputContent->toPlainText().size() > 0)
        {
            this->Modify->setEnabled(1);
        }
    else
        {
            this->Modify->setEnabled(0);
        }
}

// setter-ul pentru widgetul care face o cerere de modificare
void UserAddNewsDialog::setWidgetModifyRequest(QWidget * backto)
{
    // setez backto cu cel din parametru
    BackTo = backto;

    // ii asociez conexiunea
    connect(this, SIGNAL(Updated(int, QString, QString, QString, int)), BackTo,
            SLOT(LoadData(int, QString, QString, QString, int)));
}

void UserAddNewsDialog::onCloseDialog()
{
    this->close();

    QString ButtonMeaning("adauga");

    Modify->setText(ButtonMeaning);
    setWindowTitle("newshaolin | Adaugare stire");
    InputCatId->setText("");
    InputTitle->setText("");
    InputContent->setPlainText("");
    NewId = -1;

    emit Done();
}

UserAddNewsDialog::~UserAddNewsDialog()
{
    delete All;
    delete Title;
    delete Cat;
    delete Description;
    delete InputTitle;
    delete InputCatId;
    delete InputContent;
    delete Modify;
    delete Cancel;
    delete ValidCatId;
    delete ValidTitle;
    delete LeftVBox;
    delete RightVBox;
    delete All;
    delete Top;
    delete Bottom;
    delete AddNewsThread;
}
// ---------------------------END----------------------------------------------------------------


// -------------------------BEGIN----------------------------------------------------------------
// constructorul si metodele butonului de vizualizare/modificare utilizatori, ADMIN
UsersViewModifyButton::UsersViewModifyButton(QString &text, QWidget *parent)
{
    // setez parintele obiectului
    this->setParent(parent);

    // setez textul care va apare pe buton, dar ii dau posibilitatea de a-l redenumi
    this->setText(text);

    // il pozitionez pe ecran
    this->move(parent->width() - 100, 100);

    // ii dau hide, pentru ca apoi sa ii dau show din WidgetList
    this->hide();

    // realize conectul la apasarea butonului de click
    connect(this, SIGNAL(clicked()), parent, SIGNAL(ViewUsers()));
}

// functia care imi apeleaza constructorul cu parinte dat de mine si imi returneaza pointer catre elementul nou creat;
QWidget * UsersViewModifyButton::CreateUsersViewModifyButton(QWidget *parent)
{
    // ii asociez numele
    QString text("Admin useri");

    // apelez constructorul
    return new UsersViewModifyButton(text, parent);
}

// destructor
UsersViewModifyButton::~UsersViewModifyButton()
{
    // nimic
}
// ---------------------------END----------------------------------------------------------------

// -------------------------BEGIN---------------------------------------------------------------
// constructorul si medodele clasei de creare/modificare a unei stiri
UsersViewModifyDialog::UsersViewModifyDialog(QWidget *parent): UsersModifyThread(0), UsersViewThread(0)
{
    // setez parintele
    this->setParent(parent);

    // setez titlul
    this->setWindowTitle("Newshaolin | Vizualizare | Modificare utilizatori");

    this->resize(800,600);

    // incep crearea elementelor de interfata

    // label
    if(!(AllUsers = new QLabel(this)))
        exit(0);

    if(!(UserId = new QLabel("<b>id: </b>")))
        exit(0);

    if(!(LabelMod = new QLabel("<h2>Modifica utlizator </h2>< /hr>")))
        exit(0);
    // label
    if(!(UserPass = new QLabel("<b>parola: </b>")))
        exit(0);

    // label
    if(!(UserPerm = new QLabel("<b>permisiuni: </b>")))
        exit(0);

    // validatorul pentru
    if(!(ValidPass = new QRegExpValidator(QRegExp("^[^|]{1,256}$"), this)))
        exit(0);

    // validatorul pentru
    if(!(ValidNumber = new QRegExpValidator(QRegExp("^[0-9]+$"), this)))
        exit(0);

    //  LineEditValidate
     if (!(InputUserId = new LineEditValidate(ValidNumber, this)))
        exit(0);

     if (!(InputUserPass = new LineEditValidate(ValidPass, this)))
        exit(0);

     if (!(InputUserPerm = new LineEditValidate(ValidNumber, this)))
        exit(0);

     // butonul de trimitere a comnezii
    if(!(Modify = new QPushButton("modifica", this)))
        exit(0);

    // il fac disabled pentu a permite apoi enable
    Modify->setEnabled(0);

    // butonul de inchidere al dialogului
    if(!(Cancel = new QPushButton("anuleaza", this)))
        exit(0);

    // asociez functionalitatea butoanelor create
    connect(Modify, SIGNAL(clicked()), this, SLOT(UserModifyAttempt()));
    connect(Cancel, SIGNAL(clicked()), this, SLOT(onCloseDialog()));

    // la mofificarea unui utilizator fac din nou updatarea ! ! !  !
    connect(this, SIGNAL(UsersSignalModify(int)), this, SLOT(UserViewUsersAttempt()));

    // asociez modificarile asupra lineediturile cu slotul crea de mine si deci cu activarea
    // sau dezactivarea butonului de modify
    connect(InputUserId,   SIGNAL(textChanged(QString)), this, SLOT(onInputEdit()));
    connect(InputUserPass, SIGNAL(textChanged(QString)), this, SLOT(onInputEdit()));
    connect(InputUserPerm, SIGNAL(textChanged(QString)), this, SLOT(onInputEdit()));

    // creez aranjarile in pagina
    if(!(All = new QHBoxLayout()))
        exit(0);

    if(!(LeftBox = new QVBoxLayout()))
        exit(0);

    if(!(RightBox = new QVBoxLayout()))
        exit(0);

    if(!(ViewUsersArea = new QScrollArea()))
        exit(0);

    if(!(LeftContent = new QVBoxLayout()))
        exit(0);

    if(!(RightContent = new QVBoxLayout()))
        exit(0);

    if(!(Content = new QVBoxLayout()))
        exit(0);

    if(!(HContent = new QHBoxLayout()))
        exit(0);

    if(!(Buttons = new QHBoxLayout()))
        exit(0);

    // incarc hbox-ul cu butoane
    Buttons->setAlignment(Qt::AlignRight | Qt::AlignTop);
    Buttons->addWidget(Modify);
    Buttons->addWidget(Cancel);

    // spacing ++
    LeftContent->addWidget(UserId);
    LeftContent->addWidget(UserPass);
    LeftContent->addWidget(UserPerm);

    // spacing ++
    RightContent->addWidget(InputUserId);
    RightContent->addWidget(InputUserPass);
    RightContent->addWidget(InputUserPerm);

    HContent->addLayout(LeftContent);
    HContent->addLayout(RightContent);

    Content->addSpacerItem(new QSpacerItem(0, 2300, QSizePolicy::Minimum, QSizePolicy::Maximum));
    Content->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
    Content->addWidget(LabelMod);
    Content->addSpacing(25);
    Content->addLayout(HContent);
    Content->addSpacerItem(new QSpacerItem(0, 2300, QSizePolicy::Minimum, QSizePolicy::Maximum));

    // incarc v box din dreapta
    RightBox->addLayout(Content);
    RightBox->addLayout(Buttons);

    ViewUsersArea->setWidget(AllUsers);

    // incarc v box din stanga
    LeftBox->addWidget(ViewUsersArea);

    All->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);

    // continutul
    All->addLayout(LeftBox);
    All->addLayout(RightBox);

    // setez aranjarea in pagina pentru obiectul curent
    setLayout(All);

    // tentativa de a afisa utilizatorii existenti
    UserViewUsersAttempt();

}
// tentativa de a vizualiza userii
void UsersViewModifyDialog::UserViewUsersAttempt()
{
    char *comanda = 0;

    QString aux("viewusers");
    handle_string(comanda, aux, 0);
    comanda = tmp;

    // creez thread-ul de comunicare cu serverul
    UsersViewThread = new CommunicationThread(sd, comanda, this);

    delete comanda;

    // conectez semnalul de terminare al threadului cu slotul care se va executa apoi
    connect(UsersViewThread, SIGNAL(Over(int)), this, SLOT(ServerViewUsersAnswer(int)));

    // pornesc threadul
    UsersViewThread->start();

}

// raspunsul de la server(tratare , how ==1 ==> threadul s-a executat cu succes)
void UsersViewModifyDialog::ServerViewUsersAnswer(int how)
{
    if (how == 1)
    {
        QString message = UsersViewThread->getResponse();

        if (message.startsWith("success"))
        {

            // preiau raspunsul il convertesc la un char* din std si il parsez

            char *string, sep [] = "|";
            if(!(string = (char *)malloc(sizeof(char) * (message.size() + 1))))
            {
               printf("Eroare la alocarea de memorie, inchid!");
               exit(0);
               memset(string, 0, message.size() + 1);
            };

            // copiez datele
            strcpy(string, message.toStdString().c_str());

           // imi creez pointer auxiliar si incep parsarea
            char *p = strtok(string, sep);

            // pentru verificare afisez mesaje la consola
            QTextStream out(stdout);

            QString parsed;

            while(p)
            {

                // preiau id-ul
                p = strtok(NULL, sep);
               if(p)
               {
                   parsed.append("\nUser <");
                   parsed.append(p);
                   parsed.append("> ");

               }

                // preiau numele
                p = strtok(NULL, sep);
                if(p)
                     {
                       parsed.append(" <");
                       parsed.append(p);
                       parsed.append("> ");
                     }

                // preiau permisiunile
                p = strtok(NULL, sep);
                if(p)
                   {
                       parsed.append(" <");
                       parsed.append(p);
                       parsed.append("> ");

                   }

                 //  NU preiau data
                p = strtok(NULL, sep);
             }

            // dealoc memoria folosita pentru containerul auxiliar
            if(string)
                delete string;

            //setez contentul utilizatori
            parsed.prepend(" <Permisiuni>");

            parsed.prepend(" <Nume> ");
            parsed.prepend("User <Id> ");

            AllUsers->setText(parsed);
            // setez dimensiunea optima contentului pentru textul introdus
            AllUsers->resize(AllUsers->sizeHint());

        }
        else
        {
             QMessageBox::information(this, "newshaolin | info", "Eroare de tipul:\n" + message,
                                             QMessageBox::Ok);
        }

    }
    else
    {
         QMessageBox::information(this, "newshaolin | info", "Eroare fatala!  Comunicarea cu serverul s-a pierdut!",
                                             QMessageBox::Ok);
    }

    //inchid threadul
        UsersViewThread->quit();

}

// tentativa
void UsersViewModifyDialog::UserModifyAttempt()
{
    char *comanda = 0;

    // comanda
    QString aux("moduser|");
    handle_string(comanda, aux, 0);
    comanda = tmp;

    // separator
    QString aux2("|");

    // adaug id-ul userului
    handle_string(comanda, InputUserId->text(), 1);
    comanda = tmp;

    // separator
    handle_string(comanda,aux2, 1);
    comanda = tmp;

    // adaug parola userului
    handle_string(comanda, InputUserPass->text(), 1);
    comanda = tmp;

    // separator
    handle_string(comanda,aux2, 1);
    comanda = tmp;

    // adaug permisiunea setata acum
    handle_string(comanda, InputUserPerm->text(), 1);
    comanda = tmp;

    // creez thread-ul de comunicare cu serverul
    UsersModifyThread = new CommunicationThread(sd, comanda, this);

    delete comanda;

    // conectez semnalul de terminare al threadului cu slotul care se va executa apoi
    connect(UsersModifyThread, SIGNAL(Over(int)), this, SLOT(ServerModifyUsersAnswer(int)));

    // pornesc threadul
    UsersModifyThread->start();

}

// tratare raspuns
void UsersViewModifyDialog::ServerModifyUsersAnswer(int how)
{
    if (how == 1)
    {
        QString message = UsersModifyThread->getResponse();

        if (message.startsWith("success"))
        {
            InputUserId->setText("");
            InputUserPass->setText("");
            InputUserPerm->setText("");

            // emit semnalul de updatare
            UsersSignalModify(1);
        }
        else
        {
             QMessageBox::information(this, "newshaolin | info", "Eroare de tipul:\n" + message,
                                             QMessageBox::Ok);
        }

    }
    else
    {
         QMessageBox::information(this, "newshaolin | info", "Eroare fatala!  Comunicarea cu serverul s-a pierdut!",
                                             QMessageBox::Ok);
    }

     // inchid threadul
     UsersModifyThread->quit();

}

// validarea inpututului/ activarea butonului sau dezactivarea lui
void UsersViewModifyDialog::onInputEdit()
{
    if((InputUserId->validate(InputUserId->text(), InputUserId->text().size()) == QRegExpValidator::Acceptable)
        && (InputUserPass->validate(InputUserPass->text(), InputUserPass->text().size()) == QRegExpValidator::Acceptable)
        && (InputUserPerm->validate(InputUserPerm->text(), InputUserPerm->text().size()) == QRegExpValidator::Acceptable))
        {
            this->Modify->setEnabled(1);
        }
    else
        {
            this->Modify->setEnabled(0);
        }
}

// inchiderea dialogului, golirea inputurilor ramase
void UsersViewModifyDialog::onCloseDialog()
{
    this->close();

    InputUserId->setText("");
    InputUserPass->setText("");
    InputUserPerm->setText("");
}

UsersViewModifyDialog::~UsersViewModifyDialog()
{
    delete Modify;
    delete Cancel;
    delete InputUserId;
    delete InputUserPass;
    delete InputUserPerm;
    delete ValidPass;
    delete ValidNumber;
    delete UserId;
    delete UserPass;
    delete UserPerm;
    delete AllUsers;
    delete ViewUsersArea;
    delete Labels;
    delete LineEdits;
    delete Buttons;
    delete UsersModifyThread;
    delete UsersViewThread;
}
// ---------------------------END----------------------------------------------------------------



