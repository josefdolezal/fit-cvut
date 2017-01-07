# all after symbol '#' is comment
# === which communication library to use ===
CC	=	gcc
CFLAGS	=       -Wall -pedantic -ansi 
LIBS	=	-lpthread  

all:	hello hello_arg1 hello_arg2 join1 join2 zrychleni

hello: hello.c
	$(CC) $(CFLAGS) -o hello hello.c $(LIBS)

hello_arg1: hello_arg1.c
	$(CC) $(CFLAGS) -o hello_arg1 hello_arg1.c $(LIBS)

hello_arg2: hello_arg2.c
	$(CC) $(CFLAGS) -o hello_arg2 hello_arg2.c $(LIBS)

join1: join1.c
	$(CC) $(CFLAGS) -o join1 join1.c $(LIBS)

join2: join2.c
	$(CC) $(CFLAGS) -o join2 join2.c $(LIBS)

zrychleni: zrychleni.c 
	$(CC) $(CFLAGS) -o zrychleni zrychleni.c $(LIBS)

clean:
	\rm -f hello hello_arg1 hello_arg2 join1 join2 zrychleni *~ core

