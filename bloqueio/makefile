CXX		 = g++
CXXFLAGS = -std=c++11 -O3
LDFLAGS  =
DEPS	 = main.cpp node.cpp node.h character.cpp character.h algorithms.cpp algorithms.h mapLoader.cpp mapLoader.h ui_utilities.cpp ui_utilities.h makefile
OBJFILES = main.o node.o character.o algorithms.o mapLoader.o ui_utilities.o
TARGET	 = main


all: $(TARGET)


$(TARGET): $(OBJFILES) $(DEPS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)


clean:
	rm -f $(OBJFILES) $(TARGET) *~

recompile: makefile
	make clean
	make $(TARGET)