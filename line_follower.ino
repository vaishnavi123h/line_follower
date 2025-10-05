#define i0 29   // Leftmost
#define i1 31
#define i2 33   // Center
#define i3 35
#define i4 37   // Rightmost

#define pl 6
#define pr 8
#define inl 7
#define inr 9

int s0,s1,s2,s3,s4;
int e = 0;
int prev_e = 0;
long t = 0;
long time = 0;
long prev_time = 0;
float ref_error = 0;
float error = 0;
float kp = 18;
float ki = 0.01;
float kd = 0.01;
float I = 0;
float D = 0;
float u = 0;
bool stop = 0;

void setup() {
  pinMode(i0, INPUT_PULLUP);
  pinMode(i1, INPUT_PULLUP);
  pinMode(i2, INPUT_PULLUP);
  pinMode(i3, INPUT_PULLUP);
  pinMode(i4, INPUT_PULLUP);

  pinMode(pl, OUTPUT);
  pinMode(pr, OUTPUT);
  pinMode(inl, OUTPUT);
  pinMode(inr, OUTPUT);

  Serial.begin(115200);
}

void loop() {
  cal_error();
  PID();

  while(stop) {
    motor_free();
    cal_error();
  }
}

void cal_error() {
  s0 = digitalRead(i0);
  s1 = digitalRead(i1);
  s2 = digitalRead(i2);
  s3 = digitalRead(i3);
  s4 = digitalRead(i4);

  // ---- Error Mapping for 5 IR sensors ----
  if(s0==0 && s1==1 && s2==1 && s3==1 && s4==1) {   // Line far left
    error = +2;
    stop = 0;
  }
  else if(s0==0 && s1==0 && s2==1 && s3==1 && s4==1) {  // Slight left
    error = +1;
    stop = 0;
  }
  else if(s0==1 && s1==0 && s2==1 && s3==0 && s4==1) {  // Perfect center
    error = 0;
    stop = 0;
  }
  else if(s0==1 && s1==1 && s2==1 && s3==0 && s4==0) {  // Slight right
    error = -1;
    stop = 0;
  }
  else if(s0==1 && s1==1 && s2==1 && s3==1 && s4==0) {  // Line far right
    error = -2;
    stop = 0;
  }
  else if(s0==1 && s1==1 && s2==1 && s3==1 && s4==1) {  // All white
    stop = 1;
    motor_free();
  }
  else if(s0==0 && s1==0 && s2==0 && s3==0 && s4==0) {  // All black
    stop = 1;
    motor_free();
  }
}

void PID() {
  time = millis();
  if(time - prev_time > 50) {
    t = time - prev_time;
    e = error - ref_error;
    D = (e - prev_e) * 20;
    I = I + e * 0.05;
    u = kp*e + kd*D + ki*I;

    set_motor(20 + u, 20 - u);

    prev_e = e;
    prev_time = millis();
  }
}

void right_motor(float pwm) {
  if(pwm < 0) pwm = 0;
  analogWrite(pl, pwm);
  digitalWrite(inl, 1);   // inl = 1 : anticlockwise
}

void left_motor(float pwm) {
  if(pwm < 0) pwm = 0;
  analogWrite(pr, pwm);
  digitalWrite(inr, 1);   // inr = 1 : clockwise
}

void motor_free() {
  left_motor(0);
  right_motor(0);
  analogWrite(pl, 0);
  analogWrite(pr, 0);
}

void set_motor(float l, float r) {
  if (l >= 0) {
    analogWrite(pl, l);
    digitalWrite(inl, LOW);
  } else {
    analogWrite(pl, -l);
    digitalWrite(inl, HIGH);
  }

  if (r >= 0) {
    analogWrite(pr, r);
    digitalWrite(inr, LOW);
  } else {
    analogWrite(pr, -r);
    digitalWrite(inr, HIGH);
  }
}

