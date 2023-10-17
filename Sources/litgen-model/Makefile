CC = g++
CFLAGS = -c -Wall -std=gnu++17  -Wunused  -fdiagnostics-color=always  # -Wdeprecated-declarations
LDFLAGS = -ltins -lpcap -pthread
EXTERNAL_INCLUDES = -I../libs/cpptools_0.1.0.0/include
EXTERNAL_LDFLAGS = ../libs/cpptools_0.1.0.0/bin/libcpptools.a

SRCDIR = src
COMMONS_SRCDIR = ../commons/src
INCDIR = include
COMMONS_INCDIR = ../commons/include
OBJDIR = obj
COMMONS_OBJDIR = ../commons/obj
BINDIR = bin

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
COMMONS_SOURCES = $(wildcard $(COMMONS_SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))
COMMONS_OBJECTS = $(patsubst $(COMMONS_SRCDIR)/%.cpp,$(COMMONS_OBJDIR)/%.o,$(COMMONS_SOURCES))
EXECUTABLE = $(BINDIR)/litgen-model.exe

all: $(EXECUTABLE)

# build the executable
$(EXECUTABLE): prebuild $(OBJECTS) $(COMMONS_OBJECTS)
	$(CC) $(OBJECTS)  $(COMMONS_OBJECTS) $(EXTERNAL_LDFLAGS) -o  $@ $(LDFLAGS) 

# build the objects
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) $(EXTERNAL_INCLUDES) -I$(INCDIR) -I$(COMMONS_INCDIR) $< -o $@

$(COMMONS_OBJDIR)/%.o: $(COMMONS_SRCDIR)/%.cpp
	$(CC) $(CFLAGS) $(EXTERNAL_INCLUDES) -I$(INCDIR) -I$(COMMONS_INCDIR) $< -o $@

# any command to run before the build
prebuild:
	mkdir -p $(BINDIR)
	mkdir -p $(OBJDIR)
	mkdir -p $(COMMONS_OBJDIR)	
	
# clean last build
clean:
	rm -f $(OBJDIR)/*.o $(COMMONS_OBJDIR)/*.o $(EXECUTABLE) $(OBJDIR)/*.h

# clean and build
rebuild:
	make clean
	make all

