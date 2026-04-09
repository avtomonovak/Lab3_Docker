#include <iostream>
#include <string>
#include <cctype>
#include <chrono>
#include <stdexcept>

class FibonacciCalculator {
public:
    static long long calculate(int n) {
        if (n < 0) {
            throw std::invalid_argument("Число не может быть отрицательным");
        }
        if (n > 50) {
            throw std::invalid_argument("Число слишком велико (максимум 50)");
        }
        
        if (n == 0) return 0;
        if (n == 1) return 1;
        
        long long prev = 0;
        long long curr = 1;
        long long next;
        
        for (int i = 2; i <= n; ++i) {
            next = prev + curr;
            prev = curr;
            curr = next;
        }
        
        return curr;
    }
    
    static bool isValidNumber(const std::string& str, int& result) {
        if (str.empty()) return false;
        
        for (char c : str) {
            if (!std::isdigit(c)) {
                return false;
            }
        }
        
        try {
            result = std::stoi(str);
            return true;
        } catch (const std::exception&) {
            return false;
        }
    }
};

// Функция для режима с аргументами командной строки
int runWithArgs(int argc, char* argv[]) {
    if (argc != 2) return 0;  // не наш случай
    
    std::string arg = argv[1];
    int n = 0;  // ИНИЦИАЛИЗИРУЕМ переменную!
    
    if (FibonacciCalculator::isValidNumber(arg, n)) {
        try {
            auto start = std::chrono::high_resolution_clock::now();
            long long result = FibonacciCalculator::calculate(n);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            
            std::cout << result << std::endl;
            
        } catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << std::endl;
            return 1;
        }
    } else {
        std::cerr << "Ошибка: '" << arg << "' не является целым неотрицательным числом" << std::endl;
        return 1;
    }
    return 0;
}

// Интерактивный режим
int runInteractive() {
    std::cout << "========================================" << std::endl;
    std::cout << "  Программа вычисления чисел Фибоначчи" << std::endl;
    std::cout << "  Вариант 1: Последовательность Фибоначчи" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;
    
    std::string input;
    int n = 0;  // ИНИЦИАЛИЗИРУЕМ переменную!
    
    while (true) {
        std::cout << "Введите целое неотрицательное число n (0-50): ";
        
        if (!std::getline(std::cin, input)) {
            break;
        }
        
        if (input.empty()) {
            std::cout << "Ошибка: Ввод не может быть пустым!" << std::endl;
            continue;
        }
        
        if (input == "q" || input == "quit" || input == "exit") {
            std::cout << "До свидания!" << std::endl;
            break;
        }
        
        if (FibonacciCalculator::isValidNumber(input, n)) {
            if (n >= 0 && n <= 50) {
                try {
                    auto start = std::chrono::high_resolution_clock::now();
                    long long result = FibonacciCalculator::calculate(n);
                    auto end = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                    
                    std::cout << "Fibonacci(" << n << ") = " << result << std::endl;
                    std::cout << "Время: " << duration.count() << " мкс" << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << "Ошибка: " << e.what() << std::endl;
                }
            } else {
                std::cout << "Ошибка: Число должно быть в диапазоне от 0 до 50!" << std::endl;
            }
        } else {
            std::cout << "Ошибка: Введите целое неотрицательное число!" << std::endl;
        }
        std::cout << std::endl;
    }
    
    return 0;
}

int main(int argc, char* argv[]) {
    // Режим 1: Аргумент командной строки (для CI/CD)
    if (argc == 2) {
        return runWithArgs(argc, argv);
    }
    
    // Режим 2: Интерактивный режим
    if (argc > 2) {
        std::cout << "Использование: " << argv[0] << " [n]" << std::endl;
        std::cout << "  n - вычислить n-е число Фибоначчи" << std::endl;
        return 1;
    }
    
    return runInteractive();
}
