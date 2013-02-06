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

#include "main.h"

/* definesc functia care implementeaza asteptarea clientilor si gestioneaza procesarea lor */
int main(int argc, char *argv[])
{	
	/* declar si initializez variabila care retine optiunea pentru setarea reutilizarii adresei */
	int option = 1;

	/* declar variabila care retine datele despre server */
	struct sockaddr_in server;

	/* permit asocierea unui port, CU TRATAREA ERORILOR */
	if (argc >= 2)
		if ((port = atoi(argv[1])) <= 0)
			handle_error("main::main::argv[1]");

	/* permit specificarea unui numar maxim de clienti, CU TRATAREA ERORILOR */
	if (argc >= 3)
		if ((maxc = atoi(argv[2])) <= 0)
			handle_error("main::main::argv[2]");

	/* asociez semnalului SIGCHLD, primit de la copil cand se inchide, functia de tratare, CU TRATAREA ERORILOR */
	if (signal(SIGCHLD, handle_signal) == SIG_ERR)
		handle_error("main::main::signal(SIGCHLD)");

	/* asociez semnalului SIGPIPE, primit cand se inchide conexiunea, functia de ignorare, CU TRATAREA ERORILOR */
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
		handle_error("main::main::signal(SIGPIPE)");

	/* creez socketul, cu protocolul AF_INET + SOCK_STREAM = TCP implicit (0), pentru primirea clientilor, CU TRATAREA ERORILOR */
	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		handle_error("main::main::socket(sd)");

	/* setez reutilizarea adresei */
	setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

	/* initializez (0) datele despre server, pentru asocierea la socket prin primitiva bind() */
	bzero(&server, sizeof(server));

	/* populez datele despre server, pentru asocierea la socket prin primitiva bind() */
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	/* asociez socketul pentru server cu datele despre server, spre a primi clienti, CU TRATAREA ERORILOR */
	if (bind(sd, &server, sizeof(server)) < 0)
		handle_error("main::main::bind(sd)");

	/* astept venirea vreunui client, tinand cont de numarul maxim de clienti din coada, CU TRATAREA ERORILOR */
	if (listen(sd, maxc) < 0)
		handle_error("main::main::listen(sd, maxc)");

	/* scriu mesaj catre supraveghetor */
	printf("[Proces %d] Astept maxim %d clienti la portul %d\n", getpid(), maxc, port);

	/* descriu bucla care trateaza clientii */
	do
	{
		/* scriu mesaj catre supraveghetor */
		printf("[Proces %d] Sunt parintele, mai astept clienti\n", getpid());

		/* accept un client, fara sa fie necesare date despre el (NULL), CU TRATAREA ERORILOR */
		if ((cd = accept(sd, NULL, NULL)) < 0)
			handle_error("main::main::accept(sd)");

		/* verific daca am atins numarul maxim de clienti */
		if (numc >= maxc)
		{
			/* NU servesc clientul, ci inchid socketul de comunicare cu clientul */
			close(cd);
		}
		else
		{
			/* servesc clientul, lansand un proces fiu, CU TRATAREA ERORILOR */
			switch(fork())
			{
				case -1:
				{
					/* tratez cazul de eroare */
					handle_error("main::main::fork()");
					break;
				}
				case 0:
				{
					/* apelez functia de comunicare cu clientul, apeland functia de comunicare cu clientul */
					handle_client();

					/* scriu mesaj catre supraveghetor */
					printf("[Proces %d] Sunt copilul lui %d si nu m-am inchis\n", getpid(), getppid());

					break;
				}
				default:
				{
					/* scriu mesaj catre supraveghetor */
					printf("[Proces %d] Incrementez nr de clienti de la %d la %d, unde max e %d\n", getpid(), numc, numc + 1, maxc);

					/* incrementez numarul de clienti serviti */
					numc++;

					/* tratez cazul parinte */
					break;
				}
			}
		}
	}
	while (1);

	/* intorc valoarea de succes */
	return 0;
}

