#ifndef PATH_IMAGE_H
#define PATH_IMAGE_H

#include <cstdlib>  // for size_t
#include <vector>
#include <string>

#include "color.hpp"
#include "path.hpp"
#include "grayscale_image.hpp"
#include "elevation_dataset.hpp"

class PathImage {
public:
  // write behavior declarations here; define in path_image.cc.

PathImage(const GrayscaleImage &image, const ElevationDataset &dataset);
size_t Width() const;
size_t Height() const;
unsigned int MaxColorValue() const;
const std::vector<Path>& Paths() const;
const std::vector<std::vector<Color> >& GetPathImage() const;
void ToPpm(const std::string& name) const;
void CreatePath(const ElevationDataset& dataset, size_t starting_row);
int ChooseStep(size_t row, size_t col, const ElevationDataset& dataset);
void ColorImage(const GrayscaleImage& image, size_t best_path_row);
const Color& ColorAt(int row, int col) const;

private:
   std::vector<Path> paths_;
   size_t width_ = 0;
   size_t height_ = 0;
   std::vector<std::vector<Color>> path_image_;
   static const int kMaxColorValue = 255;
};

#endif