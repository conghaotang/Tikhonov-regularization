#pragma once
#include<Eigen/core>
#include<Eigen/Dense>
#include<Eigen/QR>
#include <random>
#include <chrono>
#include<iostream>
#include<algorithm>
#include<fstream>
#include <iomanip>


using namespace Eigen;
using namespace std;

const double PI = 3.1415926535897;
const double simulation_time = 80;//40s
const double sensor_error = 20 * PI / 648000;//satellite error
const double sensor_sample = 0.5;//satellite sample frequency
