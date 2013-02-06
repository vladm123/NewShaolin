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

#include "usersc.h"
#include "globals.h"

	/* definesc functia care adauga o categorie */
	void c_cat_add()
	{
		/* declar variabila care retine idul parintelui categoriei */
		int catpid;

		/* declar variabila care retine rezultate */
		int res;

		/* declar variabila care retine numarul intors din baza de date */
		char number[11];

		/* declar variabila care retine numele categoriei */
		char *name = NULL;

		/* verific ca utilizatorul sa fie conectat si sa aiba drepturi */
		if (connected >= 1)
		{
			/* verific ca utilizatorul sa aiba drepturi */
			if (!(permitted == 3 || permitted == 4))
			{
				/* scriu eroare de permisiuni */
				handle_output(errors[8], 0);
			}

			/* extrag numele */
			else if ((command = strtok(NULL, "|")) == NULL)
			{
				/* scriu eroare de nume */
				handle_output(errors[2], 0);
			}
	
			/* tratez celalalt caz */
			else
			{
				/* calculez lungimea numelui */
				res = handle_alphanumerical(command, 256);

				/* verific situatiile de eroare */
				if (res < 1 || res > 256)
				{
					/* scriu eroare de nume */
					handle_output(errors[2], 0);
				}
		
				/* tratez celalalt caz */
				else
				{
					/* construiesc numele */
					handle_string(name, command, 0);
					name = tmp;

					/* extrag cidul */
					if ((command = strtok(NULL, "|")) == NULL)
					{
						/* scriu eroare de categorie */
						handle_output(errors[0], 0);
					}

					/* tratez celalalt caz */
					else
					{
						/* construiesc categoria parinte */
						catpid = atoi(command);

						/* verific sa nu mai am separatori in plus */
						if (command = strtok(NULL, "|"))
						{
							/* scriu eroare de comanda */
							handle_output(errors[6], 0);
						}

						/* adaug categoria, CU TRATAREA ERORILOR */
						else if ((res = sql_cat_add(name, catpid)) <= 0)
						{
							/* scriu eroare de id */
							handle_output(errors[1], 0);
						}
						
						/* tratez celalalt caz */
						else
						{
							/* construiesc raspunsul */
							handle_output("success|", 0);

							/* construiesc numarul */
							sprintf(number, "%d", res);

							/* construiesc raspunsul */
							handle_output(number, 1);
						}
					}
				}
			}

			/* eliberez sirurile alocate */
			free(name);
		}

		/* tratez cazul cand nu am drepturi */
		else
		{
			/* scriu eroare de drepturi */
			handle_output(errors[8], 0);
		}
	}

	/* definesc functia care modifica o categorie */
	void c_cat_modify()
	{
		/* declar variabila care retine idul categoriei */
		int id;

		/* declar variabila care retine idul userului propunator */
		int user;

		/* declar variabila care retine rezultatul */
		int res;

		/* declar variabila care retine idul parintelui categoriei */
		int catpid;

		/* declar variabila care retine numele categoriei */
		char *name = NULL;

		/* verific ca utilizatorul sa fie conectat si sa aiba drepturi */
		if (connected >= 1)
		{
			/* verific sa am drepturi */
			if (!(permitted == 3 || permitted == 4))
			{
				/* scriu eroare de drepturi */
				handle_output(errors[8], 0);
			}

			/* extrag idul */
			else if ((command = strtok(NULL, "|")) == NULL)
			{
				/* scriu eroare de id */
				handle_output(errors[1], 0);
			}

			/* calculez idul */
			else if ((id = atoi(command)) <= 0)
			{
				/* scriu eroare de id */
				handle_output(errors[1], 0);
			}

			/* retin rezultatul existentei idului, CU TRATAREA ERORILOR */
			else if ((user = sql_cat_user_exists(id)) <= 0)
			{
				/* scriu eroare de drept */
				handle_output(errors[8], 0);
			}

			/* testez sa aiba drepturi de modificare */
			else if (permitted == 3 && user != connected)
			{
				/* scriu eroare de drept */
				handle_output(errors[8], 0);
			}

			/* extrag numele */
			else if ((command = strtok(NULL, "|")) == NULL)
			{
				/* scriu eroare de nume */
				handle_output(errors[2], 0);
			}
			
			/* tratez celalalt caz */
			else
			{
				/* calculez lungimea numelui */
				res = handle_alphanumerical(command, 256);

				/* verific situatiile de eroare */
				if (res < 1 || res > 256)
				{
					/* scriu eroare de nume */
					handle_output(errors[2], 0);
				}

				/* tratez celalalt caz */
				else
				{
					/* construiesc numele */
					handle_string(name, command, 0);
					name = tmp;

					/* extrag cidul */
					if ((command = strtok(NULL, "|")) == NULL)
					{
						/* eroare de categorie */
						handle_output(errors[0], 0);
					}

					/* tratez celalalt caz */
					else
					{
						/* calculez cidul, daca pot */
						catpid = atoi(command);

						/* verific sa nu mai am separatori in plus */
						if (command = strtok(NULL, "|"))
						{
							/* scriu eroare de comanda */
							handle_output(errors[6], 0);
						}

						/* modific categoria, CU TRATAREA ERORILOR */
						else if (sql_cat_modify(id, name, catpid, connected) == 0)
						{
							/* scriu eroare de id */
							handle_output(errors[1], 0);
						}
			
						/* tratez cazul celalalt */
						else
						{
							/* construiesc raspunsul */
							handle_output("success", 0);
						}
					}
				}
			}

			/* eliberez sirurile alocate */
			free(name);
		}

		/* tratez cazul cand nu am drepturi */
		else
		{
			/* scriu eroare de drepturi */
			handle_output(errors[8], 0);
		}
	}

	/* definesc functia care sterge o categorie */
	void c_cat_remove()
	{
		/* declar variabila care retine idul categoriei */
		int id;

		/* declar variabila care retine idul userului propunator */
		int user;

		/* declar variabila care retine rezultate */
		int res;

		/* verific ca utilizatorul sa fie conectat */
		if (connected >= 1)
		{
			/* verific ca utilizatorul sa aiba drepturi */
			if (!(permitted == 3 || permitted == 4))
			{
				/* scriu eroare de drepturi */
				handle_output(errors[8], 0);
			}

			/* extrag idul */
			else if ((command = strtok(NULL, "|")) == NULL)
			{
				/* scriu eroare de id */
				handle_output(errors[1], 0);
			}

			/* calculez idul */
			else if ((id = atoi(command)) <= 0)
			{
				/* scriu eroare de id */
				handle_output(errors[1], 0);
			}

			/* retin rezultatul existentei idului, CU TRATAREA ERORILOR */
			else if ((user = sql_cat_user_exists(id)) <= 0)
			{
				/* scriu eroare de drepturi */
				handle_output(errors[8], 0);
			}

			/* testez sa aiba drepturi de modificare */
			else if (permitted == 3 && user != connected)
			{
				/* scriu eroare de drepturi */
				handle_output(errors[8], 0);
			}

			/* verific sa nu mai am separatori in plus */
			else if (command = strtok(NULL, "|"))
			{
				/* scriu eroare de comanda */
				handle_output(errors[6], 0);
			}

			/* sterg categoria, CU TRATAREA ERORILOR */
			else if (sql_cat_remove(id) == 0)
			{
				/* scriu eroare de id */
				handle_output(errors[1], 0);
			}
			
			/* tratez celalalt caz */
			else
			{
				/* construiesc raspunsul */
				handle_output("success", 0);
			}
		}

		/* tratez cazul cand nu am drepturi */
		else
		{
			/* scriu eroare de drepturi */
			handle_output(errors[8], 0);
		}
	}

	/* definesc functia care vizualizeaza categoriile */
	void c_cats_view()
	{
		/* declar variabila care retine rezultate */
		int res;

		/* verific ca utilizatorul sa fie conectat */
		if (connected >= 1)
		{
			/* verific sa am drepturi */
			if (!(permitted == 1 || permitted == 2 || permitted == 3 || permitted == 4)) 
			{
				/* scriu eroare de permisiuni */
				handle_output(errors[8], 0);
			}

			/* verific daca mai am separatori in plus */
			else if (command = strtok(NULL, "|"))
			{
				/* scriu eroare de comanda */
				handle_output(errors[6], 0);
			}

			/* tratez celalalt caz */
			else
			{
				/* scriu mesajul de succes */
				handle_output("success", 0);

				/* apelez functia de selectare din baza de date */
				sql_cats_view(NULL, 0);
			}
		}

		/* tratez cazul cand nu era conectat */
		else
		{
			/* scriu eroare de permisiuni */
			handle_output(errors[8], 0);
		}
	}

	/* definesc functia care vizualizeaza o categorie */
	void c_cat_view()
	{
		/* declar variabila care retine idul categoriei */
		int id;

		/* declar variabila care retine rezultate */
		int res;

		/* verific ca utilizatorul sa fie conectat si sa aiba drepturi */
		if (connected >= 1)
		{
			/* verific sa am permisiuni */
			if (!(permitted == 1 || permitted == 2 || permitted == 3 || permitted == 4))
			{
				/* scriu eroare de permisiuni */
				handle_output(errors[8], 0);
			}

			/* extrag idul */
			else if ((command = strtok(NULL, "|")) == NULL)
			{
				/* scriu eroare de id */
				handle_output(errors[1], 0);
			}

			/* calculez idul */
			else if ((id = atoi(command)) <= 0)
			{
				/* scriu eroare de id */
				handle_output(errors[1], 0);
			}

			/* verific sa nu mai am separatori in plus */
			else if (command = strtok(NULL, "|"))
			{
				/* scriu eroare de comanda */
				handle_output(errors[6], 0);
			}
			
			/* apelez functia de vizualizare din baza de date */
			else if (sql_cat_view(id) == 0)
			{
				/* scriu eroare de id */
				handle_output(errors[1], 0);
			}
		}

		/* tratez cazul cand nu am drepturi */
		else
		{
			/* scriu eroare de drepturi */
			handle_output(errors[8], 0);
		}
	}


