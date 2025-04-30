
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

SRCS = main.cpp block.cpp stream.cpp utility.cpp # files used
OBJS = $(SRCS:.cpp=.o) # object files

TARGET = cipher # exe

$(TARGET): $(OBJS) # build
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)


clean:
	rm -f $(TARGET) $(OBJS)
