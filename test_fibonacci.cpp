#include <iostream>
#include <cassert>
#include <stdexcept>
#include <cstdlib>

class FibonacciCalculator {
public:
    static long long calculate(int n) {
        if (n < 0) throw std::invalid_argument("n < 0");
        if (n > 50) throw std::invalid_argument("n > 50");
        
        if (n == 0) return 0;
        if (n == 1) return 1;
        
        long long prev = 0, curr = 1;
        for (int i = 2; i <= n; ++i) {
            long long next = prev + curr;
            prev = curr;
            curr = next;
        }
        return curr;
    }
};

void test_basic() {
    std::cout << "Test 1: Basic values... ";
    assert(FibonacciCalculator::calculate(0) == 0);
    assert(FibonacciCalculator::calculate(1) == 1);
    assert(FibonacciCalculator::calculate(2) == 1);
    assert(FibonacciCalculator::calculate(3) == 2);
    std::cout << "OK" << std::endl;
}

void test_known() {
    std::cout << "Test 2: Known values... ";
    assert(FibonacciCalculator::calculate(5) == 5);
    assert(FibonacciCalculator::calculate(10) == 55);
    assert(FibonacciCalculator::calculate(15) == 610);
    assert(FibonacciCalculator::calculate(20) == 6765);
    std::cout << "OK" << std::endl;
}

void test_edge() {
    std::cout << "Test 3: Edge values... ";
    assert(FibonacciCalculator::calculate(0) == 0);
    assert(FibonacciCalculator::calculate(50) == 12586269025LL);
    std::cout << "OK" << std::endl;
}

void test_negative() {
    std::cout << "Test 4: Negative input... ";
    try {
        FibonacciCalculator::calculate(-1);
        assert(false);
    } catch (const std::invalid_argument&) {
        std::cout << "OK" << std::endl;
    }
}

void test_too_large() {
    std::cout << "Test 5: Too large input... ";
    try {
        FibonacciCalculator::calculate(51);
        assert(false);
    } catch (const std::invalid_argument&) {
        std::cout << "OK" << std::endl;
    }
}

void test_performance() {
    std::cout << "Test 6: Performance (calculating 0-50)... ";
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i <= 50; ++i) {
        FibonacciCalculator::calculate(i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "OK (" << duration.count() << " ms)" << std::endl;
}

// Тесты через запуск программы с аргументами командной строки
void test_command_line() {
    std::cout << "Test 7: Command line arguments... ";
    
    // Тест с аргументом 10
    std::string cmd = "./fibonacci 10";
    int result = system(cmd.c_str());
    assert(result == 0);
    
    std::cout << "OK" << std::endl;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "  Запуск тестов Fibonacci Calculator" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;
    
    test_basic();
    test_known();
    test_edge();
    test_negative();
    test_too_large();
    test_performance();
    
    std::cout << std::endl;
    std::cout << "=================================" << std::endl;
    std::cout << "  Все тесты пройдены успешно!" << std::endl;
    std::cout << "=================================" << std::endl;
    
    return 0;
}
