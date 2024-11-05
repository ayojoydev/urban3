#include <iostream>
#include <vector>

using namespace std;

// Словарь сегментов для цифр от 0 до 9
const vector<int> digit_segments = {
    0b1110111, // 0
    0b0010010, // 1
    0b1011101, // 2
    0b1011011, // 3
    0b0111010, // 4
    0b1101011, // 5
    0b1101111, // 6
    0b1010010, // 7
    0b1111111, // 8
    0b1111011  // 9
};

bool can_display(int faulty, int segment) {
    // Проверяет, может ли сломанный сегмент (faulty) отобразить данный сегмент (segment)
    return (faulty & segment) == segment;
}

int main() {
    string first, second;
    cin >> first >> second;

    int first_segments = 0;
    int second_segments = 0;

    // Преобразуем входные данные в 7-битовые представления
    for (int i = 0; i < 7; i++) {
        if (first[i] == '1') first_segments |= (1 << (6 - i));
        if (second[i] == '1') second_segments |= (1 << (6 - i));
    }

    int max_k = 0;

    // Проверяем все значения y от 99 до 1
    for (int y = 99; y >= 1; y--) {
        bool valid = true;

        // Проверяем последовательности y, y-1, ..., y-k
        for (int k = 0; k < 99; k++) {
            int current = y - k;
            if (current < 1) break; // Вышли за границы
            // Получаем цифры
            int first_digit = current / 10;
            int second_digit = current % 10;

            // Проверяем, могут ли индикаторы отобразить цифры
            if (!can_display(first_segments, digit_segments[first_digit]) ||
                !can_display(second_segments, digit_segments[second_digit])) {
                valid = false;
                break; // Прерываем, если хотя бы одна цифра не отображается
            }
        }

        // Если последовательность для данного y была валидной
        if (valid) {
            max_k = max(max_k, 99 - y); // Находим максимальное k
        }
    }

    cout << max_k << endl;
    return 0;
}
