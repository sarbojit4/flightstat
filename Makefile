SRCS = $(wildcard src/*.cpp) 
OBJS = $(SRCS:.cpp=.o)
TARGET = flightstat
CXX = g++
CXXFLAGS = -Wall -O2
LDFLAGS = -lmysqlcppconnx

.PHONY: all

all: $(OBJS) .depend
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

.PHONY: .depend

.depend: $(SRCS)
	$(MAKE) -C src
$(OBJS): $(SRCS)
	$(MAKE) -C src

.PHONY: clean
clean:
	rm -f $(TARGET)
	$(MAKE) -C src clean
