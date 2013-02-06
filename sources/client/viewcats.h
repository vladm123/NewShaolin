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

#ifndef VIEWCATS_H
#define VIEWCATS_H

#include "globals.h"
#include "communicationthread.h"

class ViewCats: public QWidget
{
    Q_OBJECT
public:

    // constructor
    ViewCats(QWidget *parent = 0);

    // destructor
    ~ViewCats();

    // declar functia care imi creeaza instanta
    static QWidget * CreateWiewCats(QWidget *parent);

private:

    // elementele de interfata

    // label-urile unde voi pune continutulu
    QLabel *Title, *Content;

    // zona in care pot vedea categoriile, restul va fi cu scroll
    QScrollArea *ViewArea;

    // butonul de upate
    QPushButton *UpdateCats;

    // hbox-ul unde voi pune butonul de actualizare
    QHBoxLayout *Button, *TitleBox;

    // aranjarea in pagina
    QVBoxLayout *All, *ContentBox;


    // zonele de date unde voi retine ... lista ...

    // threadul de comunicare cu serverul
    CommunicationThread *ViewCatsThread;

signals:

    void ViewCatsResponse(int how);

public slots:

    // slotul care se executa la apasarea butonului de update
    void UpdateCatsAttempt();

    // slotul care se executa cand am raspus de la server
    void ServerUpdateCatsResponse(int how);

};

#endif // VIEWCATS_H
