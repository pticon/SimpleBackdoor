TARGET=bd

DEBUG?=0
VERBOSE?=0


CROSS?=
CC=$(CROSS)gcc


CFLAGS=-Wall -Werror
LDFLAGS=


RM=rm -f
CHOWN=chown
CHMOD=chmod


SRCS=main.c
SRCS+=
OBJS=${SRCS:.c=.o}


# debug option
ifeq ($(DEBUG), 1)
CFLAGS+=-O0 -g -DDEBUG
else
CFLAGS+=-O3
endif


# verbose option
ifeq ($(VERBOSE), 1)
Q := 
echo-cmd := @echo $(1) > /dev/null
else
Q := @
echo-cmd := @echo $(1)
endif


.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(echo-cmd) " LD    $@"
	$(Q)$(CC) $(LDFLAGS) -o $@ $^
	$(echo-cmd) " STICK $@"
	$(Q)$(CHMOD) +s $@


%.o : %.c
	$(echo-cmd) " CC    $@"
	$(Q)$(CC) $(CFLAGS) -c $< -o $@


clean:
	$(echo-cmd) " CLEAN"
	$(Q)$(RM) $(OBJS) $(TARGET)
