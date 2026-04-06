# Компилятор и флаги
CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -std=c++17
LDFLAGS = 

# Имена исполняемых файлов
TARGET = fibonacci
TEST_TARGET = test_fibonacci

# Цель по умолчанию
all: $(TARGET)

# Сборка основной программы
$(TARGET): fibonacci.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) fibonacci.cpp $(LDFLAGS)

# Сборка тестов
$(TEST_TARGET): test_fibonacci.cpp
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) test_fibonacci.cpp $(LDFLAGS)

# Запуск программы (интерактивный режим)
run: $(TARGET)
	./$(TARGET)

# Запуск программы с аргументом
run-arg: $(TARGET)
	@echo "=== Запуск с аргументом 10 ==="
	./$(TARGET) 10

# Запуск тестов
test: $(TEST_TARGET)
	@echo "=== Запуск unit-тестов ==="
	./$(TEST_TARGET)

# Тестирование программы через аргументы командной строки
test-cli: $(TARGET)
	@echo "=== Тестирование через CLI аргументы ==="
	@echo "Тест 1: n=0"
	@./$(TARGET) 0 | grep -q "0" && echo "n=0 passed"
	@echo "Тест 2: n=1"
	@./$(TARGET) 1 | grep -q "1" && echo "n=1 passed"
	@echo "Тест 3: n=10"
	@./$(TARGET) 10 | grep -q "55" && echo "n=10 passed"
	@echo "Тест 4: n=20"
	@./$(TARGET) 20 | grep -q "6765" && echo "n=20 passed"
	@echo "Тест 5: n=50"
	@./$(TARGET) 50 | grep -q "12586269025" && echo "n=50 passed"
	@echo ""
	@echo "=== Тестирование неверных аргументов ==="
	@./$(TARGET) abc 2>&1 | grep -q "Ошибка" && echo "invalid string passed"
	@./$(TARGET) -5 2>&1 | grep -q "Ошибка" && echo "negative passed"
	@./$(TARGET) 100 2>&1 | grep -q "Ошибка" && echo "too large passed"

# Очистка
clean:
	rm -f $(TARGET) $(TEST_TARGET)
	@echo "✓ Очистка завершена"

# Проверка зависимостей
check:
	@command -v $(CXX) >/dev/null 2>&1 || { echo "✗ Ошибка: $(CXX) не установлен"; exit 1; }
	@echo "✓ Компилятор $(CXX) установлен"

.PHONY: all run run-arg test test-cli clean check
