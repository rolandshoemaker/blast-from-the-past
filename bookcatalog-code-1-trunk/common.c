#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlreader.h>
#include "books.h"

void freeInfo(ISBN_info *info) {
	if (info->title!=NULL) {
		xmlFree(info->title);
	}
	if (info->author!=NULL) {
		xmlFree(info->author);
	}
	if (info->publisher!=NULL) {
		xmlFree(info->publisher);
	}
	if (info->comment!=NULL) {
		free(info->comment);
	}
	if (info->genre!=NULL) {
		free(info->genre);
	}
	if (info->isbn!=NULL) {
		free(info->isbn);
	}
	if (info->bin!=NULL) {
		free(info->bin);
	}
}

int get_rest(ISBN_info *info) {
        char *new;
        char buf[512];
        int len;
        printf("title: %s\nauthor: %s\npublisher: %s\n", info->title, info->author, info->publisher);
        printf("genre: ");
        if (!fgets(buf, sizeof(buf), stdin)) return 1;
        len = strlen(buf);
        if (len>1) {
                if ((new = strchr(buf, '\n'))!=NULL) *new = '\0';
                info->genre = malloc(len);
                strncpy(info->genre, buf, len);
        } else {
        	info->genre = NULL;
        }
        printf("comment: ");
        if (!fgets(buf, sizeof(buf), stdin)) return 1;
        len = strlen(buf);
        if (len>1) {
                if ((new = strchr(buf, '\n'))!=NULL) *new = '\0';
                info->comment = malloc(len);
                strncpy(info->comment, buf, len);
        } else {
        	info->comment = NULL;
        }
        printf("read: ");
        if (!fgets(buf, sizeof(buf), stdin)) return 1;
        len = strlen(buf);
        if (len>1) {
                if ((new = strchr(buf, '\n'))!=NULL) *new = '\0';
                info->bin = malloc(len);
                strncpy(info->bin, buf, len);
        } else {
        	info->bin = NULL;
        }
        return 0;

}

int check_ans(ISBN_info *info) {
	char *new;
	char buf[512];
	int len;
	start:
	printf("title: %s\nauthor: %s\npublisher: %s\ngenre: %s\ncomment: %s\nread: %s\nisbn: %s\n", info->title, info->author, info->publisher, info->genre, info->comment, info->bin, info->isbn);
	printf("happy: ");
	fflush(stdout);
	if (!fgets(buf, sizeof(buf), stdin)) return 1;
	len = strlen(buf);
	if ((new = strchr(buf, '\n'))!=NULL) *new = '\0';
	if (!strcmp(buf, "no")) {
		with:
		printf("with: ");
		fflush(stdout);
		if (!fgets(buf, sizeof(buf), stdin)) return 1;
		len = strlen(buf);
		if ((new = strchr(buf, '\n'))!=NULL) *new = '\0';
		if (!strcmp(buf, "title")) {
			printf("title: ");
			if (!fgets(buf, sizeof(buf), stdin)) return 1;
			len = strlen(buf);
        		if (len>1) {
				if ((new = strchr(buf, '\n'))!=NULL) *new = '\0';
				if (info->title!=NULL) free(info->title);
                		info->title = malloc(len);
               			memset(info->title, '\0', len);
                		strncpy(info->title, buf, len);
       			}
		} else if (!strcmp(buf, "author")) {
			len = strlen(buf);
        		if (len>1) {
				if ((new = strchr(buf, '\n'))!=NULL) *new = '\0';
				if (info->author!=NULL) free(info->author);
                		info->author = malloc(len);
               			memset(info->author, '\0', len);
                		strncpy(info->author, buf, len);
       			}
		} else if (!strcmp(buf, "publisher")) {
			len = strlen(buf);
        		if (len>1) {
				if ((new = strchr(buf, '\n'))!=NULL) *new = '\0';
				if (info->publisher!=NULL) free(info->publisher);
                		info->publisher = malloc(len);
               			memset(info->publisher, '\0', len);
                		strncpy(info->publisher, buf, len);
       			}
		} else if (!strcmp(buf, "genre")) {
			len = strlen(buf);
        		if (len>1) {
				if ((new = strchr(buf, '\n'))!=NULL) *new = '\0';
				if (info->genre!=NULL) free(info->genre);
                		info->genre = malloc(len);
               			memset(info->genre, '\0', len);
                		strncpy(info->genre, buf, len);
       			}
		} else if (!strcmp(buf, "comment")) {
			len = strlen(buf);
        		if (len>1) {
				if ((new = strchr(buf, '\n'))!=NULL) *new = '\0';
				if (info->comment!=NULL) free(info->comment);
                		info->comment = malloc(len);
               			memset(info->comment, '\0', len);
                		strncpy(info->comment, buf, len);
       			}
		} else if (!strcmp(buf, "read")) {
			len = strlen(buf);
        		if (len>1) {
				if ((new = strchr(buf, '\n'))!=NULL) *new = '\0';
				if (info->bin!=NULL) free(info->bin);
                		info->bin = malloc(len);
               			memset(info->bin, '\0', len);
                		strncpy(info->bin, buf, len);
       			}
		} else {
			goto with;
		}
		goto start;
	} else if (!strcmp(buf, "yes")) {
		printf("okies\n");
		return 0;
	} else {
		goto start;
	}
}

