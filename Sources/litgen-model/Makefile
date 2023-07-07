CC = g++
CFLAGS = -c -Wall -std=gnu++17  -Wunused  -fdiagnostics-color=always  # -Wdeprecated-declarations
LDFLAGS = -ltins -lpcap -pthread
EXTERNAL_INCLUDES = -I../libs/cpptools/include
EXTERNAL_LDFLAGS = ../libs/cpptools/bin/libcpptools.a

SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))
EXECUTABLE = $(BINDIR)/litgen-model.exe

all: $(EXECUTABLE)

# build the executable
$(EXECUTABLE): prebuild $(OBJECTS) 
	$(CC) $(OBJECTS) -o  $@ $(LDFLAGS) $(EXTERNAL_LDFLAGS)

# build the objects
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) $(EXTERNAL_INCLUDES) -I$(INCDIR) $< -o $@


# any command to run before the build
prebuild:
	mkdir -p $(BINDIR)
	mkdir -p $(OBJDIR)
	
# clean last build
clean:
	rm -f $(OBJDIR)/*.o $(EXECUTABLE) $(OBJDIR)/*.h

# clean and build
rebuild:
	make clean
	make all

