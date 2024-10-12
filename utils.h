#pragma once
#include "config.h"

Matrix3d Antisymmetric_matrix(Vector3d mat)
{
	Matrix3d temp = Matrix3d::Zero(3, 3);
	temp(0, 1) = -mat(2, 0); temp(1, 0) = mat(2, 0);
	temp(0, 2) = mat(1, 0); temp(2, 0) = -mat(1, 0);
	temp(1, 2) = -mat(0, 0); temp(2, 1) = mat(0, 0);
	return temp;
}

double condition_number(MatrixXd Mat)
{
	// 计算奇异值分解
	Eigen::JacobiSVD<Eigen::MatrixXd> svd(Mat);
	// 获取最大和最小奇异值
	double sigma_max = svd.singularValues()(0);
	double sigma_min = svd.singularValues()(svd.singularValues().size() - 1);

	// 计算条件数
	double condition_number = sigma_max / sigma_min;
	return condition_number;
}

Matrix3d Euler2DCM(Vector3d EulerAngles)
{   //航向角 俯仰角  横滚角 // 外旋 ZYX|321
	double yaw = EulerAngles(0, 0);//航向角psi|ψ
	double pitch = EulerAngles(1, 0);//俯仰角theta|θ
	double roll = EulerAngles(2, 0);//横滚角phi|φ
	Matrix3d DCM = Matrix3d::Zero(3, 3);
	DCM(0, 0) = cos(pitch) * cos(yaw);
	DCM(0, 1) = cos(pitch) * sin(yaw);
	DCM(0, 2) = -sin(pitch);
	DCM(1, 0) = -cos(roll) * sin(yaw) + sin(roll) * sin(pitch) * cos(yaw);
	DCM(1, 1) = cos(roll) * cos(yaw) + sin(roll) * sin(pitch) * sin(yaw);
	DCM(1, 2) = sin(roll) * cos(pitch);
	DCM(2, 0) = sin(roll) * sin(yaw) + cos(roll) * sin(pitch) * cos(yaw);
	DCM(2, 1) = -sin(roll) * cos(yaw) + cos(roll) * sin(pitch) * sin(yaw);
	DCM(2, 2) = cos(roll) * cos(pitch);
	return DCM;
}

Matrix3d DCM(double angle,double T)
{
	double angle_roll = angle * PI / 180, angle_head = angle * PI / 180, angle_pitch = angle * PI / 180;//三个角的幅值
	double inint_angle_roll = 10, inint_angle_head = 10, inint_angle_pitch = 10;//初始相位
	double anglur = 2 * PI / 60;//角频率
	Vector3d Euler = Vector3d::Constant(3, 1, 0);
	Euler(0, 0) = angle_roll * cos(anglur * T + inint_angle_roll);
	Euler(1, 0) = angle_head * cos(anglur * T + inint_angle_head);
	Euler(2, 0) = angle_pitch * cos(anglur * T + inint_angle_pitch);
	return Euler2DCM(Euler);
}

MatrixXd Errors(int col, int row, double mean, double standard)
{
	// 从epoch（1970年1月1日00:00:00 UTC）开始经过的纳秒数，unsigned类型会截断这个值
	random_device rd;
	mt19937 generator(rd());
	// 第一个参数为高斯分布的平均值，第二个参数为标准差
	std::normal_distribution<double> distribution(mean, standard);
	MatrixXd errors = MatrixXd::Zero(col, row);
	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < row; j++)
		{
			errors(i, j) = distribution(generator);
		}
	}
	return errors;
}

MatrixXd Vector_var(vector<Vector3d> matrix)
{
	MatrixXd W = MatrixXd::Constant(matrix.size() * 3, 1, 0);
	for (int i = 0; i < matrix.size(); i++)
	{
		W.block<3, 1>(i * 3, 0) = *(matrix.begin() + i);
	}
	return W;
}

MatrixXd Set_P(vector<Matrix3d>& dcm_covariance)
{
	int size_P = dcm_covariance.size();
	MatrixXd P = MatrixXd::Constant(size_P * 3, size_P * 3, 0);
	for (int i = 0; i < size_P; i++)
	{
		P.block<3, 3>(i * 3, i * 3) = *(dcm_covariance.begin() + i);
	}
	return P;
}

MatrixXd generate_u(int n) {
	MatrixXd u = MatrixXd::Constant(n, 1, 0);
	random_device rd;  // 用于获得种子
	mt19937 gen(rd()); // 生成器
	uniform_int_distribution<> dis(0, 1); // 均匀分布，生成 0 或 1
	for (int i = 0; i < n; ++i) {
		u(i, 0) = dis(gen) * 2 - 1; // 将 0 转换为 -1，1 保持为 1
	}
	return u;
}

Vector3d AngleErrors(Matrix3d pre, Matrix3d next)
{
	Matrix3d error = pre.transpose() * next;
	Matrix3d errors = 0.5 * (error - error.transpose());
	Vector3d error_angle = Vector3d::Constant(3, 1, 0);
	error_angle(0, 0) = errors(2, 1); error_angle(1, 0) = errors(0, 2); error_angle(2, 0) = errors(1, 0);
	return error_angle;
}

MatrixXd Better_Estimate(vector<Matrix3d>& dcm_true, vector<Matrix3d>& dcm_observe, vector<Vector3d>& alpha)
{
	MatrixXd Better = MatrixXd::Constant(dcm_true.size() * 3, 1, 0);
	MatrixXd temp, better;
	for (int i = 0; i < (simulation_time / sensor_sample); i++)
	{
		temp = MatrixXd::Identity(3, 3) - Antisymmetric_matrix(*(alpha.begin() + i));
		better = temp * (*(dcm_observe.begin() + i));
		Better.block<3, 1>(i * 3, 0) = AngleErrors((*(dcm_true.begin() + i)), better);
	}
	return Better;
}

void outpu_data_direct(string file_path1, string file_path2, vector<Matrix3d>& dcm_true, vector<Matrix3d>& dcm_observe, MatrixXd& alpha)
{
	MatrixXd temp, better;
	Vector3d result1, result2;
	double previous = 0; double now = 0;
	fstream fs1; fstream fs2;
	fs1.open(file_path1, ios::out); fs2.open(file_path2, ios::out);
	for (int i = 0; i < (simulation_time / sensor_sample); i++)
	{
		temp = MatrixXd::Identity(3, 3) - Antisymmetric_matrix(alpha.block<3, 1>(i * 3, 0));
		better = temp * (*(dcm_observe.begin() + i));

		result1 = AngleErrors((*(dcm_true.begin() + i)), (*(dcm_observe.begin() + i))) * 180 * 3600 / PI;
		result2 = AngleErrors((*(dcm_true.begin() + i)), better) * 180 * 3600 / PI;

		fs1 << result1(0, 0) << "," << result1(1, 0) << "," << result1(2, 0) << ",";
		fs2 << result2(0, 0) << "," << result2(1, 0) << "," << result2(2, 0) << ",";

		previous = previous + pow(result1(0, 0), 2);
		now = now + pow(result2(0, 0), 2);
	}
	fs1.close();
	fs2.close();
	cout << previous << endl;
	cout << now << endl;
}

void outpu_data_btma(string file_path1, string file_path2, vector<Matrix3d>& dcm_true, vector<Matrix3d>& dcm_observe, vector<Vector3d>& alpha)
{
	MatrixXd temp, better;
	Vector3d result1, result2;
	fstream fs1; fstream fs2;
	fs1.open(file_path1, ios::out); fs2.open(file_path2, ios::out);
	double previous = 0;
	double now = 0;
	for (int i = 0; i < (simulation_time / sensor_sample); i++)
	{
		temp = MatrixXd::Identity(3, 3) - Antisymmetric_matrix(*(alpha.begin() + i));
		better = temp * (*(dcm_observe.begin() + i));

		result1 = AngleErrors((*(dcm_true.begin() + i)), (*(dcm_observe.begin() + i))) * 180 * 3600 / PI;
		result2 = AngleErrors((*(dcm_true.begin() + i)), better) * 180 * 3600 / PI;

		fs1 << result1(0, 0) << "," << result1(1, 0) << "," << result1(2, 0) << ",";
		fs2 << result2(0, 0) << "," << result2(1, 0) << "," << result2(2, 0) << ",";

		previous = previous + pow(result1(0, 0), 2);
		now = now + pow(result2(0, 0), 2);
	}
	cout << previous << endl;
	cout << now << endl;
	fs1.close();
	fs2.close();
}

void output_angle()
{
	double angle_roll = 10 * PI / 180, angle_head = 5 * PI / 180, angle_pitch = 2 * PI / 180;//三个角的幅值
	double inint_angle_roll = 10, inint_angle_head = 10, inint_angle_pitch = 10;//初始相位
	double anglur = 2 * PI / 60;
	fstream fs1;
	fs1.open("angle.txt", ios::out);
	for (int i = 0; i < (simulation_time / sensor_sample - 1); i++)
	{
		fs1 << (angle_roll * cos(anglur * (i + 1) * sensor_sample + inint_angle_roll) - angle_roll * cos(anglur * i * sensor_sample + inint_angle_roll))*180*3600/PI << ",";
		fs1 << (angle_head * cos(anglur * (i + 1) * sensor_sample + inint_angle_roll) - angle_head * cos(anglur * i * sensor_sample + inint_angle_roll)) * 180 * 3600 / PI << ",";
		fs1 << (angle_pitch * cos(anglur * (i + 1) * sensor_sample + inint_angle_roll) - angle_pitch * cos(anglur * i * sensor_sample + inint_angle_roll)) * 180 * 3600 / PI << ",";
	}
	fs1.close();
}