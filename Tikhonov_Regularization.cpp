#include "data.h"
#include "simulation.h"
#include <chrono>
using namespace chrono;

int main()
{
	//Simulation dcm and Covariance

	vector<Vector3d> error = DCM_Error();

	//10 2e6  5 1.2e6 2 4e7 
	double anglur[3] = { 10 ,5 ,2 };
	double mu[3] = { 100000 ,7.5 * 1e6 , 3.7 * 1e7 };
	double b;
	vector<Matrix3d> dcm_true, dcm_observe, dcm_covariance;
	//dcm_data(anglur[k], dcm_true, dcm_observe, error, dcm_covariance);
	dcm_data(10, dcm_true, dcm_observe, error, dcm_covariance);
	//formula coefficient
	vector<Matrix3d> H_K, F_K;
	vector<Vector3d>  coefficient_f;
	MatrixXd J, P, f;
	set_coefficient_direct(dcm_observe, dcm_covariance, H_K, F_K, coefficient_f, J, P, f);

	//regularization parameter


	//direct calculate
	//MatrixXd alpha1 = direct_alpha(mu, J, P, f);

	//Output_direct error
	//outpu_data_direct("result1.txt", "result2.txt", dcm_true, dcm_observe, alpha1);

	b = 3e7;
	//BTMA
	vector<Matrix3d> A_k, B_k, C_k;
	//vector<Vector3d> alpha2 = BTMA(mu[k], F_K, coefficient_f, dcm_covariance, A_k, B_k, C_k);
	vector<Vector3d> alpha2 = BTMA(b, F_K, coefficient_f, dcm_covariance, A_k, B_k, C_k);

	//Output_BTMA error
	outpu_data_btma("result3.txt", "result4.txt", dcm_true, dcm_observe, alpha2);

	//GCV
	MatrixXd Better = Better_Estimate(dcm_true, dcm_observe, alpha2);
	//double gcv = GCV(P, A_k, B_k, C_k, Better);
	cout << b << endl;
	//cout << (3 * (coefficient_f.size() + 1) * Better.transpose() * P.inverse() * Better) / (pow(3 * (coefficient_f.size() + 1) - ((P.inverse() + b * J.transpose() * J).inverse() * P.inverse()).trace(), 2)) << endl;
	int a = 0;
	output_angle();
	return 0;
}
