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

#ifndef _newssql_h
#define _newssql_h

/* includ anteturile necesare functiilor */
#include <mysql.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* declar functia care adauga stirile */
int sql_new_add(char *, char *, int);

/* declar functia care modifica stirile */
int sql_new_modify(int, char *, char *, int);

/* declar functia care sterge stirile */
int sql_new_remove(int);

/* declar functia de vizualizare a stirilor */
void sql_news_view(int, int, int, int);

/* declar functia de vizualizare a unei stiri */
int sql_new_view(int);

/* declar functia de test a existentei unei stiri */
int sql_new_user_exists(int);

#endif
