/*

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

#include "handlers.h"
#include "globals.h"

/* definesc functia care adauga un sir la alt sir */
void handle_string(char *str, char *msg, int inc)
{
	/* declar variabila care contine noua valoare */
	int newlen;

	/* tratez cazul incremental */
	if (inc)
	{
		/* maresc lungimea functie de parametru */
		newlen = strlen(str) + strlen(msg);
	}

	/* tratez celalalt caz */
	else
	{
		/* initializez lungimea functie de parametru */
		newlen = strlen(msg);
	}

	/* aloc memorie pentru raspuns */
	if ((tmp = (char *)realloc(str, (newlen + 1) * sizeof(char))) == NULL)
		handle_error("handlers::handle_string::realloc(str, newlen)");

	/* tratez cazul incremental */
	if (inc)
	{
		/* concatenez sirul */
		strcat(tmp, msg);
	}

	/* tratez celalalt caz */
	else
	{
		/* adaug sirul */
		strcpy(tmp, msg);
	}

	/* setez octetul de terminare */
	tmp[newlen] = 0;
}

/* definesc functia de adaugare in output */
void handle_output(char *msg, int inc)
{
	/* tratez cazul incremental */
	if (inc)
	{
		/* maresc lungimea functie de parametru */
		outlength += strlen(msg);
	}

	/* tratez celalalt caz */
	else
	{
		/* initializez lungimea functie de parametru */
		outlength = strlen(msg);
	}

	/* aloc memorie pentru raspuns */
	if ((tmp = (char *)realloc(output, (outlength + 1) * sizeof(char))) == NULL)
		handle_error("handlers::handle_output::realloc(output, outlength)");
	else
		output = tmp;

	/* tratez cazul incremental */
	if (inc)
	{
		/* concatenez sirul */
		strcat(output, msg);
	}

	/* tratez celalalt caz */
	else
	{
		/* adaug sirul */
		strcpy(output, msg);
	}

	/* setez octetul de terminare */
	output[outlength] = 0;
}

/* definesc functia de tratare a semnalelor */
void handle_signal(int sig)
{
	/* tratez cazul cand semnalul este trimis de copil */
	if (sig == SIGCHLD)
	{
		/* astept copilul sa se termine */
		wait(NULL);
		
		/* decrementez numarul de clienti */
		numc--;

		/* scriu mesaj catre supraveghetor */
		printf("[Proces %d] Decrementez numarul de clienti de la %d la %d, unde maximul este %d\n", getpid(), numc + 1, numc, maxc);
	}
}

/* definesc functia de tratare a erorilor */
void handle_error(char *name)
{
	/* inchid socketul de comunicare cu clientul */
	close(cd);

	/* scriu mesaj catre supraveghetor */
	printf("[Proces %d cu parintele %d] Eroare fatala: %s\n", getpid(), getppid(), name);

	/* termin cu eroare */
	exit(1);
}

/* definesc functia de test si inlocuire */
int handle_alphanumerical(char *string, int max)
{
	/* declar o variabila cu care ma plimb in sir */
	int i;

	/* parcurg sirul */
	for (i = 0; string[i] && i <= max; ++i)
	{
		/* inlocuiesc ghilimeaua */
		if (string[i] == '"')
			string[i] = '`';

		/* inlocuiesc apostroful */
		if (string[i] == '\'')
			string[i] = '`';
	}

	/* intorc lungimea sirului rezultat */
	return i;
}

/* definesc functia care citeste cererea de la client la server */
void handle_read()
{
	/* declar variabila care retine numarul de octeti cititi */
	int ip;

	/* declar variabila care retine numarul curent de octeti cititi */
	int iq;

	/* declar variabila care retine lungimea cererii */
	char *length = NULL;

	/* construiesc sirul lungime */
	handle_string(length, "1234567890", 0);
	length = tmp;

	/* scriu mesaj catre supraveghetor */
	printf("[Proces %d cu parintele %d] Astept read\n", getpid(), getppid());		

	/* citesc lungimea de comanda de la client, CU TRATAREA ERORILOR */
	for (ip = 0, iq = 1; ip < 10; ip += iq)
	{
		/* citesc bit cu bit pana la eroare */
		if ((iq = read(cd, length + ip, 10 - ip)) <= 0)
			handle_error("handlers::handle_read::read(cd, length, 10)");
	}

	/* scriu mesaj catre supraveghetor */
	printf("[Proces %d cu parintele %d] Facut read de lungime %d si valoare %s\n", getpid(), getppid(), ip, length);		

	/* tratez starea de eroare a comenzii */
	if (ip <= 0)
		handle_error("handlers::handle_read::read(cd, input, 32)");

	/* calculez lungimea mesajului de citit */
	if ((inlength = atoi(length)) <= 0)
	{
		/* scriu eroare de comanda */
		handle_output(errors[6], 0);

		/* eliberez sirul lungime */
		free(length);

		/* intorc */
		return;
	}

	/* aloc memorie pentru sirul in care citesc lungimea mesajului */
	if ((tmp = (char *)realloc(input, (inlength + 1) * sizeof(char))) == NULL)
		handle_error("handlers::handle_read::realloc(input, inlength)");
	else
		input = tmp;

	/* scriu mesaj catre supraveghetor */
	printf("[Proces %d cu parintele %d] Astept read\n", getpid(), getppid());		

	/* citesc comanda de la client, CU TRATAREA ERORILOR */
	for (ip = 0, iq = 1; ip < inlength; ip += iq)
	{
		/* citesc bit cu bit pana la eroare */
		if ((iq = read(cd, input + ip, inlength - ip)) <= 0)
			handle_error("handlers::handle_read::read(cd, input, inlength");
	}

	/* setez 0 octetul de terminare */
	input[inlength] = 0;

	/* scriu mesaj catre supraveghetor */
	printf("[Proces %d cu parintele %d] Facut read de lungime %d si valoare %s\n", getpid(), getppid(), ip, input);		

	/* eliberez sirul lungime */
	free(length);
}

/* definesc functia care proceseaza cererea de la client intr-un raspuns de la server */
void handle_process()
{
	/* initializez variabila care retine prima portiune din input */
	command = strtok(input, "|");

	/* verific cazul in care sirul de iesire este deja completat */
	if (outlength > 0)
	{
		/* intorc */
		return;
	}	

	/* verific ca respectiva comanda sa existe */
	if (command == NULL)
	{
		/* scriu eroare de comanda */
		handle_output(errors[6], 0);

		/* intorc */
		return;
	}

	/* apelez o comanda */
	if (requests() == 0)
	{
		/* scriu eroarea de comanda */
		handle_output(errors[6], 0);
	}
}

/* definesc functia care scrie raspunsul de la server catre client */
void handle_write()
{
	/* declar variabila care retine numarul de octeti scrisi */
	int op;

	/* declar variabila care contine sirul cu lungimea mesajului */
	char *length = NULL;

	/* verific cazul in care sirul de iesire nu este completat */
	if (outlength <= 0)
	{
		/* intorc */
		return;
	}

	/* sonstruiesc raspunsul */
	handle_string(length, "1234567890", 0);
	length = tmp;	

	/* construiesc sirul lungime */
	sprintf(length, "%10d", outlength);

	/* scriu mesaj catre supraveghetor */
	printf("[Proces %d cu parintele %d] Astept write\n", getpid(), getppid());		

	/* scriu rezultatul catre client, CU TRATAREA ERORILOR */  
	if ((op = write(cd, length, 10)) <= 0)
		handle_error("handlers::handle_write::write(cd, length)");

	/* scriu mesaj catre supraveghetor */
	printf("[Proces %d cu parintele %d] Facut write de lungime %d si valoare %s\n", getpid(), getppid(), op, length);		

	/* scriu mesaj catre supraveghetor */
	printf("[Proces %d cu parintele %d] Astept write\n", getpid(), getppid());		

	/* scriu rezultatul catre client, CU TRATAREA ERORILOR */  
	if ((op = write(cd, output, outlength)) <= 0)
		handle_error("handlers::handle_write::write(cd, output)");

	/* scriu mesaj catre supraveghetor */
	printf("[Proces %d cu parintele %d] Facut write de lungime %d si valoare %s\n", getpid(), getppid(), op, output);		

	/* eliberez variabilele alocate */
	free(length);
}

/* definesc functia de tratare a unui client */
void handle_client()
{
	/* scriu mesaj catre supraveghetor */
	printf("[Proces %d cu parintele %d] Start client\n", getpid(), getppid());

	/* aloc pentru prima data sirurile cerere si raspuns */
	input = output = NULL;

	/* initializez lungimile sirurilor de intrare si iesire */
	inlength = outlength = 0;

	/* creez bucla de comunicare cu clientul */
	do
	{
		/* apelez functia care citeste cererea de la client catre server, CU TRATAREA ERORILOR */
		handle_read();

		/* apelez functia care proceseaza cererea de la client intr-un raspuns de la server, CU TRATAREA ERORILOR */			
		handle_process();
	
		/* apelez functia care scrie raspunsul de la server catre client, CU TRATAREA ERORILOR */			
		handle_write();

		/* tratez cazul in care nu pot scrie nimic */
		if (outlength <= 0) 
			handle_error("handlers::handle_client::output()");
		
		/* scriu mesaj catre supraveghetor */
		printf("[Proces %d cu parintele %d] Reinitializez\n", getpid(), getppid());

		/* initializez (0) fluxul de intrare */
		free(input);
		input = NULL;

		/* initializez (0) fluxul de iesire */
		free(output);
		output = NULL;

		/* initializez lungimile sirurilor de intrare si iesire */
		inlength = outlength = 0;
	}
	while (1);
}

