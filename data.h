#pragma once
#include "utils.h"

vector<Vector3d> DCM_Error()
{
	vector<Vector3d> error;
	for (int i = 0; i < (simulation_time / sensor_sample); i++)
	{
		Vector3d error_dcm = Errors(3, 1, 0, sensor_error);
		error.push_back(error_dcm);
	}
	return error;
}

void dcm_data(double angle,vector<Matrix3d>& dcm_true, vector<Matrix3d>& dcm_observe, vector<Vector3d>& error, vector<Matrix3d>& dcm_covariance)
{
	Matrix3d sensor_covariance = Matrix3d::Identity(3, 3) * pow(sensor_error, 2);
	for (int i = 0; i < (simulation_time / sensor_sample); i++)
	{
		Matrix3d true_dcm = DCM(angle,i * sensor_sample);
		Vector3d error_dcm = *(error.begin()+i);
		Matrix3d observe_dcm = true_dcm * (Matrix3d::Identity(3, 3) + Antisymmetric_matrix(error_dcm));
		Matrix3d covariance_dcm = true_dcm * sensor_covariance * true_dcm.transpose();
		dcm_true.push_back(true_dcm); dcm_observe.push_back(observe_dcm); dcm_covariance.push_back(covariance_dcm);
	}
}

void set_coefficient_direct(vector<Matrix3d>& dcm_observe, vector<Matrix3d>& dcm_covariance, vector<Matrix3d>& H_K, vector<Matrix3d>& F_K, vector<Vector3d>& coefficient_f, MatrixXd& J, MatrixXd& P, MatrixXd& f)
{
	for (vector< Matrix3d>::iterator it = dcm_observe.begin(); it != (dcm_observe.end() - 1); it++)
	{
		Matrix3d h_k = (*(it + 1)) * (*it).transpose();
		Matrix3d f_k = 0.5 * (h_k - h_k.trace() * Matrix3d::Identity(3, 3));
		Vector3d F = Vector3d::Constant(3, 1, 0);
		F(0, 0) = 0.5 * (h_k(2, 1) - h_k(1, 2));
		F(1, 0) = 0.5 * (h_k(0, 2) - h_k(2, 0));
		F(2, 0) = 0.5 * (h_k(1, 0) - h_k(0, 1));
		H_K.push_back(h_k); F_K.push_back(f_k); coefficient_f.push_back(F);
	}

	int size_F_K = F_K.size(); int size_f = coefficient_f.size(); int size_P = dcm_covariance.size();
	P = MatrixXd::Constant(size_P * 3, size_P * 3, 0);
	for (int i = 0; i < size_P; i++)
	{
		P.block<3, 3>(i * 3, i * 3) = *(dcm_covariance.begin() + i);
	}
	J = MatrixXd::Constant(size_F_K * 3, (size_F_K + 1) * 3, 0);
	f = MatrixXd::Constant(size_f * 3, 1, 0);
	for (int i = 0; i < size_F_K; i++)
	{
		J.block<3, 3>(i * 3, i * 3) = Matrix3d::Identity(3, 3);
		J.block<3, 3>(i * 3, (i + 1) * 3) = *(F_K.begin() + i);
		f.block<3, 1>(i * 3, 0) = *(coefficient_f.begin() + i);
	}
}
