#ifndef __CNN_H__
#define __CNN_H__

#include "images.h"
#include "kernels.h"
#include "convolution.h"
#include "maxpool.h"
#include "typedefs.h"
#include "utils/read_params.h"

#define FIRST_TWO_LAYERS 0
#define LAST_TWO_LAYERS  1

/*
// ********** PARAMETERS OVERVIEW *********  //
-------------+--------+--------+------+-------+
|            | BLOCKS | FRAMES | ROWS | COLS  |
+------------+------LAYER0-----+------+-------+
|L0_INPUT    |   --   |   1    |  28  |  28   |
|L0_KERNEL   |   20   |   1    |  5   |  5    |
|L0_OUTPUT_1 |   --   |   20   |  24  |  24   |
|L0_OUTPUT_2 |   --   |   20   |  12  |  12   |
+------------+------LAYER1------------+-------+
|L1_INPUT    |   --   |   20   |  12  |  12   |
|L1_KERNEL   |   50   |   20   |  5   |  5    |
|L1_OUTPUT_1 |   --   |   50   |  8   |  8    |
|L1_OUTPUT_2 |   --   |   50   |  4   |  4    |
+------------+--------+--------+------+-------+
+------------+--------+--------+------+-------+
|Serialize L1_OUTPUT_2 into L2_input [50*4*4] |
+------------+--------+--------+------+-------+
+------------+------LAYER2------------+-------+
|L2_INPUT    |Array[800] -> A: Matrix[1 x 800]|
|L2_KERNEL   |     K: Matrix[800 x 500]       |
|L2_OUTPUT   |Array[500] -> B=Matrix[1 x 500] |
|            |            B = A*K             | 
+------------+--------+--------+------+-------+
+------------+------LAYER3------------+-------+
|L3_INPUT    |Array[500] -> A: Matrix[1 x 500]|
|L3_KERNEL   |      K: Matrix[500 x 10]       |
|L3_OUTPUT   | Array[10] -> B=Matrix[1 x 10]  |
|            |            B = A*K             | 
+------------+--------+--------+------+-------+
*/

int cnn (Images img) {
  // *************** LAYER 0 ***************** //
  // 'Images' parameters
  int L0_INPUT_FRAMES = img.get_frames();
  int L0_INPUT_ROWS   = img.get_rows();
  int L0_INPUT_COLS   = img.get_cols();    

  // 'Kernels' parameters  
  int L0_KERNEL_BLOCKS;
  int L0_KERNEL_FRAMES;
  int L0_KERNEL_ROWS;
  int L0_KERNEL_COLS;
  
  weight_bias_type* L0_weights = NULL;
  weight_bias_type* L0_biases  = NULL;

  read_params("layer_params0.dat", L0_weights, L0_biases, \
							L0_KERNEL_FRAMES	 , L0_KERNEL_BLOCKS			, \
							L0_KERNEL_ROWS		 , L0_KERNEL_COLS	 			, \
							FIRST_TWO_LAYERS );
  
	// Calculate output 'Images' parameters
	int L0_OUTPUT_1_FRAMES  =	L0_KERNEL_BLOCKS;
  int L0_OUTPUT_1_ROWS    =	L0_INPUT_ROWS - L0_KERNEL_ROWS + 1;
  int L0_OUTPUT_1_COLS    =	L0_INPUT_COLS - L0_KERNEL_COLS + 1;
  int L0_OUTPUT_2_FRAMES  =	L0_OUTPUT_1_FRAMES;
  int L0_OUTPUT_2_ROWS    =	L0_OUTPUT_1_ROWS % 2 == 0 ? \
														L0_OUTPUT_1_ROWS / 2 : (L0_OUTPUT_1_ROWS + 1) / 2;
  int L0_OUTPUT_2_COLS    =	L0_OUTPUT_1_COLS % 2 == 0 ? \
														L0_OUTPUT_1_COLS / 2 : (L0_OUTPUT_1_COLS + 1) / 2;
/*    
  std::cout << "====== LeNet Layer 0 Info ======" <<std::endl;
  std::cout << "Input Image: " << L0_INPUT_FRAMES << " x " \
						<< L0_INPUT_ROWS << " x " << L0_INPUT_COLS << std::endl;
  std::cout << "Conv Kernel: " << L0_KERNEL_ROWS << " x " \
						<< L0_KERNEL_COLS << std::endl;
  std::cout << "Out Image 1: " << L0_OUTPUT_1_FRAMES << " x " \
						<< L0_OUTPUT_1_ROWS << " x " << L0_OUTPUT_1_COLS << std::endl;
  std::cout << "Out Image 2: " << L0_OUTPUT_2_FRAMES << " x " \
						<< L0_OUTPUT_2_ROWS << " x " << L0_OUTPUT_2_COLS << std::endl;
  std::cout << "================================" << std::endl;
*/    
  Kernels kn_0( L0_KERNEL_BLOCKS, L0_KERNEL_FRAMES, \
								L0_KERNEL_ROWS	, L0_KERNEL_COLS	, \
								L0_weights			, L0_biases );
  
  Images L0_OUTPUT_1 = convolve(img, kn_0);
  //L0_OUTPUT_1.print();
  Images L0_OUTPUT_2 = maxpool(L0_OUTPUT_1);
  //L0_OUTPUT_2.print();

  //while(1);
    
  // *************** LAYER 1 ***************** //
  // 'Images' parameters
  int L1_INPUT_FRAMES = L0_OUTPUT_2.get_frames();
  int L1_INPUT_ROWS   = L0_OUTPUT_2.get_rows();
  int L1_INPUT_COLS   = L0_OUTPUT_2.get_cols();
    
  // 'Kernels' parameters
  int L1_KERNEL_BLOCKS;
  int L1_KERNEL_FRAMES;
  int L1_KERNEL_ROWS;
  int L1_KERNEL_COLS;
 
  weight_bias_type* L1_weights = NULL;
  weight_bias_type* L1_biases = NULL;
    
  read_params("layer_params1.dat", L1_weights, L1_biases,
              L1_KERNEL_FRAMES	 , L1_KERNEL_BLOCKS			,
              L1_KERNEL_ROWS		 , L1_KERNEL_COLS				,
              FIRST_TWO_LAYERS);
  
  // Calculate output 'Images' parameters
  int L1_OUTPUT_1_FRAMES	=	L1_KERNEL_BLOCKS;
  int L1_OUTPUT_1_ROWS    =	L1_INPUT_ROWS - L1_KERNEL_ROWS + 1;
  int L1_OUTPUT_1_COLS    =	L1_INPUT_COLS - L1_KERNEL_COLS + 1;
  int L1_OUTPUT_2_FRAMES  =	L1_OUTPUT_1_FRAMES;
  int L1_OUTPUT_2_ROWS    =	L1_OUTPUT_1_ROWS%2==0 ? \
														L1_OUTPUT_1_ROWS/2 : (L1_OUTPUT_1_ROWS+1)/2;
  int L1_OUTPUT_2_COLS    =	L1_OUTPUT_1_COLS%2==0 ? \
														L1_OUTPUT_1_COLS/2 : (L1_OUTPUT_1_COLS+1)/2;
/*  
  std::cout << "====== LeNet Layer 1 Info ======" <<std::endl;
  std::cout << "Input Image: " << L1_INPUT_FRAMES << " x " \
						<< L1_INPUT_ROWS << " x " << L1_INPUT_COLS << std::endl;
  std::cout << "Conv Kernel: " << L1_KERNEL_ROWS << " x " \
						<< L1_KERNEL_COLS << std::endl;
  std::cout << "Out Image 1: " << L1_OUTPUT_1_FRAMES << " x " \
						<< L1_OUTPUT_1_ROWS << " x " << L1_OUTPUT_1_COLS << std::endl;
  std::cout << "Out Image 2: " << L1_OUTPUT_2_FRAMES << " x " \
						<< L1_OUTPUT_2_ROWS << " x " << L1_OUTPUT_2_COLS << std::endl;
  std::cout << "================================" << std::endl;
*/
  Kernels kn_1(L1_KERNEL_BLOCKS, L1_KERNEL_FRAMES, \
							 L1_KERNEL_ROWS	 , L1_KERNEL_COLS, \
							 L1_weights			 , L1_biases); 
  Images L1_OUTPUT_1 = convolve(L0_OUTPUT_2, kn_1);
  //L1_OUTPUT_1.print();
  Images L1_OUTPUT_2 = maxpool(L1_OUTPUT_1);
  //L1_OUTPUT_2.print();   
  
  // *************** LAYER 2 ***************** //
  // Fully connected layer, calculate inner product
  
  // First serialize layer 1 output into 1-dimension array
  int L2_INPUT_LENGTH \
    = L1_OUTPUT_2.get_frames()*L1_OUTPUT_2.get_rows()*L1_OUTPUT_2.get_cols();
  image_type* L2_INPUT = new image_type[L2_INPUT_LENGTH];
  for ( int i=0; i<L2_INPUT_LENGTH; i++ ) {
    L2_INPUT[i] = L1_OUTPUT_2.get_data()[i];
  }
    
  // 'Kernels' parameters
  int L2_NUM_OUT;    // Number of output
  int L2_NUM_IN;     // Number of input
  int L2_NUM_ROWS;   // Always 1 for fully connected layers
  int L2_NUM_COLS;   // Always 1 for fully connected layers

  weight_bias_type* L2_weights  = NULL;
  weight_bias_type* L2_biases   = NULL;

  read_params("layer_params2.dat", L2_weights, L2_biases, \
							L2_NUM_IN	         , L2_NUM_OUT			  , \
							L2_NUM_ROWS		     , L2_NUM_COLS	 		, \
							LAST_TWO_LAYERS );
							
	assert( L2_INPUT_LENGTH == L2_NUM_IN \
	     && L2_NUM_ROWS == 1 && L2_NUM_COLS == 1);	
	
	// Init L2 output parameters
	image_type* L2_OUTPUT = new image_type[L2_NUM_OUT];
	for ( int i=0; i<L2_NUM_OUT; i++ ) {
	  L2_OUTPUT[i] = 0;
	}

  // L2_NUM_OUT=500, L2_NUM_IN=800	
  // Be careful that weights[800][500] instead of weights[500][800]
	for ( int i=0; i<L2_NUM_OUT; i++ ) {
	  for ( int j=0; j<L2_NUM_IN; j++ ) {
	    L2_OUTPUT[i] += L2_INPUT[j] * L2_weights[j * L2_NUM_OUT + i];
	  } 
	  L2_OUTPUT[i] += L2_biases[i];
	}
	/*
	for ( int i=0; i<L2_NUM_OUT; i++ ) {
	  std::cout << L2_OUTPUT[i] << "   ";
	}
	std::cout << std::endl;
	*/
  
  // ReLU
  for ( int i=0; i<L2_NUM_OUT; i++ ) {
    L2_OUTPUT[i] = L2_OUTPUT[i] > 0 ? L2_OUTPUT[i] : 0;
  }
	
	// *************** LAYER 3 ***************** //
  // Fully connected layer, calculate inner product
  
  image_type* L3_INPUT = L2_OUTPUT;
  
  /*
  std::cout << "****************\n";
  for ( int i=0; i<L2_NUM_OUT; i++ ){
    std::cout << L2_OUTPUT[i] << " " << L3_INPUT[i] << std::endl;
  } 
  std::cout << "****************\n";
  */
    
  // 'Kernels' parameters
  int L3_NUM_OUT;    // Number of output
  int L3_NUM_IN;     // Number of input
  int L3_NUM_ROWS;   // Always 1 for fully connected layers
  int L3_NUM_COLS;   // Always 1 for fully connected layers

  weight_bias_type* L3_weights  = NULL;
  weight_bias_type* L3_biases   = NULL;

  read_params("layer_params3.dat", L3_weights, L3_biases, \
							L3_NUM_IN	         , L3_NUM_OUT			  , \
							L3_NUM_ROWS		     , L3_NUM_COLS	 		, \
							LAST_TWO_LAYERS );
							
	assert( L2_NUM_OUT == L3_NUM_IN && L3_NUM_ROWS == 1 && L3_NUM_COLS == 1);	

//  for ( int i=0; i<L3_NUM_IN*L3_NUM_OUT*L3_NUM_ROWS*L3_NUM_COLS; i++ ) {
//    std::cout << L3_weights[i] << " ";
//  }
	
	// Init L3 output parameters
	image_type* L3_OUTPUT = new image_type[L3_NUM_OUT];
	for ( int i=0; i<L3_NUM_OUT; i++ ) {
	  L3_OUTPUT[i] = 0;
	}
	
	for ( int i=0; i<L3_NUM_OUT; i++ ) {
	  for ( int j=0; j<L3_NUM_IN; j++ ) {
	    L3_OUTPUT[i] += L3_INPUT[j] * L3_weights[j * L3_NUM_OUT + i];
	  } 
	  L3_OUTPUT[i] += L3_biases[i];
	}
	
//	for ( int i=0; i<L3_NUM_OUT; i++ ) {
//	  std::cout << L3_OUTPUT[i] << "   ";
//	}
//	std::cout << std::endl;
	
	int predicted = -1;
	weight_bias_type max_value = -255;
	for ( int i=0; i<L3_NUM_OUT; i++ ) {
	  if (L3_OUTPUT[i] > max_value) {
	    max_value = L3_OUTPUT[i];
	    predicted = i;
	  }
	}
	
	return predicted;

}


#endif
