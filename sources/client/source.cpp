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
#include<source.h>

int conectareServer(int *sd, char* SAddr, int SPort)
{
    struct sockaddr_in server;      // structura folosita pentru conectare

  /* cream socketul */
  if ((*sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
        fprintf(stdout,"Eroare la crearea socketului!\n");
        exit(0);
    }
  /* umplem structura folosita pentru realizarea conexiunii cu serverul */
  /* familia socket-ului */

  server.sin_family = AF_INET;
  /* adresa IP a serverului */
  server.sin_addr.s_addr = inet_addr(SAddr);
  /* portul de conectare */
  server.sin_port = htons (SPort);
  /* ne conectam la server */

  if (connect (*sd, (struct sockaddr *) &server, sizeof(struct sockaddr)) == -1)
      return 0;
  else
      return 1;
}

// deconectare de la server prin inchiderea socketului sd
int deconectareServer(int *sd)
{
    return close(*sd);
}

// pointerul comanda trebuie sa fie intotdeauna alocat atunci cand se apeleaza functia,
// pointerul raspuns va fi alocat dinamic in functia respectiva
int trimitprimescdelaServer(int *sd, char *comanda, char *raspuns)
{
        char len[10];
        bzero(len, 10);
        int rd, rs;

        sprintf(len, "%10d", strlen(comanda));

        if ((rd = write(*sd, len, 10)) <= 0)
        {
            fprintf(stdout, "Am eroare la comunicarea cu serverul! La trimiterea lungimii comenzii!\n");
            return 0;
        }

        fprintf(stdout, "Trimis lungimea comenzii: %s, codul de write: %d \n", len, rd);
        fflush (stdout);

        bzero(len, 10);

        if ((rd = write (*sd, comanda, strlen(comanda))) <= 0)
        {
            fprintf(stdout, "Am eroare la comunicarea cu serverul! La trimiterea comenzii!\n");
            return 0;
        }

        printf("Trimis comanda: %s, cu codul de write: %d\n", comanda, rd);
        fflush (stdout);

  /* citirea raspunsului dat de server
     (apel blocant pina cind serverul raspunde) */

        bzero(len, 10);

        if ((rd = read (*sd, len, 10)) <= 0)
        {
            fprintf(stdout, "Am eroare la comunicarea cu serverul! La primirea lungimii comenzii!\n");
            return 0;
        }

        if(!(tmp = (char*) realloc (raspuns, sizeof(char) * (atoi(len) + 1))))
        {
           fprintf(stdout, "n-am putut aloca, inchid!");
           exit(0);
        }

        printf("Primit mesaj(lungime de raspuns): %s, cu codul de read: %d\n", len, rd);
        fflush (stdout);

        /* citesc comanda de la client, CU TRATAREA ERORILOR */
        for (rd = 0, rs = 1; rd < atoi(len); rd += rs)
        {
                printf("Primit mesaj: %s, cu codul de read:  %d \n", tmp, rd);
                fflush (stdout);

                /* citesc bit cu bit pana la eroare */
                if ((rs = read(*sd, tmp + rd, atoi(len) - rd)) < 0)
                {
                     fprintf(stdout, "Am eroare la comunicarea cu serverul! Pierd comanda pe drum!\n");
                     return 0;
                }
        }

        printf("Primit mesaj: %s, cu codul de read: %d\n", tmp, rd);
        fflush (stdout);
       return 1;
}


