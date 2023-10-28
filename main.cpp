#include "src/Motor.h"
#define DirectionPin 4
#define BaudRate 115200

// left = +
// right = -

int M;
int time_mili = 0;
//
void time_target_forward_backward(int RPM, int distance, char dir_fb)
{
  int count_fb;
  float interval_fb = (distance * 10) / (RPM * (2 * (3.142) / 60000) * 33.8);
  long cur_time = millis();
  time_mili = millis();

  if (dir_fb == 'F')
  {
    while (time_mili - cur_time < interval_fb)
    {
      Motor.turnWheel(1, LEFT, RPM);
      Motor.turnWheel(2, RIGHT, RPM + 1);
      time_mili = millis();
      Serial.println("Done moving Forward");
    }
  }
  else if (dir_fb == 'B')
  {
    while (time_mili - cur_time < interval_fb)
    {
      Motor.turnWheel(1, RIGHT, RPM);
      Motor.turnWheel(2, LEFT, RPM + 1);
      time_mili = millis();
      Serial.println("Done moving Backward");
    }
  }
}

void time_target_turn(int RPM_1, int RPM_2, int angle, String dir_to_turn)
{
  int count_lr;
  int wheels = RPM_1 * RPM_2;
  long cur_time_turn = millis();
  int interval_90 = 1120;
  int interval_45 = 900;
  time_mili = millis();

  if (RPM_1 == 0 && dir_to_turn == "tL")
  { // turn-left
    while (time_mili - cur_time_turn < interval_90)
    {
      Motor.turnWheel(1, LEFT, 0);
      Motor.turnWheel(2, RIGHT, RPM_2);
      time_mili = millis();
      Serial.println("Done turning left");
    }
  }
  else if (RPM_1 != 0 && dir_to_turn == "tR")
  { // turn right
    while (time_mili - cur_time_turn < interval_90)
    {
      Motor.turnWheel(1, LEFT, RPM_1);
      Motor.turnWheel(2, RIGHT, 0);
      time_mili = millis();
      Serial.println("Done turning right");
    }
  }
  else if (RPM_1 != 0 && dir_to_turn == "tR_45")
  { // turn right
    while (time_mili - cur_time_turn < interval_45)
    {
      Motor.turnWheel(1, LEFT, RPM_1);
      Motor.turnWheel(2, RIGHT, 0);
      time_mili = millis();
      Serial.println("Done turning right");
    }
  }  
  else if (RPM_2 != 0 && dir_to_turn == "tL_45")
  { // turn right
    while (time_mili - cur_time_turn < interval_45)
    {
      Motor.turnWheel(1, LEFT, 0);
      Motor.turnWheel(2, RIGHT, RPM_2);
      time_mili = millis();
      Serial.println("Done turning right");
    }
  }
}

void move_twowheels_front(int RPM_1, int RPM_2)
{
  float interval_fb = (45 * 10) / (RPM_1 * (2 * (3.142) / 60000) * 33.8);
  long cur_time = millis();
  time_mili = millis();

  while (time_mili - cur_time < interval_fb)
  {
    Motor.turnWheel(1, LEFT, RPM_1);
    Motor.turnWheel(2, RIGHT, RPM_2);
    time_mili = millis();
    Serial.println("Done turning left");
  }
}

void stopp()
{
  Motor.turnWheel(1, LEFT, 0);
  Motor.turnWheel(2, RIGHT, 0);
  delay(500);
}

void setup()
{
  Serial.begin(115200);
  Motor.begin(BaudRate, DirectionPin, &Serial2);
}

void loop()
{
}
