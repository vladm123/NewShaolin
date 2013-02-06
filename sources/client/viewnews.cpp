#include "viewnews.h"

// implementarea clasei ViewNews care ofera posibiliatea utilizatorului de a citi stiro
// -------------------------BEGIN---------------------------------------------------------------

// constructor
ViewNews::ViewNews(QWidget *parent): ViewNewsThread(0), NewsContainer(0)
{
    // setez parintele
    this->setParent(parent);
    // setez dimensiunile si pozitia
    this->setGeometry(250, 80, 773, 618);

    // creez interfata grafica

    if(!(NewsFromCat = new QLabel ("<b>stiri din categoria: </b>", this)))
        exit(0);

   if(!(ViewLast = new QLabel ("<b>ultimele: </b>", this)))
        exit(0);

   if(!(RecursivelyOn = new QLabel ("<b>recursiv pe: </b>", this)))
        exit(0);

   if(!(Levels = new QLabel ("<b>nivele.</b>", this)))
        exit(0);

   if(!(ValidInputMany = new QRegExpValidator (QRegExp("[0-9]+"), 0)))
        exit(0);

   if(!(ValidInputCat = new QRegExpValidator (QRegExp("[0-9]+"), 0)))
        exit(0);

   if(!(ValidInputRec = new QRegExpValidator (QRegExp("[0-9]+"), 0)))
        exit(0);

   if(!(InputCat = new LineEditValidate(ValidInputCat, this)))
        exit(0);

   if(!(InputHowMany = new LineEditValidate(ValidInputMany, this)))
        exit(0);

   if(!(InputRecursivelyOn = new LineEditValidate(ValidInputRec, this)))
        exit(0);

   // setez dimensiunea maxima pe orizontala a inputurilor utilizatorilor
   InputCat->setMaximumWidth(40);
   InputHowMany->setMaximumWidth(40);
   InputRecursivelyOn->setMaximumWidth(40);
   
   connect(InputCat,SIGNAL(textChanged(QString)), this, SLOT(onInputEdit()));
   connect(InputHowMany,SIGNAL(textChanged(QString)), this, SLOT(onInputEdit()));
   connect(InputRecursivelyOn,SIGNAL(textChanged(QString)), this, SLOT(onInputEdit()));
    
   if(!(UpdateButton = new QPushButton("vizualizeaza", this)))
        exit(0);

    // ii asociez functionalitatea
    connect(UpdateButton, SIGNAL(clicked()), this, SLOT(ViewNewsAttempt()));

    // il afisez
    UpdateButton->show();

    if(!(TopUp = new QHBoxLayout()))
        exit(0);

    if(!(TopDown = new QHBoxLayout()))
        exit(0);

    if(!(TopButton = new QHBoxLayout()))
        exit(0);

    if(!(Top = new QVBoxLayout()))
        exit(0);

    if(!(Content = new QVBoxLayout()))
        exit(0);

    if(!(All = new QVBoxLayout()))
        exit(0);

    // primul rand
    TopUp->setAlignment(Qt::AlignRight|Qt::AlignTop);
    TopUp->addWidget(ViewLast);
    TopUp->addWidget(InputHowMany);
    TopUp->addWidget(NewsFromCat);
    TopUp->addWidget(InputCat);

    TopUp->addWidget(RecursivelyOn);
    TopUp->addWidget(InputRecursivelyOn);
    TopUp->addWidget(Levels);
    TopUp->addSpacing(10);
    TopUp->addWidget(UpdateButton);

    TopUp->addSpacerItem(new QSpacerItem(1500, 0, QSizePolicy::Maximum, QSizePolicy::Minimum));


    TopDown->addSpacerItem(new QSpacerItem(1500, 0, QSizePolicy::Maximum, QSizePolicy::Minimum));

    // butonul de go
    TopButton->setAlignment(Qt::AlignRight|Qt::AlignTop);
    //TopButton->addWidget(UpdateButton);

    TopButton->addSpacerItem(new QSpacerItem(150, 0, QSizePolicy::Maximum, QSizePolicy::Minimum));

    // incar sectiunea de top
    Top->addLayout(TopUp);
    //Top->addLayout(TopDown);
    Top->addSpacing(10);
    //Top->addLayout(TopButton);

    if(!(NewsBoxArea = new QScrollArea()))
        exit(0);

    if(!(NewsContainer = new ViewNewsBoxContainer(this)))
        exit(0);

    // setez widgetul zonei de scroll
    NewsBoxArea->setWidget(NewsContainer);

    // incarc sectiunea centrala, stirile (cu scroll)
    Content->addWidget(NewsBoxArea);

    All->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    // incarc aranjarea principala
    All->addLayout(Top);
    All->addSpacing(25);
    All->addLayout(Content);

    // setez aranjarea principala
    setLayout(All);

    // conectul dintre raspunsul serverului si incarcarea stirilor din lista globala..
    connect(this, SIGNAL(UpdatedGlobalNewsList(int)), NewsContainer, SLOT(LoadNews(int)));
}

// functia care imi creeaza obiectul, functie statica
QWidget* ViewNews::CreateViewNews(QWidget *parent)
{
    // creez o noua instanta si returnez pointerul catre ea
    return new ViewNews(parent);
}

// slotul care se executa la apasarea lui UpdateButton.
void ViewNews::ViewNewsAttempt()
{
    char *comanda = 0;

    QString aux("viewnews|");
    handle_string(comanda, aux, 0);
    comanda = tmp;

    // adaug id-ul categoriei (Din care categorie vreau sa selectez date
    if(InputCat->text().size())
    {
        handle_string(comanda, InputCat->text(), 1);
        comanda = tmp;
    }
    else
    {
        handle_string(comanda, QString("0"), 1);
        comanda = tmp;
    }

    // adaug separatorul
    QString aux2("|");
    handle_string(comanda, aux2, 1);
    comanda = tmp;


    // adaug numarul de nivele dorite (Cat de adanc vreau sa ma duc in subcategorii.
    // Ex: Nivel 1 ==> doar din categoria curenta
    if(InputRecursivelyOn->text().size())
    {
        handle_string(comanda, InputRecursivelyOn->text(), 1);
        comanda = tmp;
    }
    else
    {
        handle_string(comanda, QString("0"), 1);
        comanda = tmp;
    }

    // adaug separatorul
    handle_string(comanda, aux2, 1);
    comanda = tmp;

    // adaug limit-ul (Cate stiri?)
    if(InputHowMany->text().size())
    {
        handle_string(comanda, InputHowMany->text(), 1);
        comanda = tmp;
    }
    else
    {
        handle_string(comanda, QString("0"), 1);
        comanda = tmp;
    }

    // creez thread-ul de comunicare cu serverul

    ViewNewsThread = new CommunicationThread(sd, comanda, this);

    // sterg comanda alocata local
    delete comanda;

    // conectez semnalul de terminare al threadului cu slotul care se va executa apoi
    connect(ViewNewsThread, SIGNAL(Over(int)), this, SLOT(ServerViewNewsResponse(int)));

    // pornesc threadul
    ViewNewsThread->start();

}

// slotul care se executa la primirea raspunsului de la server
void ViewNews::ServerViewNewsResponse(int how)
{
     if (how == 1)
    {
        QString message = ViewNewsThread->getResponse();

        if (message.startsWith("success"))
        {
            // sterg ultimele stiri existente, pentru ca deja am obtinut cu succes altele
            GlobalNewsList.clear();

            // sterg obiectele
            NewsContainer->RemoveContent();

            // incarc lista de stiri cu cele din mesajul primit

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

            while(p)
            {
                // creez un nou Nod pentru a retine informatiile despre stirea curenta
                NewsInfo newNewsInfo;

                // out << "sunt in bucla, am creat un nou nod .. " << endl;

                // preiau nivelul
                p = strtok(NULL, sep);
               if(p)
                   newNewsInfo.level = atoi(p);

        //      out << "preluat nivel = " << newNewsInfo.level << endl;

                // preiau id-ul

                   p = strtok(NULL, sep);
               if(p)
                   newNewsInfo.id = atoi(p);

        //      out << "preluat id = " << newNewsInfo.id << endl;

                // preiau numele
                p = strtok(NULL, sep);
                if(p)
                    newNewsInfo.name = QString(p);

       //       out << "preluat nume = " << newNewsInfo.name << endl;

                // preiau content
                p = strtok(NULL, sep);
                if(p)
                    newNewsInfo.Content = QString(p);

        //        out << "preluat content = " << newNewsInfo.Content << endl;

                // preiau data
                p = strtok(NULL, sep);
                if(p)
                    newNewsInfo.Date = QString(p);

         //      out << "preluat Date = " << newNewsInfo.Date << endl;

                // preiau categoria stirii
                p = strtok(NULL, sep);
                if(p)
                    newNewsInfo.parent = atoi(p);

          //     out << "preluat categ = " << newNewsInfo.parent << endl;

                // preiau owner-ul
                p = strtok(NULL, sep);
                if(p)
                    newNewsInfo.owner = atoi(p);

             // out << "preluat owner = " << newNewsInfo.owner << endl;

                // adaug la lista de stiri, stirea extrasa
                if(p)
                    GlobalNewsList.append(newNewsInfo);
            }

            // dealoc memoria folosita pentru containerul auxiliar
            if(string)
                delete string;

            QMessageBox::information(this, "newshaolin | info", "Operatiune incheiata cu succes!\n",
                                             QMessageBox::Ok);

//            for(int i = 0; i < GlobalNewsList.count(); i++)
//            {
//                out << "\n elem " << i << endl;
//                out << " " << GlobalNewsList[i].level << " ";
//                out << GlobalNewsList[i].id << " ";
//                out << GlobalNewsList[i].name << " ";
//                out << GlobalNewsList[i].Content << " ";
//                out << GlobalNewsList[i].Date << " ";
//                out << GlobalNewsList[i].parent << " ";
//                out << GlobalNewsList[i].owner << " \n";
//            }

            emit UpdatedGlobalNewsList(1);

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

    // inchid threadul dupa ce am preluat raspunsul
            ViewNewsThread->quit();

}

// slotul care se executa la modificare inputului de catre user
void ViewNews::onInputEdit()
{
    if(((InputCat->validate(InputCat->text(), InputCat->text().size()) == QRegExpValidator::Acceptable)
        || !InputCat->text().size()) &&
       ((InputHowMany->validate(InputHowMany->text(), InputHowMany->text().size()) == QRegExpValidator::Acceptable)
        || !InputHowMany->text().size()) &&
        ((InputRecursivelyOn->validate(InputRecursivelyOn->text(),
                                      InputRecursivelyOn->text().size()) == QRegExpValidator::Acceptable )
        || !InputRecursivelyOn->text().size()))

    {
        UpdateButton->setEnabled(1);
    }
    else
    {
        UpdateButton->setEnabled(0);
    }

}

// destructor
ViewNews::~ViewNews()
{
    QTextStream out(stdout);

    if(ViewNewsThread)
        delete ViewNewsThread;

     out << " 1 sters .." << endl;

    if(ViewLast)
        delete ViewLast;

     out << " 2 sters .." << endl;

     if(NewsFromCat)
         delete NewsFromCat;

     out << " 3 sters .." << endl;

     if(RecursivelyOn)
         delete RecursivelyOn;

     out << " 4 sters .." << endl;

     if(Levels)
         delete Levels;

     out << " 4 sters .." << endl;

     if(InputHowMany)
         delete InputHowMany;

     out << " 5 sters .." << endl;

     if(InputCat)
         delete InputCat;

     out << " 6 sters .." << endl;

     if(InputRecursivelyOn)
         delete InputRecursivelyOn;

     out << " 7 sters .." << endl;

//     if(ValidInputCat)
//         delete ValidInputCat;
//
//     out << " 8 sters .." << endl;
//
//     if(ValidInputMany)
//         delete ValidInputMany;
//
//     out << " 9 sters .." << endl;
//
//     if(ValidInputRec)
//         delete ValidInputRec;
//
//     out << " 10 sters .." << endl;

     if(UpdateButton)
         delete UpdateButton;

//     out << " 11 sters .." << endl;
//
//     if(NewsBoxArea)
//         delete NewsBoxArea;

     out << " 12 sters .." << endl;

     if(NewsContainer)
       NewsContainer->~ViewNewsBoxContainer();
//
     out << " 13 sters .." << endl;

//     if(Top)
//         delete Top;
//
//     out << " 14 sters .." << endl;

//     if(TopUp)
//         delete TopUp;
//
//     out << " 15 sters .." << endl;
//
//     if(TopDown)
//         delete TopDown;
//
//     out << " 16 sters .." << endl;
//
//     if(TopButton)
//         delete TopButton;
//
//     out << " 17 sters .." << endl;
//
//     if(All)
//         delete All;
//
//     out << " 18 sters .." << endl;
//
//     if(Content)
//         delete Content;
//
//     out << " 19 sters .." << endl;

}
// ---------------------------END----------------------------------------------------------------
