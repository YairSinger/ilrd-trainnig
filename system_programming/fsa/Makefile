NAME := fsa
GD = gcc 
CPPFLAGS = -I ../../include/ 
CFLAGS = -ansi  -Wall -Wextra -g -pedantic-errors 
RFLAGS = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
OBJS = $(NAME)_test.o $(NAME).o 
LIBRARY = lib$(NAME).ar


.PHONY: clean release all debug

../../bin/debug/$(NAME).out : $(OBJS)
	$(GD) $(CFLAGS) $(CPPFLAGS) -o ../../bin/debug/$(NAME).out $(OBJS) 
	
$(NAME).o : $(NAME).c ../../include/$(NAME).h
	$(GD) $(CFLAGS) $(CPPFLAGS) -c -o $(NAME).o $(NAME).c 

$(NAME)_test.o : ../../test/$(NAME)_test.c ../../include/$(NAME).h
	$(GD) $(CFLAGS) $(CPPFLAGS) -c -o $(NAME)_test.o ../../test/$(NAME)_test.c 
		
all : ../../bin/debug/$(NAME).out

release : $(OBJS)
	$(GD) $(RFLAGS) $(OBJS) $(CPPFLAGS) -o ../../bin/release/$(NAME).out	

debug : ../../bin/debug/$(NAME).out

$(LIBRARY) : $(OBJS)
	ar rcs $(LIBRARY) $(OBJS) $(CPPFLAGS)

clean :
	rm  $(NAME).o $(NAME)_test.o ../../bin/debug/$(NAME).out ../../bin/release/$(NAME).out lib$(NAME).ar
