#  Line Following Robot (PID Control)

This project implements a **PID-controlled line follower robot** using **5 IR sensors** and an Arduino-compatible board.  
The robot detects the line position, calculates an error, and adjusts motor speeds using a PID algorithm for smooth and accurate tracking.



## 📌 Features
- Uses **5 IR sensors** (`i0` to `i4`) for line detection.  
- Implements **PID control** (`Kp`, `Ki`, `Kd`) for smooth turns and stability.  
- Stops automatically if the line is lost (all white) or robot goes completely off track (all black).  
- Modular motor control functions (`set_motor()`, `motor_free()`).  
- Tunable PID gains for different track conditions.



##  Hardware Requirements
- Arduino (or compatible microcontroller)  
- 5 x IR Sensors (digital output type)  
- Motor driver (e.g., L298N, L293D, or similar)  
- 2 x DC Motors with wheels  
- Power supply (Li-ion / Li-Po / Battery pack)  



##  Pin Connections
### IR Sensors
| Sensor          | Pin |
|-----------------|-----|
| Leftmost (i0)   | 29  |
| i1              | 31  |
| Center (i2)     | 33  |
| i3              | 35  |
| Rightmost (i4)  | 37  |

### Motor Driver
| Motor       | Enable | Input |
|-------------|--------|-------|
| Left Motor  | pl = 6 | inl = 7 |
| Right Motor | pr = 8 | inr = 9 |


##  PID Parameters
You can tune the PID constants for best performance:

float kp = 18;
float ki = 0.01;
float kd = 0.01;


##  Error Mapping
The robot uses sensor readings to calculate error:

- `+2` → Line far left  
- `+1` → Line slightly left  
- `0`  → Centered  
- `-1` → Line slightly right  
- `-2` → Line far right  
- **Stop** → All sensors white (lost line) or all black  



##  How It Works
1. Sensors detect line position.  
2. Error is calculated using `cal_error()`.  
3. PID algorithm (`PID()`) computes correction value.  
4. Motors are driven with adjusted PWM (`set_motor()`).  
5. Robot follows the line smoothly.  


