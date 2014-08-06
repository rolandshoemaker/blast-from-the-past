#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>

/** typedef struct ISBN_info {
	xmlChar *title;
	xmlChar *author;
	xmlChar *publisher;
	char *comment;
	char *genre;
	char *isbn;
	char *bin;
} ISBN_info __attribute__((packed)); **/

struct _ISBN_info {
        xmlChar *title;
        xmlChar *author;
        xmlChar *publisher;
        char *comment;
        char *genre;
        char *isbn;
        char *bin;
} __attribute__((packed));
 
typedef struct _ISBN_info ISBN_info;

/* xml.c declarations */
xmlDocPtr get_xml(char *isbn);
ISBN_info parse_xml(xmlDocPtr xml);
void parse_nodes(xmlDocPtr xml, xmlNodePtr cur, ISBN_info *info);

/* common.c declarations */
void freeInfo(ISBN_info *info);
int get_rest(ISBN_info *info);
int check_ans(ISBN_info *info);

/* isbn.c declarations */
int check_isbn(char *isbn);
char *convert(char *isbn);

/* mysql.c declarations */
void mysql_send(ISBN_info *info);

