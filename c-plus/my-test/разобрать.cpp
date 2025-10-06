#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>

class String {
    char* data;
    size_t length;

    void free_memory() {
        if (data) {
            delete[] data;
            data = nullptr;
            length = 0;
        }
    }

    void copy_from(const char* str, size_t len) {
        free_memory();
        if (len > 0) {
            data = new char[len + 1];
            std::memcpy(data, str, len);
            data[len] = '\0';
            length = len;
        }
    }

public:
    // Конструкторы
    String() : data(nullptr), length(0) {}
    
    String(const char* str) {
        size_t len = str ? std::strlen(str) : 0;
        copy_from(str, len);
    }
    
    // Конструктор копирования
    String(const String& other) {
        copy_from(other.data, other.length);
    }
    
    // Move-конструктор
    String(String&& other) noexcept 
        : data(other.data), length(other.length) {
        other.data = nullptr;
        other.length = 0;
    }
    
    // Деструктор
    ~String() {
        free_memory();
    }
    
    // Оператор присваивания
    String& operator=(const String& other) {
        if (this != &other) {
            copy_from(other.data, other.length);
        }
        return *this;
    }
    
    // Move-оператор присваивания
    String& operator=(String&& other) noexcept {
        if (this != &other) {
            free_memory();
            data = other.data;
            length = other.length;
            other.data = nullptr;
            other.length = 0;
        }
        return *this;
    }
    
    // Оператор +=
    String& operator+=(const String& other) {
        if (other.length > 0) {
            char* new_data = new char[length + other.length + 1];
            if (length > 0) {
                std::memcpy(new_data, data, length);
            }
            std::memcpy(new_data + length, other.data, other.length);
            new_data[length + other.length] = '\0';
            free_memory();
            data = new_data;
            length += other.length;
        }
        return *this;
    }
    
    // Оператор += для C-строк
    String& operator+=(const char* str) {
        if (str) {
            size_t str_len = std::strlen(str);
            if (str_len > 0) {
                char* new_data = new char[length + str_len + 1];
                if (length > 0) {
                    std::memcpy(new_data, data, length);
                }
                std::memcpy(new_data + length, str, str_len);
                new_data[length + str_len] = '\0';
                free_memory();
                data = new_data;
                length += str_len;
            }
        }
        return *this;
    }
    
    // Получение C-строки
    const char* c_str() const {
        return data ? data : "";
    }
    
    // Получение длины
    size_t size() const {
        return length;
    }
    
    // Оператор сравнения для сортировки
    bool operator<(const String& other) const {
        if (!data) return other.data != nullptr;
        if (!other.data) return false;
        return std::strcmp(data, other.data) < 0;
    }
    
    // Оператор вывода
    friend std::ostream& operator<<(std::ostream& os, const String& str) {
        return os << (str.data ? str.data : "");
    }
};

// Внешний оператор сложения
String operator+(const String& lhs, const String& rhs) {
    String result(lhs);
    result += rhs;
    return result;
}

// Внешний оператор сложения для C-строк
String operator+(const String& lhs, const char* rhs) {
    String result(lhs);
    result += rhs;
    return result;
}

// Функция сравнения без учета регистра для сортировки
bool case_insensitive_compare(const String& a, const String& b) {
    const char* str1 = a.c_str();
    const char* str2 = b.c_str();
    
    while (*str1 && *str2) {
        char c1 = std::tolower(*str1);
        char c2 = std::tolower(*str2);
        if (c1 != c2) {
            return c1 < c2;
        }
        str1++;
        str2++;
    }
    return *str1 < *str2;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " string1 string2 ... stringN\n";
        return 1;
    }

    std::vector<String> strings;
    for (int i = 1; i < argc; ++i) {
        strings.emplace_back(argv[i]);
    }

    // Сортировка в обратном лексикографическом порядке без учета регистра
    std::sort(strings.begin(), strings.end(), [](const String& a, const String& b) {
        return !case_insensitive_compare(a, b);
    });

    // Вывод результатов
    for (const auto& str : strings) {
        std::cout << str << '\n';
    }

    return 0;
}