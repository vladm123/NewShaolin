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

#ifndef _catssql_h
#define _catssql_h

/* includ anteturile necesare functiilor */
#include <mysql.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* declar functia care adauga categoriile */
int sql_cat_add(char *, int);

/* declar functia care modifica categoriile */
int sql_cat_modify(int, char *, int);

/* declar functia care sterge categoriile */
int sql_cat_remove(int);

/* declar functia care vizualizeaza categorii */
void sql_cats_view(char *, int);

/* declar functia care vizualizeaza o categorie */
int sql_cat_view(int);

/* declar functia recursiva care vizualizeaza parintii categoriei curente */
void sql_cat_view_parents(char *);

/* declar functia de test a existentei unei categorii */
int sql_cat_user_exists(int);

#endif
