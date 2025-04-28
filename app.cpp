#include "app.h"
#include "Button.h"
#include "ColorSensor.h"
#include "Port.h"
#include <iostream>

using namespace spikeapi;

ColorSensor colorsensor(EPort::PORT_C);
Button button;
bool lightOn = true;

void main_task(intptr_t unused) {
  // 周期的に攻略(proc_task)を実行
  sta_cyc(CYC_ACT);
  slp_tsk();
  
  // 攻略処理(process)の終了
  stp_cyc(CYC_ACT);
  ext_tsk();
}

void proc_task(intptr_t exinf) {
    if (button.isRightPressed())
    {
        ColorSensor::HSV hsv;
        colorsensor.getHSV(hsv);
        printf("[HSV] H:%u, S:%u, V:%u\n", hsv.h, hsv.s, hsv.v);
    }
    else if (button.isLeftPressed())
    {
        ColorSensor::RGB rgb;
        colorsensor.getRGB(rgb);
        printf("[RGB] R:%u, G:%u, B:%u\n", rgb.r >> 2, rgb.g >> 2, rgb.b >> 2);
    }
    else if (button.isCenterPressed())
    {
        printf("exit task\n");
        wup_tsk(MAIN_TASK);
    }
    else if (button.isBluetoothPressed())
    {
        if (lightOn)
        {
            printf("light off\n");
            colorsensor.lightOff();
            lightOn = false;
        }
        else
        {
            printf("light on\n");
            colorsensor.lightOn();
            lightOn = true;
        }
    }
}
