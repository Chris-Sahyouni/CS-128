#include "path_image.hpp"

#include <cstdlib>  // for size_t
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

#include "color.hpp"
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"

PathImage::PathImage(const GrayscaleImage& image,
                     const ElevationDataset& dataset) {
  width_ = image.Width();
  height_ = image.Height();
  unsigned int best_ele_change = std::numeric_limits<int>::max();
  size_t best_row = 0;
  for (size_t row = 0; row < dataset.Height(); ++row) {
    CreatePath(dataset, row);
    if (paths_.at(row).EleChange() < best_ele_change) {
      best_ele_change = paths_.at(row).EleChange();
      best_row = row;
    }
  }
  ColorImage(image, best_row);
}

size_t PathImage::Width() const { return width_; }
size_t PathImage::Height() const { return height_; }
unsigned int PathImage::MaxColorValue() const { return kMaxColorValue; }
const std::vector<Path>& PathImage::Paths() const { return paths_; }
const std::vector<std::vector<Color>>& PathImage::GetPathImage() const {
  return path_image_;
}

void PathImage::ToPpm(const std::string& name) const {
  std::ofstream ofs{name};
  if (!ofs.is_open()) {
    throw std::runtime_error("PPM was not open for Pathimage to write to");
  }
  ofs << "P3" << std::endl;
  ofs << width_ << " " << height_ << std::endl;
  ofs << kMaxColorValue << std::endl;
  for (size_t row = 0; row < height_; ++row) {
    for (size_t col = 0; col < width_; ++col) {
      Color color = ColorAt(row, col);
      ofs << color.Red() << " " << color.Green() << " " << color.Blue() << " ";
    }
    ofs << std::endl;
  }
  ofs.close();
}

void PathImage::CreatePath(const ElevationDataset& dataset,
                           size_t starting_row) {
  Path path(dataset.Width(), starting_row);
  // std::cout << "New Path" << std::endl;
  size_t current_row = starting_row;
  // this loop might miss the last element so be careful!!!
  size_t col = 0;
  for (; col < width_ - 1; ++col) {
    path.SetLoc(col, current_row);
    // std::cout << path.GetPath().at(col) << std::endl;
    int direction = ChooseStep(current_row, col, dataset);
    int next_ele = dataset.DatumAt(current_row + direction, col + 1);
    int current_ele = dataset.DatumAt(current_row, col);
    int ele_step_change = abs(next_ele - current_ele);
    path.IncEleChange(ele_step_change);
    current_row += direction;
  }
  //  std::cout << "last row, col: " << current_row << " " << col << std::endl;
  path.SetLoc(col, current_row);
  paths_.push_back(path);
}

// will return -1 for northeast, 0 for east, 1 for southeast
int PathImage::ChooseStep(size_t row,
                          size_t col,
                          const ElevationDataset& dataset) {
  unsigned int northeast_diff = 0;
  unsigned int east_diff = 0;
  unsigned int southeast_diff = 0;
  if (row > 0) {
    northeast_diff =
        abs(dataset.DatumAt(row - 1, col + 1) - dataset.DatumAt(row, col));
  }
  east_diff = abs(dataset.DatumAt(row, col + 1) - dataset.DatumAt(row, col));
  if (row < dataset.Height() - 1) {
    southeast_diff =
        abs(dataset.DatumAt(row + 1, col + 1) - dataset.DatumAt(row, col));
  }

  // these check the first and last row cases
  if (row == 0) {
    if (east_diff <= southeast_diff) {
      return 0;
    }
    return 1;
  }
  if (row == dataset.Height() - 1) {
    if (east_diff <= northeast_diff) {
      return 0;
    }
    return -1;
  }

  // regular cases
  if (northeast_diff < east_diff && northeast_diff < southeast_diff) {
    return -1;
  }
  if (southeast_diff <= northeast_diff && southeast_diff < east_diff) {
    return 1;
  }
  return 0;
}

void PathImage::ColorImage(const GrayscaleImage& image, size_t best_path_row) {
  path_image_ = image.GetImage();
  const int kRr = 252;
  const int kRg = 25;
  const int kRb = 63;
  Color red(kRr, kRg, kRb);
  const int kGr = 31;
  const int kGg = 253;
  const int kGb = 13; 
  Color green(kGr, kGg, kGb);
  for (const Path& p : paths_) {
    for (size_t col = 0; col < width_; ++col) {
      path_image_.at(p.GetPath().at(col)).at(col) = red;
    }
  }
  for (const Path& p : paths_) {
    if (p.StartingRow() == best_path_row) {
      for (size_t col = 0; col < width_; ++col) {
        path_image_.at(p.GetPath().at(col)).at(col) = green;
      }
    }
  }
  // for (const Path& p : paths_) {
  //   Color color(252, 25, 63);
  //   if (p.StartingRow() == best_path_row) {
  //     color = Color(31, 253, 13);
  //   }
  //   for (size_t col = 0; col < width_; ++col) {
  //     path_image_.at(p.GetPath().at(col)).at(col) = color;
  //   }
  // }
}

const Color& PathImage::ColorAt(int row, int col) const {
  return path_image_.at(row).at(col);
}
