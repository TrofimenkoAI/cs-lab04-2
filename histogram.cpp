#include<vector>
#include"histogram.h"
#include<iostream>

using namespace std;


void find_minmax (const vector<double>& numbers, double& min, double& max) {
    if (numbers.size() != 0)
    {
        min = numbers[0];
        max = numbers[0];
        for (double number : numbers) {
        if (number < min) {
            min = number;
        }
        if (number > max) {
            max = number;
        }
        }
    }
}
vector<size_t> make_histogram(const Input& data) {
    vector<size_t> result(data.bin_count);
    double min;
    double max;
    find_minmax(data.numbers, min, max);
    for (double number : data.numbers) {
        size_t bin = (size_t)((number - min) / (max - min) * data.bin_count);
        if (bin == data.bin_count) {
            bin--;
        }
        result[bin]++;
    }

    return result;
}

string custome_width(double width, double BLOCK_WIDTH, size_t number_count, size_t min, size_t max) {
    stringstream str;
    if (width < min)
        str << "Width < " << min << ". Enter the width again:";
    else if (width > max)
        str << "Width > " << max << ". Enter the width again:";
    else if (width < BLOCK_WIDTH*number_count/3)
        str << "Width < number_count/3. Enter the width again:";

    return str.str();
}

void show_histogram_text(const vector<size_t>& bins, Input& data) {
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 4 - 1;

    while (data.width < 7 || data.width > 80 || data.width  < data.number_count/3)
    {
        cerr << custome_width(SCREEN_WIDTH, 1, data.number_count, 7, 8);
        cin >> data.width;
    }

    size_t max_count = 0;
    for (size_t count : bins) {
        if (count > max_count) {
            max_count = count;
        }
    }
    const bool scaling_needed = max_count > MAX_ASTERISK;

    for (size_t bin : bins) {
        if (bin < 100) {
            cout << ' ';
        }
        if (bin < 10) {
            cout << ' ';
        }
        cout << bin << "|";

        size_t height = bin;
        if (scaling_needed) {
            const double scaling_factor = (double)MAX_ASTERISK / max_count;
            height = (size_t)(bin * scaling_factor);
        }

        for (size_t i = 0; i < height; i++) {
            cout << '*';
        }
        cout << '\n';
    }

}


