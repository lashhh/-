#include <SoftwareSerial.h>
#include<Servo.h>
Servo s;
int p;
int STBY = 10; //standby
 
//Motor A
int PWMA = 11; //A轮速度控制 
int AIN1 = 12; //方向
int AIN2 = 13; //方向
 
//Motor B
int PWMB = 6; //轮速度控制
int BIN1 = 8; //方向
int BIN2 = 7; //方向

SoftwareSerial ESP_Serial(2,3); //软串口定义，2为Tx,3为Rx

void forward(){
   move(2, 110, 0); 
   move(1, 110, 0);
   delay(750); //前进0.75s
   stop(); //停止
}
void Forward(){
   move(2, 110, 0); 
   move(1, 110, 0);
   delay(2000); //前进2s
   stop(); //停止
}
void backward(){
   move(1, 110, 1); 
   move(2, 110, 1);
   delay(750); //后退0.75s
   stop(); //停止
}
void right(){
   move(1, 80, 0); 
   move(2, 80, 1);
   delay(500); //运行0.5s
   stop(); //停止
}
void left(){
   move(1, 80, 1); 
   move(2, 80, 0);
   delay(500); //运行0.5s
   stop(); //停止
}

void move(int motor, int speed, int direction){
//motor: 0 即 B，1 即 A
  digitalWrite(STBY, HIGH);
 
  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;
 
  if(direction == 1){
    inPin1 = HIGH;
    inPin2 = LOW;
  }
 
  if(motor == 1){
    digitalWrite(AIN1, inPin1);
    digitalWrite(AIN2, inPin2);
    analogWrite(PWMA, speed);
  }else{
    digitalWrite(BIN1, inPin1);
    digitalWrite(BIN2, inPin2);
    analogWrite(PWMB, speed);
  }
}
 
void stop(){
  
  digitalWrite(STBY, LOW); 
}

void SerCatch() { //抓取

    s.write(50);
    delay(30);
}

void SerRelease() { //释放
    s.write(80);
    delay(30);
}

void setup() {
  s.attach(5);     //定义舵机输出口
  Serial.begin(9600);  //定义串口波特率
  ESP_Serial.begin(115200);  //定义软串口波特率
  //定义各个引脚
  
  pinMode(STBY, OUTPUT);
 
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
 
  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
}

void loop() {
  while (ESP_Serial.available() > 0)  //判断是否获得数据
  {
    p = ESP_Serial.parseInt();
    Serial.println(p);
  }
  
  if (p == 1)
  {
    SerCatch();
  }
  else if (p == 0)
  {
    SerRelease();
  }
  else if(p==2){
    forward();
  }
  else if(p==3){
    backward();
  }
  else if(p==4){
    left();
  }
  else if(p==5){
    right();
  }
  else if(p==6){
    Forward();
  }
  delay(2000);
}
