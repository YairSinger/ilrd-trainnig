GD = gcc 
CFLAGS = -ansi  -Wall -Wextra -g -pedantic-errors 
RFLAGS = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
OBJS = main.o foo.o 
LIBRARY = libfoo.ar

.PHONY: clean release all debug


fooer.out : $(OBJS)
	$(GD) $(CFLAGS) -o fooer.out $(OBJS) 
	
main.o : main.c foo.h
	$(GD) $(CFLAGS) -c -o main.o main.c 

foo.o : foo.c foo.h
	$(GD) $(CFLAGS) -c -o foo.o foo.c 
		
all : fooer.out 

release : $(OBJS)
	$(GD) $(RFLAGS) $(OBJS) -o fooer.out	

debug : fooer.out

libfoo.ar : $(OBJS)
	ar rcs $(LIBRARY) $(OBJS)

clean :
	rm  main.o foo.o fooer.out libfoo.ar
