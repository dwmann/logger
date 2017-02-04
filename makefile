
cc=gcc
ld=gcc
cflags=-O3 -g0
lflags=-lc

obj=main.o logger.o


test : $(obj)
	$(ld) -o $@ $(obj) $(lflags)

%.o : %.c
	$(cc) $(cflags) -c -o $@ $<

clean:
	rm test
	rm *.o
