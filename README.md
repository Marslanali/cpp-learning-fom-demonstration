# cpp_learning_from_demonstration

This repositroy is C++ implementation of learning from demonstration/Imitation Learning which is part of my research project. For more details please check the reference section of this Readme.md

### Prerequisite

This project was buit using CLion with Cmake build system and tested on Ubuntu 16.04.

The program requires:

  - LAPACK (Linear Algebra Package)
  - MLPACK (C++ Machine Learning Library)
  - Armadillo (C++ library for linear algebra & scientific computing)
  - Matplotlib-CPP (for plotting directly in c++) 

### Armadillo installation

Make sure latest version of Armadillo C++ install on your system. For Armadillo installation, see http://arma.sourceforge.net/download.html for instructions.

#### MLPACK installation

**On Debian and Ubuntu:**

```
sudo apt-get install libmlpack-dev
```

To build from Source, Assuming all dependencies are installed in the system, you can run the commands below directly to build and install mlpack.

```
wget https://www.mlpack.org/files/mlpack-3.2.2.tar.gz
tar -xvzpf mlpack-3.2.2.tar.gz
cd mlpack-3.2.2
mkdir build 
cd build
cmake ../
make -j4  # The -j is the number of cores you want to use for a build.
sudo make install
```

#### LAPACK installation

**On Debian and Ubuntu:**

```
sudo apt-get install liblapack-dev
```

### matplotlib-cpp library installation

see https://github.com/lava/matplotlib-cpp for instructions. 

### Runing the Code

To run, first clone the repository.

```git clone``` https://github.com/Marslanali/cpp_learning_from_demonstration.git

```
cd cpp_learning_from_demonstration-master
mkdir build
cd build
cmake ..   
make
```

### Data for example code

The data folder contains the test data which constitutes of 4 demonstrations. The collected demonstratiosn consists of cartesian trajectories of 3 DOF robot.

### References

For reference please check the following papers.

https://ieeexplore.ieee.org/document/4126276/


If you face any difficulty, feel free to drop an email at arslanali800@hotmail.com
