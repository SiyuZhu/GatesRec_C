#ifndef __MAXPOOL_H__
#define __MAXPOOL_H__

#include "images.h"
#include "typedefs.h"

Images maxpool( Images img ) {
	assert( img.get_frames() > 0 && img.get_rows() > 2 && img.get_cols() > 2 );   
	
	int result_frames = img.get_frames();    
	int result_rows = img.get_rows()%2==0 ? \
										img.get_rows()/2 : (img.get_rows()+1)/2;
	int result_cols = img.get_cols()%2==0 ? \
										img.get_cols()/2 : (img.get_cols()+1)/2;

	Images result( result_frames, result_rows, result_cols, \
								 new image_type[result_frames*result_rows*result_cols] );

	for ( int f=0; f<img.get_frames(); f++ ) {
		for ( int r=0; r<img.get_rows(); r+=2 ) {
    	for ( int c=0; c<img.get_cols(); c+=2 ) {
      	image_type n_00 = img.get(f, r, c);
        image_type n_01 = img.get(f, r, (img.get_cols()==(c+1)) ? c : (c+1));
        image_type n_10 = img.get(f, (img.get_rows()==(r+1)) ? r : (r+1), c);
        image_type n_11 = img.get(f, (img.get_rows()==(r+1)) ? r : (r+1), \
																 (img.get_cols()==(c+1)) ? c : (c+1));
        image_type n_a = (n_00>n_01) ? n_00 : n_01;
        image_type n_b = (n_10>n_11) ? n_10 : n_11;
        image_type n_c = (n_a >n_b ) ? n_a  : n_b ;
        result.set(f, r/2, c/2, n_c);
    	}
    }
	}
	return result;
}

#endif
