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

#ifndef _handlers_h
#define _handlers_h

/* includ anteturile necesare functiilor */
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

/* declar functia de adaugare in output */
void handle_output(char *, int);

/* declar functia de adaugare intr-un sir oarecare */
void handle_string(char *, char *, int);

/* declar functia de tratare a semnalelor */
void handle_signal(int);

/* declar functia de tratare a erorilor */
void handle_error(char *);

/* declar functia care citeste cererea de la client la server */
void handle_read();

/* declar functia de test alfanumeric */
int handle_alphanumerical(char *, int);

/* declar functia care proceseaza cererea de la client intr-un raspuns de la server */
void handle_process();

/* declar functia care scrie raspunsul de la server catre client */
void handle_write();

/* declar functia de tratare a unui client */
void handle_client();

#endif
