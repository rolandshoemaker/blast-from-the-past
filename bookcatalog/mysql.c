#include <stdio.h>
#include <mysql/mysql.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include "books.h"

void mysql_send(ISBN_info *info) {
	MYSQL *conn = mysql_init(NULL);
	int i = 0;
	i += strlen("INSERT INTO books (title, author, genre, isbn, publisher, comment, bin) VALUES ('");
	i += strlen("', '")*6;
	i += strlen("');");
	if (info->title!=NULL) i+=strlen(info->title);
	if (info->author!=NULL) i+=strlen(info->author);
	if (info->genre!=NULL) i+=strlen(info->genre);
	if (info->isbn!=NULL) i+=strlen(info->isbn);
	if (info->publisher!=NULL) i+=strlen(info->publisher);
	if (info->comment!=NULL) i+=strlen(info->comment);
	if (info->bin!=NULL) i+=strlen(info->bin);
	char *query=NULL;
	query = malloc(i);
	sprintf(query, "INSERT INTO books (name, author, genre, isbn, publisher, comments, bin) VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s');", (info->title) ? (char *)info->title : "", (info->author) ? (char *)info->author : "", (info->genre) ? info->genre : "", (info->isbn) ? info->isbn : "", (info->publisher) ? (char *)info->publisher : "", (info->comment) ? info->comment : "", (info->bin) ? info->bin : "");
	if (conn==NULL) {fprintf(stderr, "mysql_init() failed :)\n");}
	if (!mysql_real_connect(conn, "localhost", "root", "fracture", "ruby", 0, NULL, 0)) {
		fprintf(stderr, "Failed to connect to db, Error: %s\n", mysql_error(conn));
	}
	if (mysql_query(conn, query)!=0) {
		fprintf(stderr, "INSERT statement failed\n");
		free(query);
	} else {
		printf("Insert succeeded\n");
		free(query);
	}
}

