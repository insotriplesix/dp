EXEC=main
EXECDL=main_dl
CC=gcc
CFLAGS=-std=gnu99 -Wall -g -lm

LD=LD_LIBRARY_PATH
LIBNAME=complex

STATIC=stc
DYNAMIC=dyn
SEPARATED=sep

BUILDDIR=build
PLUGINSDIR=build/plugins
SOURCEDIR=src

SOURCES=$(wildcard $(SOURCEDIR)/c_*.c)
PLUGINS=$(patsubst $(SOURCEDIR)/c_%.c,$(PLUGINSDIR)/c_%.o,$(SOURCES))

all: clean dir static dynamic separated $(EXEC)

dir:
	mkdir -p $(PLUGINSDIR)

static:
	$(CC) -c $(SOURCEDIR)/$(LIBNAME).c -o $(BUILDDIR)/$(LIBNAME).o
	ar rc $(BUILDDIR)/lib$(STATIC).a $(BUILDDIR)/$(LIBNAME).o
	ranlib $(BUILDDIR)/lib$(STATIC).a

dynamic:
	$(CC) -fPIC -c $(SOURCEDIR)/$(LIBNAME).c -o $(BUILDDIR)/$(LIBNAME).o
	$(CC) -shared -o $(BUILDDIR)/lib$(DYNAMIC).so $(BUILDDIR)/$(LIBNAME).o
	$(LD)=${PWD}/$(BUILDDIR):${LD_LIBRARY_PATH}
	export $(LD)

separated: $(PLUGINS)

$(PLUGINS): $(PLUGINSDIR)/c_%.o : $(SOURCEDIR)/c_%.c
	$(CC) -fPIC -c $< -o $@
	$(CC) -shared -o $(subst .o,.so,$@) $@

$(EXEC):
	$(CC) $(CFLAGS) $(EXEC).c -L $(BUILDDIR)/ -l$(STATIC) -o $(EXEC)_static.out
	$(CC) $(CFLAGS) $(EXEC).c -L $(BUILDDIR)/ -l$(DYNAMIC) -o $(EXEC)_dynamic.out
	$(CC) $(CFLAGS) $(EXECDL).c -ldl -o $(EXECDL).out

clean:
	rm -f *.out
	rm -rf $(BUILDDIR)
	$(LD)=""
	export $(LD)
