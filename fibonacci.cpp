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

/**
 * Вычисляет число Фибоначчи и выводит результат
 * Возвращает 0 при успехе, 1 при ошибке
 */
int runWithArgs(int argc, char* argv[]) {
    int n;
    
    // Если передан аргумент командной строки - используем его
    if (argc > 1) {
        std::string arg = argv[1];
        if (FibonacciCalculator::isValidNumber(arg, n)) {
            if (n >= 0 && n <= 50) {
                long long result = FibonacciCalculator::calculate(n);
                std::cout << result << std::endl;
                return 0;
            } else {
                std::cerr << "Ошибка: Число должно быть в диапазоне от 0 до 50!" << std::endl;
                return 1;
            }
        } else {
            std::cerr << "Ошибка: Введите целое неотрицательное число!" << std::endl;
            return 1;
        }
    }
    
    // Интерактивный режим (для пользователя)
    std::string input;
    
    while (true) {
        std::cout << "Введите целое неотрицательное число n (0-50): ";
        
        if (!std::getline(std::cin, input)) {
            // Если достигнут конец ввода (например, при перенаправлении)
            break;
        }
        
        if (input.empty()) {
            std::cout << "Ошибка: Ввод не может быть пустым!" << std::endl;
            continue;
        }
        
        if (FibonacciCalculator::isValidNumber(input, n)) {
            if (n >= 0 && n <= 50) {
                break;
            } else {
                std::cout << "Ошибка: Число должно быть в диапазоне от 0 до 50!" << std::endl;
            }
        } else {
            std::cout << "Ошибка: Введите целое неотрицательное число!" << std::endl;
        }
    }
    
    try {
        auto start = std::chrono::high_resolution_clock::now();
        long long result = FibonacciCalculator::calculate(n);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << std::endl;
        std::cout << "Результат вычислений:" << std::endl;
        std::cout << "  Fibonacci(" << n << ") = " << result << std::endl;
        std::cout << "  Время вычисления: " << duration.count() << " микросекунд" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}

int main(int argc, char* argv[]) {
    std::cout << "========================================" << std::endl;
    std::cout << "  Программа вычисления чисел Фибоначчи" << std::endl;
    std::cout << "  Вариант 1: Последовательность Фибоначчи" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;
    
    return runWithArgs(argc, argv);
}
