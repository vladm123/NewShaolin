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

#include "globals.h"

/* declar si initializez variabila care contine mesajele de eroare */
char *errors[] = 
{
	"error|catid|invalid",
	"error|id|invalid",
	"error|name|invalid",
	"error|password|invalid",
	"error|permissions|invalid",
	"error|r|invalid",
	"error|server|command",
	"error|server|internal",
	"error|server|permissions",
	"error|t|invalid",
	"error|text|invalid",
	"error|username|invalid"
};

/* declar variabila care retine descriptorul pentru server, utilizat la primitiva socket() */
int sd;

/* declar variabila care retine descriptorul pentru client, utilizat la primitiva accept() */
int cd;

/* declar si initializez variabila care retine portul folosit pentru raspunsul la clienti */
int port = 1 << 12;

/* declar si initializez variabila care retine numarul maxim de clienti in coada de asteptare */
int maxc = 1 << 10;

/* declar variabila care retine numarul curent de clienti serviti din coada de asteptare */
int numc;

/* declar si initializez (0) variabila care retine sirul la intrare */
char *input = 0;

/* declar si initializez (0) variabila care retine sirul la iesire */
char *output = 0; 

/* declar si initializez (0) variabila care retine sirul la iesire */
char *command = 0; 

/* declar si initializez (0) variabila care retine temporare */
char *tmp = 0;

/* declar si initializez (0) variabila care retine lungimea sirului la intrare */
int inlength = 0;

/* declar si initializez (0) variabila care retine lungimea sirului la iesire */
int outlength = 0; 

/* declar si initializez (-1) variabila care retine idul utilizatorului conectat */
int connected = -1;

/* declar si initializez (-1) variabila care retine permisiunile utilizatorului conectat */
int permitted = -1;

