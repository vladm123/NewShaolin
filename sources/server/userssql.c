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

#include "userssql.h"
#include "globals.h"

/* definesc functia de conectare a unui utilizator */
int sql_user_connect(char *username, char *password)
{
	/* declar si initializez (0) numarul de utilizatori rezultati */
	int ans;
	
	/* declar variabila care retine interogarea */
	char *query = NULL;

	/* declar variabila care retine conexiunea la serverul MySQL */
	MYSQL *conn = NULL;

	/* declar variabila care retine rezultatul interogarii */
	MYSQL_RES *result = NULL;

	/* declar variabila care retine randul interogarii */
	MYSQL_ROW row;	

	/* aloc memorie pentru query */
	if ((query = (char *)realloc(query, sizeof(char) * (128 + inlength))) == NULL)
		handle_error("userssql::sql_user_connect::realloc(query, 128 + inlength)");

	/* initializez conexiunea la baza de date, CU TRATAREA ERORILOR */
	if ((conn = mysql_init(NULL)) == NULL)
		handle_error("userssql::sql_user_connect::mysql_init(conn)");

	/* conectez la baza de date, CU TRATAREA ERORILOR */
	if (mysql_real_connect(conn, "localhost", "root", "root", "rcnews", 0, NULL, 0) == NULL)
		handle_error("userssql::sql_user_connect::mysql_real_connect(conn, rcnews)");

	/* creez sirul de caractere pentru query SELECT */
	sprintf(query, "SELECT id, permission FROM users WHERE username = '%s' and password = '%s';", username, password);

	/* gasesc utilizatorul, CU TRATAREA ERORILOR */
	if (mysql_query(conn, query))
		handle_error("userssql::sql_user_connect::mysql_query(conn, select)");

	if ((result = mysql_store_result(conn)) == NULL)
		handle_error("userssql::sql_user_connect::mysql_store_result(conn, select)");	

	/* verific valoarea raspunsului */
	if (row = mysql_fetch_row(result))
	{
		/* retin idul */
		connected = atoi(row[0]);

		/* retin permisiunea */
		permitted = atoi(row[1]); 

		/* construiesc raspunsul */
		handle_output("success|", 0);

		/* scriu identificatorul in raspuns */
		handle_output(row[0], 1);
		
		/* scriu o bara in raspuns */
		handle_output("|", 1);

		/* scriu numele in raspuns */
		handle_output(row[1], 1);

		/* consider valid raspunsul */
		ans = 1;
	}

	/* tratez cazul cand nu s-a putut face conectarea */
	else
	{
		/* consider invalid raspunsul */
		ans = 0;
	}

	/* eliberez rezultatul */
	mysql_free_result(result);

	/* inchid conexiunea la baza de date */
	mysql_close(conn);

	/* intorc starea */
	return ans;
}

/* definesc functia de adaugare a unui utilizator, care intoarce identificatorul utilizatorului adaugat */
int sql_user_add(char *username, char *password)
{
	/* declar variabila care retine rezultatul */
	int ans;

	/* declar variabila care retine interogarea */
	char *query = NULL;

	/* declar variabila care retine conexiunea la serverul MySQL */
	MYSQL *conn = NULL;

	/* declar variabila care retine rezultatul interogarii */
	MYSQL_RES *result = NULL;

	/* declar variabila care retine randul interogarii */
	MYSQL_ROW row;

	/* aloc memorie pentru query */
	if ((query = (char *)realloc(query, sizeof(char) * (128 + inlength))) == NULL)
		handle_error("userssql::sql_user_add::realloc(query, 128 + inlength)");

	/* initializez conexiunea la baza de date, CU TRATAREA ERORILOR */
	if ((conn = mysql_init(NULL)) == NULL)
		handle_error("userssql::sql_user_add::mysql_init(conn)");

	/* conectez la baza de date, CU TRATAREA ERORILOR */
	if (mysql_real_connect(conn, "localhost", "root", "root", "rcnews", 0, NULL, 0) == NULL)
		handle_error("userssql::sql_user_add::mysql_real_connect(conn, rcnews)");

	/* creez sirul de caractere pentru query SELECT */
	sprintf(query, "SELECT id FROM users WHERE username = '%s';", username);

	/* aflu utilizatorul, CU TRATAREA ERORILOR */
	if (mysql_query(conn, query))
		handle_error("userssql::sql_user_add::mysql_query(conn, select)");

	/* citesc rezultatul interogarii */
	if (!(result = mysql_store_result(conn)))
		handle_error("userssql::sql_user_add::mysql_store_result(conn, select)");

	/* verific valoarea raspunsului */
	if (row = mysql_fetch_row(result))
	{
		/* consider suprascriere, deci eroare */
		ans = 0;
	}

	/* tratez cazul celalalt */
	else
	{
		/* creez sirul de caractere pentru query INSERT */
		sprintf(query, "INSERT INTO users VALUES ('', '%s', '%s', 1, CONCAT(CURRENT_DATE(), ' ', CURRENT_TIME()));", username, password);

		/* adaug utilizatorul, CU TRATAREA ERORILOR */
		if (mysql_query(conn, query))
			handle_error("userssql::sql_user_add::mysql_query(conn, insert)");

		/* creez sirul de caractere pentru query SELECT */
		sprintf(query, "SELECT id FROM users WHERE username = '%s';", username);

		/* aflu utilizatorul, CU TRATAREA ERORILOR */
		if (mysql_query(conn, query))
			handle_error("userssql::sql_user_add::mysql_query(conn, select)");

		/* citesc rezultatul interogarii */
		if (!(result = mysql_store_result(conn)))
			handle_error("userssql::sql_user_add::mysql_store_result(conn, select)");

		/* verific valoarea raspunsului */
		if (row = mysql_fetch_row(result))
		{
			/* retin primul camp */
			ans = atoi(row[0]);
		}

		/* tratez celalalt caz */
		else
		{
			/* consider utilizator fictiv, dar e posibil sa fi fost sters! */
			ans = 0;
		}
	}

	/* eliberez rezultatul */
	mysql_free_result(result);

	/* inchid conexiunea la baza de date */
	mysql_close(conn);

	/* intorc raspunsul */
	return ans;	
}

/* definesc functia de modificare a unui utilizator, care intoarce identificatorul utilizatorului modificat */
int sql_user_modify(int id, char *password, int permissions)
{
	/* declar variabila care retine rezultatul */
	int ans;

	/* declar variabila care retine interogarea */
	char *query = NULL;

	/* declar variabila care retine conexiunea la serverul MySQL */
	MYSQL *conn = NULL;

	/* declar variabila care retine rezultatul interogarii */
	MYSQL_RES *result = NULL;

	/* declar variabila care retine randul interogarii */
	MYSQL_ROW row;

	/* aloc memorie pentru query */
	if ((query = (char *)realloc(query, sizeof(char) * (128 + inlength))) == NULL)
		handle_error("userssql::sql_user_modify::realloc(query, 128 + inlength)");

	/* initializez conexiunea la baza de date, CU TRATAREA ERORILOR */
	if ((conn = mysql_init(NULL)) == NULL)
		handle_error("userssql::sql_user_modify::mysql_init(conn)");

	/* conectez la baza de date, CU TRATAREA ERORILOR */
	if (mysql_real_connect(conn, "localhost", "root", "root", "rcnews", 0, NULL, 0) == NULL)
		handle_error("userssql::sql_user_modify::mysql_real_connect(conn, rcnews)");

	/* creez sirul de caractere pentru query INSERT */
	if (permissions >= 0)
		sprintf(query, "UPDATE users SET password='%s', permission='%d' WHERE id='%d';", password, permissions, id);
	else
		sprintf(query, "UPDATE users SET password='%s' WHERE id='%d';", password, id);

	/* adaug utilizatorul, CU TRATAREA ERORILOR */
	if (mysql_query(conn, query))
		handle_error("userssql::sql_user_modify::mysql_query(conn, insert)");

	/* creez sirul de caractere pentru query SELECT */
	sprintf(query, "SELECT id FROM users WHERE id = '%d';", id);

	/* aflu utilizatorul, CU TRATAREA ERORILOR */
	if (mysql_query(conn, query))
		handle_error("userssql::sql_user_modify::mysql_query(conn, select)");

	/* citesc rezultatul interogarii */
	if (!(result = mysql_store_result(conn)))
		handle_error("userssql::sql_user_modify::mysql_store_result(conn, select)");

	/* verific valoarea raspunsului */
	if (row = mysql_fetch_row(result))
	{
		/* retin primul camp */
		ans = atoi(row[0]);
	}
	else
	{
		/* consider utilizator fictiv, dar e posibil sa fi fost sters! */
		ans = 0;
	}

	/* eliberez rezultatul */
	mysql_free_result(result);

	/* inchid conexiunea la baza de date */
	mysql_close(conn);

	/* intorc raspunsul */
	return ans;	
}

/* definesc functia de vizualizarea a utilizatorilor */
void sql_users_view()
{
	/* declar variabila care retine interogarea */
	char *query = NULL;

	/* declar variabila care retine conexiunea la serverul MySQL */
	MYSQL *conn = NULL;

	/* declar variabila care retine rezultatul interogarii */
	MYSQL_RES *result = NULL;

	/* declar variabila care retine randul interogarii */
	MYSQL_ROW row;	

	/* aloc memorie pentru query */
	if ((query = (char *)realloc(query, sizeof(char) * (128 + inlength))) == NULL)
		handle_error("userssql::sql_users_view::realloc(query, 128 + inlength)");

	/* initializez conexiunea la baza de date, CU TRATAREA ERORILOR */
	if ((conn = mysql_init(NULL)) == NULL)
		handle_error("userssql::sql_users_view::mysql_init(conn)");

	/* conectez la baza de date, CU TRATAREA ERORILOR */
	if (mysql_real_connect(conn, "localhost", "root", "root", "rcnews", 0, NULL, 0) == NULL)
		handle_error("userssql::sql_users_view::mysql_real_connect(conn, rcnews)");

	/* creez sirul de caractere pentru query SELECT */
	strcpy(query, "SELECT id, username, permission, moment FROM users ORDER BY username ASC;");

	/* gasesc utilizatorul, CU TRATAREA ERORILOR */
	if (mysql_query(conn, query))
		handle_error("userssql::sql_users_view::mysql_query(conn, select)");

	if ((result = mysql_store_result(conn)) == NULL)
		handle_error("userssql::sql_users_view::mysql_store_result(conn, select)");	

	/* construiesc raspunsul */
	handle_output("success", 0);

	/* parcurg intrarile selectate din baza de date */
	while (row = mysql_fetch_row(result))
	{
		/* adaug o bara incremental la raspuns*/
		handle_output("|", 1);

		/* adaug identificatorul utilizatorului curent */
		handle_output(row[0], 1);

		/* adaug o bara incremental la raspuns*/
		handle_output("|", 1);

		/* adaug numele utilizatorului curent */
		handle_output(row[1], 1);

		/* adaug o bara incremental la raspuns*/
		handle_output("|", 1);

		/* adaug momentul utilizatorului curent */
		handle_output(row[2], 1);
     
		/* adaug o bara incremental la raspuns*/
		handle_output("|", 1);

		/* adaug drepturile utilizatorului curent */
		handle_output(row[3], 1);
	}

	/* eliberez rezultatul */
	mysql_free_result(result);

	/* inchid conexiunea la baza de date */
	mysql_close(conn);
}

/* definesc functia de vizualizarea a utilizatorilor */
int sql_user_view(int id)
{
	/* declar si initializez (0) numarul de utilizatori rezultati */
	int ans;
	
	/* declar variabila care retine interogarea */
	char *query = NULL;

	/* declar variabila care retine conexiunea la serverul MySQL */
	MYSQL *conn = NULL;

	/* declar variabila care retine rezultatul interogarii */
	MYSQL_RES *result = NULL;

	/* declar variabila care retine randul interogarii */
	MYSQL_ROW row;	

	/* aloc memorie pentru query */
	if ((tmp = (char *)realloc(query, sizeof(char) * (128 + inlength))) == NULL)
		handle_error("userssql::sql_user_view::realloc(query, 128 + inlength)");
	else
		query = tmp;

	/* initializez conexiunea la baza de date, CU TRATAREA ERORILOR */
	if ((conn = mysql_init(NULL)) == NULL)
		handle_error("userssql::sql_user_view::mysql_init(conn)");

	/* conectez la baza de date, CU TRATAREA ERORILOR */
	if (mysql_real_connect(conn, "localhost", "root", "root", "rcnews", 0, NULL, 0) == NULL)
		handle_error("userssql::sql_user_view::mysql_real_connect(conn, rcnews)");

	/* creez sirul de caractere pentru query SELECT */
	sprintf(query, "SELECT id, username, permission, moment FROM users WHERE id ='%d';", id);

	/* gasesc utilizatorul, CU TRATAREA ERORILOR */
	if (mysql_query(conn, query))
		handle_error("userssql::sql_user_view::mysql_query(conn, select)");

	if ((result = mysql_store_result(conn)) == NULL)
		handle_error("userssql::sql_user_view::mysql_store_result(conn, select)");	

	/* parcurg intrarile selectate din baza de date */
	if (row = mysql_fetch_row(result))
	{
		/* construiesc sirul de raspuns */
		handle_output("success|", 0);

		/* scriu in output identificatorul utilizatorului curent */
		handle_output(row[0], 1);

		/* adaug o bara incremental la raspuns*/
		handle_output("|", 1);

		/* adaug numele utilizatorului curent */
		handle_output(row[1], 1);

		/* adaug o bara incremental la raspuns*/
		handle_output("|", 1);

		/* adaug momentul utilizatorului curent */
		handle_output(row[2], 1);

		/* adaug o bara incremental la raspuns*/
		handle_output("|", 1);

		/* adaug permisiunile utilizatorului curent */
		handle_output(row[3], 1);

		/* consider raspuns valid */
		ans = 1;
	}
	
	/* tratez cazul cand nu am utilizator */
	else
	{
		/* consider raspuns invalid */
		ans = 0;
	}

	/* eliberez rezultatul */
	mysql_free_result(result);

	/* inchid conexiunea la baza de date */
	mysql_close(conn);

	/* intorc starea */
	return ans;
}

