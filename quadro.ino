#include <Servo.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>


int rcPin1 = A0; //подключение 1 го канала приемника к входу А0
int rcPin2 = A1; //подключение 2 го канала приемника к входу А1
int rcPin3 = A2; //подключение 3 го канала приемника к входу А2
int rcPin4 = A3; //подключение 4 го канала приемника к входу А3


Servo motor1; //обозначение motor1 как сервопривода
Servo motor2; //обозначение motor2 как сервопривода
Servo motor3; //обозначение motor3 как сервопривода
Servo motor4; //обозначение motor4 как сервопривода




double ch1 ; // переменная для значение 1 канала     
double ch2 ; // переменная для значение 2 канала   
double ch3 ; // переменная для значение 3 канала
double ch4 ; // переменная для значение 4 канала


double ch1pol = 0;  //ch1pol это значение при том что ch1  принмает значение больше ____
double ch2pol = 0;  //ch1pol это значение при том что ch2  принмает значение больше ____
double ch4pol = 0;  //ch1pol это значение при том что ch4  принмает значение больше ____

double ch1otr = 0;  //ch1pol это значение при том что ch1  принмает значение меньше ____
double ch2otr = 0;  //ch1pol это значение при том что ch2  принмает значение меньше ____
double ch4otr = 0;  //ch1pol это значение при том что ch4  принмает значение меньше ____ 


// Присваиваем уникальный идентификатор для датчика. ВЕСЬ ДАЛЬНЕЙШИЙ КУСОК КОДА ДО SETUP НУЖЕН ДЛЯ РАБОТЫ АКСЕЛЕРОМЕТРА (ЕГО ТРОГАТЬ НЕ СТОИТ)//////////////////////////
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

void displaySensorDetails(void)
{
 sensor_t sensor;
 accel.getSensor(&sensor);
 Serial.println("------------------------------------");
 Serial.print ("Датчик: "); Serial.println(sensor.name);
 Serial.print ("Версия драйвера: "); Serial.println(sensor.version);
 Serial.print ("Уникальный ID: "); Serial.println(sensor.sensor_id);
 Serial.print ("Макс значение: "); Serial.print(sensor.max_value); Serial.println(" m/s^2");
 Serial.print ("Мин значение: "); Serial.print(sensor.min_value); Serial.println(" m/s^2");
 Serial.print ("Разрешение: "); Serial.print(sensor.resolution); Serial.println(" m/s^2"); 
 Serial.println("------------------------------------");
 Serial.println("");
 delay(5);
}
 
void displayDataRate(void)
{
 Serial.print ("Скорость передачи: "); 
 
 switch(accel.getDataRate())
 {
 case ADXL345_DATARATE_3200_HZ:
 Serial.print ("3200 "); 
 break;
 case ADXL345_DATARATE_1600_HZ:
 Serial.print ("1600 "); 
 break;
 case ADXL345_DATARATE_800_HZ:
 Serial.print ("800 "); 
 break;
 case ADXL345_DATARATE_400_HZ:
 Serial.print ("400 "); 
 break;
 case ADXL345_DATARATE_200_HZ:
 Serial.print ("200 "); 
 break;
 case ADXL345_DATARATE_100_HZ:
 Serial.print ("100 "); 
 break;
 case ADXL345_DATARATE_50_HZ:
 Serial.print ("50 "); 
 break;
 case ADXL345_DATARATE_25_HZ:
 Serial.print ("25 "); 
 break;
 case ADXL345_DATARATE_12_5_HZ:
 Serial.print ("12.5 "); 
 break;
 case ADXL345_DATARATE_6_25HZ:
 Serial.print ("6.25 "); 
 break;
 case ADXL345_DATARATE_3_13_HZ:
 Serial.print ("3.13 "); 
 break;
 case ADXL345_DATARATE_1_56_HZ:
 Serial.print ("1.56 "); 
 break;
 case ADXL345_DATARATE_0_78_HZ:
 Serial.print ("0.78 "); 
 break;
 case ADXL345_DATARATE_0_39_HZ:
 Serial.print ("0.39 "); 
 break;
 case ADXL345_DATARATE_0_20_HZ:
 Serial.print ("0.20 "); 
 break;
 case ADXL345_DATARATE_0_10_HZ:
 Serial.print ("0.10 "); 
 break;
 default:
 Serial.print ("???? "); 
 break;
 } 
 Serial.println(" Hz"); 
}
 
void displayRange(void)
{
 Serial.print ("Диапазон: +/- "); 
 
 switch(accel.getRange())
 {
 case ADXL345_RANGE_16_G:
 Serial.print ("16 "); 
 break;
 case ADXL345_RANGE_8_G:
 Serial.print ("8 "); 
 break;
 case ADXL345_RANGE_4_G:
 Serial.print ("4 "); 
 break;
 case ADXL345_RANGE_2_G:
 Serial.print ("2 "); 
 break;
 default:
 Serial.print ("?? "); 
 break;
 } 
 Serial.println(" g"); 
}
/////////////////////////////////////////////////////////КОНЕЦ КОДА АКСЕЛЕРОМЕТРА////////////////////////////////////////////////////////////////////////////////

void setup() {    //настройка производимая при включении 
///////////////////////////////////////////////////////ЕЩЕ НЕМНОГО КОДА ДЛЯ АКСЕЛЕРОМЕТРА////////////////////////////////////////////////////////////////////////
  Serial.println("Проверка акселерометра"); Serial.println("");
  // Инициализация датчика
  if(!accel.begin())
  {
   // Если не обнаружен, выводим сообщение о проблеме
   Serial.println("Датчик не обнаружен ... проверьте соединение!");
   while(1);
  }
  // Задайте диапазон, в соответствии с вашим проектом
  accel.setRange(ADXL345_RANGE_16_G);
  // Вывод основной информации о датчике
  displaySensorDetails();
  // Отображение дополнительных параметров
  displayDataRate();
  displayRange();
  Serial.println("");
/////////////////////////////////////////////////////////КОНЕЦ КОДА АКСЕЛЕРОМЕТРА////////////////////////////////////////////////////////////////////////////////
motor1.attach(2);   // подключение первого мотора к пину номер 2 , 1 и 2 заняты на RX и TX 
motor2.attach(3);   // подключение второго мотора к пину номер 3 
motor3.attach(4);   // подключение третьего мотора к пину номер 4
motor4.attach(5);   // подключение четвертого мотора к пину номер 5  
  
pinMode(rcPin1, INPUT);  // названичение пина под номером rcPin1 как входящего , для принятия значения с первого канала приемника 
pinMode(rcPin2, INPUT);  // названичение пина под номером rcPin2 как входящего , для принятия значения с второго канала приемника 
pinMode(rcPin3, INPUT);  // названичение пина под номером rcPin3 как входящего , для принятия значения с третьего канала приемника 
pinMode(rcPin4, INPUT);  // названичение пина под номером rcPin4 как входящего , для принятия значения с четвертого канала приемника 

Serial.begin(9600);  // настройка манитора порта 

}


void loop() { //выполняется в цикле (при работе)
 sensors_event_t event; 
 accel.getEvent(&event);
 
 // Вывод результатов (ускорение измеряется по формуле m/s^2)
 Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print(" ");
 Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print(" ");
 Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print(" ");Serial.println("m/s^2 ");

ch1 = pulseIn(rcPin1, HIGH, 250000) ;  //ch# принимает значение канала rcPin#
ch2 = pulseIn(rcPin2, HIGH, 250000) ;  //ch# принимает значение канала rcPin#
ch3 = pulseIn(rcPin3, HIGH, 250000) ;  //ch# принимает значение канала rcPin#
ch4 = pulseIn(rcPin4, HIGH, 250000) ;  //ch# принимает значение канала rcPin#

ch3 = ch3-300;

ch1pol = 0;  
ch2pol = 0;  
ch4pol = 0;  

ch1otr = 0;  
ch2otr = 0;  
ch4otr = 0;

if (ch1 > 1485) {
  ch1pol = (ch1-1485)/3;
  if (ch1pol>600 or ch1pol<40 or ch1 == 0)
  {
    ch1pol = 0;
  }
}
else 
{
  ch1otr = (-ch1+1485)/3;
  if (ch1otr>600 or ch1otr<40 or ch1 == 0)
  {
    ch1otr = 0;
  }
}

if (ch2 > 1485) {
  ch2pol = (ch2-1485)/3;
  if (ch2pol>600 or ch2pol<40 or ch2 == 0)
  {
    ch2pol = 0;
  }
}
else 
{
  ch2otr = (-ch2+1485)/3;
  if (ch2otr>600 or ch2otr<40 or ch2 == 0)
  {
    ch2otr = 0;
  }
}

if (ch4 > 1485) {
  ch4pol = (ch4-1485)/3;
  if (ch4pol>600 or ch4pol<40 or ch4 == 0)
  {
    ch4pol = 0;
  }
}
else 
{
  ch4otr = (-ch4+1485)/3;
  if (ch4otr>600 or ch4otr<40 or ch4 == 0)
  {
    ch4otr = 0;
  }
}
if (ch3 != 0 ) 

 {
          motor1.writeMicroseconds(ch3+ch1pol+ch2otr+ch4otr);
          motor2.writeMicroseconds(ch3+ch1otr+ch2otr+ch4pol);
          motor3.writeMicroseconds(ch3+ch1pol+ch2pol+ch4pol);
          motor4.writeMicroseconds(ch3+ch1otr+ch2pol+ch4otr);
 }
      
delay(5);
  
}
    
