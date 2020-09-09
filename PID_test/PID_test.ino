#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
 int rcPin1 = A1; //пин подключения 1 канала 
 int ch1 ; // значение 1 канала 
 const double Kp = 4;
 const double Ki = 0.2;
 const double Kd = 1; 

 double errorX = 0;
 double preerrX = 0;
 double pid_px = 0;
 double pid_ix = 0; 
 double pid_dx = 0;

 double errorX = 0;
 double preerrY = 0;
 double pid_pY = 0;
 double pid_iY = 0; 
 double pid_dY = 0;

// Присваиваем уникальный идентификатор для датчика
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
 delay(500);
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
 
void setup(void) 
{
 Serial.begin(9600);
 Serial.println("Проверка акселерометра"); Serial.println("");

  pinMode(rcPin1, INPUT);  // названичение пина под номером rcPin1 как входящего , для принятия значения с первого канала приемника 
  
 // Инициализация датчика
 if(!accel.begin())
 {
 // Если не обнаружен, выводим сообщение о проблеме
 Serial.println("Датчик не обнаружен ... проверьте соединение!");
 while(1);
 }
 
 // Задайте диапазон, в соответствии с вашим проектом
 accel.setRange(ADXL345_RANGE_16_G);
 // displaySetRange(ADXL345_RANGE_8_G);
 // displaySetRange(ADXL345_RANGE_4_G);
 // displaySetRange(ADXL345_RANGE_2_G);
 
 // Вывод основной информации о датчике
 displaySensorDetails();
 
 // Отображение дополнительных параметров
 displayDataRate();
 displayRange();
 Serial.println("");
}
 
void loop(void) 
{
  ch1 = pulseIn(rcPin1, HIGH, 250000) ;
 // Получение нового события датчика
 sensors_event_t event; 
 accel.getEvent(&event);
 
 // Вывод результатов (ускорение измеряется по формуле m/s^2)
 Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print(" ");
 Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print(" ");
 Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print(" ");Serial.println("m/s^2 ");


     
      double  pch = ch1 -1520;
      preerrX = errorX;
      
      errorX = event.acceleration.x*25 - pch ;
      
      pid_px = errorX*Kp;
      if (pid_px > 500)
      {
        pid_px = 500; 
      }
      
      if (pid_px < -500)
      {
        pid_px = -500; 
      }
      
      pid_ix = pid_ix + (errorX*Ki);
            if (pid_ix > 500)
      {
        pid_ix = 500; 
      }
            if (pid_ix < -500)
      {
        pid_ix = -500; 
      }
      
      pid_dx = ((pid_px-preerrX)*Kd)/10;
            if (pid_dx > 500)
      {
        pid_dx = 500; 
      }
            if (pid_dx < -500)
      {
        pid_dx = -500; 
      }
      delay (10);
      Serial.print("Пропорциональная ошибка ");Serial.println(pid_px);
      Serial.print("Интегральная ошибка");Serial.println(pid_ix);
      Serial.print("Диференциальная ошибка");Serial.println(pid_dx);
      
      
 delay(400);
}
