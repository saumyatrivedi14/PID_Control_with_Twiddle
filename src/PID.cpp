#include <limits>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <math.h> 
#include <uWS/uWS.h>


#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd, bool init_twiddle) {
		
	this->Kp = Kp;
	this->Ki = Ki;
	this->Kd = Kd;
	
	p_error = 0.0;
	i_error = 0.0;
	d_error = 0.0;
	
	if(init_twiddle){
		//std::cout<<"Twiddle Initiated!"<<std::endl;
		tol = 0.00001;
		dp = 0.0005;
	}
}
	

void PID::UpdateError(double cte) {
	d_error = cte - p_error;
	p_error = cte;
	i_error += cte;	
}

double PID::ControlOutput(double cte){
	UpdateError(cte);
	
	double correction = -1.0 * (Kp * p_error + Ki * i_error + Kd * d_error);
	
	if (correction > 1.0){
		correction = 1.0;
	}
	else if (correction < -1.0){
		correction = -1.0;
	}
	
	return correction;
} 

double PID::TotalError() { 
}

void PID::Reset_Simulator(uWS::WebSocket<uWS::SERVER> ws) {
  std::string reset_msg = "42[\"reset\",{}]";
  ws.send(reset_msg.data(), reset_msg.length(), uWS::OpCode::TEXT);
}

double PID::Twiddle(double total_errs, double param){
	static double best_err = std::numeric_limits<double>::max();
	static double last_param = 0.0;
	static bool reset_twiddle = false;
	static bool active_twiddle = false;
	
	cout<<"Best Avg Error: "<<(best_err/300)<<endl;
	cout<<"Dp: "<<dp<<endl;
	
	if (!active_twiddle){
		cout<<"Twiddle runnning!"<<endl;
		best_err = total_errs;
		active_twiddle = true;
		return param;
	}
		
	if (fabs(dp) > tol){
		if(reset_twiddle){
			cout<<"Reset Twiddle!"<<endl;
			last_param = param;
			param += dp;
			cout<<"Parameter increased!"<<endl;
			reset_twiddle = false;
		}
		else{
			if (total_errs < best_err){
				best_err = total_errs;
				dp *= 1.1;
				reset_twiddle = true;
			}
			else{
				if (fabs(last_param) < fabs(param)){
					last_param = param;
					param -= 2.0*dp;
					cout<<"Parameter decreased!"<<endl;
				}
				else{
					last_param = param;
					param += dp;
					dp *= 0.9;
					cout<<"Parameter kept same!"<<endl;
					reset_twiddle = true;					
				}
			}
		}
	}
	return param;
}

