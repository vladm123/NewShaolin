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

#ifndef _newsc_h
#define _newsc_h

/* includ antetul cu variabile globale */
#include "globals.h"

/* includ anteturile necesare functiilor */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* declar functia care adauga o stire */
void c_new_add();

/* declar functia care modifica o stire */
void c_new_modify();

/* declar functia care sterge o stire */
void c_new_remove();

/* declar functia care vizualizeaza o stire */
void c_new_view();

/* declar functia care vizualizeaza stiri */
void c_news_view();

#endif
