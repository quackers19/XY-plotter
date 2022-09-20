#include <AFMotor.h>
#include <Servo.h>

// Connect a stepper motor with 48 steps per revolution (7.5 degree)
// to motor port #2 (M3 and M4)
AF_Stepper motor1(200, 1);
AF_Stepper motor2(200, 2);

Servo pen;

int penpos = 60;

//mm per step
double const step_distance = 0.16;

//cords
int const minx = 0;
int const maxx = 210;
int const miny = 0;
int const maxy = 297;

//motor x and y cords
int const m1x = -83;
int const m1y = -115;
int const m2x = 300;
int const m2y = -115;

double m1_line = 134;
double m2_line = 190;
double new_m1_line = 134;
double new_m2_line = 190;
double distance_m1;
double distance_m2;
int steps_m1;
int steps_m2;

float targetx;
float targety;

float ratio;
int m1_line_step = 1;
int m2_line_step;
int steps_done_m1;
int steps_done_m2;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(1);
  motor1.setSpeed(10);  // 10 rpm
  motor2.setSpeed(10);

  pen.attach(10);
  pen.write(penpos);
  
  delay(5000);
  Serial.print("ready");
  delay(1000);
 
}

void loop() {

 delay(500);
 String cmd = Serial.readString();
 
 if (cmd.startsWith("s")) {
  Serial.print("next");
 }
 else if (cmd.endsWith("u")) {
  penpos = 60;
  pen.write(penpos);
  delay(300);
  Serial.print("next");
 }
 else if (cmd.endsWith("d")) {
  penpos = 160;
  pen.write(penpos);
  delay(300);
  Serial.print("next");
 }
 else if (cmd.charAt(2) == '0' or cmd.charAt(2) == '1') {

  //get x cord from cmd
  int increment = 6;
  
  while (cmd.charAt(increment) != '.') {
    increment += 1;
  }
  
  targetx = cmd.substring(5, increment).toFloat();

  //get y cord from cmd
  increment = 5;
  int ystart = 5;
  while (cmd.charAt(ystart) != 'Y') {
    ystart += 1;
  }
  ystart += 1;
  increment = ystart;
  while (cmd.charAt(increment) != '.') {
    increment += 1;
  }

  targety = cmd.substring(ystart, increment).toFloat();

  //find line length
  new_m1_line = sqrt(sq(targetx-m1x)+sq(targety-m1y));
  new_m2_line = sqrt(sq(targetx-m2x)+sq(targety-m2y));
  
  //find distance
  distance_m1 = new_m1_line - m1_line;
  distance_m2 = new_m2_line - m2_line;

  steps_m1 = distance_m1 / step_distance;
  steps_m2 = distance_m2 / step_distance;

  m1_line = new_m1_line;
  m2_line = new_m2_line;

  //ratio and fighurings out order of stuff
  if (abs(steps_m1) < abs(steps_m2)) {
    ratio = abs(steps_m2) / abs(steps_m1);
    m1_line_step = round(1 * ratio);
    m2_line_step = 1;
  }
  else if (abs(steps_m1) > abs(steps_m2)) {
    ratio = abs(steps_m1) / abs(steps_m2);
    m2_line_step = round(1 * ratio);
    m1_line_step = 1;
  }
  else {
    ratio = 1;
    m1_line_step = 1;
    m2_line_step = 1;
  }
  

  //start moving stuff
  steps_done_m1 = 0;
  steps_done_m2 = 0;
  while (steps_done_m1 < abs(steps_m1) or steps_done_m2 < abs(steps_m2)){
    //if both need to move
    if (steps_done_m1 < abs(steps_m1) and steps_done_m2 < abs(steps_m2)) {
       steps_done_m1 += m1_line_step;
       steps_done_m2 += m2_line_step;
       for (int i = 0; i <= m1_line_step; i++) {
        if (steps_m1 < 0) {
          motor1.onestep(BACKWARD, SINGLE);
          delay(1);
        }
        else if (steps_m1 > 0) {
          motor1.onestep(FORWARD, SINGLE);
          delay(1);
        }
        else {
        } 
       }
       for (int i = 0; i <= m2_line_step; i++) {
        if (steps_m2 < 0) {
          motor2.onestep(BACKWARD, SINGLE);
          delay(1);
        }
        else if (steps_m2 > 0) {
          motor2.onestep(FORWARD, SINGLE);
          delay(1);
        }
        else {
        } 
       }
    }
    //if m1 needs to move
    else if (steps_done_m1 < abs(steps_m1)) {
       steps_done_m1 += m1_line_step;
       for (int i = 0; i <= m1_line_step; i++) {
        if (steps_m1 < 0) {
          motor1.onestep(BACKWARD, SINGLE);
          delay(1);
        }
        else if (steps_m1 > 0) {
          motor1.onestep(FORWARD, SINGLE);
          delay(1);
        }
        else {
        } 
       }
    }
    //if m2 needs to move
    else if (steps_done_m2 < abs(steps_m2)) {
       steps_done_m2 += m2_line_step;
       for (int i = 0; i <= m2_line_step; i++) {
        if (steps_m2 < 0) {
          motor2.onestep(BACKWARD, SINGLE);
          delay(1);
        }
        else if (steps_m2 > 0) {
          motor2.onestep(FORWARD, SINGLE);
          delay(1);
        }
        else {
        } 
       }
    }
    
    
    
  }
  
  
  Serial.print("next");
 }
 else {
  //Serial.print("opps");
 }
}
