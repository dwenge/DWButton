#include <DWButton.h>

DWButton k1(A3, 15, 500);
DWButton k2(A3, 73, 1000);
DWButton k3(A3, 125, 1500);
DWButton k4(A3, 172, 2000);

void setup() {
  Serial.begin(115200);
}

void loop() {

  //if (k1.isPresses()) Serial.println("K1 presses!");
  if (k1.isPress()) Serial.println("K1 press!");
  if (k1.isClick()) Serial.println("K1 clicked!");
  if (k1.isHold()) Serial.println("K1 hold!");
  if (k1.isRelease()) Serial.println("K1 release!");

  if (k2.isClick()) Serial.println("K2 clicked!");
  if (k2.isHold()) Serial.println("K2 hold!");
  if (k2.isRelease()) Serial.println("K2 release!");

  if (k3.isClick()) Serial.println("K3 clicked!");
  if (k3.isHold()) Serial.println("K3 hold!");
  if (k3.isRelease()) Serial.println("K3 release!");

  if (k4.isClick()) Serial.println("K4 clicked!");
  if (k4.isHold()) Serial.println("K4 hold!");
  if (k4.isRelease()) Serial.println("K4 release!");
  
  k1.tick();
  k2.tick();
  k3.tick();
  k4.tick();
}
