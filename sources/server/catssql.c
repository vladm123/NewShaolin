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

#include "catssql.h"
#include "globals.h"

/* definesc functia de adaugare a unei categorii, care intoarce identificatorul categoriei adaugate */
int sql_cat_add(char *name, int catpid)
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
		handle_error("catssql::sql_cat_add::realloc(query, 128 + inlength)");

	/* initializez conexiunea la baza de date, CU TRATAREA ERORILOR */
	if ((conn = mysql_init(NULL)) == NULL)
		handle_error("catssql::sql_cat_add::mysql_init(conn)");

	/* conectez la baza de date, CU TRATAREA ERORILOR */
	if (mysql_real_connect(conn, "localhost", "root", "root", "rcnews", 0, NULL, 0) == NULL)
		handle_error("catssql::sql_cat_add::mysql_real_connect(conn, rcnews)");

	/* creez sirul de caractere pentru query INSERT */
	if (catpid == 0 || sql_cat_user_exists(catpid) <= 0)
		sprintf(query, "INSERT INTO categories VALUES ('', '%s', CONCAT(CURRENT_DATE(), ' ', CURRENT_TIME()), NULL, '%d');", name, connected);
	else
		sprintf(query, "INSERT INTO categories VALUES ('', '%s', CONCAT(CURRENT_DATE(), ' ', CURRENT_TIME()), '%d', '%d');", name, catpid, connected);

	/* adaug categoria, CU TRATAREA ERORILOR */
	if (mysql_query(conn, query))
		handle_error("catssql::sql_cat_add::mysql_query(conn, insert)");

	/* creez sirul de caractere pentru query SELECT */
	if (catpid == 0 || sql_cat_user_exists(catpid) <= 0)
		sprintf(query, "SELECT id FROM categories WHERE name = '%s' and parent_id IS NULL and user_id='%d';", name, connected);
	else
		sprintf(query, "SELECT id FROM categories WHERE name = '%s' and parent_id='%d' and user_id='%d';", name, catpid, connected);

	/* aflu categoria, CU TRATAREA ERORILOR */
	if (mysql_query(conn, query))
		handle_error("catssql::sql_cat_add::mysql_query(conn, select)");

	/* citesc rezultatul interogarii */
	if (!(result = mysql_store_result(conn)))
		handle_error("catssql::sql_cat_add::mysql_store_result(conn, select)");

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

/* definesc functia de modificare a unei categorii, care intoarce idul categoriei modificate */
int sql_cat_modify(int id, char *name, int catpid)
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
		handle_error("catssql::sql_cat_modify::realloc(query, 128 + inlength)");

	/* initializez conexiunea la baza de date, CU TRATAREA ERORILOR */
	if ((conn = mysql_init(NULL)) == NULL)
		handle_error("catssql::sql_cat_modify::mysql_init(conn)");

	/* conectez la baza de date, CU TRATAREA ERORILOR */
	if (mysql_real_connect(conn, "localhost", "root", "root", "rcnews", 0, NULL, 0) == NULL)
		handle_error("catssql::sql_cat_modify::mysql_real_connect(conn, rcnews)");

	/* retin rezultatul existentei idului, CU TRATAREA ERORILOR */
	if (catpid == 0)
		sprintf(query, "UPDATE categories SET name='%s', moment=CONCAT(CURRENT_DATE(), ' ', CURRENT_TIME()), parent_id=NULL WHERE id='%d';", name, id);
	else if (sql_cat_user_exists(catpid) <= 0)
		sprintf(query, "UPDATE categories SET name='%s', moment=CONCAT(CURRENT_DATE(), ' ', CURRENT_TIME()) WHERE id='%d';", name, id);
	else
		sprintf(query, "UPDATE categories SET name='%s', moment=CONCAT(CURRENT_DATE(), ' ', CURRENT_TIME()), parent_id='%d' WHERE id='%d';", name, catpid, id);

	/* adaug categoria, CU TRATAREA ERORILOR */
	if (mysql_query(conn, query))
		handle_error("catssql::sql_cat_modify::mysql_query(conn, insert)");

	/* creez sirul de caractere pentru query SELECT */
	sprintf(query, "SELECT id FROM categories WHERE id = '%d';", id);

	/* aflu categoria, CU TRATAREA ERORILOR */
	if (mysql_query(conn, query))
		ans = 0;
	else
		ans = id;

	/* eliberez rezultatul */
	mysql_free_result(result);

	/* inchid conexiunea la baza de date */
	mysql_close(conn);

	/* intorc raspunsul */
	return ans;	
}

/* definesc functia de stergere a unei categorii */
int sql_cat_remove(int id)
{
	/* declar variabila care retine rezultatul */
	int ans;

	/* declar variabila care retine interogarea */
	char *query = NULL;

	/* declar variabila care retine conexiunea la serverul MySQL */
	MYSQL *conn = NULL;

	/* aloc memorie pentru query */
	if ((query = (char *)realloc(query, sizeof(char) * (128 + inlength))) == NULL)
		handle_error("catssql::sql_cat_remove::realloc(query, 128 + inlength)");

	/* initializez conexiunea la baza de date, CU TRATAREA ERORILOR */
	if ((conn = mysql_init(NULL)) == NULL)
		handle_error("catssql::sql_cat_remove::mysql_init(conn)");

	/* conectez la baza de date, CU TRATAREA ERORILOR */
	if (mysql_real_connect(conn, "localhost", "root", "root", "rcnews", 0, NULL, 0) == NULL)
		handle_error("catssql::sql_cat_remove::mysql_real_connect(conn, rcnews)");

	/* construiesc cererea sql */
	sprintf(query, "DELETE FROM categories WHERE id = '%d';", id);

	/* adaug categoria, CU TRATAREA ERORILOR */
	if (mysql_query(conn, query))
		handle_error("catssql::sql_cat_remove::mysql_query(conn, insert)");

	/* inchid conexiunea la baza de date */
	mysql_close(conn);	

	/* am sters cu succes categoria */
	return 1;
}

/* definesc  functia care vizualizeaza categoriile */
void sql_cats_view(char *id, int lev)
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
		handle_error("catssql::sql_cats_view::realloc(query, 128 + inlength)");

	/* initializez conexiunea la baza de date, CU TRATAREA ERORILOR */
	if ((conn = mysql_init(NULL)) == NULL)
		handle_error("catssql::sql_cats_view::mysql_init(conn)");

	/* conectez la baza de date, CU TRATAREA ERORILOR */
	if (mysql_real_connect(conn, "localhost", "root", "root", "rcnews", 0, NULL, 0) == NULL)
		handle_error("catssql::sql_cats_view::mysql_real_connect(conn, rcnews)");

	/* creez sirul de caractere pentru query SELECT */
	if (id == NULL)
		sprintf(query, "SELECT id, name, moment, user_id FROM categories WHERE parent_id IS NULL ORDER BY name ASC;");
	else
		sprintf(query, "SELECT id, name, moment, user_id FROM categories WHERE parent_id = '%s' ORDER BY name ASC;", id);

	/* gasesc categoria, CU TRATAREA ERORILOR */
	if (mysql_query(conn, query))
		handle_error("catssql::sql_cats_view::mysql_query(conn, select)");

	if ((result = mysql_store_result(conn)) == NULL)
		handle_error("catssql::sql_cats_view::mysql_store_result(conn, select)");	

	/* verific valoarea raspunsului */
	while (row = mysql_fetch_row(result))
	{
		/* reinitializez query-ul */
		memset(query, 0, 11 * sizeof(char));

		/* scriu numarul de nivel */
		sprintf(query, "%d", lev);

		/* scriu bara in raspuns */
		handle_output("|", 1);

		/* scriu nivelul in raspuns */
		handle_output(query, 1);

		/* scriu bara in raspuns */
		handle_output("|", 1);

		/* scriu identificatorul in raspuns */
		handle_output(row[0], 1);

		/* scriu bara in raspuns */
		handle_output("|", 1);

		/* scriu numele in raspuns */
		handle_output(row[1], 1);

		/* scriu bara in raspuns */
		handle_output("|", 1);

		/* scriu momentul in raspuns */
		handle_output(row[2], 1);

		/* scriu bara in raspuns */
		handle_output("|", 1);

		/* scriu identificatorul propunatorului in raspuns */
		handle_output(row[3], 1);

		/* apelez functia recursiva care adauga la output lista parintilor categoriei de vizualizat */
		sql_cats_view(row[0], lev + 1);
	}

	/* eliberez rezultatul */
	mysql_free_result(result);

	/* inchid conexiunea la baza de date */
	mysql_close(conn);	
}

/* definesc functia care vizualizeaza o categorie */
int sql_cat_view(int id)
{
	/* declar variabila care retine succesul interogarii */
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
		handle_error("catssql::sql_cat_view::realloc(query, 128 + inlength)");

	/* initializez conexiunea la baza de date, CU TRATAREA ERORILOR */
	if ((conn = mysql_init(NULL)) == NULL)
		handle_error("catssql::sql_cat_view::mysql_init(conn)");

	/* conectez la baza de date, CU TRATAREA ERORILOR */
	if (mysql_real_connect(conn, "localhost", "root", "root", "rcnews", 0, NULL, 0) == NULL)
		handle_error("catssql::sql_cat_view::mysql_real_connect(conn, rcnews)");

	/* creez sirul de caractere pentru query SELECT */
	sprintf(query, "SELECT id, name, moment, parent_id, user_id FROM categories WHERE id = '%d';", id);

	/* gasesc categoria, CU TRATAREA ERORILOR */
	if (mysql_query(conn, query))
		handle_error("catssql::sql_cat_view::mysql_query(conn, select)");

	if ((result = mysql_store_result(conn)) == NULL)
		handle_error("catssql::sql_cat_view::mysql_store_result(conn, select)");	

	/* verific valoarea raspunsului */
	if (row = mysql_fetch_row(result))
	{
		/* construiesc raspunsul */
		handle_output("success|", 0);

		/* scriu identificatorul categoriei */
		handle_output(row[0], 1);

		/* scriu bara in raspuns */
		handle_output("|", 1);

		/* scriu numele categoriei */
		handle_output(row[1], 1);

		/* scriu bara in raspuns */
		handle_output("|", 1);

		/* scriu momentul categoriei */
		handle_output(row[2], 1);

		/* scriu bara in raspuns */
		handle_output("|", 1);

		/* scriu identificatorul propunatorului categoriei */
		handle_output(row[4], 1);

		/* apelez functia recursiva care adauga la output lista parintilor categoriei de vizualizat */
		sql_cat_view_parents(row[3]);

		/* consider succes */
		ans = 1;
	}
	else
	{
		/* consider esec */
		ans = 0;
	}

	/* eliberez rezultatul */
	mysql_free_result(result);

	/* inchid conexiunea la baza de date */
	mysql_close(conn);
	
	/* intorc rezultatul */
	return ans;
}

/* definesc functia recursiva care vizualizeaza parintii categoriei curente */
void sql_cat_view_parents(char *id)
{
	/* declar variabila care retine interogarea */
	char *query = NULL;
	
	/* declar variabila care retine conexiunea la serverul MySQL */
	MYSQL *conn = NULL;

	/* declar variabila care retine rezultatul interogarii */
	MYSQL_RES *result = NULL;

	/* declar variabila care retine randul interogarii */
	MYSQL_ROW row;

	/* verific conditia de oprire din recursivitate */
	if (id == NULL)
	{
		/* intorc */
		return;
	}

	/* aloc memorie pentru query */
	if ((query = (char *)realloc(query, sizeof(char) * (128 + inlength))) == NULL)
		handle_error("catssql::sql_cat_view_parents::realloc(query, 128 + inlength)");

	/* initializez conexiunea la baza de date, CU TRATAREA ERORILOR */
	if ((conn = mysql_init(NULL)) == NULL)
		handle_error("catssql::sql_cat_view_parents::mysql_init(conn)");

	/* conectez la baza de date, CU TRATAREA ERORILOR */
	if (mysql_real_connect(conn, "localhost", "root", "root", "rcnews", 0, NULL, 0) == NULL)
		handle_error("catssql::sql_cat_view_parents::mysql_real_connect(conn, rcnews)");

	/* creez sirul de caractere pentru query SELECT */
	sprintf(query, "SELECT id, name, parent_id FROM categories WHERE id = '%s';", id);

	/* gasesc categoria, CU TRATAREA ERORILOR */
	if (mysql_query(conn, query))
		handle_error("catssql::sql_cat_view_parents::mysql_query(conn, select)");

	if ((result = mysql_store_result(conn)) == NULL)
		handle_error("catssql::sql_cat_view_parents::mysql_store_result(conn, select)");	

	/* verific valoarea raspunsului */
	if (row = mysql_fetch_row(result))
	{
		/* construiesc raspunsul */
		handle_output("|", 1);

		/* scriu in output identificatorul categoriei curente */
		handle_output(row[0], 1);

		/* construiesc raspunsul */
		handle_output("|", 1);

		/* scriu in output numele categoriei curente */
		handle_output(row[1], 1);

		/* apelez functia recursiva care adauga la output lista parintilor categoriei de vizualizat */
		sql_cat_view_parents(row[2]);
	}

	/* eliberez rezultatul */
	mysql_free_result(result);

	/* inchid conexiunea la baza de date */
	mysql_close(conn);
}

/* definesc functia de test a existentei unei categorii dupa id */
int sql_cat_user_exists(int id)
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
		handle_error("catssql::sql_cat_user_exists::realloc(query, 128 + inlength)");

	/* initializez conexiunea la baza de date, CU TRATAREA ERORILOR */
	if ((conn = mysql_init(NULL)) == NULL)
		handle_error("catssql::sql_cat_user_exists::mysql_init(conn)");

	/* conectez la baza de date, CU TRATAREA ERORILOR */
	if (mysql_real_connect(conn, "localhost", "root", "root", "rcnews", 0, NULL, 0) == NULL)
		handle_error("catssql::sql_cat_user_exists::mysql_real_connect(conn, rcnews)");

	/* creez sirul de caractere pentru query SELECT */
	sprintf(query, "SELECT user_id FROM categories WHERE id = '%d';", id);

	/* gasesc categoria, CU TRATAREA ERORILOR */
	if (mysql_query(conn, query))
		handle_error("catssql::sql_cat_user_exists::mysql_query(conn, select)");

	if ((result = mysql_store_result(conn)) == NULL)
		handle_error("catssql::sql_cat_user_exists::mysql_store_result(conn, select)");	

	/* verific valoarea raspunsului */
	if (row = mysql_fetch_row(result))
	{
		/* retin primul camp */
		ans = atoi(row[0]);
	}
	else
	{
		/* consider categorie fictiva, dar e posibil sa fi fost stearsa! */
		ans = 0;
	}

	/* eliberez rezultatul */
	mysql_free_result(result);

	/* inchid conexiunea la baza de date */
	mysql_close(conn);

	/* intorc raspunsul */
	return ans;	
}

