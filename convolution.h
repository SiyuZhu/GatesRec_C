#ifndef __CONVOLUTION_H__
#define __CONVOLUTION_H__

#include "images.h"
#include "kernels.h"
#include "typedefs.h"

// Calculating convolution between 3D image and 4D kernel
// An 'Images' object has 3 dimensions, 
// (Frames_i) x (Rows_i) x (Cols_i)
// An 'Kernels' object has 4 dimensions, 
// (Blocks_k) x (Frames_k) x (Rows_k) x (Cols_k)
// Convolution operation must meet (Frames_i) == (Frames_k)
// The convolution output of 'Images' and 'Kernels' object is an 
// 'Images' object, which has 3 dimensions, size of 
// (Blocks_k) x (Rows_i-Rows_k+1) x (Cols_i-Cols_k+1)

Images convolve( Images img, Kernels kn ) {
	// Get parameters of input 'Images'
	int Frames_i	=	img.get_frames();
	int Rows_i		= img.get_rows();
	int Cols_i		= img.get_cols(); 
 
	// Get parameters of input 'Kernels'
	int Blocks_k	= kn.get_blocks();
	int Frames_k	= kn.get_frames();
	int Rows_k		= kn.get_rows();
	int Cols_k		= kn.get_cols();

	// Assert that input parameters meet convolution condition
	assert ( Frames_i==Frames_k && Frames_i>0 && Frames_k>0 
	&& Rows_i>0 && Rows_k>0 && Cols_i>0 && Cols_k>0 && Blocks_k>0 );
    
	// Calculate output 'Images' parameters
	int Frames_o    = Blocks_k;
	int Rows_o      = Rows_i - Rows_k + 1;
	int Cols_o      = Cols_i - Cols_k + 1;
  
	// Assert that output parameters are legal and number of 
	// rows and cols of 'Kernels' are odd
	assert( Rows_o>0 && Cols_o>0 && Rows_k%2==1 && Cols_k%2==1 );
	image_type* result_pixels = new image_type[Frames_o*Rows_o*Cols_o];
	for ( int i=0; i<Frames_o*Rows_o*Cols_o; i++ ) 
		result_pixels[i] = (image_type) 0;

	Images result( Frames_o, Rows_o, Cols_o, result_pixels );
  
  for ( int b=0; b<Blocks_k; b++ ) { 
    for ( int f=0; f<Frames_k; f++ ) { 
      for ( int r=0; r<Rows_o; r++ ) { 
        for ( int c=0; c<Cols_o; c++ ) { 
          for ( int rr=0; rr<Rows_k; rr++ ) { 
            for ( int cc = 0; cc < Cols_k; cc++ ) { 
              result.set( b, r, c, result.get(b, r, c) + \
													img.get(f, r + rr, c + cc) * 
													kn.get(b, f, Rows_k-1-rr, Cols_k-1-cc) ) ;
						} 
					} 
				} 
			} 
		}
		for ( int r=0; r<Rows_o; r++ ) { 
			for ( int c=0; c<Cols_o; c++ ) { 
				result.set(b, r, c, result.get(b, r, c) + kn.get(b));
			}    
		}
	}
	return result;
}

#endif
