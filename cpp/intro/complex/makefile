# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra
DEBUG_FLAGS := -g
RELEASE_FLAGS := -O2

# Directories
SRCDIR := src
INCLUDEDIR := include
BINDIR := bin
DEBUGDIR := $(BINDIR)/debug
RELEASEDIR := $(BINDIR)/release
LIBDIR := lib
TESTDIR := test

# Files
SRC := $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(TESTDIR)/*.cpp)
OBJ := $(SRC:%.cpp=%.o)
DEPS := $(wildcard $(INCLUDEDIR)/*.hpp)

# Targets
DEBUGTARGET := $(DEBUGDIR)/a.out
RELEASETARGET := $(RELEASEDIR)/a.out

# Rules
.PHONY: all clean debug release

all: debug release

debug: $(DEBUGTARGET)

release: $(RELEASETARGET)

$(DEBUGTARGET): $(OBJ)
	@mkdir -p $(DEBUGDIR)
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) -o $@ $^

$(RELEASETARGET): $(OBJ)
	@mkdir -p $(RELEASEDIR)
	$(CXX) $(CXXFLAGS) $(RELEASE_FLAGS) -o $@ $^

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -I$(INCLUDEDIR) -c -o $@ $<

clean:
	$(RM) -r $(BINDIR)/*.out $(OBJ)
