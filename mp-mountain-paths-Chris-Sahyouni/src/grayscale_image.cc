#include "grayscale_image.hpp"

#include <cmath>
#include <cstdlib>  // for size_t
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "color.hpp"
#include "elevation_dataset.hpp"

GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) {
  width_ = dataset.Width();
  height_ = dataset.Height();
  ConstructImage(dataset);
}

GrayscaleImage::GrayscaleImage(const std::string& filename,
                               size_t width,
                               size_t height):
    width_(width), height_(height) {
  ElevationDataset dataset(filename, width, height);
  ConstructImage(dataset);
}

size_t GrayscaleImage::Width() const { return width_; }
size_t GrayscaleImage::Height() const { return height_; }
unsigned int GrayscaleImage::MaxColorValue() const { return kMaxColorValue; }

const Color& GrayscaleImage::ColorAt(int row, int col) const {
  return image_.at(row).at(col);
}

const std::vector<std::vector<Color>>& GrayscaleImage::GetImage() const {
  return image_;
}

void GrayscaleImage::ToPpm(const std::string& name) const {
  std::ofstream ofs{name};
  if (!ofs.is_open()) {
    throw std::runtime_error("PPM was not open for grayscale to write to");
  }
  ofs << "P3" << std::endl;
  ofs << width_ << " " << height_ << std::endl;
  ofs << kMaxColorValue << std::endl;
  for (unsigned int row = 0; row < height_; ++row) {
    for (unsigned int col = 0; col < width_; ++col) {
      Color color = ColorAt(row, col);
      ofs << color.Red() << " " << color.Green() << " " << color.Blue() << " ";
    }
    ofs << std::endl;
  }
  ofs.close();
}

void GrayscaleImage::ConstructImage(const ElevationDataset& dataset) {
  for (unsigned int row = 0; row < dataset.Height(); ++row) {
    std::vector<Color> row_vect;
    for (unsigned int col = 0; col < dataset.Width(); ++col) {
      int datum = dataset.DatumAt(row, col);
      if (dataset.MaxEle() == dataset.MinEle()) {
        row_vect.push_back(Color(0, 0, 0));
      } else {
        double min = dataset.MinEle();
        double max = dataset.MaxEle();
        int shade_of_gray = (int)std::round((datum - min) / (max - min) * kMaxColorValue);
        Color grayshade(shade_of_gray, shade_of_gray, shade_of_gray);
        row_vect.push_back(grayshade);
      }
    }
    image_.push_back(row_vect);
  }
}
