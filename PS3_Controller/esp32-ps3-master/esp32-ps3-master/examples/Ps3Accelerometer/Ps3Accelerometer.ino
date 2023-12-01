#include <Ps3Controller.h>

void notify()
{
    Serial.print(Ps3.data.sensor.accelerometer.x);
    Serial.print(" ");
    Serial.print(Ps3.data.sensor.accelerometer.y);
    Serial.print(" ");
    Serial.print(Ps3.data.sensor.accelerometer.z);

    /* Uncomment the following if you also want
       to display the gryoscope data: */
    // Serial.print(" ");
    // Serial.print(Ps3.data.sensor.gyroscope.z);

    Serial.println();
}


void setup()
{
    Serial.begin(115200);
    Ps3.attach(notify);
    Ps3.begin("a0:5a:5a:a0:09:67");
}


void loop()
{

}
