CXX = clang++
CXXFLAGS = -std=c++17 -I/opt/homebrew/opt/sfml/include
LDFLAGS = -L/opt/homebrew/opt/sfml/lib
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
TARGET = game

all: $(TARGET)

$(TARGET): game.cpp
	$(CXX) $(CXXFLAGS) game.cpp -o $(TARGET) $(LDFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)

.PHONY: all clean