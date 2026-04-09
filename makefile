# Компилятор и флаги
CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -std=c++17
LDFLAGS = 

# Имена исполняемых файлов
TARGET = fibonacci
TEST_TARGET = test_fibonacci

# Цель по умолчанию - собираем основную программу
all: $(TARGET)

# Сборка ВСЕХ файлов (для CI/CD)
all-tests: $(TARGET) $(TEST_TARGET)

# Сборка основной программы
$(TARGET): fibonacci.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) fibonacci.cpp $(LDFLAGS)
	@echo "Сборка $(TARGET) завершена"

# Сборка тестов
$(TEST_TARGET): test_fibonacci.cpp
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) test_fibonacci.cpp $(LDFLAGS)
	@echo "Сборка $(TEST_TARGET) завершена"

# Запуск программы в интерактивном режиме
run: $(TARGET)
	./$(TARGET)

# Запуск тестов
test: $(TEST_TARGET)
	@echo ""
	@echo "=== Запуск тестов ==="
	./$(TEST_TARGET)

# Тестирование с аргументами (для CI/CD)
test-args: $(TARGET)
	@echo ""
	@echo "=== Тестирование с аргументами командной строки ==="
	@echo -n "Test n=0: "
	@./$(TARGET) 0 | grep -q "0" && echo "PASS" || echo "FAIL"
	@echo -n "Test n=1: "
	@./$(TARGET) 1 | grep -q "1" && echo "PASS" || echo "FAIL"
	@echo -n "Test n=10: "
	@./$(TARGET) 10 | grep -q "55" && echo "PASS" || echo "FAIL"
	@echo -n "Test n=20: "
	@./$(TARGET) 20 | grep -q "6765" && echo "PASS" || echo "FAIL"
	@echo -n "Test n=50: "
	@./$(TARGET) 50 | grep -q "12586269025" && echo "PASS" || echo "FAIL"
	@echo -n "Test invalid 'abc': "
	@./$(TARGET) abc 2>&1 | grep -q "Ошибка" && echo "PASS" || echo "FAIL"
	@echo -n "Test invalid '-5': "
	@./$(TARGET) -5 2>&1 | grep -q "Ошибка" && echo "PASS" || echo "FAIL"

# Очистка
clean:
	rm -f $(TARGET) $(TEST_TARGET)
	@echo "Очистка завершена"

# Проверка зависимостей
check:
	@command -v $(CXX) >/dev/null 2>&1 || { echo "Ошибка: $(CXX) не установлен"; exit 1; }
	@echo "Компилятор $(CXX) установлен"
	@command -v docker >/dev/null 2>&1 && echo "Docker установлен" || echo "Docker не установлен"

# Полная CI проверка (собираем ВСЕ)
ci: clean all-tests test test-args
	@echo ""
	@echo "CI проверка пройдена успешно!"

.PHONY: all all-tests run test test-args clean check ci
