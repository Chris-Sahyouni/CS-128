#include "elevation_dataset.hpp"

#include <cstdlib>  // for size_t
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

ElevationDataset::ElevationDataset(const std::string& filename,
                                   size_t width,
                                   size_t height):
    width_(width), height_(height) {
  if (width < 1 || height < 1)
    throw std::invalid_argument("width and/or height was passed as < 1");
  std::ifstream ifs(filename);
  if (!ifs.is_open()) throw std::runtime_error("input file not open");
  int running_max = std::numeric_limits<int>::min();
  int running_min = std::numeric_limits<int>::max();

  unsigned int i = 0;
  std::vector<int> elevation_data_row;

  while (ifs.good()) {
    int datum = 0;
    ifs >> datum;
    if (!ifs) break;
    if (datum > running_max) {
      running_max = datum;
    }
    if (datum < running_min) {
      running_min = datum;
    }
    elevation_data_row.push_back(datum);
    ++i;
    if (i % width == 0) {
      data_.push_back(elevation_data_row);
      elevation_data_row.clear();
    }
  }
  data_.push_back(elevation_data_row);

  max_ele_ = running_max;
  min_ele_ = running_min;
  if (width * height != i) {
    throw std::runtime_error(
        "The amount of data was not equal to the width times height");
  }
}

size_t ElevationDataset::Width() const { return width_; }
size_t ElevationDataset::Height() const { return height_; }
int ElevationDataset::MaxEle() const { return max_ele_; }
int ElevationDataset::MinEle() const { return min_ele_; }

int ElevationDataset::DatumAt(size_t row, size_t col) const {
  if (row < 0 || row > height_ - 1 || col < 0 || col > width_ - 1) {
    throw std::invalid_argument("Args passed to DatumAt() were out of range");
  }
  return data_.at(row).at(col);
}

const std::vector<std::vector<int>>& ElevationDataset::GetData() const {
  return data_;
}