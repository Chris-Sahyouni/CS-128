#include "seam_carver.hpp"

#include "image_ppm.hpp"

// implement the rest of SeamCarver's functions here

const ImagePPM& SeamCarver::GetImage() const { return image_; }
int SeamCarver::GetHeight() const { return height_; }
int SeamCarver::GetWidth() const { return width_; }

int SeamCarver::GetEnergy(int row, int col) const {

  Pixel left(0, 0, 0);
  if (col > 0)
    left = image_.GetPixel(row, col - 1);
  else
    left = image_.GetPixel(row, image_.GetWidth() - 1);

  Pixel right = image_.GetPixel(row, (col + 1) % image_.GetWidth());

  Pixel up(0, 0, 0);
  if (row > 0)
    up = image_.GetPixel(row - 1, col);
  else
    up = image_.GetPixel(image_.GetHeight() - 1, col);

  Pixel down = image_.GetPixel((row + 1) % image_.GetHeight(), col);

  int vert_red = up.GetRed() - down.GetRed();
  int vert_green = up.GetGreen() - down.GetGreen();
  int vert_blue = up.GetBlue() - down.GetBlue();

  int delta_vert = (vert_red * vert_red) + (vert_green * vert_green) +
                   (vert_blue * vert_blue);

  int horiz_red = left.GetRed() - right.GetRed();
  int horiz_green = left.GetGreen() - right.GetGreen();
  int horiz_blue = left.GetBlue() - right.GetBlue();

  int delta_horiz = (horiz_red * horiz_red) + (horiz_green * horiz_green) +
                    (horiz_blue * horiz_blue);

  return delta_horiz + delta_vert;
}

int* SeamCarver::GetHorizontalSeam() const {
  int** energy_array = GetEnergyArray();
  if (height_ > 1) {
    ConvertToHorizontalSeamArray(energy_array);
  }
  return TraceHorizontalSeam(energy_array);
}

void SeamCarver::ConvertToHorizontalSeamArray(int**& energy_array) const {
  for (int col = width_ - 2; col >= 0; --col) {
    for (int row = 0; row < height_; ++row) {
      std::initializer_list<int> adjacent_energies;
      if (row == 0) {
        adjacent_energies = {energy_array[row][col],
                             energy_array[row + 1][col + 1]};
      } else if (row == height_ - 1) {
        adjacent_energies = {energy_array[row - 1][col + 1],
                             energy_array[row][col + 1]};
      } else {
        adjacent_energies = {energy_array[row - 1][col + 1],
                             energy_array[row][col + 1],
                             energy_array[row + 1][col + 1]};
      }
      energy_array[row][col] += std::min(adjacent_energies);
    }
  }
}

int** SeamCarver::GetEnergyArray() const {
  const int kH = height_;
  const int kW = width_;
  int** energy_array = new int*[kH];
  for (int row = 0; row < height_; ++row) {
    energy_array[row] = new int[kW];
    for (int col = 0; col < width_; ++col) {
      energy_array[row][col] = GetEnergy(row, col);
    }
  }
  return energy_array;
}

void SeamCarver::DestroyEnergyArray(int**& energy_array) const {
  for (int row = 0; row < height_; ++row) {
    delete[] energy_array[row];
  }
  delete[] energy_array;
}

void SeamCarver::ConvertToVerticalSeamArray(int**& energy_array) const {
  for (int row = height_ - 2; row >= 0; --row) {
    for (int col = 0; col < width_; ++col) {
      std::initializer_list<int> adjacent_energies;
      if (col == 0) {
        adjacent_energies = {energy_array[row + 1][col],
                             energy_array[row + 1][col + 1]};
      } else if (col == width_ - 1) {
        adjacent_energies = {energy_array[row + 1][col - 1],
                             energy_array[row + 1][col]};
      } else {
        adjacent_energies = {energy_array[row + 1][col - 1],
                             energy_array[row + 1][col],
                             energy_array[row + 1][col + 1]};
      }
      energy_array[row][col] += std::min(adjacent_energies);
    }
  }
}

int* SeamCarver::TraceHorizontalSeam(int**& energy_array) const {
  const int kW = width_;
  int* seam = new int[kW];
  int running_start_min = energy_array[0][0];
  seam[0] = 0;
  for (int row = 0; row < height_; ++row) {
    if (energy_array[row][0] < running_start_min) seam[0] = row;
  }
  for (int col = 1; col < width_; ++col) {
    int last_row_in_seam = seam[col - 1];
    if (last_row_in_seam == 0) {
      if (energy_array[0][col] <= energy_array[1][col]) {
        seam[col] = 0;
      } else {
        seam[col] = 1;
      }
    } else if (last_row_in_seam == height_ - 1) {
        if (energy_array[height_ - 1][col] <= energy_array[height_ - 2][col]) {
        seam[col] = height_ - 1;
      } else {
        seam[col] = height_ - 2;
      }
    } else {
      int offset = CompareThree(energy_array[last_row_in_seam - 1][col], energy_array[last_row_in_seam][col], energy_array[last_row_in_seam + 1][col]);
      seam[col] = last_row_in_seam + offset;
    }
  }
  DestroyEnergyArray(energy_array);
  return seam;
}

int* SeamCarver::TraceVerticalSeam(int**& energy_array) const {
  const int kH = height_;
  int* seam = new int[kH];
  int running_start_min = energy_array[0][0];
  seam[0] = 0;
  for (int col = 0; col < width_; ++col) {
    if (energy_array[0][col] < running_start_min) seam[0] = col;
  }
  for (int row = 1; row < height_; ++row) {
    int last_col_in_seam = seam[row - 1];
    if (last_col_in_seam == 0) {
      if (energy_array[row][0] <= energy_array[row][1]) {
        seam[row] = 0;
      } else {
        seam[row] = 1;
      }
    } else if (last_col_in_seam == width_ - 1) {
        if (energy_array[row][width_ - 1] <= energy_array[row][width_ - 2]) {
        seam[row] = width_ - 1;
      } else {
        seam[row] = width_ - 2;
      }
    } else {
      int offset = CompareThree(energy_array[row][last_col_in_seam - 1], energy_array[row][last_col_in_seam], energy_array[row][last_col_in_seam + 1]);
      seam[row] = last_col_in_seam + offset;
    }
  }
  DestroyEnergyArray(energy_array);
  return seam;
}

int* SeamCarver::GetVerticalSeam() const {
  int** energy_array = GetEnergyArray();
  ConvertToVerticalSeamArray(energy_array);
  return TraceVerticalSeam(energy_array);
}

int SeamCarver::CompareThree(int first, int second, int third) const {
  if (second <= first && second <= third) return 0;
  if (first < second && first <= third) return -1;
  return 1;
}

void SeamCarver::DestroyOldImage(ImagePPM& image) const {
  for (int row = 0; row < height_; ++row) {
    delete[] image.GetPixelRow(row);
  }
  if (image.GetPixelArray() != nullptr) delete[] image.GetPixelArray();
}


void SeamCarver::RemoveHorizontalSeam() {
  int* seam = GetHorizontalSeam();
  const int kH = height_ - 1;
  const int kW = width_;
  auto** carved = new Pixel*[kH];
  for (int row = 0; row < height_ - 1; ++row) {
    carved[row] = new Pixel[kW];
  }
  for (int col = 0; col < width_; ++col) {
    for (int row = 0; row < height_ - 1; ++row) {
      int skip_seam = 0;
      if (row >= seam[col]) ++skip_seam;
      carved[row][col] = image_.GetPixel(row + skip_seam, col); 
    }
  }

  delete[] seam;
  DestroyOldImage(image_);
  image_.SetPixels(carved);
  image_.SetHeight(height_ - 1);
  --height_;
}

void SeamCarver::RemoveVerticalSeam() {
  int* seam = GetVerticalSeam();
  const int kH = height_;
  const int kW = width_ - 1;
  auto** carved = new Pixel*[kH];
  for (int row = 0; row < height_; ++row) {
    carved[row] = new Pixel[kW];
    
    for (int col = 0; col < width_ - 1; ++col) {
        int skip_seam = 0;
        if (col >= seam[row]) ++skip_seam;
        carved[row][col] = image_.GetPixel(row, col + skip_seam); 
    }
  }

  delete[] seam;
  DestroyOldImage(image_);
  image_.SetPixels(carved);
  image_.SetWidth(width_ - 1);
  --width_;
}

// given functions below, DO NOT MODIFY

SeamCarver::SeamCarver(const ImagePPM& image): image_(image) {
  height_ = image.GetHeight();
  width_ = image.GetWidth();
}

void SeamCarver::SetImage(const ImagePPM& image) {
  image_ = image;
  width_ = image.GetWidth();
  height_ = image.GetHeight();
}
