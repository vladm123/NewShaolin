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

#ifndef _globals_h
#define _globals_h

/* declar variabila care contine mesajele de eroare */
extern char *errors[];

/* declar variabila care retine descriptorul pentru server, utilizat la primitiva socket() */
extern int sd;

/* declar variabila care retine descriptorul pentru client, utilizat la primitiva accept() */
extern int cd;

/* declar variabila care retine portul folosit pentru raspunsul la clienti */
extern int port;

/* declar variabila care retine numarul maxim de clienti in coada de asteptare */
extern int maxc;

/* declar variabila care retine numarul curent de clienti serviti din coada de asteptare */
extern int numc;

/* declar variabila care retine sirul la intrare */
extern char *input;

/* declar variabila care retine sirul la iesire */
extern char *output; 

/* declar variabila care retine comanda */
extern char *command;

/* declar variabila care retine temporare */
extern char *tmp;

/* declar variabila care retine idul conectatului */
extern int connected;

/* declar variabila care retine permisiunile conectatului */
extern int permitted;

/* declar variabila care retine lungimea sirului la intrare */
extern int inlength;

/* declar variabila care retine lungimea sirului la iesire */
extern int outlength; 

#endif
