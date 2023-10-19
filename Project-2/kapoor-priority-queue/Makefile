CXX = g++
CXXFLAGS = -Iinclude -Wall
OBJDIR = build
SRCDIR = src
BINDIR = bin
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Create the bin directory if it doesn't exist
$(shell mkdir -p $(BINDIR))

all: $(BINDIR)/useHeap.exe

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BINDIR)/useHeap.exe: $(OBJECTS)
	$(CXX) $^ -o $@

debug: CXXFLAGS += -g
debug: $(BINDIR)/useHeapDebug.exe

$(BINDIR)/useHeapDebug.exe: $(OBJECTS)
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
