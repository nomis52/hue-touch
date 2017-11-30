#include "controller.h"

Controller controller;

void setup() {
  controller.Init();
}

void loop() {
  controller.Loop();
}

