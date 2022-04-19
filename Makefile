# photon makefile

STD=-std=c99
WFLAGS=-Wall -Wextra
OPT=-O2
IDIR=-I. -Iinclude
CC=gcc
NAME=libphoton
SRC=src/*.c

SCRIPT=build.sh

LDIR=lib
LIBS=fract
LSTATIC=$(patsubst %,lib%.a,$(LIBS))
LPATHS=$(patsubst %,$(LDIR)/%,$(LSTATIC))
LFLAGS=$(patsubst %,-L%,$(LDIR))
LFLAGS += $(patsubst %,-l%,$(LIBS))

CFLAGS=$(STD) $(WFLAGS) $(OPT) $(IDIR)

OS=$(shell uname -s)
ifeq ($(OS),Darwin)
	OSFLAGS=-dynamiclib
	LIB=$(NAME).dylib
else
	OSFLAGS=-lm -shared -fPIC
	LIB=$(NAME).so
endif

static: $(SRC)
	$(CC) $(CFLAGS) -c $(SRC) && ar -cr $(NAME).a *.o && rm *.o

$(LDIR):
	@[ -d $@ ] || mkdir $@ && echo "mkdir $@"

$(LDIR)%.a: %
	cd $^ && make && mv $@ ../

$(LPATHS): $(LDIR) $(LSTATIC)
	mv *.a $(LDIR)/

shared: $(SRC) $(LPATHS)
	$(CC) -o $(LIB) $(SRC) $(CFLAGS) $(LFLAGS) $(OSFLAGS)

clean: $(SCRIPT)
	./$^ $@

install: $(SCRIPT)
	./$^ $@

uninstall: $(SCRIPT)
	./$^ $@

