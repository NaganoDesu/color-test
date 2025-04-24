#include "app.h"
#include "Button.h"
#include "ColorSensor.h"
#include "Port.h"
#include <iostream>

using namespace spikeapi;

ColorSensor colorsensor(EPort::PORT_C);

void main_task(intptr_t unused) {
  // 周期的に攻略(proc_task)を実行
  sta_cyc(CYC_ACT);
  slp_tsk();
  
  // 攻略処理(process)の終了
  stp_cyc(CYC_ACT);
  ext_tsk();
}

void proc_task(intptr_t exinf) {
  Button button;
  colorsensor.lightOff();
  // ev3_button_is_pressed(BACK_BUTTON)
  if (button.isCenterPressed()) {
    // バックボタンが押されたらmain_taskに制御を移す
    wup_tsk(MAIN_TASK);
  } else {
    // 攻略処理(process)の実行
    if (button.isRightPressed())
    {
      ColorSensor::HSV hsv;
      colorsensor.getHSV(hsv);
      printf("H:%u, S:%u, V:%u\n", hsv.h, hsv.s, hsv.v);
    } else if (button.isLeftPressed()) {
      ColorSensor::RGB rgb;
      colorsensor.getRGB(rgb);
      printf("R:%u, G:%u, B:%u\n", rgb.r, rgb.g, rgb.b);
    }
  }
  ext_tsk();
}
