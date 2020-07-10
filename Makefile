CXX=g++
CFLAGS=-c -g -pthread -pedantic -std=c++17 -Wall
LDFLAGS=-lncursesw
EXECUTABLE=./SoliCurses-C.out
SRCDIR=./src
BINDIR=./bin

SOURCES=$(wildcard ${SRCDIR}/*.cpp)

OBJECTS=$(SOURCES:${SRCDIR}/%.cpp=$(BINDIR)/%.o)

all : $(EXECUTABLE)

$(EXECUTABLE) : ${OBJECTS}
	$(CXX) -o $@ $^ $(LDFLAGS)

$(BINDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(CFLAGS) -o $@ $<

clean : 
	rm -r $(BINDIR)/*.o $(EXECUTABLE)

run : all
	$(EXECUTABLE)
