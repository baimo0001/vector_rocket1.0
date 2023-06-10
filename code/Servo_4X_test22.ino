#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Servo.h>

Adafruit_MPU6050 mpu;
int x = 0;
int y = 0;
int z = 0;

Servo servo1; 
Servo servo2;
Servo servo3;
Servo servo4;

int value  = 0;

void setup(void) {
  Serial.begin(115200);

  // 尝试初始化
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  // 将加速度计范围设置为 +-8G
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  // 将陀螺仪范围设置为 +- 500 度/秒
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  // 将滤波器带宽设置为 21 Hz
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(100);
  servo1.attach(8);
  //servo2.attach(6); 
  //servo3.attach(5); 
  servo4.attach(6); 

  servo1.write(90);
  servo2.write(0);
  servo3.write(0);
  servo4.write(90);
}

void loop() {
  /* 使用读数获取新的传感器事件 */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

////acceleration就是加速度的意思///
  x = a.acceleration.x;
  y = a.acceleration.y;
  z = a.acceleration.z;
  
  Serial.print(x);Serial.print(" ");
  Serial.println(y);Serial.print(" ");
  Serial.println(z);Serial.print("\n");
  
if (x < 10 && x > 0 && y < 4 && y > -4){
  Serial.println("up");
   value = map(x,  0, 10, 0, 180);
   servo1.write(value);
   Serial.print(value);
  }
else if (x > -10 && x < 0 && y < 4 && y > -4){   //2
  Serial.println("down");
  value = map(x,  -10, 0, 180, 0);
  servo1.write(180-value);
  Serial.print(value);
  }

if (y < 10 && y > 0 && x < 4 && x > -4){      //3
  Serial.println("Right");
  value = map(y,  0, 10, 0, 180);
  servo4.write(180-value);
  Serial.print(value);
  }
else if (y > -10 && y < 0  && x < 4 && x > -4){
  Serial.println("left");
  value = map(y,  -10, 0, 180, 0);
  servo4.write(value);
  Serial.print(value);
  }
}
