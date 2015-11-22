#ifndef __KERNELS_H__
#define __KERNELS_H__

#include <iostream>
#include <assert.h>
#include <iomanip>
#include "typedefs.h"

class Kernels {
public:
	Kernels( int blocks, int frames, int rows, int cols, \
					 weight_bias_type* weights, weight_bias_type* biases ){
		this->blocks	=	blocks;
    this->frames	=	frames;
    this->rows		=	rows;
    this->cols		=	cols;
    this->weights	=	new weight_bias_type[blocks*frames*rows*cols];
    this->biases	=	new weight_bias_type[blocks];
		for (int i=0; i<blocks*frames*rows*cols; i++) {
			this->weights[i] = weights[i];
		}
    for (int i=0; i<blocks; i++) {
    	this->biases[i] = biases[i];
    }
  }
  
  int get_blocks ( void ) { return this->blocks; }

	int get_frames ( void ) { return this->frames; }

  int get_rows ( void ) { return this->rows; }

  int get_cols ( void ) { return this->cols; }
    
  weight_bias_type get ( int b, int f, int r, int c ) {
    assert ( b<this->blocks	&& b>=0	&& f<this->frames	&& f>=0
					&& r<this->rows   && r>=0	&& c<this->cols   && c>=0 );
    return this->weights[b	*	this->frames	*	this->rows	*	this->cols
                       + f	*	this->rows		*	this->cols
                       + r	*	this->cols 		+ c];
  }
    
  weight_bias_type get ( int b ) {
		assert ( b<this->blocks && b>=0 );
    return this->biases[b];
  }  
  
	void print ( void ) {
		for ( int b=0; b<this->blocks; b++ ) {
    	std::cout << "-- Block " << b << " --" << std::endl;
      for ( int f=0; f<this->frames; f++ ) {
      std::cout << "-- Frame " << f << " --" << std::endl;
      std::cout << "**Weights**" << std::endl;
      for ( int r=0; r<this->rows; r++ ) {
      	for ( int c=0; c<this->cols; c++ ) 
        	std::cout << std::setw(15) << get (b, f, r, c);
          std::cout << std::endl;
        }
      }
	    std::cout << "**Bias**" << std::endl;
	    std::cout << this->biases[b] << std::endl << std::endl;
    }
  }

private:
  int blocks;
  int frames;
  int rows;
  int cols;
  weight_bias_type   *weights;
  weight_bias_type   *biases;
};

#endif

