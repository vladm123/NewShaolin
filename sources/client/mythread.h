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

#ifndef MYTHREAD_H
#define MYTHREAD_H

#include "globals.h"

// threadul de conectare la server

class mythread: public QThread
{
    Q_OBJECT

public:
    mythread(char *Addr, int Port, QObject *parent = 0);
    void run();

signals:
    void Over(int how);

private:

    char *SAddr;
    int SPort;
    char *tmp;

};

#endif // MYTHREAD_H
