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

#ifndef VIEWNEWSBOXCONTAINER_H
#define VIEWNEWSBOXCONTAINER_H

#include "globals.h"
#include "communicationthread.h"
#include "lineeditvalidate.h"

// clasa unei stiri

class NewsClass: public QWidget
{
    Q_OBJECT
public:

    // constructor
    NewsClass(int level, int id, QString title, QString date, QString content, int cat, int owner, QWidget *parent = 0);

    // metoda care imi seteaza pozitia in lista a stirei respective
    void SetIndex(int index);

    // destructor
    ~NewsClass();

private:

 // datele din baza de date

    // identificatorul stirii
    int NewsId;

    // categoria din care face parte
    int NewsParentCat;

    // owner-ul ce a publicat-o
    int NewsOwner;

 // elementele de interfata folosite

    // indexul stirii
    QLabel *NewsIndex;

    // label-urile standard
    QLabel *Title, *Date, *Cat, *Description;

    // continutul stirii curente
    QTextEdit *NewsTitle, *NewsCat, *NewsContent, *NewsDate;

    // butoanele care vor fi create doar daca id-ul utilizatorului coincide cu propunatorul
    QPushButton *Modify, *Cancel;

    // arajarile in pagina
    QVBoxLayout *LeftVBox, *RightVBox, *All;

    // bottom va fi creat doar daca id-ul user-ului coincide cu propunatorul
    QHBoxLayout *Top, *Bottom;

    // declar threadul folosit pentru comunicarea cu serverul
    CommunicationThread *DelNewThread;

    // functie privata construieste arborele de categorii
    QString ConstructTreeCats(int cat);

signals:

    // semnalul de care se transmite la apasarea butonului de modificare
    void Update(int id, QString title, QString content, int cat, QWidget *me);

    // semnalul care il trimit dupa ce serverul mi-a sters cu succes stirea
    void Deleted(QWidget *me);

public slots:

    // slotul care se executa la apasarea butonului de modificare, care va emite semnalul de modificare
    void OnUpdateAttempt();

    // slotul care se executa la apasarea butonului de stergere
    void OnDeleteAttempt();

    // slotul care se executa la primirea raspunsului de la server si daca am succes emit Delete(this);
    void ServerDeleteNewResponse(int how);

    // slotul care il voi executa la updatarea continutului dupa ce am fost modificat
    void LoadData(int id, QString title, QString data, QString content, int cat);

};

// clasa containter care detine stirile
class ViewNewsBoxContainer: public QWidget
{
    Q_OBJECT

public:

    // constructor
    ViewNewsBoxContainer(QWidget *parent  = 0);

    // functie care imi sterge stirile curente pentru a updata contintul cu altele noi
    void RemoveContent();

    // destructor
    ~ViewNewsBoxContainer();

private:

    // elementele de interfata folosite
    QList<NewsClass*> ListOfNews;

    // aranjarea in pagina
    QVBoxLayout NewsBox;

signals:

    // semnale

public slots:

   // se va executa dupa ce voi incarca datele in lista globala de stiri
   void LoadNews(int how);

   // se va executa cand se sterge o stire cu succes
   void DeleteNewsElement(QWidget *news);

};

#endif // VIEWNEWSBOXCONTAINER_H
