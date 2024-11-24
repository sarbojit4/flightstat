SRCS = $(wildcard src/*.cpp) 
OBJS = $(SRCS:.cpp=.o)
TARGET = flightstat
CXX = g++

.PHONY: all

all : $(OBJS)
	$(CXX) $^ -o $(TARGET)

$(OBJS):
	$(MAKE) -C src

.PHONY: clean
clean:
	rm -f $(TARGET)
	$(MAKE) -C src clean
