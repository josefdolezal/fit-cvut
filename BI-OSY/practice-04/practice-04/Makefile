# all after symbol '#' is comment

# === which communication library to use ===
CC	=	gcc
CFLAGS	=       -Wall -pedantic
LIBS	=	-lpthread -lrt 

default: server client process-alternation-SV4 thread-alternation-POSIX process-alternation-POSIX

server:server.c
	$(CC) $(CFLAGS) -o server server.c $(LIBS)

client:client.c
	$(CC) $(CFLAGS) -o client client.c $(LIBS)

process-alternation-SV4:process-alternation-SV4.c
	$(CC) $(CFLAGS) -o process-alternation-SV4 process-alternation-SV4.c

thread-alternation-POSIX:thread-alternation-POSIX.c
	$(CC) $(CFLAGS) -o thread-alternation-POSIX thread-alternation-POSIX.c $(LIBS)

process-alternation-POSIX:process-alternation-POSIX.c
	$(CC) $(CFLAGS) -o process-alternation-POSIX process-alternation-POSIX.c $(LIBS)

clear:
	\rm server client process-alternation-SV4 thread-alternation-POSIX process-alternation-POSIX 
