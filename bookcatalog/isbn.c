#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "books.h"

char *convert(char *isbn) {
	int len = strlen(isbn);
	int e[len];
	int i = 0;
	int r = 0;
	char a;
	while (isbn[i]!='\0') {
		if (isbn[i]!='-') {
			if (isbn[i] == 'X' || isbn[i] == 'x') {
				if (r>0) {
					e[i-r] = 10;
					i++;
				} else {
					e[i] = 10;
					i++;
				}
			} else {
				if (r>0) {
					a = isbn[i];
					e[i-r] = atoi(&a);
					i++;
				} else {
					a = isbn[i];
					e[i] = atoi(&a);
					i++;
				}
			}
		} else {
			i++;
			r++;
		}
	}
	if (sizeof(e)/sizeof(int)==10||(sizeof(e)/sizeof(int)==10+r&&r>0)) {
		int new[12];
		int b;
		new[0] = 9;
		new[1] = 7;
		new[2] = 8;
		for (b = 0; b<sizeof(e)/sizeof(int); b++) {
			new[b+3] = e[b];
		}
		new[12] = 10-(((new[0])+(3*new[1])+(new[2])+(3*new[3])+(new[4])+(3*new[5])+(new[6])+(3*new[7])+(new[8])+(3*new[9])+(new[10])+(3*new[11]))%10);
		char *string = malloc(sizeof(new)/sizeof(int)+2);
		int k;
		for (k = 0; k<=(sizeof(new)/sizeof(int)); k++) {
			string[k] = (char)new[k]+48;
		}
		string[13] = '\0';
		return string;
	} else if (sizeof(e)/sizeof(int)==13||(sizeof(e)/sizeof(int)==13+r&&r>0)) {
		int new[9];
		int b;
		for (b = 0; b<(sizeof(e)/sizeof(int))-3; b++) {
			new[b] = e[b+3];
		}
		new[9] = 11-(((10*new[0])+(9*new[1])+(8*new[2])+(7*new[3])+(6*new[4])+(5*new[5])+(4*new[6])+(3*new[7])+(2*new[8]))%11);
		char *string = malloc(sizeof(new)/sizeof(int)+2);
		int k;
		for (k = 0; k<=(sizeof(new)/sizeof(int)); k++) {
			string[k] = new[k]+48;
		}
		string[10] = '\0';
		return string;
	} else {
		printf("There is something wrong with your isbn dude....");
		return NULL;
	}
}

int check_isbn(char *isbn) {
	int len = strlen(isbn);
	int e[len];
	int i = 0;
	int r = 0;
	char a;
	while (isbn[i]!='\0') {
		if (isbn[i]!='-') {
			if (isbn[i] == 'X' || isbn[i] == 'x') {
				if (r>0) {
					e[i-r] = 10;
					i++;
				} else {
					e[i] = 10;
					i++;
				}
			} else {
				if (r>0) {
					a = isbn[i];
					e[i-r] = atoi(&a);
					i++;
				} else {
					a = isbn[i];
					e[i] = atoi(&a);
					i++;
				}
			}
		} else {
			i++;
			r++;
		}
	}
	if (sizeof(e)/sizeof(int)==10||(sizeof(e)/sizeof(int)==10+r&&r>0)) {
		int check = 11-(((10*e[0])+(9*e[1])+(8*e[2])+(7*e[3])+(6*e[4])+(5*e[5])+(4*e[6])+(3*e[7])+(2*e[8]))%11);
		if (check!=e[9]) {
			printf("the ISBN entered doesn't check out math wise\n");
			return 1;
		} else {
			return 0;
		}
	} else if (sizeof(e)/sizeof(int)==13||(sizeof(e)/sizeof(int)==13+r&&r>0)) {
		int check = 10-(((e[0])+(3*e[1])+(e[2])+(3*e[3])+(e[4])+(3*e[5])+(e[6])+(3*e[7])+(e[8])+(3*e[9])+(e[10])+(3*e[11]))%10);
		if (check!=e[12]) {
			printf("the ISBN entered doesn't check out math wise\n");
			return 1;
		} else {
			return 0;
		}
	} else {
		printf("there is something really wrong with your isbn...\n");
		return 1;
	}
}
