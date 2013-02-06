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

#include "mythread.h"

// implementare

// constructor
mythread::mythread(char *Addr, int Port, QObject *parent)
{
    this->setParent(parent);

     fprintf(stdout,"\ncheck thread 1\n");

    if((tmp = (char*)malloc (sizeof(char) * 16)))
        SAddr = tmp;
    else
    {
       fprintf(stdout, "n-am putut aloca, inchid!");
       exit(0);
    }

    memset(SAddr, 0, sizeof(char) * 16);

    fprintf(stdout,"\ncheck thread 1\n");
    strcpy(SAddr, Addr);
    SPort = Port;
}

// functia de run
void mythread::run()
{
     fprintf(stdout,"\ncheck thread 3\n");

    if(conectareServer(sd, SAddr, SPort))
    {
         fprintf(stdout,"\ncheck thread 4\n");

        emit Over(1);
    }
    else
    {
         fprintf(stdout,"\ncheck thread 5\n");
        emit Over(0);
    }
}
