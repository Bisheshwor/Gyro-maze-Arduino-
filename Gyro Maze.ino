// RemoteXY select connection mode and include library  
#define REMOTEXY_MODE__SOFTSERIAL
#include <SoftwareSerial.h> 
#include <RemoteXY.h> 
#include <Wire.h>
#include <Servo.h>

// RemoteXY connection settings  
#define REMOTEXY_SERIAL_RX 2 
#define REMOTEXY_SERIAL_TX 3 
#define REMOTEXY_SERIAL_SPEED 9600


// RemoteXY configurate   
#pragma pack(push, 1) 
uint8_t RemoteXY_CONF[] = 
  { 255,3,0,1,0,35,0,8,0,0,
  5,16,32,9,43,43,2,26,31,2,
  0,4,7,14,8,2,26,31,31,79,
  78,0,79,70,70,0,65,4,86,51,
  9,9 }; 
   
// this structure defines all the variables of your control interface  
struct { 

    // input variable
  int8_t joystick_x=0; // =-100..100 x-coordinate joystick position 
  int8_t joystick_y=0; // =-100..100 y-coordinate joystick position 
  uint8_t switch_1=0; // =1 if switch ON and =0 if OFF 

    // output variable
  uint8_t led_1_r=0; // =0..255 LED Red brightness 

    // other variable
  uint8_t connect_flag=0;  // =1 if wire connected, else =0 

} RemoteXY; 
#pragma pack(pop) 

//           END RemoteXY include          // 

#define PIN_SWITCH_1 13

// defination for servo motor
Servo ServoMot_X;
Servo ServoMot_Y;

int16_t GyX=0;
int16_t GyY=0; //Variabile int a 16bit

int16_t x=30 ;
void setup()  
{ 
  RemoteXY_Init ();  
   
  pinMode (PIN_SWITCH_1, OUTPUT);

  // TODO you setup code 

  ServoMot_X.attach(10);
  ServoMot_Y.attach(9);
  Serial.begin(9600);
  
} 

void loop()  
{  
  RemoteXY_Handler (); 
   
  digitalWrite(PIN_SWITCH_1, (RemoteXY.switch_1==0)?LOW:HIGH);
  
   
  // TODO you loop code 
  // use the RemoteXY structure for data transfer 
  GyX=(RemoteXY.joystick_x)*x;
  GyY=(RemoteXY.joystick_y)*x;
  
  int PosServo_X = map(GyX, -16000, 16000, -15, 180);
  int PosServo_Y = map(GyY, 16000, -16000, -35,180);

  ServoMot_X.write(PosServo_X);
  ServoMot_Y.write(PosServo_Y);

  //Serial.println("Giroscopo");
  //Serial.print("Asse X : "); Serial.println(PosServo_X);
  //Serial.print("Asse Y : "); Serial.println(PosServo_Y);
  //Serial.println(" ");
  delay(100);


}
