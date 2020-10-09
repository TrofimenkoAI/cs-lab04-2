#ifndef SVG_H_INCLUDED
#define SVG_H_INCLUDED

#include <vector>
#include <string>
#include"histogram.h"
#include <windows.h>


void svg_begin(double width, double height);
void svg_end();
void svg_text(double left, double baseline, size_t text);
void svg_rect(double x, double y, double width, double height, std::string stroke = "black", std::string fill = "black");
void show_histogram_svg(const std::vector<size_t>& bins, size_t number_count, char computer_name[], DWORD version_major, DWORD version_minor, DWORD build);
std::string custome_width(double IMAGE_WIDTH,double BLOCK_WIDTH,size_t number_count);

#endif // SVG_H_INCLUDED

