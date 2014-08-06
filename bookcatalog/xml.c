#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlreader.h>
#include "books.h"

xmlDocPtr get_xml(char *isbn) {
	xmlDocPtr xml = NULL;
	char *base = "http://isbndb.com/api/books.xml?access_key=Q4G55RUL&index1=isbn&value1=";
	char *url = malloc(strlen(base)+strlen(isbn));
	strncat(url, base, strlen(base));
	strncat(url, isbn, strlen(isbn));
	xml = xmlParseFile(url);
	if (xml==NULL) {
		fprintf(stderr, "Document not parsed properly.\n");
		exit(1);
	}
	free(url);
	return xml;
}

void parse_nodes(xmlDocPtr xml, xmlNodePtr cur, ISBN_info *info) {
	xmlChar *key;
	cur = cur->xmlChildrenNode;
	while (cur!=NULL) {
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"Title"))) {
			key = xmlNodeListGetString(xml, cur->xmlChildrenNode, 1);
			info->title = malloc(xmlStrlen(key));
			info->title = xmlStrdup(key);
			xmlFree(key);
		}
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"TitleLong"))) {
			key = xmlNodeListGetString(xml, cur->xmlChildrenNode, 1);
			if (key!=NULL) {
				info->title = malloc(xmlStrlen(key));
				info->title = xmlStrdup(key);
			}
			xmlFree(key);
		}
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"AuthorsText"))) {
			key = xmlNodeListGetString(xml, cur->xmlChildrenNode, 1);
			info->author = malloc(xmlStrlen(key));
			info->author = xmlStrdup(key);
			xmlFree(key);
		}
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"PublisherText"))) {
			key = xmlNodeListGetString(xml, cur->xmlChildrenNode, 1);
			info->publisher = malloc(xmlStrlen(key));
			info->publisher = xmlStrdup(key);
			xmlFree(key);
		}
		cur = cur->next;
	}
	xmlCleanupParser();
	return;
}

ISBN_info parse_xml(xmlDocPtr xml) {
	ISBN_info info;
	xmlNodePtr cur = xmlDocGetRootElement(xml);
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"BookData"))){
			parse_nodes(xml, cur, &info);
			break;
		}
		if (cur->xmlChildrenNode!=NULL) {cur = cur->xmlChildrenNode;}
		else {cur = cur->next;}
	}
	xmlCleanupParser();
	return info;
}

