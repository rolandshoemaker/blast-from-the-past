CC = gcc
LD = gcc
LDFLAGS =
CFLAGS = -Wall -g -Wno-pointer-sign
RM = /bin/rm -f
SRCS = books.c xml.c common.c isbn.c mysql.c
OBJS = books.o xml.o common.o isbn.o mysql.o
PROG = books

all: books

books: books.o xml.o common.o isbn.o mysql.o
	$(LD) $(LDFLAGS) -o $(PROG) $(OBJS) `xml2-config --cflags --libs` `mysql_config --cflags --libs`

%.o: %.c books.h
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) $(PROG) $(OBJS)
