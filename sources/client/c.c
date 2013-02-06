/*

	Copyright 2009, Lenuta Alboaie
	Copyright 2009, 2010 Vlad Manea, Sebastian Codrin Ditu

	This file is part of newshaolin.

    	newshaolin is free software: you can redistribute it and/or modify
    	it under the terms of the GNU General Public License as published by
    	the Free Software Foundation, either version 3 of the License, or
    	(at your option) any later version.

    	newshaolin is distributed in the hope that it will be useful,
    	but WITHOUT ANY WARRANTY; without even the implied warranty of
    	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    	GNU General Public License for more details.

    	You should have received a copy of the GNU General Public License
    	along with newshaolin.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>

/* codul de eroare returnat de anumite apeluri */
extern int errno;

/* portul de conectare la server*/
int port;

int rd, rs;

int main (int argc, char *argv[])
{
  int sd;			// descriptorul de socket
  struct sockaddr_in server;	// structura folosita pentru conectare 
  char msg[10000], len[10000];		// mesajul trimis

  /* exista toate argumentele in linia de comanda? */
  if (argc != 3)
    {
      printf ("Sintaxa: %s <adresa_server> <port>\n", argv[0]);
      return -1;
    }

  /* stabilim portul */
  port = atoi (argv[2]);

  /* cream socketul */
  if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("Eroare la socket().\n");
      return errno;
    }

  /* umplem structura folosita pentru realizarea conexiunii cu serverul */
  /* familia socket-ului */
  server.sin_family = AF_INET;
  /* adresa IP a serverului */
  server.sin_addr.s_addr = inet_addr(argv[1]);
  /* portul de conectare */
  server.sin_port = htons (port);
  
  /* ne conectam la server */
  if (connect (sd, (struct sockaddr *) &server,sizeof (struct sockaddr)) == -1)
    {
      perror ("[client]Eroare la connect().\n");
      return errno;
    }

	while (1)
{
	bzero (msg, 10000);
	bzero(len, 10000);

	printf("Astept de la tastatura\n");
	fflush (stdout);


  	read (0, msg, 10000);

	int i;
	for (i = 0; i < 10000; ++i)
		if (msg[i] == '\n') msg[i] = 0;

	sprintf(len, "%10d", strlen(msg));

	if ((rd = write(sd, len, 10)) <= 0)
    	{
      		perror ("[client]Eroare la write() spre server.\n");
      		return errno;
    	}

	printf("Facut write1 cu codul %d si mesajul %s\n", rd, len);
	fflush (stdout);

	if ((rd = write (sd, msg, strlen(msg))) <= 0)
	{
		perror ("[client]Eroare la write() spre server.\n");
		return errno;
	}

	printf("Facut write2 cu codul %d si mesajul %s\n", rd, msg);
	fflush (stdout);

  /* citirea raspunsului dat de server 
     (apel blocant pina cind serverul raspunde) */
	
	bzero(msg, 10000);
	bzero(len, 10000);

	fflush (stdout);

	if ((rd = read (sd, len, 10)) <= 0)
	{
      		perror ("[client]Eroare la read() de la server.\n");
      		return errno;
   	}

	printf("Facut read1 cu codul %d si valoarea %s\n",rd, len );
	fflush (stdout);

	/* citesc comanda de la client, CU TRATAREA ERORILOR */
	for (rd = 0, rs = 1; rd < atoi(len); rd += rs)
	{
		printf("Fac read2 cu codul %d si valoarea %s\n",rd, msg );
		fflush (stdout);

		/* citesc bit cu bit pana la eroare */
		if ((rs = read(sd, msg + rd, atoi(len) - rd)) < 0)
		{
			perror ("[client]Eroare la write() spre server.\n");
			return errno;
		}
	}



	printf("Facut read2 cu codul %d si valoarea %s\n",rd, msg );
	fflush (stdout);
}

  /* inchidem conexiunea, am terminat */
  close (sd);
}
