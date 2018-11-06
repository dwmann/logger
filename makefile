
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
	if [ -f test ] ; then rm test ; fi
	if ls *o 1> /dev/null 2>&1 ; then rm *.o ; fi
