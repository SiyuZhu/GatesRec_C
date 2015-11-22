#include "images.h"
#include "typedefs.h"
#include "cnn.h"
#include "utils/read_mnist.h"

#include <iostream>
#include <vector>

int main ( int argc, char **argv ) {

  // Read mnist labels
  int count = 0;
  uint8_t* labels_raw = read_mnist_test_labels(count);
  int* in_labels = new int[count];
  for (int i=0; i<count; i++) {
    in_labels[i] = (int)labels_raw[i];
  } 

  // std::cout << "count=" << count << std::endl; 

  // Read mnist data and cast into 'Images' objects
  int in_rows, in_cols, in_number;
  image_raw_type* in_raw = \
		read_mnist_test_images ( in_number, in_rows, in_cols );
	image_type* in_data = new image_type[in_number*in_rows*in_cols];
	for ( int i=0; i<in_number*in_rows*in_cols; i++ ) {
		in_data[i] = (image_type) in_raw[i];
	}

  std::vector<Images> in_imgs;
  for ( int i=0; i<in_number; i++ ) {
    Images im(1, in_rows, in_cols, in_data + i * in_rows * in_cols);
    in_imgs.push_back(im);
  }

  int correct = 0;
  for ( int i=0; i<300; i++ ) {
    //in_imgs[i].print();
    std::cout << "label: " << in_labels[i] << ", predicted: " << cnn(in_imgs[i]) << " -- ";
    if ( in_labels[i] == cnn(in_imgs[i]) ) {
      correct++;
      std::cout << "Hit! " << correct << "/" << i+1 << std::endl;
    }
    else {
      std::cout << "Miss! " << std::endl;
    }
  }
  float rate = (float) correct / 300;

  std::cout << "Accuracy = " << rate << std::endl;

	return 0; 
}

