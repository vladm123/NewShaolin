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

	/* definesc functia care adauga o stire */
	void c_new_add()
	{
		/* declar variabila care retine idul categoriei */
		int catid;

		/* declar variabila care retine rezultate */
		int res;

		/* declar variabila care retine utilizatorul */
		int user;

		/* declar variabila care retine numarul din raspuns */
		char number[11];

		/* declar variabila care retine numele stirii */
		char *name = NULL;

		/* declar variabila care retine textul stirii */
		char *text = NULL;

		/* verific ca utilizatorul sa fie conectat si sa aiba drepturi */
		if (connected >= 1)
		{
			/* testez sa am drepturi */			
			if (!(permitted == 2 || permitted == 3 || permitted == 4))
			{
				/* scriu eroare de drepturi */
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

					/* extrag textul */
					if ((command = strtok(NULL, "|")) == NULL)
					{
						/* scriu eroare de text */
						handle_output(errors[10], 0);
					}

					/* tratez celalalt caz */
					else
					{
						/* calculez lungimea numelui */
						res = handle_alphanumerical(command, 32768);

						/* verific situatiile de eroare */
						if (res < 1 || res > 32768)
						{
							/* scriu eroare de text */
							handle_output(errors[10], 0);
						}

						/* tratez celalalt caz */
						else
						{
							/* construiesc textul */
							handle_string(text, command, 0);
							text = tmp;

							/* extrag cidul */
							if ((command = strtok(NULL, "|")) == NULL)
							{
								/* scriu eroare de cid */
								handle_output(errors[0], 0);
							}

							/* calculez cidul, daca pot */
							else if ((catid = atoi(command)) <= 0)
							{
								/* scriu eroare de cid */
								handle_output(errors[0], 0);
							}

							/* retin rezultatul existentei idului, CU TRATAREA ERORILOR */
							else if (sql_cat_user_exists(catid) <= 0)
							{
								/* scriu eroare de cid */
								handle_output(errors[0], 0);
							}

							/* verific sa nu mai am separatori in plus */
							else if (command = strtok(NULL, "|"))
							{
								/* scriu eroarea de comanda */
								handle_output(errors[6], 0);
							}

							/* adaug stirea, CU TRATAREA ERORILOR */
							else if ((res = sql_new_add(name, text, catid)) == 0)
							{
								/* scriu eroare de id */
								handle_output(errors[1], 0);
							}

							/* tratez celalalt caz */
							else
							{							
								/* construiesc raspunsul */
								handle_output("success|", 0);

								/* creez numarul de raspuns */
								sprintf(number, "%d", res);

								/* construiesc raspunsul */
								handle_output(number, 1);
							}
						}
					}
				}
			}

			/* eliberez variabilele folosite */
			free(name);
			free(text);	
		}

		/* tratez cazul cand nu am drepturi */
		else
		{
			/* scriu eroare de drepturi */
			handle_output(errors[8], 0);
		}
	}

	/* definesc functia care modifica o stire */
	void c_new_modify()
	{
		/* declar variabila care retine idul categoriei */
		int catid;

		/* declar variabila care retine rezultate */
		int res;

		/* declar variabila care retine idul stirii */
		int id;

		/* declar variabila care retine idul userului propunator */
		int user;

		/* declar variabila care retine numele stirii */
		char *name = NULL;

		/* declar variabila care retine textul stirii */
		char *text = NULL;

		/* verific ca utilizatorul sa fie conectat */
		if (connected >= 1)
		{
			/* verific ca utilizatorul sa aiba drepturi */
			if (!(permitted == 2 || permitted == 3 || permitted == 4))
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

			/* tratez celalalt caz */
			else
			{
				/* retin rezultatul existentei idului, CU TRATAREA ERORILOR */
				if ((user = sql_new_user_exists(id)) == 0)
				{
					/* scriu eroare de drepturi */
					handle_output(errors[8], 0);
				}

				/* testez sa aiba drepturi de modificare */
				else if ((permitted == 2 || permitted == 3) && user != connected)
				{
					/* scriu eroare de drepturi */
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

						/* extrag textul */
						if ((command = strtok(NULL, "|")) == NULL)
						{
							/* scriu eroare de nume */
							handle_output(errors[10], 0);
						}

						/* tratez celalalt caz */
						else
						{
							/* calculez lungimea textului */
							res = handle_alphanumerical(command, 32768);

							/* verific situatiile de eroare */
							if (res < 1 || res > 32768)
							{
								/* scriu eroare de nume */
								handle_output(errors[10], 0);
							}

							/* tratez celalalt caz */
							else
							{
								/* construiesc textul */
								handle_string(text, command, 0);
								text = tmp;

								/* extrag cidul */
								if ((command = strtok(NULL, "|")) == NULL)
								{
									/* scriu eroare de categorie */
									handle_output(errors[0], 0);
								}

								/* calculez cidul, daca pot */
								else if ((catid = atoi(command)) <= 0)
								{
									/* scriu eroare de categorie */
									handle_output(errors[0], 0);
								}

								/* retin rezultatul existentei idului, CU TRATAREA ERORILOR */
								else if (sql_cat_user_exists(catid) <= 0)
								{
									/* scriu eroare de categorie */
									handle_output(errors[0], 0);
								}

								/* verific sa nu mai am separatori in plus */
								else if (command = strtok(NULL, "|"))
								{
									/* scriu eroare de comanda */
									handle_output(errors[6], 0);
								}

								/* modific stirea, CU TRATAREA ERORILOR */
								else if (sql_new_modify(id, name, text, catid) == 0)
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
						}
					}
				}
			}

			/* eliberez numele */
			free(name);
			free(text);
		}

		/* tratez cazul cand nu am drepturi */
		else
		{
			/* scriu eroare de drepturi */
			handle_output(errors[8], 0);
		}
	}

	/* definesc functia care sterge o stire */
	void c_new_remove()
	{
		/* declar variabila care retine idul stirii */
		int id;

		/* declar variabila care retine idul userului propunator */
		int user;

		/* declar variabila care retine rezultate */
		int res;

		/* verific ca utilizatorul sa fie conectat si sa aiba drepturi */
		if (connected >= 1)
		{
			if (!(permitted == 2 || permitted == 3 || permitted == 4))
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
			
			/* tratez celalalt caz */
			else
			{
				/* retin rezultatul existentei idului, CU TRATAREA ERORILOR */
				if ((user = sql_new_user_exists(id)) <= 0)
				{
					/* scriu eroare de id */
					handle_output(errors[1], 0);
				}

				/* testez sa aiba drepturi de modificare */
				else if ((permitted == 2 || permitted == 3) && user != connected)
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

				/* sterg stirea, CU TRATAREA ERORILOR */
				else if (sql_new_remove(id) <= 0)
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
		}

		/* tratez cazul cand nu am drepturi */
		else
		{
			/* scriu eroare de drepturi */
			handle_output(errors[8], 0);
		}
	}

	/* definesc functia care vizualizeaza stiri */
	void c_news_view()
	{
		/* declar variabila care retine categoria */
		int catid;

		/* declar variabila care retine recursia */
		int r;

		/* declar variabila care retine limitarea */
		int t;

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

			/* extrag cidul */
			else if ((command = strtok(NULL, "|")) == NULL)
			{
				/* scriu eroare de cid */
				handle_output(errors[0], 0);
			}

			/* extrag categoria */
			else if ((catid = atoi(command)) < 0)
			{
				/* scriu eroare de cid */
				handle_output(errors[0], 0);
			}

			/* extrag recursia */
			else if ((command = strtok(NULL, "|")) == NULL)
			{
				/* scriu eroare de recursie */
				handle_output(errors[5], 0);
			}

			/* extrag recursivitatea */
			else if ((r = atoi(command)) < 0)
			{
				/* scriu eroare de recursie */
				handle_output(errors[5], 0);
			}
	
			/* extrag limita */
			else if ((command = strtok(NULL, "|")) == NULL)
			{
				/* scriu eroare de limita */
				handle_output(errors[9], 0);
			}

			/* extrag recursivitatea */
			else if ((t = atoi(command)) < 0)
			{
				/* scriu eroare de limita */
				handle_output(errors[9], 0);
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
				sql_news_view(catid, r, 0, t);
			}
		}

		/* tratez cazul cand nu era conectat */
		else
		{
			/* scriu eroare de permisiuni */
			handle_output(errors[8], 0);
		}
	}

	/* definesc functia care vizualizeaza o stire */
	void c_new_view()
	{
		/* declar variabila care retine idul de utilizator */
		int id;

		/* declar variabila care retine rezultate */
		int res;

		/* verific ca utilizatorul sa fie conectat */
		if (connected >= 1)
		{
			/* extrag idul */
			if ((command = strtok(NULL, "|")) == NULL)
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

			/* verific sa am drepturi */
			else if (!(permitted == 4 || permitted == 3 || permitted == 2 || permitted == 1)) 
			{
				/* scriu eroare de drepturi */
				handle_output(errors[8], 0);
			}

			/* verific daca mai am separatori in plus */
			else if (command = strtok(NULL, "|"))
			{
				/* scriu eroare de id */
				handle_output(errors[6], 0);
			}

			/* apelez functia de selectare din baza de date */
			else if (sql_new_view(id) == 0)
			{
				/* scriu eroare de id */
				handle_output(errors[1], 0);
			}
		}

		/* tratez cazul cand nu are drepturi */
		else
		{
			/* scriu eroare de drepturi */
			handle_output(errors[8], 0);
		}
	}

