#include "viewcats.h"

// constructor
ViewCats::ViewCats(QWidget *parent)
{
    // setez parintele
    this->setParent(parent);

    // ii setez coordonatele
    this->setGeometry(30, 125, 250, 450);

    //  creez zona in care pot vedea categoriile, restul va fi cu scroll
    ViewArea = new QScrollArea(this);

    // creez label-ul
    if(!(Title = new QLabel("<h2>categorii&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</h2><hr />", this)))
        exit(0);

    // creez label-ul unde voi pune continutul
    if(!(Content = new QLabel(this)))
        exit(0);

    ViewArea->setMaximumWidth(187);
    ViewArea->setMinimumHeight(300);

    // pun contentul in zona de scroll
    ViewArea->setWidget(Content);
    Content->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    // creez butonul de actualizare
    if(!(UpdateCats = new QPushButton("Actualizeaza", this)))
        exit(0);

    // ii asociez functionalitate
    connect(UpdateCats, SIGNAL(clicked()), this, SLOT(UpdateCatsAttempt()));

    // il afisez
    UpdateCats->show();

    // creez aranjarile in pagina
    if(!(All = new QVBoxLayout(this)))
        exit(0);

    if(!(TitleBox = new QHBoxLayout(this)))
        exit(0);

    TitleBox->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    TitleBox->addWidget(Title);

    if(!(Button = new QHBoxLayout(this)))
        exit(0);

    // setez aliniamenul si incarc butonul
    Button->setAlignment(Qt::AlignRight | Qt::AlignTop);
    Button->addWidget(UpdateCats);

    if(!(ContentBox = new QVBoxLayout(this)))
        exit(0);

    ContentBox->setAlignment(Qt::AlignLeft| Qt::AlignTop);
    ContentBox->addWidget(ViewArea);
    ContentBox->addLayout(Button);

    // incarc aranjarea principala
    All->setAlignment(Qt::AlignLeft| Qt::AlignTop);
    All->addLayout(TitleBox);
    All->addSpacing(5);
    All->addLayout(ContentBox);

    // setez aranjarea in pagina
    setLayout(All);

    // conectez primirea semnalului de raspuns al serverului cu functia slot a clasei
    connect(this, SIGNAL(ViewCatsResponse(int)), this, SLOT(ServerUpdateCatsResponse(int)));

}

// definesc functia care imi creeaza instanta
QWidget * ViewCats::CreateWiewCats(QWidget *parent)
{
    // creez instanta si returnez pointerul respectiv
    return new ViewCats(parent);
}


// definesc slotul care se executa la apasarea butonului de update
void ViewCats::UpdateCatsAttempt()
{
    char *comanda = 0;

    QString aux("viewcats");
    handle_string(comanda, aux, 0);
    comanda = tmp;

    ViewCatsThread = new CommunicationThread(sd, comanda, this);

    connect(ViewCatsThread, SIGNAL(Over(int)), this, SLOT(ServerUpdateCatsResponse(int)));

    ViewCatsThread->start();

}

// definesc care se executa cand am raspus de la server
void ViewCats::ServerUpdateCatsResponse(int how)
{
    if (how == 1)
    {
        QString message = ViewCatsThread->getResponse();

        if (message.startsWith("success"))
        {
            // updatarea continutului listei mele

            // o golesc
            CatsList.clear();

            // o incarc cu info din mesajul primit

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

            while(p)
            {
                // creez un nou Nod pentru a retine informatiile despre categoria curenta
                CatInfo newCatInfo;

                // out << "sunt in bucla, am creat un nou nod .. " << endl;

                // preiau level-ul
                p = strtok(NULL, sep);
               if(p)
                   newCatInfo.level = atoi(p);

                // preiau id-ul

                   p = strtok(NULL, sep);
               if(p)
                   newCatInfo.id = atoi(p);

               // out << "preluat id = " << newCatInfo.id << endl;

                // preiau numele
                p = strtok(NULL, sep);
                if(p)
                    newCatInfo.name = QString(p);

               // out << "preluat nume = " << newCatInfo.name << endl;

                // preiau data
                p = strtok(NULL, sep);
                if(p)
                    newCatInfo.Date = QString(p);

               // out << "preluat Date = " << newCatInfo.Date << endl;

                /*
               // preiau parintele
                p = strtok(NULL, sep);
               if(p)
                   newCatInfo.parent = atoi(p);
                */

                // preiau owner-ul
                p = strtok(NULL, sep);
                if(p)
                    newCatInfo.owner = atoi(p);

               // out << "preluat owner = " << newCatInfo.owner << endl;

                // adaug la lista de categorii categoria extrasa
                if(p)
                    CatsList.append(newCatInfo);
            }

            // dealoc memoria folosita pentru containerul auxiliar
            if(string)
                delete string;

            QMessageBox::information(this, "newshaolin | info", "Operatiune efectuata cu succes!\n",
                                             QMessageBox::Ok);

            // parcurgerea in preordine a listei, apel functia recursiva din globals
            Preorder();

            //setez contentul categoriilor
            Content->setText(cats);

            // setez dimensiunea optima contentului pentru textul introdus
            Content->setMinimumSize(Content->sizeHint());

            out << cats << endl;
            // sterg continutul care era in cats
            cats.clear();
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
      ViewCatsThread->quit();

}

// destructor
ViewCats::~ViewCats()
{

}
