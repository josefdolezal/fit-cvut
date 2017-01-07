# all after symbol '#' is comment

# === which communication library to use ===
CC	=	gcc
CFLAGS	=       -Wall -pedantic -ansi 
CFLAGS-NOANSI  = -Wall -pedantic    
LIBS	=	-lrt

TARGETS=print-pid system fork fork-exec sigquit pipe1 pipe2 pipe3

all: $(TARGETS)

print-pid:print-pid.c
	$(CC) $(CFLAGS) -o print-pid print-pid.c $(LIBS)

system:system.c
	$(CC) $(CFLAGS) -o system system.c $(LIBS)

fork:fork.c
	$(CC) $(CFLAGS) -o fork fork.c $(LIBS)

fork-exec:fork-exec.c
	$(CC) $(CFLAGS) -o fork-exec fork-exec.c $(LIBS)

sigquit:sigquit.c
	$(CC) $(CFLAGS-NOANSI) -o sigquit sigquit.c $(LIBS)

pipe1:pipe1.c
	$(CC) $(CFLAGS) -o pipe1 pipe1.c $(LIBS)

pipe2:pipe2.c
	$(CC) $(CFLAGS-NOANSI) -o pipe2 pipe2.c $(LIBS)

pipe3:pipe3.c
	$(CC) $(CFLAGS-NOANSI) -o pipe3 pipe3.c $(LIBS)

clean:
	rm -f $(TARGETS) core *~

