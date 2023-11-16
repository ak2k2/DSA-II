CXX = g++
CXXFLAGS = -Iinclude -Wall -std=c++11
OBJDIR = build
SRCDIR = src
BINDIR = bin
INCLUDE = include
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Create the bin and obj directories if they don't exist
$(shell mkdir -p $(BINDIR) $(OBJDIR))

all: $(BINDIR)/graphApp.exe

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BINDIR)/graphApp.exe: $(OBJECTS)
	$(CXX) $^ -o $@

debug: CXXFLAGS += -g
debug: $(BINDIR)/graphAppDebug.exe

$(BINDIR)/graphAppDebug.exe: $(OBJECTS)
	$(CXX) $^ -o $@

.PHONY: clean backup

clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(BINDIR)/*

backup:
	test -d backups || mkdir backups
	cp $(SRCDIR)/*.cpp backups
	cp $(INCLUDE)/*.h backups
	cp Makefile backups
