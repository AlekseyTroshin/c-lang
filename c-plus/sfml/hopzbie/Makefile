CXX = clang++
CXXFLAGS = -std=c++17 -I/opt/homebrew/opt/sfml/include
LDFLAGS = -L/opt/homebrew/opt/sfml/lib
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
TARGET = main

run: $(TARGET)
	./$(TARGET)

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o $(TARGET) $(LDFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)

.PHONY: all clean run