LIB_NAME = lib_sched

CC = gcc

CFLAGS = -c -ansi -pedantic-errors -Wall -Wextra -g -fPIC

INCLUDES = -I../../../../ds/include/ -I../../../include/

DVECTOR = ../../../../ds/src/dvector/dvector.c
HEAP = ../../../../ds/src/heap/heap.c
HEAP_PQ_C = ../../../../ds/src/heap_pqueue/heap_pqueue.c
UID_C = ../../uid/ilrd_uid.c
TASK_C = ../../task/task.c

SRCS = $(DVECTOR) $(HEAP) $(HEAP_PQ_C) $(UID_C) $(TASK_C)

OBJS = $(SRCS:.c=.o)

.PHONY: clean

all: $(LIB_NAME).so

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

$(LIB_NAME).so: $(OBJS)
	$(CC) -shared $^ -o $@

clean:
	rm -f $(OBJS) $(LIB_NAME).so
