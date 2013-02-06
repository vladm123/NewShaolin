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

#include "requests.h"

/* definesc functia care onoreaza cererile */
int requests()
{
	/* verific conditia de inregistrare a utilizatorului */
	if (strncmp(command, "reguser", 7) == 0)
	{
		/* apelez functia de inregistrare */
		c_user_add();

		/* intorc */
		return 1;
	}
	
	/* verific conditia de modificare a utilizatorului */
	if (strncmp(command, "moduser", 7) == 0)
	{
		/* apelez functia de modificare */
		c_user_modify();

		/* intorc */
		return 1;
	}

	/* verific conditia de vizualizare a utilizatorilor */
	if (strncmp(command, "viewusers", 9) == 0)
	{
		/* apelez functia de vizualizare */
		c_users_view();

		/* intorc */
		return 1;
	}

	/* verific conditia de vizualizare a utilizatorului */
	if (strncmp(command, "viewuser", 8) == 0)
	{
		/* apelez functia de vizualizare */
		c_user_view();

		/* intorc */
		return 1;
	}
	/* verific conditia de conectare a utilizatorului */
	if (strncmp(command, "connuser", 8) == 0)
	{
		/* apelez functia de conectare */
		c_user_connect();

		/* intorc */
		return 1;
	}

	/* verific conditia de deconectare a utilizatorului */
	if (strncmp(command, "dconnuser", 9) == 0)
	{
		/* apelez functia de deconectare */
		c_user_disconnect();

		/* intorc */
		return 1;
	}

	/* verific conditia de adaugare a stirii */
	if (strncmp(command, "addnew", 6) == 0)
	{
		/* apelez functia de adaugare */
		c_new_add();

		/* intorc */
		return 1;
	}

	/* verific conditia de modificare a stirii */
	if (strncmp(command, "modnew", 6) == 0)
	{
		/* apelez functia de modificare */
		c_new_modify();

		/* intorc */
		return 1;
	}

	/* verific conditia de stergere a stirii */
	if (strncmp(command, "delnew", 6) == 0)
	{
		/* apelez functia de stergere */
		c_new_remove();

		/* intorc */
		return 1;
	}

	/* verific conditia de vizualizare a stirilor */
	if (strncmp(command, "viewnews", 8) == 0)
	{
		/* apelez functia de vizualizare */
		c_news_view();

		/* intorc */
		return 1;
	}

	/* verific conditia de vizualizare a stirii */
	if (strncmp(command, "viewnew", 7) == 0)
	{
		/* apelez functia de vizualizare */
		c_new_view();

		/* intorc */
		return 1;
	}

	/* verific conditia de adaugare a categoriei */
	if (strncmp(command, "addcat", 6) == 0)
	{
		/* apelez functia de adaugare */
		c_cat_add();

		/* intorc */
		return 1;
	}

	/* verific conditia de modificare a categoriei */
	if (strncmp(command, "modcat", 6) == 0)
	{
		/* apelez functia de modificare */
		c_cat_modify();

		/* intorc */
		return 1;
	}

	/* verific conditia de stergere a categoriei */
	if (strncmp(command, "delcat", 6) == 0)
	{
		/* apelez functia de stergere */
		c_cat_remove();

		/* intorc */
		return 1;
	}

	/* verific conditia de vizualizare a categoriilor */
	if (strncmp(command, "viewcats", 8) == 0)
	{
		/* apelez functia de vizualizare */
		c_cats_view();

		/* intorc */
		return 1;
	}

	/* verific conditia de vizualizare a categoriilor */
	if (strncmp(command, "viewcat", 7) == 0)
	{
		/* apelez functia de vizualizare */
		c_cat_view();

		/* intorc */
		return 1;
	}

	/* intorc esec */
	return 0;
}

