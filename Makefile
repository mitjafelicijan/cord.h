UNAME := $(shell uname)

CC       = clang
CFLAGS   =
LDLIBS   =
INCLUDES =

# MacOS specific
ifeq ($(UNAME), Darwin)
endif

# Linux specific
ifeq ($(UNAME), Linux)
endif

# Debug options (DEBUG=1 make clone)
ifeq ($(DEBUG), 1)
CFLAGS += -W -ggdb
endif

.PHONY: all

test: clean test.c
	$(CC) -o test test.c $(CFLAGS) $(INCLUDES) $(LDLIBS)

clean:
	@-rm test
