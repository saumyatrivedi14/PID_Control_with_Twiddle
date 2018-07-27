#ifndef PID_H
#define PID_H

class PID {
public:
 
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;
  
  /*
	Twiddle Parameters
  */

  double tol;
  double dp;

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd, bool init_twiddle);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);
  
  /*
	Control output from the PID controller
  */
  double ControlOutput(double cte);
  
  /*
	Reset Simulator
  */
  void Reset_Simulator(uWS::WebSocket<uWS::SERVER> ws);

  /*
  * Calculates the total error during the Twiddle step.
  */
  double TotalError();
  
  /*
	Tunes one hyperparameter at a time
  */
  double Twiddle(double sum_errs, double param);
  
};

#endif /* PID_H */
