#include <Servo.h>
int rcPin4 = A3; //пин подключения 4 канала 
int rcPin3 = A2; //пин подключения 3 канала 
int rcPin2 = A1; //пин подключения 2 канала 
int rcPin1 = A0;
Servo motor1;
double ch1 ; // значение 1 канала 
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
  ch1 = pulseIn(rcPin1, HIGH, 250000) ;  //ch# принимает значение канала rcPin#
  ch2 = pulseIn(rcPin2, HIGH, 250000) ;
  ch3 = pulseIn(rcPin3, HIGH, 250000) ;
  ch4 = pulseIn(rcPin4, HIGH, 250000) ;

  Serial.println(ch1+6);
  Serial.println(ch2);
  Serial.println(ch3);
  Serial.println(ch4+10);

  ch1 = (ch1-1500)/100;

  Serial.println(ch1);

  delay(100);
 /*Serial.print("znach =");
 Serial.println(ch1);
 motor1.writeMicroseconds(ch1);
 delay(1000);
 */
  
}
