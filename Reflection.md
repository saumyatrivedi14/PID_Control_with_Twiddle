# Reflection of Project
---
[//]: # (Image References)
[image1]: ./media/PID-feedback-loop-v1.png "PID Controller"

## Introduction to PID Controller
---
The general schematic diagram of a PID controller is shown below, it is a closed loop feedback controller used in many ways in industry.
It calculates the error (difference between a set-point and measured feedback) and corrects it using three terms: Proportional, Integral and Derivative. 

![alt text][image1]

In this project the setpoint reference is the center-line of the road and the cross-talk-error (CTE) is measured in realtime as the vehicle deviates from the center-line. 

Proportional Term - It dpeicts linear relationship between the control output and the error. If the error gets bigger, the control action gets bigger. If the gain (Kp) is too low, the system never turns towards the set-point and if its too large, then it will oscillate around set-point and become marginally stable or unstable after a point.

Integral Term - The integral component (Ki) sums the error term over time. The result is that even a small error term will cause the integral component to increase slowly. The integral response will continually increase over time and redusces the Steady-State error to zero, it doesn't play role in Transient error reduction. A phenomenon called integral windup results when integral action saturates a controller without the controller driving the error signal toward zero.

Derivative Term - The derivative component (Kd) causes the output to decrease if the process variable is increasing rapidly. The derivative response is proportional to the rate of change of the process variable. Increasing the derivative term will cause the control system to react more strongly to changes in the error term and will increase the speed of the overall control system response.

## Effect of Hyperparameters
---
I started with Proprtional-gain (Kp), increasing it also increased the oscillations of the car around the center-line just like a spring. Lower Kp didn't get the car back in time while with higher Kp, it produced high overshoots and constant oscillations.

Derivative gain (Kd) introduced the damping of the oscillations. With higher Kd, it increased high frequency oscillations, making controller too sensitive to error changes. 

Integral gain (Ki) had no effect on the transient response as expected but it helped in getting the 
steady state error to zero, but there were instances when I ended up in a integral wind up problem.

After few iterations, the hypermeters selected were:
```sh
Kp = 0.1, Ki = 0.001, Kd = 1.0
```

These hyper-parameters were chosen as initial values for auto-tuning using twiddle algorithm. Each hyperparameter was selected individually with different increment(dp) and tolerance limits (tol) to twing. I started with Kp and kept other parameters constant, the simulator ran for 300 steps and Average Tuning Error was recorded to change the hypermparameter values in the direction of least error.

Similarly, Kd and Ki was tuned keeping other parameters constant. The final hyperparameters values selected were:
```sh
Kp = 0.1576, Ki = 0.0003, Kd = 1.4530
```

## Further Improvements
---
With the current implementation, one draws back is to tune each parameter with different incremental values which can be merged together into one single algorithm where when twiddle is activated, it tunes all three hyperparameters and returns best values for all three. One more addition which would be great would be the PID speed controller, which can make the car go at higher speeds because at higher speeds the turns are more tighter and have aggressive gain values. An alternative solution to above idea could be to create a lookup table of best values of hyperparameters at different speeds, so that it reduces the computational load to run two PID controllers.
