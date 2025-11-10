CXX = clang++
CXXFLAGS = -std=c++17 -I/opt/homebrew/opt/sfml/include
LDFLAGS = -L/opt/homebrew/opt/sfml/lib
LIBS = -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
SOURCES = ZobieShooter.cpp Player.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = ZobieShooter

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: clean