#include <math.h>
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  double pi = 3.142;
  double R = 7; //from tf mini once the laser is set...
  double y = 1.9; // height of pole=1500mm + elevation = 400mm
  double t = 0.0604 * R * R;
  double p = t - (y-0.6);
  double sqr = sqrt((R*R) - (4*t*p));
  double numerator = R + sqr;
  double denominator = 2*t;
  double angle = atan(numerator / denominator);
  Serial.println(angle);

  delay(100);
  
  
}
