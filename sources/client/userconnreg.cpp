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

#include "userconnreg.h"

UserConnReg::UserConnReg(QWidget *parent, const int &wid, const int &hei)
{
    this->setParent(parent);

    resize(wid, hei);
    setGeometry(0, 0, wid, hei);

    parent->setWindowTitle("newshaolin :: conectare/inregistrare utilizator");
    //moveToCenter(this, wid, hei);

    if(!(Conn = new QLabel("<h3>Conectare</h3>")))
        exit(0);

    if(!(UserC = new QLabel("<b>Utilizator</b><br />ionel")))
        exit(0);

    // declar validatorul pentru inputul userului la conectare
    if(!(ValidUserC = new QRegExpValidator(QRegExp("^[a-zA-Z0-9_]{1,32}$"), this)))
        exit(0);

     if (!(LineEditUserC = new LineEditValidate(ValidUserC, this)))
        exit(0);

    //declar label-ul si line editul pentru Parola
    if(!(PassC = new QLabel("<b>Parola</b><br />salut234")))
        exit(0);

    // declar validatorul pentru inputul parolei la conectare
    if(!(ValidPassC = new QRegExpValidator(QRegExp("^[a-zA-Z0-9_]{1,64}$"), this)))
        exit(0);

     if (!(LineEditPassC = new LineEditValidate(ValidPassC, this)))
        exit(0);

    //label-ul si line-editul pentru Utilizator la Inregistrare
    if(!(Reg = new QLabel("<h3>Inregistrare</h3>")))
        exit(0);

    if(!(UserR = new QLabel("<b>Utilizator</b><br />ionel")))
        exit(0);

    // declar validatorul pentru inputul userului la conectare
    if(!(ValidUserR = new QRegExpValidator(QRegExp("^[a-zA-Z0-9_]{1,32}$"), this)))
        exit(0);

     if (!(LineEditUserR = new LineEditValidate(ValidUserR, this)))
        exit(0);

    //declar label-ul si line editul pentru Parola
    if(!(PassR = new QLabel("<b>Parola</b><br />salut234")))
        exit(0);

    // declar validatorul pentru inputul userului la conectare
    if(!(ValidPassR = new QRegExpValidator(QRegExp("^[a-zA-Z0-9_]{1,64}$"), this)))
        exit(0);

    if (!(LineEditPassR = new LineEditValidate(ValidPassR, this)))
        exit(0);

     connect(LineEditUserC, SIGNAL(textChanged(QString)), this, SLOT(onConnectInputEdit()));
     connect(LineEditPassC, SIGNAL(textChanged(QString)), this, SLOT(onConnectInputEdit()));

     connect(LineEditUserR, SIGNAL(textChanged(QString)), this, SLOT(onRegisterInputEdit()));
     connect(LineEditPassR, SIGNAL(textChanged(QString)), this, SLOT(onRegisterInputEdit()));

    if(!(uconnect = new QPushButton("Conectare")) || !(uregister = new QPushButton("Inregistrare")))
        exit(0);

    uconnect->setEnabled(0);
    uregister->setEnabled(0);

    QObject::connect(uconnect, SIGNAL(clicked()), this, SLOT(UserConnectAttempt()));
    QObject::connect(uregister, SIGNAL(clicked()), this, SLOT(UserRegisterAttempt()));

    if(!(all = new QVBoxLayout()) || !(title = new QLabel("<h1>new<font color='#ff6600'>shaolin</font></h1><hr />")))
        exit(0);

    //creez un hboxlayout unde voi pune conectarea si inregistrarea
    if(!(chbox1 = new QHBoxLayout()))
        exit(0);

     if(!(chbox2 = new QHBoxLayout()))
        exit(0);

     if(!(cvbox1 = new QVBoxLayout()))
        exit(0);

     if(!(cvbox2 = new QVBoxLayout()))
        exit(0);

     if(!(rhbox1 = new QHBoxLayout()))
        exit(0);

     if(!(rhbox2 = new QHBoxLayout()))
        exit(0);

     if(!(rvbox1 = new QVBoxLayout()))
        exit(0);

     if(!(rvbox2 = new QVBoxLayout()))
        exit(0);

    if(!(hbox = new QHBoxLayout()))
        exit(0);

     //creez vboxurile unde voi pune conectarea si inregistrarea
    if(!(box1 = new QVBoxLayout()) || !(box2 = new QVBoxLayout()))
        exit(0);

    //formularul din centru care va contine formularele de conectarea/inregistrarea
    if(!(form = new QWidget(this)))
        exit(0);

    //label-ul si butonul de tinut minte...
     if(!( ConnectRememberLabel = new QLabel("Tine-ma minte ", this)))
        exit(0);

     if(!( ConnectRemeberButton = new QCheckBox (this)))
        exit(0);

    //setez parametrii geometrici pentru form
    form->resize(705, 1000);

    //setez marginile pentru form
    form->setContentsMargins(100, 20, 0, 0);


    //setez afisarea de parola la QlineEdit-urile pentru conectare, inregistrare
    LineEditPassC->setEchoMode(QLineEdit::Password);
    LineEditPassR->setEchoMode(QLineEdit::Password);

    //apelez pentru box1,box2 ...

    handleHLabel(box1, Conn, chbox1, chbox2, cvbox1, cvbox2, UserC, PassC, LineEditUserC, LineEditPassC, uconnect, ConnectRememberLabel, ConnectRemeberButton);
    handleHLabelR(box2, Reg, rhbox1, rhbox2, rvbox1, rvbox2, UserR, PassR, LineEditUserR, LineEditPassR, uregister);

    hbox->addLayout(box1);
    hbox->addSpacing(25);
    hbox->addLayout(box2);

    all->setContentsMargins(10,25,0,0);
    all->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    all->addWidget(title);
    all->addLayout(hbox);

   form->setLayout(all);

    //declar butonul de ClientDconnect ce are ca parinte fereastra ConnectRegiste
    if(!(ClientDconnect = new QPushButton("Reconfigurare server", this)))
        exit(0);

    //realizez asocierea cu functia de close on mouse click
    QObject::connect(ClientDconnect, SIGNAL(clicked()), parent, SLOT(servershutdown()));
    //setez butonului de ClientDconnect pozitia si dimensiunile

    ClientDconnect->move(wid - 215, 50);
    ClientDconnect->setToolTip("Deconectare de la server");

    //afisez butonul de ClientDconnect pe ecran
    ClientDconnect->show();

     QFile LastUser("lastuserfile.txt");

      if (LastUser.open(QFile::ReadOnly))
        {
            QString username, password;
            QTextStream in(&LastUser);
            in >> username;
            in >> password;

            LineEditUserC->setText(username);
            LineEditPassC->setText(password);

           if(!username.isEmpty() && !password.isEmpty())
               uconnect->setEnabled(1);

           LastUser.close();
        }
        else
        {
             QMessageBox::information(this, "newshaolin | info","Eroare la fisierul ultimului utilizator conectat!", QMessageBox::Ok);
        }

       connect(this, SIGNAL(User(int,int)), parent, SLOT(SuccessfullUserConnect(int, int)));
}

UserConnReg::~UserConnReg()
{
    delete Conn;
    delete UserC;
    delete PassC;
    delete Reg;
    delete UserR;
    delete PassR;
    delete title;
    delete form;
    delete LineEditUserC;
    delete LineEditPassC;
    delete LineEditUserR;
    delete LineEditPassR;
    delete ClientDconnect;
    delete uconnect;
    delete uregister;
    delete hbox;
    delete chbox1;
    delete chbox2;
    delete rhbox1;
    delete rhbox2;
    delete box1;
    delete box2;
    delete all;
    delete cvbox1;
    delete cvbox2;
    delete rvbox1;
    delete rvbox2;
    delete ConnectRememberLabel;
    delete ConnectRemeberButton;
    delete ValidUserC;
    delete ValidPassC;
    delete ValidUserR;
    delete ValidPassR;
}

void UserConnReg::onConnectInputEdit()
{
    if((LineEditUserC->validate(LineEditUserC->text(), LineEditUserC->text().size()) == QRegExpValidator::Acceptable)
        && (LineEditPassC->validate(LineEditPassC->text(), LineEditPassC->text().size()) == QRegExpValidator::Acceptable))
        {
            this->uconnect->setEnabled(1);
        }
    else
        {
            this->uconnect->setEnabled(0);
        }
}

void UserConnReg::onRegisterInputEdit()
{
    if((LineEditUserR->validate(LineEditUserR->text(), LineEditUserR->text().size()) == QRegExpValidator::Acceptable)
        && (LineEditPassR->validate(LineEditPassR->text(), LineEditPassR->text().size()) == QRegExpValidator::Acceptable))
        {
            this->uregister->setEnabled(1);
        }
    else
        {
            this->uregister->setEnabled(0);
        }
}

void UserConnReg::UserConnectAttempt()
{

    QString aux("connuser|");
    handle_string(comanda, aux, 0);
    comanda = tmp;

    // pun username-ul
    handle_string(comanda, LineEditUserC->text(), 1);
    comanda = tmp;

    // adaug separatorul
    QString aux1("|");
    handle_string(comanda, aux1, 1);
    comanda = tmp;


    // adaug parola
    handle_string(comanda, LineEditPassC->text(), 1);
    comanda = tmp;

    cThread = new CommunicationThread(sd, comanda, this);

    connect(cThread, SIGNAL(Over(int)), this, SLOT(ServerConnectAnswer(int)));

    cThread->start();
}

void UserConnReg::UserRegisterAttempt()
{
    QString aux("reguser|");
    handle_string(comanda, aux, 0);
    comanda = tmp;

    // pun username-ul pentru inregistrare
    handle_string(comanda, LineEditUserR->text(), 1);
    comanda = tmp;

    // adaug separatorul
    QString aux1("|");
    handle_string(comanda, aux1, 1);
    comanda = tmp;


    // adaug parola
    handle_string(comanda, LineEditPassR->text(), 1);
    comanda = tmp;

    cThread = new CommunicationThread(sd, comanda, this);

    connect(cThread, SIGNAL(Over(int)), this, SLOT(ServerRegisterAnswer(int)));

    cThread->start();
}

 void UserConnReg::ServerConnectAnswer(int how)
 {
    if(how == 1)
    {
        // preiau mesajul
        QString raspuns = cThread->getResponse();

        // testez mesajul
        if(raspuns.startsWith("succes"))
        {
            if(ConnectRemeberButton->isChecked())
            {
                QFile LastUser("lastuserfile.txt");
                if (LastUser.open(QFile::WriteOnly))
                {
                    QTextStream out(&LastUser);
                    out <<  LineEditUserC->text();
                    out << " ";
                    out <<  LineEditPassC->text();
                    LastUser.close();
                    QMessageBox::information(this, "newshaolin | info", "Datele tale au fost salvate!",
                                             QMessageBox::Ok);

                }
                else
                {
                    QMessageBox::information(this, "newshaolin | info", "Eroare! Datele tale nu au putut fi salvate!",
                                             QMessageBox::Ok);
                }
            }

            QMessageBox::information(this, "newshaolin | info", "Te-ai conectat "
                                     + LineEditUserC->text() + "!\n" + raspuns, QMessageBox::Ok);

           int id = 0, perm = 0, i;

           // presupun ca comanda trimsa de server este corecta..
           for(i = 8; i < raspuns.size() && raspuns[i].toAscii() != '|'; i++)
               if(raspuns[i].digitValue() != -1)
                   id = id * 10 + raspuns[i].digitValue();

           for(i++; i < raspuns.size(); i++)
               if(raspuns[i].digitValue() != -1)
                    perm = perm * 10 + raspuns[i].digitValue();

           printf("%d, %d.\n", id, perm);

           // emit semnalul prin care spun ce user si cu ce prioritati s-a conectat
            emit User(id,perm);
        }
        else
        {
            QMessageBox::information(this, "newshaolin | info", "Eroare de tipul:\n"
                                     +  cThread->getResponse(), QMessageBox::Ok);
        }
    }
    else
    {
        QMessageBox::information(this, "newshaolin | info", "Thread-ul de conectare s-a terminat cu eroare! Mai incearca!",
                                  QMessageBox::Ok);
    }

    // inchid threadul
      cThread->quit();

 }


 void UserConnReg::ServerRegisterAnswer(int how)
 {
    if(how == 1)
    {
        // prealuarea mesajului de la thread
        QString raspuns = cThread->getResponse();

        // testarea mesajului
        if(raspuns.startsWith("succes"))
        {
            QMessageBox::information(this, "newshaolin | info", "Te-ai inregistrat "
                                     + LineEditUserR->text() + "!\n" + cThread->getResponse(), QMessageBox::Ok);

            // sterg continutul casetelor de la inregistrare
            LineEditUserR->setText("");
            LineEditPassR->setText("");

        }
        else
        {
            QMessageBox::information(this, "newshaolin | info", "Eroare de tipul:\n"
                                     +  cThread->getResponse(), QMessageBox::Ok);
        }
    }
    else
    {
        QMessageBox::information(this, "newshaolin | info", "Thread terminat cu eroare!"
                                 + LineEditUserC->text() + "!", QMessageBox::Ok);
    }

    // inchid threadul
        cThread->quit();


 }

void UserConnReg::clearContents()
{
   if(!ConnectRemeberButton->isChecked())
   {
       LineEditUserC->setText("");
       LineEditPassC->setText("");
       ConnectRemeberButton->setChecked(0);
   }
}
