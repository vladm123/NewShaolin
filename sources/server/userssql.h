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

#ifndef _userssql_h
#define _userssql_h

/* includ anteturile necesare functiilor */
#include <mysql.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* declar functia de vizualizarea a utilizatorilor */
void sql_users_view();

/* declar functia de vizualizarea a utilizatorilor */
int sql_user_view(int);

/* definesc functia de adaugare a unui utilizator, care intoarce identificatorul utilizatorului adaugat */
int sql_user_add(char *, char *);

/* definesc functia de modificare a unui utilizator */
int sql_user_modify(int, char *, int);

/* definesc functia de conectare a unui utilizator */
int sql_user_connect(char *, char *);

#endif
