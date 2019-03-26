CXX		 = g++
CXXFLAGS = -std=c++11 -g
LDFLAGS  =
DEPS	 = main.cpp node.cpp node.h robot.cpp robot.h algorithms.cpp algorithms.h mapLoader.cpp mapLoader.h interface.cpp interface.h ui_utilities.cpp ui_utilities.h makefile
OBJFILES = main.o node.o robot.o algorithms.o mapLoader.o interface.o ui_utilities.o
TARGET	 = main


all: $(TARGET)


$(TARGET): $(OBJFILES) $(DEPS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)


clean:
	rm -f $(OBJFILES) $(TARGET) *~

recompile: makefile
	make clean
	make $(TARGET)