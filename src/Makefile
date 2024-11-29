SRCS = $(wildcard *.cpp) 
OBJS = $(SRCS:.cpp=.o)
CXX = g++
CXXFLAGS = -Wall -O2

.PHONY: all

all: $(OBJS)


%.o: %.cpp .depend
	$(CXX) -c $(CXXFLAGS) -I./ $< -o $@

.depend: $(SRCS)
	rm -f "$@"
	$(CXX) $(CXXFLAGS) -I./ -MM $^ > "$@"

include .depend

.PHONY: clean
clean:
	rm -f $(OBJS) .depend
