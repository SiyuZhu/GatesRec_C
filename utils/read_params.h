#ifndef READ_PARAMS_H
#define READ_PARAMS_H

#include <string>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <typeinfo>
#include "../typedefs.h"
#include <cstring>

#define DEFAULT_DIR "data/mnist/"

void read_params (std::string filename, weight_bias_type* &weights, weight_bias_type* &biases, int &numin, int &numout, int &rows, int &cols, int flag) {
  // try without and with the default dir
  std::fstream fs;
  fs.open(filename.c_str(), std::fstream::in);
  if (!fs.is_open()) {
    std::string filename2 = std::string(DEFAULT_DIR) + filename;
    fs.open(filename2.c_str(), std::fstream::in);
  }
  if (!fs.is_open()) {
    fprintf (stderr, "Cannot open file %s\n", filename.c_str());
    exit(1);
  }

  std::string buffer;
  std::stringstream ss;
  std::string s;

  // search for the line "weights"
  while (!fs.eof()) {
    std::getline(fs, buffer);
    std::size_t found = buffer.find("weights");
    if (found != std::string::npos)
      break;
  }
  if (fs.eof()) {
    fprintf (stderr, "Cannot find weights\n");
    exit(1);
  }

  // extract dimensions
  std::getline(fs, buffer);
  ss.str(buffer);

  //Last two layers
  if(flag == 1){
    assert( std::getline(ss, s, ',') );
    numin = atoi(s.c_str());
    assert( std::getline(ss, s, ',') );
    numout = atoi(s.c_str());
    rows = 1;
    cols = 1;
  }
  //First two layers
  else {
    assert( std::getline(ss, s, ',') );
    numout = atoi(s.c_str());
    assert( std::getline(ss, s, ',') );
    numin = atoi(s.c_str());
    assert( std::getline(ss, s, ',') );
    rows = atoi(s.c_str());
    assert( std::getline(ss, s, ',') );
    cols = atoi(s.c_str());
  }


  // read weights
  weights = new weight_bias_type[numin*numout*rows*cols];
  weight_bias_type* wptr = weights;
  if(flag == 1){
    for (int i = 0; i < numin; ++i) {
    std::getline(fs, buffer);
    ss.str(buffer);
    for (int j = 0; j < numout; ++j) {
      assert( std::getline(ss, s, ',') );
      if (typeid(weight_bias_type) == typeid(float)) {
        *wptr = atof(s.c_str());
      }
      else if (typeid(weight_bias_type) == typeid(int)) {
        *wptr = atoi(s.c_str());
      }
      else if (typeid(weight_bias_type) == typeid(double)) {
        *wptr = strtod(s.c_str(), NULL);
      }
      else {
        *wptr = strtod(s.c_str(), NULL);
        std::cout << "Casting weights data to 'double'" << std::endl;
      }
      
      wptr++;
    }
   }
  }
  
  else
  for (int i = 0; i < numin*numout; ++i) {
    std::getline(fs, buffer);
    ss.str(buffer);
    for (int j = 0; j < rows*cols; ++j) {
      assert( std::getline(ss, s, ',') );
      if (typeid(weight_bias_type) == typeid(float)) {
        *wptr = atof(s.c_str());
      }
      else if (typeid(weight_bias_type) == typeid(int)) {
        *wptr = atoi(s.c_str());
      }
      else if (typeid(weight_bias_type) == typeid(double)) {
        *wptr = strtod(s.c_str(), NULL);
      }
      else {
        *wptr = strtod(s.c_str(), NULL);
        std::cout << "Casting weights data to 'double'" << std::endl;
      }
      
      wptr++;
    }
  }

  // search for the line "biases"
  while (!fs.eof()) {
    std::getline(fs, buffer);
    std::size_t found = buffer.find("biases");
    if (found != std::string::npos)
      break;
  }
  if (fs.eof()) {
    fprintf (stderr, "Cannot find weights\n");
    exit(1);
  }

  std::getline(fs, buffer);
  ss.str(buffer);
  assert( std::getline(ss, s, ',') );
    assert (numout == atoi(s.c_str()));

  // read biases
  biases = new weight_bias_type[numout];
  weight_bias_type* bptr = biases;
  std::getline(fs, buffer);
  ss.str(buffer);
  for (int i = 0; i < numout; ++i) {
    assert( std::getline(ss, s, ',') );
    if (typeid(weight_bias_type) ==  typeid(float)) {
        *bptr = atof(s.c_str());
    }
    else if (typeid(weight_bias_type) == typeid(int)) {
      *bptr = atoi(s.c_str());
    }
    else if (typeid(weight_bias_type) == typeid(double)) {
      *bptr = strtod(s.c_str(), NULL);
    }
    else {
      *bptr = strtod(s.c_str(), NULL);
      std::cout << "Casting biases data to 'double'" << std::endl;
    }
    
    bptr++;
  }
  fs.close();
}

#endif
