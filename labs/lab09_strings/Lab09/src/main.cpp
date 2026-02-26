#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>
#include <vector>

// Lab 09

int main() {
    // Упражнеие 1.
    
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
    int word_count = 0;
    if (!(std::cin >> word_count) || word_count > 20) {
        return 0;
    }
    std::cin.ignore();
    char **fr_array_words;
    fr_array_words = new char* [word_count];
    for (int i = 0; i < word_count; i++) {
        fr_array_words[i] = new char[10];
        std::cin.getline(fr_array_words[i], 10);
    }
    for (int i = 1; i < word_count; i = i + 2) std::cout << fr_array_words[i] << " ";
    std::cout << "\n";
    int word_count_2 = 0;
    if (!(std::cin >> word_count_2) || word_count_2 > 20) {
        return 0;
    }
    std::cin.ignore();
    std::string fr_array_strings[20];
    for (int i = 0; i < word_count_2; i++) {
        getline(std::cin, fr_array_strings[i]);
    }
    for (int i = 1; i < word_count_2; i = i + 2) std::cout << fr_array_strings[i] << " ";
    std::cout << "\n";
    return 0;
}
