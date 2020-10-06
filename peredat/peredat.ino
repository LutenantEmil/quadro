#include <Servo.h>
int rcPin4 = 5; //пин подключения 4 канала 
int rcPin3 = 4; //пин подключения 3 канала 
int rcPin2 = 3; //пин подключения 2 канала 
int rcPin1 = 2;
Servo motor1;
int ch1 ; // значение 1 канала 
int ch2 ; // значение 2 канала
int ch3 ; // значение 3 канала
int ch4 ; // значение 4 канала
void setup() {
  Serial.begin(9600);
  pinMode(rcPin1, INPUT);  // названичение пина под номером rcPin1 как входящего , для принятия значения с первого канала приемника 
  pinMode(rcPin2, INPUT);  // названичение пина под номером rcPin2 как входящего , для принятия значения с первого канала приемника 
  pinMode(rcPin3, INPUT);  // названичение пина под номером rcPin3 как входящего , для принятия значения с первого канала приемника 
  pinMode(rcPin4, INPUT);  // названичение пина под номером rcPin4 как входящего , для принятия значения с первого канала приемника 
}
void loop() {
  ch1 = pulseIn(rcPin1, HIGH, 25000) ;  //ch# принимает значение канала rcPin#
  ch2 = pulseIn(rcPin2, HIGH, 25000) ;
  ch3 = pulseIn(rcPin3, HIGH, 25000) ;
  ch4 = pulseIn(rcPin4, HIGH, 25000) ;

  Serial.println(ch1);
  Serial.println(ch2);
  Serial.println(ch3);
  Serial.println(ch4);
  
 /*Serial.print("znach =");
 Serial.println(ch1);
 motor1.writeMicroseconds(ch1);
 delay(1000);
 */
  
}
