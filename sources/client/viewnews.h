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

#ifndef VIEWNEWS_H
#define VIEWNEWS_H

#include "viewnewsboxcontainer.h"

class ViewNews: public QWidget
{
    Q_OBJECT

public:

    // constructor
    ViewNews(QWidget *parent = 0);

    // functia care imi creeaza obiectul, functie statica
    static QWidget* CreateViewNews(QWidget *parent);

    // destructor
    ~ViewNews();

private:

    // threadul de comunicare cu serverul
    CommunicationThread *ViewNewsThread;

    // elementele de interfata folosite

    // label-urile unde voi afisa text pentru utilizator
    QLabel *ViewLast, *NewsFromCat, *RecursivelyOn, *Levels;

    // liniile de introducere a informatiilor de catre utilizator
    LineEditValidate *InputHowMany, *InputCat, *InputRecursivelyOn;

    // validatorul care imi activeaza sau dezactiveaza butonul de update in functie inputul utilizatorului
    QRegExpValidator *ValidInputMany, *ValidInputCat, *ValidInputRec;

    // butonul de actualizare a categoriilor
    QPushButton *UpdateButton;

    // zona de scroll unde voi incarca widgetul care va contine stirile,
    QScrollArea *NewsBoxArea;

    ViewNewsBoxContainer *NewsContainer;

    // aranjarile in pagina

    // sectiunea de top, unde utilizatorul va introduce comanda de vizualizare de stiri
    QHBoxLayout *TopUp, *TopDown, *TopButton;

    // sectiunea unde voi incadra totul, plus sectiunea unde voi pune NewsBoxArea care va contine Widgetul cu stirile
    QVBoxLayout *All, *Top, *Content;

signals:

    // semnalul pe care il primesc doar dupa ce am actualizat lista globala cu stiri, si atunci ii spun fiului sa faca load
    void UpdatedGlobalNewsList(int how);
public slots:

    // slotul care se executa la apasarea lui UpdateButton.
    void ViewNewsAttempt();

    // slotul care se executa la primirea raspunsului de la server
    void ServerViewNewsResponse(int how);

    // slotul care se executa la modificare inputului de catre user
    void onInputEdit();

};

#endif // VIEWNEWS_H
