#ifndef HISTOGRAM_H_INCLUDED
#define HISTOGRAM_H_INCLUDED

#include<vector>
#include<string>
#include<sstream>


struct Input {
    std::vector<double> numbers;
    size_t bin_count;
    size_t number_count;
    double width;
};
void find_minmax (const std::vector<double>& numbers, double& min, double& max);

std::vector<size_t> make_histogram(const Input& data);

void show_histogram_text(std::vector<size_t> bins, Input& data);

std::string custome_width(double width, double BLOCK_WIDTH, size_t number_count, size_t min, size_t max);

#endif
