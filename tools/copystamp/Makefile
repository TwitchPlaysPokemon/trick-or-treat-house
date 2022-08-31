CXX := g++
CXXFLAGS := -std=c++11 -O2

SRCS := copystamp.cpp

.PHONY: all clean

all: copystamp
	@:

copystamp: $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $@ $(LDFLAGS)

clean:
	$(RM) copystamp copystamp.exe *.o