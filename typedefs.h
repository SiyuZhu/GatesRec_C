#ifndef __TYPEDEFS_H__
#define __TYPEDEFS_H__


// Raw image type that read from original image database
// Can be 8-bit integer (unsigned char) for 8-bit greyscale image
// May need cast to other type during computation
#define image_raw_type		unsigned char

// Image type that is used during layers of CNN computation
#define image_type				float

// Type of CNN parameters, including connection weights and biases 
#define weight_bias_type	float


#endif
