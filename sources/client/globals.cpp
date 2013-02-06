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

#include "globals.h"

// QApplicatia
QApplication *myapp;

// lista unei voi retine categoriile
QList<CatInfo> CatsList;

// declar lista unde retin stirile, ca informatie despre ele
QList<NewsInfo> GlobalNewsList;

// contentul layout-ului categorii, updatat la executia ViewCats::ServerUpdateCatsResponse(int how)
QString cats;

//
QMutex Mutex;

// socketul pentru comunicarea cu serverul
int *sd;

// lungimea mesajului trimis/primit catre/(de la) server
int length;

// mesajul trimis/primit catre/(de la) server
char *message;
char * comanda, *raspuns;

// pointerul temporar pe care il folosesc la (re)alocarea de memorie
char *tmp;
char *data;

// user-ul logat la un anumit moment dat
int UserId;

// definesc functia care muta un obiect in centrul desktopului
void moveToCenter(QWidget *w, const int &width, const int &height)
{
    // declar variabilele de pozitie
    int x, y;

    // pointez la desktopul calculatorului
    QDesktopWidget *desktop = QApplication::desktop();

    if (!desktop || !w)
        exit(0);

    // pozitionez obiectul pe orizontala
    x = (desktop->width() - width) / 2;

    // pozitionez obiectul pe verticala
    y = (desktop->height() - height) / 2;

    // mut obiectul la noile coordonate
    w->move(x, y);
}

// definesc functia care muta un obiect raportat la parinte
void moveWidgetToCenter(QWidget *w, const int &pwidth, const int &pheight, const int &width, const int &height)
{
    // declar si initializez variabila care retine noua coordonata pe x
    int x = (pwidth - width) / 2;

    // declar si initializez variabila care retine noua coordonata pe y
    int y = (pheight - height) / 2;

    if (!w)
           exit(0);

    // mut obiectul la noile coordonate
    w->move(x, y);
}

// definesc functia care se ocupa cu incarcarea unui layout vertical cu parametri

void handleHLabel(QVBoxLayout *hbox, QLabel *label, QHBoxLayout *hbox1, QHBoxLayout *hbox2, QVBoxLayout *vbox1, QVBoxLayout *vbox2, QLabel *label1, QLabel *label2, QLineEdit *line1, QLineEdit *line2, QPushButton *button, QLabel *remember, QCheckBox * rem)
{
    hbox2->setAlignment(Qt::AlignRight | Qt::AlignTop);
    hbox2->addWidget(remember);
    hbox2->addWidget(rem);
    hbox2->addSpacing(8);
    hbox2->addWidget(button);

    label1->setAlignment(Qt::AlignRight);
    label2->setAlignment(Qt::AlignRight);

    vbox1->addWidget(label1);
    vbox1->addWidget(label2);

    vbox2->addWidget(line1);
    vbox2->addWidget(line2);

    hbox1->addLayout(vbox1);
    hbox1->addLayout(vbox2);

    hbox->addWidget(label);
    hbox->addLayout(hbox1);
    hbox->addLayout(hbox2);

}

void handleHLabelR(QVBoxLayout *hbox, QLabel *label, QHBoxLayout *hbox1, QHBoxLayout *hbox2, QVBoxLayout *vbox1, QVBoxLayout *vbox2, QLabel *label1, QLabel *label2, QLineEdit *line1, QLineEdit *line2, QPushButton *button)
{
    hbox2->setAlignment(Qt::AlignRight | Qt::AlignTop);
    hbox2->addWidget(button);

    label1->setAlignment(Qt::AlignRight);
    label2->setAlignment(Qt::AlignRight);

    vbox1->addWidget(label1);
    vbox1->addWidget(label2);

    vbox2->addWidget(line1);
    vbox2->addWidget(line2);

    hbox1->addLayout(vbox1);
    hbox1->addLayout(vbox2);

    hbox->addWidget(label);
    hbox->addLayout(hbox1);
    hbox->addLayout(hbox2);

}

void handle_string(char *comanda, QString text, int inc)
{
    const char *aux = text.toStdString().c_str();

    int length;
    if(inc == 1)
        length = strlen(aux) + strlen(comanda);
    else
        length = strlen(aux);

     fprintf(stdout, "\n[handle_string]data: %s.\n", aux);
     fflush(stdout);

     if(inc == 1)
     {
          // realoc memorie pentru comanda
         if(!(tmp = (char*) realloc (comanda, sizeof(char) * (length + 1))))
         {
               fprintf(stdout, "[handle_string]Cazul cand inc = 1, n-am putut aloca, inchid!");
               exit(0);
         }
        // concatenez data la sfarsitul lui tmp
        strcat(tmp, aux);
    }
     else
     {
         tmp = 0;

          // realoc memorie pentru comanda
         if(!(tmp = (char*) malloc (sizeof(char) * (length + 1))))
         {
               fprintf(stdout, "[handle_string]Cazul cand inc = 0, n-am putut aloca, inchid!");
               exit(0);
         }
         // setez memoria in tmp pe 0
         memset(tmp, 0, sizeof(char) * (length + 1));

         // copiez datele din data in tmp
         strcpy(tmp, aux);
     }

     // pentru siguranta, pun caracterul '\0' la finalul tmp
     tmp[length] = 0;

     fprintf(stdout, "\n[handle_string - rezultat]tmp: %s.\n", tmp);
         fflush(stdout);

}

// definesc functia care imi face parcurgerea in preordine a continutului
void Preorder()
{
    int i;

    cats.append("+ 0 Toate\n");

    // spatii in functie de nivelul pe care am ajuns

    for(i = 0; i < CatsList.count(); i++)
    {
        for(int j = 0; j <= CatsList[i].level; j++)
        cats.append("  ");

        cats.append(CatsList[i].name);
        cats.append(" (id ");
        cats.append(QString::number(CatsList[i].id));
        cats.append(")\n");
    }
}
