SRCS = $(wildcard *.cpp) 
OBJS = $(SRCS:.cpp=.o)
CXX = g++

.PHONY: all

all: $(OBJS)

%.o: %.cpp
	$(CXX) -c -I./ $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJS)
