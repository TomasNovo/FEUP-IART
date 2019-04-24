CXX		 = g++
CXXFLAGS = -std=c++11 -g
LDFLAGS  =
DEPS	 = main.cpp node.cpp node.h makefile
OBJFILES = main.o node.o
TARGET	 = main


all: $(TARGET)


$(TARGET): $(OBJFILES) $(DEPS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)


clean:
	rm -f $(OBJFILES) $(TARGET) *~

recompile: makefile
	make clean
	make $(TARGET)