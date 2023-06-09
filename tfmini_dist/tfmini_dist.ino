
#include <SoftwareSerial.h>  //header file of software serial port
#include <math.h>
SoftwareSerial Serial1(2,3); //define software serial port name as Serial1 and define pin2 as RX and pin3 as TX

/* For Arduinoboards with multiple serial ports like DUEboard, interpret above two pieces of code and directly use Serial1 serial port*/

int dist; //actual distance measurements of LiDAR
int strength; //signal strength of LiDAR
int check;  //save check value
int i;
int uart[9];  //save data measured by LiDAR
const int HEADER=0x59;  //frame header of data package

void setup() {
  Serial.begin(9600); //set bit rate of serial port connecting Arduino with computer
  Serial1.begin(115200);  //set bit rate of serial port connecting LiDAR with Arduino
}

void loop() { 
  if (Serial1.available()) {  //check if serial port has data input
    if(Serial1.read() == HEADER) {  //assess data package frame header 0x59
      uart[0]=HEADER;
      if (Serial1.read() == HEADER) { //assess data package frame header 0x59
        uart[1] = HEADER;
        for (i = 2; i < 9; i++) { //save data in array
          uart[i] = Serial1.read();
        }
        check = uart[0] + uart[1] + uart[2] + uart[3] + uart[4] + uart[5] + uart[6] + uart[7];
        if (uart[8] == (check & 0xff)){ //verify the received data as per protocol
          dist = uart[2] + uart[3] * 256;     //calculate distance value
          strength = uart[4] + uart[5] * 256; //calculate signal strength value
  double dist_m = dist /100;
  #define PI 3.1415926535897932384626433832795
  double R = dist_m; //from tf mini once the laser is set...
  double y = 1.9; // height of pole=1500mm + elevation = 400mm
  double t = 0.06049382716 * R * R;
  double p = t - (y-0.6);
  double sqr = sqrt((R*R) - (4*t*p));
  double numerator = R - sqr;  // roots - R +- sqr
  double denominator = 2*t;
  double angle = atan(numerator / denominator);
  double angle_deg = (angle * 180)/PI;
//    Serial.println(angle_deg); 
      if(!isnan(angle)){
          Serial.print("dist = ");
          Serial.print(dist); //output measure distance value of LiDAR
          Serial.print('\t');
          Serial.print("angle = ");
          Serial.print(angle_deg); 
          Serial.print('\n');
      }

          
        }
      }
    }
  }
}

/*
Download the program into Arduino board and power on monitor for serial port. Then real-time distance values measured by LiDAR and corresponding signal strength can be viewed.

In addition, data curve can be viewed in curve plotter for serial port, provided, however, that the above code regarding printing for serial port should be modified:

//  Serial.print("dist = ");
Serial.print(dist);//output measure distance value of LiDAR
Serial.print(' ');
//  Serial.print("strength = ");        
Serial.print(strength);//output signal strength value
Serial.print('\n');

Reinterpret and download the program into Arduino board and power on the curve plotter. Then two curves representing dist and strength can be viewed.
*/
