# Tikhonov-regularization
Paper:Smoothing attitude series data through Tikhonov regularization  
C++: Eigen3.3.3  
Python:numpy,matplotlib

description:
The paper is divided into two parts: data generation and graphical presentation. Data generation is implemented using C++, while graphical presentation and data statistics are handled using Python.  
C++:  
config.h: Simulation experiments with fixed configurations.  
data.h: Generate simulation data sequences: true attitude values, observed values, and covariance matrices. Set the loss function coefficient matrix according to the formulas in the paper.  
simulation.h: Based on the generated data sequences, you can choose to perform direct computation and apply the BTMA algorithm, outputting the GCV values for the corresponding regularization parameters.  
utils.h: Utility functions for data processing and output files for the final results.
Tikhonov_Regularization.cpp: Algorithm workflow.  
Python:  
Each Python file corresponds to the figures and statistical data in the paper.
