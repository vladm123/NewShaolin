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

#ifndef COMMUNICATIONTHREAD_H
#define COMMUNICATIONTHREAD_H

#include "globals.h"

// clasa Thread care realizeaza comunicarea cu serverului conform protocolului specificat
class CommunicationThread: public QThread
{
    Q_OBJECT
public:
    CommunicationThread(int *socket, char *message, QObject *parent = 0);
    ~CommunicationThread();
    void run();
    QString getResponse();

signals:
    void Over(int);

private:

    char *toSend, *tempo;

    // varianta alternativa de sincronizare cu membru static
    static int Busy;
    int sd;
    QString toReceive;
  };

#endif // COMMUNICATIONTHREAD_H
