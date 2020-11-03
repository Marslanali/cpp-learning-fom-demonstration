# 🚧 CPP Learning From Demonstration 🚧

This repositroy C++ implementation of multi degrees of freedom trajectory learning using gaussian mixture model and gaussian mixture regression.

* A python implementation can be seen <a href="https://github.com/Marslanali/python-random-forest-decision-tree">here</a>.

## Branches

```
├── [master]           git checkout master
└── [develop-gmr]   git checkout master
```

## Files

```
.
├── src
├── include
├── test
├── CMakeList.txt
└── README.md
```

## Dependencies

* [CMake](https://www.mlpack.org/)   Version 3.4.1

* [LAPACK] (https://www.mlpack.org/) Linear Algebra Package  Version 3.4.1

* [MLPACK (C++ Machine Learning Library)] (https://www.mlpack.org/)   Version 3.4.1

* [Armadillo (C++ library for linear algebra & scientific computing)] (https://www.mlpack.org/)   Version 3.4.1

* [Matplotlib-CPP (for plotting directly in c++)] (https://www.mlpack.org/)   Version 3.4.1

* Ubuntu 16.04/18.04, CMake/Make, GCC

## Dependencies Installation

* Install [CMake](https://www.mlpack.org/) Version 3.4.1 from source. 

```bash
sudo apt-get install -y -q wget
wget https://cmake.org/files/v3.17/cmake-3.17.5.tar.gz 
tar xzf cmake-3.17.5.tar.gz 
cd cmake-3.17.5 
./bootstrap -- -DCMAKE_BUILD_TYPE:STRING=Release 
make -j4 # where j is the number of core
sudo make install
```

* Install [OpenCV](https://www.mlpack.org/) Version 3.4.1 from source. 

```bash
sudo apt update && sudo apt install -y g++ unzip
wget -O opencv.zip https://github.com/opencv/opencv/archive/master.zip
wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/master.zip
unzip opencv.zip
unzip opencv_contrib.zip
```

Create build directory and switch into it, Configure, and Build.

```bash
mkdir -p build && cd build
cmake -DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib-master/modules ../opencv-master
cmake --build .
```

* Install [MLPACK](https://www.mlpack.org/) Version 3.4.1 from source. 

```bash
sudo apt-get install -y -q wget
wget https://cmake.org/files/v3.17/cmake-3.17.5.tar.gz 
tar xzf cmake-3.17.5.tar.gz 
cd cmake-3.17.5 
./bootstrap -- -DCMAKE_BUILD_TYPE:STRING=Release 
make -j4 # where j is the number of core
sudo make install
```

* Install [Armadillo](https://www.mlpack.org/) Version 3.4.1 from source. 

```bash
sudo apt-get install -y -q wget
wget https://cmake.org/files/v3.17/cmake-3.17.5.tar.gz 
tar xzf cmake-3.17.5.tar.gz 
cd cmake-3.17.5 
./bootstrap -- -DCMAKE_BUILD_TYPE:STRING=Release 
make -j4 # where j is the number of core
sudo make install
```

* Install [LAPACK](https://www.mlpack.org/) Version 3.4.1 from source. 

```bash
sudo apt-get install -y -q wget
wget https://cmake.org/files/v3.17/cmake-3.17.5.tar.gz 
tar xzf cmake-3.17.5.tar.gz 
cd cmake-3.17.5 
./bootstrap -- -DCMAKE_BUILD_TYPE:STRING=Release 
make -j4 # where j is the number of core
sudo make install
```

## Demo

To build run the following command in terminal:

```bash
mkdir build
cd build
cmake ..
make -j4 
```

```bash
./kmean --mean 1000 --sigma 500 --distance 200
```

<p align="left">
   <img src="plots/input_data_1D.jpg" width ="300" height="300"/>  
   <img src="plots/input_data_2D.jpg" width ="300" height="300"/>
  <br/>
  Fig. 1. Input Data
</p>


<p align="left">
  <img src="plots/input_clock.jpg" width ="300" height="300"/>
  <img src="plots/centroids_gmm.jpg" width ="300" height="300"/>
  <br/>
  Fig. 2. Input Clock and, GMM Centroids
</p>


## Data Representation
Let X is the data sets containing n features with n data points. Each row corresponds to a data point while each column depicts the feature. Similarly, y represents the labels ![f1] to ![f2].

## Training and Test Data	  
Let ![f3] is the data sets containing n features with n data points used for the training. Each row corresponds to a data point while each column depicts the feature. Similarly, ![f4] represents the labels ![f5] to ![f6] used for the training. 

Goal is to train the model the ![f3] and ![f4] and then test it with ![f7] and ![f8] data. 

[f1]: http://chart.apis.google.com/chart?cht=tx&chl=y_0
[f2]: http://chart.apis.google.com/chart?cht=tx&chl=y_n
[f3]: http://chart.apis.google.com/chart?cht=tx&chl=X_{train}
[f4]: http://chart.apis.google.com/chart?cht=tx&chl=y_{train}
[f5]: http://chart.apis.google.com/chart?cht=tx&chl=y_0
[f6]: http://chart.apis.google.com/chart?cht=tx&chl=y_n
[f7]: http://chart.apis.google.com/chart?cht=tx&chl=X_{test}
[f8]: http://chart.apis.google.com/chart?cht=tx&chl=y_{test}


## References

[Random Forest ](https://www.researchgate.net/publication/308020680_The_k-means_clustering_technique_General_considerations_and_implementation_in_Mathematica/link/584dd9be08aeb989252647ac/download)

[Decision Trees ](https://www.researchgate.net/publication/308020680_The_k-means_clustering_technique_General_considerations_and_implementation_in_Mathematica/link/584dd9be08aeb989252647ac/download)

[Decision Trees ](https://www.researchgate.net/publication/308020680_The_k-means_clustering_technique_General_considerations_and_implementation_in_Mathematica/link/584dd9be08aeb989252647ac/download)

[Decision Trees ](https://www.researchgate.net/publication/308020680_The_k-means_clustering_technique_General_considerations_and_implementation_in_Mathematica/link/584dd9be08aeb989252647ac/download)

[Data for example code] The data folder contains the test data which constitutes of 4 demonstrations. The collected demonstratiosn consists of cartesian trajectories of 3 DOF robot.


## To-Do List

- :ballot_box_with_check: Refactor src/include with clang
- :negative_squared_cross_mark: Add CMake Cross Platform Support
- :negative_squared_cross_mark: Add Docker Image Support 


Author:
_Arslan Ali_
