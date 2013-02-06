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

#include "useraddcat.h"

// -------------------------BEGIN---------------------------------------------------------------
// constructorul si medodele clasei de creaare/modificare a unei categorii
UserAddModCatDialog::UserAddModCatDialog(QWidget *parent, int Mode)
{
    // setez parintele
    setParent(parent);

    // setez modul de construire
    mode = Mode;

    if(!mode)
        setWindowTitle("Newshaolin | Creare categorie");
    else
        setWindowTitle("Newshaolin | Modificare categorie");

    // incep crearea elementelor de interfata

    //label
    if(mode)
        if(!(CatId = new QLabel("<b>ID: </b>")))
            exit(0);

    if(!(CatName = new QLabel("<b>Nume: </b>")))
        exit(0);

    // label
    if(!(CatParent = new QLabel("<b>ID Parinte: </b>")))
        exit(0);

    // validatorul pentru inputul id-ului precum si id-ului parintelui
    if(!(ValidIdANDParent = new QRegExpValidator(QRegExp("^[0-9]+$"), this)))
        exit(0);

    // validatorul pentru inputul numelui categoriei
    if(!(ValidName = new QRegExpValidator(QRegExp("^[^|]{1,256}$"), this)))
        exit(0);

    //  LineEditValidate
    if(mode)
        if (!(InputId = new LineEditValidate(ValidIdANDParent, this)))
            exit(0);

    if (!(InputName = new LineEditValidate(ValidName, this)))
        exit(0);

    if (!(InputParent = new LineEditValidate(ValidIdANDParent, this)))
        exit(0);

    // butonul de trimitere a comnezii
    if(mode)
    {
        if(!(Modify = new QPushButton("modifica", this)))
            exit(0);
    }
    else
        if(!(Modify = new QPushButton("adauga", this)))
            exit(0);

    // il fac disabled pentur a permite apoi enable
    Modify->setEnabled(0);

    // butonul de inchidere al dialogului
    if(!(Cancel = new QPushButton("anuleaza", this)))
        exit(0);

    // asociez functionalitatea butoanelor create
    connect(Modify, SIGNAL(clicked()), this, SLOT(UserAddModCatAttempt()));
    connect(Cancel, SIGNAL(clicked()), this, SLOT(onCloseDialog()));

    // asociez modificarile asupra lineediturile cu slotul crea de mine si deci cu activarea/dezactivarea butonului de modify
    if(mode)
        connect(InputId, SIGNAL(textChanged(QString)), this, SLOT(onInputEdit()));

    connect(InputName, SIGNAL(textChanged(QString)), this, SLOT(onInputEdit()));
    connect(InputParent, SIGNAL(textChanged(QString)), this, SLOT(onInputEdit()));

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
    if(mode)
        Labels->addWidget(CatId);

    Labels->addWidget(CatName);
    Labels->addWidget(CatParent);

    if(mode)
        LineEdits->addWidget(InputId);

    LineEdits->addWidget(InputName);
    LineEdits->addWidget(InputParent);

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

// definesc slotul care imi trimite comanda catre server
void UserAddModCatDialog::UserAddModCatAttempt()
{
    //char *comanda = 0;
    QString aux2("|");

    if(mode)
    {
        // comanda de modificare categorie
        QString aux("modcat|");
        handle_string(comanda, aux, 0);
        comanda = tmp;

        // adaug id-ul introdus
        handle_string(comanda, InputId->text(), 1);
        comanda = tmp;

        // adaug separatorul
        handle_string(comanda, aux2, 1);
        comanda = tmp;
    }
    else
    {
        // comanda de creare categorie
        QString aux("addcat|");

        handle_string(comanda, aux, 0);
        comanda = tmp;
    }

    // adaug numele introdus
    handle_string(comanda, InputName->text(), 1);
    comanda = tmp;

    // adaug separatorul
    handle_string(comanda, aux2, 1);
    comanda = tmp;

    // adaug parintele introdus
    handle_string(comanda, InputParent->text(), 1);
    comanda = tmp;

    // creez threadul
    AddModCatThread = new CommunicationThread(sd, comanda, this);

    // realizez asocierea
    connect(AddModCatThread, SIGNAL(Over(int)), this, SLOT(ServerAddModCatAnswer(int)));

    // pornesc threadul
    AddModCatThread->start();
}

// definesc slotul care imi preaia raspunsul de la server
void UserAddModCatDialog::ServerAddModCatAnswer(int how)
{
    if (how == 1)
    {
        QString message = AddModCatThread->getResponse();

        // inchid threadul
        AddModCatThread->quit();

        if (message.startsWith("success"))
        {
            // daca sunt dialog de modificare al categoriilor am si un text din line-ul ID de sters
            if(mode)
                InputId->setText("");

            InputName->setText("");
            InputParent->setText("");

            QMessageBox::information(this, "newshaolin | info", "Actiune efectuata cu succes!\n" + message,
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

    emit UserSignalModifyCat(how);
}

// definesc slotul care activeaza/dezactiveaza butonul de modificare/adaugare
void UserAddModCatDialog::onInputEdit()
{
    if(mode)
    {
        if((InputId->validate(InputId->text(), InputId->text().size()) == QRegExpValidator::Acceptable)
        && (InputName->validate(InputName->text(), InputName->text().size()) == QRegExpValidator::Acceptable)
        && (InputParent->validate(InputParent->text(), InputParent->text().size()) == QRegExpValidator::Acceptable))
        {
            this->Modify->setEnabled(1);
        }
        else
        {
            this->Modify->setEnabled(0);
        }
    }
    else
    {
       if((InputName->validate(InputName->text(), InputName->text().size()) == QRegExpValidator::Acceptable)
        && (InputParent->validate(InputParent->text(), InputParent->text().size()) == QRegExpValidator::Acceptable))
        {
            this->Modify->setEnabled(1);
        }
        else
        {
            this->Modify->setEnabled(0);
        }
    }
}

// definesc slotul care se executa la apasarea butonului de anulare
void UserAddModCatDialog::onCloseDialog()
{
    this->close();
    if(mode)
       InputId->setText("");

    InputName->setText("");
    InputParent->setText("");
}


// destructor
UserAddModCatDialog::~UserAddModCatDialog()
{
    // elementele de interfata folosite, eliberez spatiul de memorie utilizat
    if(mode)
    {
        delete InputId;
        delete CatId;
    }
    delete InputName;
    delete InputParent;
    delete ValidIdANDParent;
    delete ValidName;
    delete CatName;
    delete CatParent;
    delete AddModCatThread;
    delete Modify;
    delete Cancel;
    delete Labels;
    delete LineEdits;
    delete Buttons;
    delete Content;
    delete All;
}

// ---------------------------END----------------------------------------------------------------

// -------------------------BEGIN----------------------------------------------------------------
// constructorul si metodele butonului de adaugare a unei stiri
AddCatButton::AddCatButton(QString &text, QWidget *parent)
{
    // setez parintele obiectului
    this->setParent(parent);

    // setez textul care va apare pe buton, dar ii dau posibilitatea de a-l redenumi
    this->setText(text);

    // il pozitionez pe ecran
    this->move(140, 575);

    // ii dau hide, pentru ca apoi sa ii dau show din WidgetList
    this->hide();

    // realize conectul la apasarea butonului de click
    connect(this, SIGNAL(clicked()), parent, SIGNAL(AddNewCat()));

}

// functia care imi apeleaza constructorul cu parinte dat de mine si imi returneaza pointer catre elementul nou creat;
QWidget * AddCatButton::CreateAddCatButton(QWidget *parent)
{
    // ii asociez numele
    QString text("Adauga");

    // apelez constructorul
    return new AddCatButton(text, parent);
}


// destructor
AddCatButton::~AddCatButton()
{
    // nimic
}
// ---------------------------END----------------------------------------------------------------

// -------------------------BEGIN----------------------------------------------------------------
// constructorul si metodele butonului de modificare a unei categorii
ModCatButton::ModCatButton(QString &text, QWidget *parent)
{
    // setez parintele obiectului
    this->setParent(parent);

    // setez textul care va apare pe buton, dar ii dau posibilitatea de a-l redenumi
    this->setText(text);

    // il pozitionez pe ecran
    this->move(140, 615);

    // ii dau hide, pentru ca apoi sa ii dau show din WidgetList
    this->hide();

    // realize conectul la apasarea butonului de click
    connect(this, SIGNAL(clicked()), parent, SIGNAL(ModifyCat()));

}

// functia care imi apeleaza constructorul cu parinte dat de mine si imi returneaza pointer catre elementul nou creat;
QWidget * ModCatButton::CreateModCatButton(QWidget *parent)
{
    // ii asociez numele
    QString text("Modifica");

    // apelez constructorul
    return new ModCatButton(text, parent);
}


// destructor
ModCatButton::~ModCatButton()
{
    // nimic
}
// ---------------------------END----------------------------------------------------------------

// -------------------------BEGIN----------------------------------------------------------------
// constructorul si metodele butonului de stergere a unei categorii
DelCatButton::DelCatButton(QString &text, QWidget *parent)
{
    // setez parintele obiectului
    this->setParent(parent);

    // setez textul care va apare pe buton, dar ii dau posibilitatea de a-l redenumi
    this->setText(text);

    // il pozitionez pe ecran
    this->move(140, 650);

    // ii dau hide, pentru ca apoi sa ii dau show din WidgetList
    this->hide();

    // realize conectul la apasarea butonului de click
    connect(this, SIGNAL(clicked()), parent, SIGNAL(RemoveCat()));

}

// functia care imi apeleaza constructorul cu parinte dat de mine si imi returneaza pointer catre elementul nou creat;
QWidget * DelCatButton::CreateDelCatButton(QWidget *parent)
{
    // ii asociez numele
    QString text("Sterge");

    // apelez constructorul
    return new DelCatButton(text, parent);
}

// destructor
DelCatButton::~DelCatButton()
{
    // nimic
}
// ---------------------------END----------------------------------------------------------------

// constructorul si medodele clasei de stergere a unei categorii
UserDelCatDialog::UserDelCatDialog(QWidget *parent)
{
    // setez parintele
    setParent(parent);

    // setez titlul
    setWindowTitle("Newshaolin | Stergere categorie");

    // incep crearea elementelor de interfata

    //label-ul si line editul pentru Parola curenta

    if(!(CatId = new QLabel("<b>ID categorie: </b>")))
        exit(0);

    // validatorul pentru inputul id-ului precum si id-ului parintelui
    if(!(ValidId = new QRegExpValidator(QRegExp("^[0-9]+$"), this)))
        exit(0);


    //  LineEditValidate
    if (!(InputId = new LineEditValidate(ValidId, this)))
        exit(0);

    // butonul de stergere al categoriei
    if(!(Modify = new QPushButton("sterge", this)))
            exit(0);

    // il fac disabled pentur a permite apoi enable
    Modify->setEnabled(0);

    // butonul de inchidere al dialogului
    if(!(Cancel = new QPushButton("anuleaza", this)))
        exit(0);

    // asociez functionalitatea butoanelor create
    connect(Modify, SIGNAL(clicked()), this, SLOT(UserDelCatAttempt()));
    connect(Cancel, SIGNAL(clicked()), this, SLOT(onCloseDialog()));

    // asociez modificarile cu functia care seteaza ca valid butonul de sterge
    connect(InputId, SIGNAL(textChanged(QString)), this, SLOT(onInputEdit()));

    // creez aranjarile in pagina

    if(!(Buttons = new QHBoxLayout()))
        exit(0);

    if(!(Content = new QHBoxLayout()))
        exit(0);

    if(!(All = new QVBoxLayout()))
        exit(0);

    // pentru fiecare vbox contentul sau
    Content->addWidget(CatId);
    Content->addSpacing(20);
    Content->addWidget(InputId);

    // adaugarea butoanelor la
    Buttons->addWidget(Modify);
    Buttons->addSpacing(10);
    Buttons->addWidget(Cancel);

    // continutul
    All->addLayout(Content);
    All->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
    All->addLayout(Buttons);

    // setez aranjarea in pagina pentru obiectul curent
    setLayout(All);
}

// definesc functia de trimitere a comenzii la server
void UserDelCatDialog::UserDelCatAttempt()
{
    //char *comanda = 0;
    QString aux2("|");

    // comanda de creare categorie
    QString aux("delcat|");

    handle_string(comanda, aux, 0);
    comanda = tmp;

    // adaug id-ul introdus
    handle_string(comanda, InputId->text(), 1);
    comanda = tmp;

    // creez threadul
    DelCatThread = new CommunicationThread(sd, comanda, this);

    // realizez asocierea
    connect(DelCatThread, SIGNAL(Over(int)), this, SLOT(ServerDelCatAnswer(int)));

    // pornesc threadul
    DelCatThread->start();
}

// definesc functia unde preiau raspunsul de la server
void UserDelCatDialog::ServerDelCatAnswer(int how)
{
    if (how == 1)
    {
        QString message = DelCatThread->getResponse();

        // inchid threadul
        DelCatThread->quit();

        if (message.startsWith("success"))
        {

            InputId->setText("");

            QMessageBox::information(this, "newshaolin | info", "Actiune efectuata cu succes!\n" + message,
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

    emit UserSignalDelCat(how);
}

// definesc functia de activare/dezactivare a butonului de stergere
void UserDelCatDialog::onInputEdit()
{

     if((InputId->validate(InputId->text(), InputId->text().size()) == QRegExpValidator::Acceptable))
       {
            this->Modify->setEnabled(1);
        }
        else
        {
            this->Modify->setEnabled(0);
        }
}

// definesc slotul care se executa la apasarea butonului de anulare
void UserDelCatDialog::onCloseDialog()
{
    this->close();
   InputId->setText("");
}

// destructorul
UserDelCatDialog::~UserDelCatDialog()
{
    // stert elementele de interfata folosite
    delete InputId;
    delete CatId;
    delete ValidId;
    delete Modify;
    delete Cancel;
    delete Buttons;
    delete Content;
    delete All;

    // si threadul
    delete DelCatThread;
}

// ---------------------------END----------------------------------------------------------------

