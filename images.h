#ifndef __IMAGES_H__
#define __IMAGES_H__

#include <iostream>
#include <assert.h>
#include <iomanip>
#include "typedefs.h"

class Images {
public:
	Images(int frames, int rows, int cols, image_type* data ) {
		this->frames	=	frames;
		this->rows		=	rows;
		this->cols		=	cols;
		this->data		=	new image_type[frames*rows*cols];
    for (int i=0; i<frames*rows*cols; i++) {
    	this->data[i] = data[i];
		}
	}

  int get_frames ( void ) { return this->frames; }

  int get_rows ( void ) { return this->rows; }

  int get_cols ( void ) { return this->cols; }
  
  image_type* get_data( void ) { return this->data; }

  image_type get ( int f, int r, int c ) {
		assert ( f<this->frames && f>=0 \
					&& r<this->rows 	&& r>=0 \
					&& c<this->cols 	&& c>=0 );
		return data[f*this->rows*this->cols + r*this->cols + c];
	}

	void set ( int f, int r, int c, image_type value ) {
		data[f*this->rows*this->cols + r*this->cols + c] = value;
	}
    
  void print ( void ) {
		for ( int f=0; f<frames; f++ ) {
    	std::cout << "-- Frame " << f << " --" << std::endl;
      for ( int r=0; r<this->rows; r++ ) {
      	for ( int c=0; c<this->cols; c++ ) {
					std::cout << std::setw(5) << (int) get( f, r, c );
				}
        std::cout << std::endl;
			}
			std::cout << std::endl;
    }
  }

private:
	int frames;
	int rows;
	int cols;
	image_type   *data;
};

#endif
