CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -std=c++17
TARGET = fibonacci
TEST_TARGET = test_fibonacci

all: $(TARGET)

$(TARGET): fibonacci.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) fibonacci.cpp

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): test_fibonacci.cpp
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) test_fibonacci.cpp

clean:
	rm -f $(TARGET) $(TEST_TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all test clean run
