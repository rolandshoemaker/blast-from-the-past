#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlreader.h>
#include "books.h"

int main(int argc, char *argv[]) {
	if (argc<2) {
		printf("usage: books [-ac] [isbn]\n");
		exit(1);
	}
	if (!strcmp(argv[1], "-a")&&argv[2]!=NULL) {
		if (check_isbn(argv[2])!=0) exit(1);
		xmlDocPtr xml = get_xml(argv[2]);
		ISBN_info info = parse_xml(xml);
		info.isbn = malloc(strlen(argv[2])+1);
		info.isbn = strdup(argv[2]);
		info.isbn[strlen(argv[2])] = '\0';
		if (get_rest(&info)!=0) exit(1);
		if (check_ans(&info)!=0) exit(1);
		mysql_send(&info);
		freeInfo(&info);
		xmlFreeDoc(xml);
		xmlCleanupParser();
	} else if (!strcmp(argv[1], "-c")&&argv[2]!=NULL) {
		char *converted = convert(argv[2]);
		if (converted!=NULL) { printf("%s\n", converted); free(converted); }
	} else {
		printf("error\n");
	}
	return 0;
}

