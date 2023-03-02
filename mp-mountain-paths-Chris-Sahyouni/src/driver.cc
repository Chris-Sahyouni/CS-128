#include <iostream>

#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path_image.hpp"

int main() {
    ElevationDataset dataset("/home/vagrant/src/mp-mountain-paths-Chris-Sahyouni/example-data/ex_input_data/map-input-w480-h480.dat",
    480, 480);
    GrayscaleImage gs(dataset);
    gs.ToPpm("output.ppm");
    PathImage pathim(gs, dataset);
    pathim.ToPpm("/home/vagrant/src/mp-mountain-paths-Chris-Sahyouni/example-data/ex_output_paths/output_path.ppm");
}