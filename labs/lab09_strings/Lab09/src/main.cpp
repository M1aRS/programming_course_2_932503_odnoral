#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>
#include <vector>

// Lab 09

int main() {
    // Упражнеие 1.
    int word_count = 0;
    char f_first_word[200]; char f_second_word[200];
    std::cin.getline(f_first_word, 200);
    std::cout << "Length: " << strlen(f_first_word) << "\n";
    std::cin.getline(f_second_word, 200);
    if (strcmp(f_first_word, f_second_word) == 0) { std::cout << f_first_word << " == " << f_second_word << "\n"; }
    else { std::cout << f_first_word << " != " << f_second_word << "\n"; }
    std::cout << f_first_word << " + " << f_second_word << " = "; std::cout << strcat(f_first_word, f_second_word) << "\n";

    std::string f_first_string, f_second_string, f_temp_string;
    std::getline(std::cin, f_first_string);
    int len1 = f_first_string.length(); int len2 = f_second_string.length();
    std::cout << "Length: " << len1 << "\n";  std::getline(std::cin, f_second_string);
    f_temp_string = f_first_string; f_temp_string.append(" with " + f_second_string);
    std::cout << f_temp_string << "\n";
    std::cout << f_temp_string.substr(0, len1 + len2 - 1) << "\n";

    // Упражнение 4: ввод количества слов и самих слов.
    if (!(std::cin >> word_count)) {
        return 0;
    }

    std::vector<std::string> words;
    words.reserve(word_count);
    for (int i = 0; i < word_count; ++i) {
        std::string word;
        std::cin >> word;
        words.push_back(word);
    }
    
    // TODO: выведите слова с четными номерами (2, 4, 6, ...), по одному в строке.
    return 0;
}
