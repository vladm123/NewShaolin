#include "viewnewsboxcontainer.h"

// -------------------------BEGIN---------------------------------------------------------------
// constructorul si medodele clasei stire
NewsClass::NewsClass(int level, int id, QString title, QString date, QString content, int cat, int owner, QWidget * parent)
{
    // setez parintele
    this->setParent(parent);

    // incep crearea elementelor de interfata

    // label-ul pentru indexul stirii in lista
    if (!(NewsIndex = new QLabel(this)))
        exit(0);

    //label-ul pentru titlul stirii
    if(!(Title = new QLabel("<b>Titlu: </b>")))
        exit(0);

    // label-ul pentru Categoria stirii
    if(!(Cat = new QLabel("<b>Categorie: </b>")))
        exit(0);

    // label-ul pentru continutul stirii
    if(!(Description = new QLabel("<b>Descriere: </b>")))
        exit(0);

    if(!(Date = new QLabel("<b>Data: </b>")))
        exit(0);

    //  continutul care va fi incarcat

    // categoria (recursiv)
    if(!(NewsCat = new QTextEdit(this)))
        exit(0);

    // titlul
    if (!(NewsTitle = new QTextEdit(title, this)))
        exit(0);

    // data
    if (!(NewsDate = new QTextEdit(date, this)))
        exit(0);

    // descrierea
    if (!(NewsContent = new QTextEdit(content, this)))
        exit(0);

    // text-editurile vor fi doar in citire pentru utilizator
    NewsTitle->setReadOnly(1);
    NewsDate->setReadOnly(1);
    NewsCat->setReadOnly(1);
    NewsContent->setReadOnly(1);

    // si vor avea dimensiunile standart
    NewsTitle->setFixedHeight(30);
    NewsDate->setFixedHeight(30);
    NewsCat->setFixedHeight(30);
    NewsContent->setFixedHeight(275);

    // incarc continutul

    // id-ul
    NewsId = id;

    // categoria parinte
    NewsParentCat = cat;

    // setez owner-ul
    NewsOwner = owner;

    // preiau si setez data
    NewsDate->setPlainText(date);


    QString TreeCats = ConstructTreeCats(cat), aux("Toate");

    // daca categorie e existenta, setez arborele de categorii altfel las doar cu categoria Toate

    if(!TreeCats.startsWith("0"))
        NewsCat->setPlainText(TreeCats);
    else
        NewsCat->setPlainText(aux);

    QTextStream out(stdout);
    out << "\nStire: " << TreeCats << endl;
    // creez aranjarile in pagina
    if(!(LeftVBox = new QVBoxLayout()))
        exit(0);

    if(!(RightVBox = new QVBoxLayout()))
        exit(0);

    if(!(Top = new QHBoxLayout()))
        exit(0);

    if(!(All = new QVBoxLayout()))
        exit(0);

    // incarc in partea stanga pattern-ul ..
    LeftVBox->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    LeftVBox->addSpacing(6);
    LeftVBox->addWidget(Title);
    LeftVBox->addSpacing(8);
    LeftVBox->addWidget(Cat);
    LeftVBox->addSpacing(10);
    LeftVBox->addWidget(Date);
    LeftVBox->addSpacing(13);
    LeftVBox->addWidget(Description);

    // incarc in partea dreapta continutul informational
    RightVBox->addWidget(NewsTitle);
    RightVBox->addWidget(NewsCat);
    RightVBox->addWidget(NewsDate);
    RightVBox->addWidget(NewsContent);


    // setez dimensiunile pentru data din news
    NewsTitle->setFixedWidth(this->size().width() - 55);
    NewsCat->setFixedWidth(this->size().width() - 55);
    NewsDate->setFixedWidth(this->size().width() - 55);
    //NewsTitle->setFixedWidth(this->size().width());

    // top hbox
    Top->addLayout(LeftVBox);
    Top->addLayout(RightVBox);

    // all box
    All->addWidget(NewsIndex);
    All->addLayout(Top);
    All->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);

     // apar doar la cele publicate user-ul curent, sau la admin
    if(UserId == NewsOwner || UserId == 1)
    {
        if(!(Modify = new QPushButton("modifica", this)))
            exit(0);

        // butonul de inchidere al dialogului
        if(!(Cancel = new QPushButton("sterge", this)))
            exit(0);

        // asociez functionalitatea butoanelor create
        connect(Modify, SIGNAL(clicked()), this, SLOT(OnUpdateAttempt()));
        connect(Cancel, SIGNAL(clicked()), this, SLOT(OnDeleteAttempt()));

        // bottom hbox
        if(!(Bottom = new QHBoxLayout()))
            exit(0);

        Bottom->setAlignment(Qt::AlignRight| Qt::AlignTop);
        Bottom->addWidget(Modify);
        Bottom->addSpacing(10);
        Bottom->addWidget(Cancel);

        // adaug la aranjarea principala
        All->addLayout(Bottom);

        // conectez modificarea cu parintele parintelui parintelui widgetului meu
        connect(this, SIGNAL(Update(int, QString, QString, int, QWidget*)), parent->parent()->parent()->parent()->parent(),
                SIGNAL(ModifyNew(int, QString, QString , int, QWidget*)));

        // conectez stergerea cu parintele meu
        connect(this, SIGNAL(Deleted(QWidget*)), parent, SLOT(DeleteNewsElement(QWidget *)));

   }
    // setez aranjarea in pagina pentru obiectul curent
    this->setLayout(All);
}

 // functie privata construieste arborele de categorii
QString NewsClass::ConstructTreeCats(int cat)
{
    // index
    int i;

    // declar arborele de categorii
    QString TreeCats;
    QTextStream out(stdout);


    // aflu nivelul categoriei respective
    for(i = 0; i < CatsList.count(); i++)
        if(CatsList[i].id == cat)
            break;

    if(i < CatsList.count())
    {
        // contruiesc nivelul stirii din categoria mea
        int level = CatsList[i].level;

        // orfan

        if(level == 0)
        {
            TreeCats.prepend(CatsList[i].name);
            // adaug categoria mama
           TreeCats.prepend("Toate/");

        }
        else
        {
              TreeCats.prepend(CatsList[i].name);
              TreeCats.prepend("/");

            for(; i > 0; i--)
            {
                while(CatsList[i].level >= level)
                    i--;

                if(i < 0)
                    break;

                 // prefixez numele categoriei
                 TreeCats.prepend(CatsList[i].name);
                 // prefixez cu separator
                 TreeCats.prepend("/");

                 // ultimul nivel bun
                 level = CatsList[i].level;

                 if(CatsList[i].level == 0)
                    break;

             }

           // adaug categoria mama
           TreeCats.prepend("Toate");
       }

           // intorc treecats-ul creat;
           return TreeCats;
    }

    // categorie inexistenta
    return QString::number(0);
}

void NewsClass::LoadData(int id, QString title, QString data, QString content, int cat)
{
    if(id == NewsId)
    {

        QTextStream out(stdout);

        // actualizez datele stirii
        NewsTitle->setPlainText(title);
        NewsContent->setPlainText(content);
        NewsDate->setPlainText(data);


        // daca categoria modificata exista
        QString TreeCats = ConstructTreeCats(cat);
        if(!TreeCats.startsWith("0"))
        {
            NewsParentCat = cat;
            // setez arborele de categorii
            NewsCat->setPlainText(TreeCats);
        }
        else
        {
          QMessageBox::information(this,
                                   "newshaolin | info",
                                   "Eroare de tipul:\n [updatenews]Catid Inexistent! Nu am updatat!",
                                   QMessageBox::Ok);

        }
    }
}

void NewsClass::OnUpdateAttempt()
{
    // emit semnalul de modificare
    emit Update(NewsId, NewsTitle->toPlainText(), NewsContent->toPlainText(), NewsParentCat, this);
}

void NewsClass::OnDeleteAttempt()
{
    // construiesc comanda de stergere
    char *comanda = 0;

    QString aux("delnew|");
    handle_string(comanda, aux, 0);
    comanda = tmp;

    // adaug id-ul stirii
    handle_string(comanda, QString::number(NewsId), 1);
    comanda = tmp;

    // creez threadul
    DelNewThread = new CommunicationThread(sd, comanda, this);

    // ii conectez raspunsul
    connect(DelNewThread, SIGNAL(Over(int)), this, SLOT(ServerDeleteNewResponse(int)));

    // il pornesc
    DelNewThread->start();
}

void NewsClass::ServerDeleteNewResponse(int how)
{
    if (how == 1)
    {
        QString message = DelNewThread->getResponse();

        if (message.startsWith("success"))
        {

            QMessageBox::information(this, "newshaolin | info", "Operatiune incheiata cu succes!\n" + message,
                                             QMessageBox::Ok);

            QTextStream out(stdout);
            out <<"POINTERR : "<< this << endl;
            emit Deleted(this);
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

    // inchid thread
        DelNewThread->quit();

}

// functia care imi updateaza nr stirii in lista, elementul cu index-ul 0 va fi de fapt 1
void NewsClass::SetIndex(int index)
{
    // creez sirul predefinit
    QString string("Stirea Nr. ");

    // ii adaug numarul stirii
    string.append(QString::number(index + 1));

    // setez textul Label-ului
    NewsIndex->setText(string);
}

// destructor
NewsClass::~NewsClass()
{
    QTextStream out(stdout);
    out << "[deconstructor stire]" << endl;

    if(NewsId != -1)
    {
        if(Modify)
            delete Modify;

        out << "[deconstructor stire]1" << endl;

        if(Cancel)
            delete Cancel;

        out << "[deconstructor stire]2" << endl;

        if(Bottom)
            delete Bottom;
        out << "[deconstructor stire]3" << endl;

    }
    if(NewsIndex)
        delete NewsIndex;

    out << "[deconstructor stire]4" << endl;

    if(Title)
        delete Title;

    out << "[deconstructor stire]5" << endl;

    if(Date)
        delete Date;

    out << "[deconstructor stire]6" << endl;

    if(Cat)
        delete Cat;

    out << "[deconstructor stire]7" << endl;

    if(Description)
        delete Description;

    out << "[deconstructor stire]8" << endl;

    if(NewsTitle)
        delete NewsTitle;

    out << "[deconstructor stire]9" << endl;


    if(NewsCat)
        delete NewsCat;

    out << "[deconstructor stire]10" << endl;

    if(NewsContent)
        delete NewsContent;

    out << "[deconstructor stire]11" << endl;


    if(NewsDate)
        delete NewsDate;

    out << "[deconstructor stire]12" << endl;

//    if(DelNewThread)
//        delete DelNewThread;

    out << "[deconstructor stire]13" << endl;

}
// ---------------------------END----------------------------------------------------------------

// implementarea clasei Box detinatoare de stiri
// -------------------------BEGIN---------------------------------------------------------------

// constructor
ViewNewsBoxContainer::ViewNewsBoxContainer(QWidget *parent)//: ListOfNews(0), NewsBox(0)
{
    // setez praintele
    setParent(parent);

    // creez elementele de interfata

    // vertical boxul unde voi pune toate elementele stire, din lista de obiecte nou create
//    if(!(NewsBox = new QVBoxLayout()))
//        exit(0);

    // creez lista
 //   if(!(ListOfNews = new QList<NewsClass*>()))
    //    exit(0);

    setLayout(&NewsBox);
}

// se va executa cand serverul la incarcarea de stiri
void ViewNewsBoxContainer::LoadNews(int how)
{
    if(how == 1)
    {
        int i;

        QTextStream out(stdout);


        for(i = 0; i < GlobalNewsList.count(); i++)
        {
            NewsClass *temp = new NewsClass(GlobalNewsList[i].level,
                                            GlobalNewsList[i].id,
                                            GlobalNewsList[i].name,
                                            GlobalNewsList[i].Date,
                                            GlobalNewsList[i].Content,
                                            GlobalNewsList[i].parent,
                                            GlobalNewsList[i].owner, this);

            // setez index-ul in lista a stirii curente.
            temp->SetIndex(i);

            // il inserez in vbox-ul meu
            NewsBox.addWidget(temp);

            // il afisez
            temp->show();

            // introduc in lista de stiri
            ListOfNews.append(temp);

            out << " introdus in lista " << endl;
        }

        // imi setez  dimensiunea optima
        this->resize(this->sizeHint());
    }
}

// se va executa cand se sterge o stire cu succes
void ViewNewsBoxContainer::DeleteNewsElement(QWidget *news)
{
    int i;
    QTextStream out(stdout);
    out << "[deleteNewsElement].. \n";


    for(i = 0; i < ListOfNews.count(); i++)
        if(ListOfNews.at(i) == news)
        {
            // pointezi catre el cu un obiect auxiliar
            NewsClass * temp = ListOfNews.at(i);

             out << "[deleteNewsElement].. " << i << endl;

            // il scot din lista
            ListOfNews.removeAt(i);

            // sterg elementul
            delete temp;

            // ma opresc
            break;
        }

    // actualizez indicii stirilor
    for(; i < ListOfNews.count(); i++)
        ListOfNews.at(i)->SetIndex(i);
}

void ViewNewsBoxContainer::RemoveContent()
{
    QTextStream out(stdout);

    if(&ListOfNews)
    {
        int i = 0;
        // sterg stirile existente
        for(i = 0; i < ListOfNews.count(); i++)
        {
            NewsClass *temporary = ListOfNews.at(i);
            //sterg obiectul

            if(temporary)
                delete temporary;

            out << "[deleteArhive] Am sters stirea.. " << i << " din lista" << endl;
        }

        // sterg pointerii
        ListOfNews.clear();

        // sterg lista Globala de stiri
        GlobalNewsList.clear();

      }

}

// destructor
ViewNewsBoxContainer::~ViewNewsBoxContainer()
{
    QTextStream out(stdout);
    out << "vreau sa sterg elementele listei.. \n";

    if(&ListOfNews)
    {
        // sterg stirile vizualizate de utilizatorul care se deconecteaza
        for(int i = 0; i < ListOfNews.count(); i++)
        {
            delete ListOfNews.at(i);

            out << "am sters elementul.. " << i << " din lista" << endl;
        }

    }
}

// ---------------------------END----------------------------------------------------------------
