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

	/* definesc functia care conecteaza un utilizator */
	void c_user_connect()
	{
		/* declar si initializez (0) variabila care retine numele de utilizator */
		char *username = NULL;

		/* declar si initializez (0) variabila care retine parola */
		char *password = NULL;

		/* declar variabila care retine rezultate */
		int res;

		/* verific ca utilizatorul sa nu fie conectat */
		if (connected == -1)
		{
			/* extrag numele de utilizator */
			if ((command = strtok(NULL, "|")) == NULL)
			{
				/* scriu eroare de nume */
				handle_output(errors[11], 0);
			}

			/* tratez celalalt caz */
			else
			{
				/* calculez lungimea numelui */
				res = handle_alphanumerical(command, 32);

				/* verific situatiile de eroare */
				if (res < 1 || res > 32)
				{
					/* scriu eroare de nume */
					handle_output(errors[11], 0);
				}

				/* tratez celalalt caz */
				else
				{
					/* construiesc numele de utilizator */
					handle_string(username, command, 0);
					username = tmp;

					/* extrag parola */
					if ((command = strtok(NULL, "|")) == NULL)
					{
						/* scriu eroare de nume */
						handle_output(errors[3], 0);
					}

					/* tratez celalalt caz */
					else
					{
						/* calculez lungimea parolei */
						res = handle_alphanumerical(command, 256);

						/* verific situatiile de eroare */
						if (res < 1 || res > 256)
						{
							/* scriu eroare de nume */
							handle_output(errors[3], 0);
						}
		
						/* tratez celalalt caz */
						else
						{
							/* construiesc parola */
							handle_string(password, command, 0);
							password = tmp;
			
							/* verific sa nu mai am separatori in plus */
							if (command = strtok(NULL, "|"))
							{
								/* scriu eroare de comanda */
								handle_output(errors[6], 0);
							}

							/* verific conectarea in sql */
							else if (sql_user_connect(username, password) == 0)
							{
								/* scriu eroare de nume */
								handle_output(errors[11], 0);
							}
						}
					}
				}
			}

			/* eliberez variabilele folosite */
			free(username);
			free(password);	
		}

		/* tratez cazul cand nu am drepturi suficiente */
		else
		{
			/* scriu eroare de drepturi */
			handle_output(errors[8], 0);
		}
	}

	/* definesc functia care deconecteaza un utilizator */
	void c_user_disconnect()
	{
		/* verific ca utilizatorul sa fie conectat */
		if (connected >= 1)
		{
			/* verific daca mai am separatori in plus */
			if (command = strtok(NULL, "|"))
			{
				/* scriu eroare de comanda */
				handle_output(errors[6], 0);
			}
	
			/* tratez ultimul caz */
			else
			{
				/* il deconectez */
				connected = -1;

				/* ii scot drepturile */
				permitted = -1;

				/* scriu succes */
				handle_output("success", 0);
			}
		}

		/* verific cazul cand utilizatorul nu e conectat */
		else
		{
			/* scriu eroare de drepturi */
			handle_output(errors[8], 0);
		}
	}

	/* definesc functia care adauga un utilizator */
	void c_user_add()
	{
		/* declar si initializez (0) variabila care retine numele de utilizator */
		char *username = NULL;

		/* declar si initializez (0) variabila care retine parola */
		char *password = NULL;

		/* declar variabila care retine un numar */
		char number[11];

		/* declar variabila care retine rezultate */
		int res;

		/* verific ca utilizatorul sa nu fie conectat */
		if (connected == -1)
		{
			/* extrag numele de utilizator */
			if ((command = strtok(NULL, "|")) == NULL)
			{
				/* scriu eroare de nume de utilizator */
				handle_output(errors[11], 0);
			}

			/* tratez celalalt caz */
			else
			{
				/* calculez lungimea numelui */
				res = handle_alphanumerical(command, 32);

				/* verific situatiile de eroare */
				if (res < 1 || res > 32)
				{
					/* scriu eroare de nume de utilzator */
					handle_output(errors[11], 0);
				}

				/* tratez celalalt caz */
				else
				{
					/* construiesc numele de utilizator */
					handle_string(username, command, 0);
					username = tmp;

					/* extrag parola */
					if ((command = strtok(NULL, "|")) == NULL)
					{
						/* scriu eroare de parola */
						handle_output(errors[3], 0);
					}

					/* tratez celalalt caz */
					else
					{
						/* calculez lungimea parolei */
						res = handle_alphanumerical(command, 256);

						/* verific situatiile de eroare */
						if (res < 1 || res > 256)
						{
							/* scriu eroare de parola */
							handle_output(errors[3], 0);
						}

						/* tratez celalalt caz */
						else
						{
							/* construiesc parola */
							handle_string(password, command, 0);
							password = tmp;

							/* verific sa nu mai am separatori in plus */
							if (command = strtok(NULL, "|"))
							{
								/* scriu eroare de comanda */
								handle_output(errors[6], 0);

							}

							/* initializez variabila care retine identificatorul */
							else if ((res = sql_user_add(username, password)) <= 0)
							{
								/* scriu eroare de username */
								handle_output(errors[11], 0);
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
			}

			/* eliberez variabilele folosite */
			free(username);
			free(password);	
		}

		/* tratez cazul cand nu am drepturi suficiente */
		else
		{
			/* scriu eroare de drepturi */
			handle_output(errors[8], 0);
		}
	}


	/* definesc functia care modifica un utilizator */
	void c_user_modify()
	{
		/* declar variabila care retine parola */
		char *password = NULL;

		/* declar variabila care retine identificatorul de utilizator */
		int id;

		/* declar variabila care retine permisiunile (optional) */
		int permissions;

		/* declar variabila care retine rezultate */
		int res;

		/* verific ca utilizatorul sa fie conectat */
		if (connected >= 1)
		{
			/* extrag identificatorul */
			if ((command = strtok(NULL, "|")) == NULL)
			{
				/* scriu eroare de id */
				handle_output(errors[1], 0);
			}

			/* calculez identificatorul */
			else if ((id = atoi(command)) <= 0)
			{
				/* scriu eroare de id */
				handle_output(errors[1], 0);
			}

			/* extrag parola */
			else if ((command = strtok(NULL, "|")) == NULL)
			{
				/* scriu eroare de id */
				handle_output(errors[3], 0);
			}

			/* tratez celalalt caz */
			else
			{
				/* calculez lungimea parolei */
				res = handle_alphanumerical(command, 256);

				/* verific situatiile de eroare */
				if (res < 1 || res > 256)
				{
					/* scriu eroare de id */
					handle_output(errors[3], 0);
				}
	
				/* tratez celalalt caz */
				else
				{
					/* creez parola */
					handle_string(password, command, 0);
					password = tmp;

					/* verific daca mai am separatori in plus */
					if (command = strtok(NULL, "|"))
					{
						/* verific sa am drepturi */
						if (!(permitted == 4 && connected != id))
						{
							/* scriu eroare de drepturi */
							handle_output(errors[8], 0);
						} 

						/* calculez permisiunile de pus in loc */
						else if ((permissions = atoi(command)) < 0)
						{
							/* scriu eroare de permisiuni */
							handle_output(errors[4], 0);
						}

						/* verific sa nu mai am separatori in plus */
						else if (command = strtok(NULL, "|"))
						{
							/* scriu eroare de comanda */
							handle_output(errors[6], 0);
						}
			
						/* modific utilizatorul, CU TRATAREA ERORILOR */
						else if ((res = sql_user_modify(id, password, permissions)) <= 0)
						{
							/* scriu eroare de id */
							handle_output(errors[1], 0);
						}

						/* tratez celalalt caz */
						else
						{
							/* scriu succes */
							handle_output("success", 0);
						}	
					}
			
					/* comanda trebuie sa fi fost facuta de utilizatorul conectat */
					else
					{
						/* verific sa am drepturi */
						if (connected != id && permitted != 4)
						{
							/* scriu eroare de drepturi */
							handle_output(errors[8], 0);
						} 

						/* modific utilizatorul, CU TRATAREA ERORILOR */
						else if ((res = sql_user_modify(id, password, -1)) <= 0)
						{
							/* scriu eroare de id */
							handle_output(errors[1], 0);
						}

						/* tratez celalalt caz */
						else
						{
							/* scriu succes */
							handle_output("success", 0);
						}	
					}
				}
			}

			/* eliberez variabilele folosite */
			free(password);	
		}

		/* verific cazul cand utilizatorul nu e conectat */
		else
		{
			/* scriu eroare de drepturi */
			handle_output(errors[8], 0);
		}
	}

	/* definesc functia care vizualizeaza utilizatorii */
	void c_users_view()
	{
		/* declar variabila care retine rezultate */
		int res;

		/* verific ca utilizatorul sa fie conectat */
		if (connected >= 1)
		{
			/* verific sa am drepturi */
			if (permitted != 4) 
			{
				/* scriu eroare de drepturi */
				handle_output(errors[8], 0);
			}

			/* verific daca mai am separatori in plus */
			else if (command = strtok(NULL, "|"))
			{
				/* scriu eroare de comanda */
				handle_output(errors[6], 0);
			}

			/* tratez ultimul caz */
			else
			{
				/* apelez functia de vizualizare utilizatori */
				sql_users_view();
			}		
		}

		/* tratez cazul cand nu e conectat */
		else
		{
			/* scriu eroarea de drepturi */
			handle_output(errors[8], 0);
		}
	}

	/* definesc functia care vizualizeaza un utilizator */
	void c_user_view()
	{
		/* declar variabila care retine identificatorul de utilizator */
		int id = 0;

		/* declar variabila care retine rezultate */
		int res;

		/* verific ca utilizatorul sa fie conectat */
		if (connected >= 1)
		{
			/* extrag identificatorul */
			if ((command = strtok(NULL, "|")) == NULL)
			{
				/* scriu eroare de id */
				handle_output(errors[1], 0);
			}

			/* calculez identificatorul */
			else if ((id = atoi(command)) <= 0)
			{
				/* scriu eroare de id */
				handle_output(errors[1], 0);
			}

			/* verific sa am drepturi */
			else if (!(permitted == 4 || (permitted == 0 || permitted == 1 || permitted == 2 || permitted == 3) && connected == id)) 
			{
				/* scriu eroare de drepturi */
				handle_output(errors[8], 0);
			}

			/* verific daca mai am separatori in plus */
			else if (command = strtok(NULL, "|"))
			{
				/* scriu eroare de comanda */
				handle_output(errors[6], 0);
			}

			/* apelez functia de selectare din baza de date */
			else if (sql_user_view(id) == 0)
			{
				/* scriu eroare de id */
				handle_output(errors[1], 0);
			}
		}

		/* tratez cazul cand nu e conectat */
		else
		{
			/* scriu eroarea de drepturi */
			handle_output(errors[8], 0);
		}
	}

