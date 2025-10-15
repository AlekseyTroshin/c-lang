CXX = clang++
CXXFLAGS = -std=c++17 -I/opt/homebrew/opt/sfml/include
LDFLAGS = -L/opt/homebrew/opt/sfml/lib
LIBS = -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
TARGET = Timber

all: $(TARGET)

$(TARGET): Timber.cpp
	$(CXX) $(CXXFLAGS) Timber.cpp -o $(TARGET) $(LDFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)

.PHONY: all clean