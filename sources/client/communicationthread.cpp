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

#include "communicationthread.h"

// initializez cu 0 pentru a permite intrarea in sectiunea critica
int CommunicationThread::Busy = 0;

CommunicationThread::CommunicationThread(int *socket, char *message, QObject *parent): toSend(0), tempo(0)
{
    //setez parintele
    this->setParent(parent);

    char *tempu;
    // imi pregatesc structurile de date pentru rulare
     if(!(tempu = (char*)malloc(sizeof(char) * strlen(message))))
     {
         fprintf(stdout, "Am eroare la alocarea memoriei in thread!\n");
         fflush(stdout);
         exit(0);
     }

        fprintf(stdout, "\n[CommunicationThread]Atribuire");
         fflush(stdout);

        toSend = tempu;

        // copiez datele din comanda in toSend
        strcpy(toSend, message);
        toSend[strlen(message)] = 0;

        this->sd = *socket;

        fprintf(stdout, "\n[CommunicationThread]Setat Comanda: %s\n", toSend);
        fflush(stdout);
}
void CommunicationThread::run()
{

    fprintf(stdout, "\n[CommunicationThread]RUN\n");
    fflush(stdout);


    // intru in sectiunea critica, lock
    Mutex.lock();

    // varianta alternativa de sincronizare

    // cat timp socketul e ocupat
//    while(CommunicationThread::Busy)
//    {
//        // asteapta
//    }

//    CommunicationThread::Busy = 1;

    char len[10];
    bzero(len, 10);
    int rd, rs;

    sprintf(len, "%10d", strlen(toSend));

    fprintf(stdout, "[CommunicationThread]Vreau sa trimit comanda: %s.\n", toSend);
    fflush(stdout);

       if ((rd = write(sd, len, 10)) <= 0)
       {
           fprintf(stdout, "[CommunicationThread]Eroare la trimiterea lungimii comenzii catre server!\n");
           fflush(stdout);
           exit(0);
       }

        fprintf(stdout, "[CommunicationThread]Trimis catre server lungimea comenzii: %s, codul de write: %d \n", len, rd);
        fflush (stdout);

        bzero(len, 10);

        if ((rd = write (sd, toSend, strlen(toSend))) <= 0)
        {
            fprintf(stdout, "[CommunicationThread]Eroare la trimiterea comenzii catre server!\n");
            fflush(stdout);
            exit(0);
        }

        fprintf(stdout, "[CommunicationThread]Trimis catre server comanda: %s, cu codul de write: %d\n", toSend, rd);
        fflush (stdout);

      /* citirea raspunsului dat de server
         (apel blocant pina cind serverul raspunde) */

        bzero(len, 10);

        if ((rd = read (sd, len, 10)) <= 0)
        {
            fprintf(stdout, "[CommunicationThread]Eroare la primirea lungimii raspunsului de la sercer!\n");
            fflush(stdout);
            exit(0);
        }

        fprintf(stdout, "[CommunicationThread]Alocare");
        fflush (stdout);

        if(!(tempo = (char*) malloc(sizeof(char) * (atoi(len) + 1))))
        {
           fprintf(stdout, "[CommunicationThread]N-am putut aloca memorie pentru raspuns. Inchid!");
           fflush(stdout);
           exit(0);
        }

        memset(tempo, 0, sizeof(char) * (atoi(len) + 1));

       fprintf(stdout,"[CommunicationThread]Primit lungimea raspunsului de la server: %s, cu codul de read: %d\n", len, rd);
       fflush (stdout);

        /* citesc comanda de la client, CU TRATAREA ERORILOR */
        for (rd = 0, rs = 1; rd < atoi(len); rd += rs)
        {
            fprintf(stdout, "[CommunicationThread]%d %d \n", rs, rd);
             fflush (stdout);

             /* citesc bit cu bit pana la eroare */
             if ((rs = read(sd, tempo + rd, atoi(len) - rd)) < 0)
             {
                 fprintf(stdout, "[CommunicationThread]Eroare primirea comenzii de la server! Inchid\n");
                 exit(0);
             }

             fprintf(stdout, "[CommunicationThread]Primit raspuns de la server: pointer: %p - %s, cu codul de read:  %d \n",tempo, tempo, rs);
             fflush (stdout);
        }

     toReceive = QString::fromAscii(tempo);

     free(tempo);
   // am terminat comunicatia cu serverul
   // CommunicationThread::Busy = 0;

   // end sectiunea critica
    Mutex.unlock();

    // emit semnalul
   emit Over(1);

}

// gettter pentru mesaj
QString CommunicationThread::getResponse()
{
     return toReceive;
}

CommunicationThread::~CommunicationThread()
{
    if(toSend)
        delete toSend;

    fprintf(stdout,"[CommunicationThread]am sters toSend");
    fflush(stdout);
}
