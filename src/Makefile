SRCS = $(wildcard *.cpp) 
OBJS = $(SRCS:.cpp=.o)
CXX = g++
CXXFLAGS = -Wall -O2
INCLUDE = -I./ -I/usr/include/mysql-cppconn

.PHONY: all

all: $(OBJS)


%.o: %.cpp .depend
	$(CXX) -c $(CXXFLAGS) $(INCLUDE) $< -o $@

.depend: $(SRCS)
	rm -f "$@"
	$(CXX) $(CXXFLAGS) $(INCLUDE) -MM $^ > "$@"

include .depend

.PHONY: clean
clean:
	rm -f $(OBJS) .depend
