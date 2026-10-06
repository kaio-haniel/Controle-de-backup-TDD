CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g -fprofile-arcs -ftest-coverage
TARGET = testa_backup

SRCS = backup.cpp testa_backup.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TARGET)
	./$(TARGET)

gcov: test
	gcov backup.cpp

valgrind: $(TARGET)
	valgrind --leak-check=full --track-origins=yes ./$(TARGET)

check:
	cppcheck --enable=warning --suppress=missingIncludeSystem .
	cpplint --filter=-legal/copyright,-whitespace/braces backup.hpp backup.cpp testa_backup.cpp

clean:
	rm -f $(TARGET) *.o *.gcno *.gcda *.gcov

doc:
	doxygen

clean:
	rm -rf $(TARGET) *.o *.gcno *.gcda *.gcov html