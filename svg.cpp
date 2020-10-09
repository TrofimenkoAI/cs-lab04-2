#include "svg.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

void svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_end() {
    cout << "</svg>\n";
}

void svg_text(double left, double baseline, size_t text) {
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text <<"</text>";
}

void svg_rect(double x, double y, double width, double height, string stroke, string fill) {
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "' />";
}

string custome_width(double width, double BLOCK_WIDTH, size_t number_count) {
    string str = "";
    if (width < 70)
        str = "Width < 70. Enter the width again:";
    else if (width > 800)
        str = "Width > 800. Enter the width again:";
    else if (width < BLOCK_WIDTH*number_count/3)
        str = "Width < BLOCK_WIDTH*number_count/3. Enter the width again:";

    return str;
}

void show_histogram_svg(const vector<size_t>& bins, size_t number_count, char computer_name[], DWORD version_major, DWORD version_minor, DWORD build) {
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const double BLOCK_WIDTH = 10;

    double IMAGE_WIDTH;

    cerr << "Enter width:";
    cin >> IMAGE_WIDTH;
    while (IMAGE_WIDTH < 70 || IMAGE_WIDTH > 800 || IMAGE_WIDTH  < BLOCK_WIDTH*number_count/3)
    {
        cerr << custome_width(IMAGE_WIDTH, BLOCK_WIDTH, number_count);
        cin >> IMAGE_WIDTH;
    }

    const size_t MAX_ASTERISK = IMAGE_WIDTH - TEXT_LEFT - TEXT_WIDTH;

    size_t max_count = 0;
    for (size_t count : bins) {
        if (count > max_count) {
            max_count = count;
        }
    }

    const bool scaling_needed = max_count * BLOCK_WIDTH > MAX_ASTERISK;

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);


    double top = 0;
    for (size_t bin : bins) {

        size_t height = bin;
        if (scaling_needed) {
            const double scaling_factor = (double)MAX_ASTERISK / (max_count * BLOCK_WIDTH);
            height = (size_t)(bin * scaling_factor);
        }

        const double bin_width = BLOCK_WIDTH * height;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, bin);
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "red", "green");
        top += BIN_HEIGHT;
    }
    cout << "<text x='" << left << "' y='" << top + TEXT_BASELINE << "'>Computer name: " << computer_name << "</text>";
    cout << "<text x='" << left << "' y='" << top + 2*TEXT_BASELINE << "'>Windows v" << version_major << "."
    << version_minor << " (build " << build << ")</text>";
    svg_end();
}
