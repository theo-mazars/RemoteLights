#include <analogWrite.h>
#include "GPIO.h"

void rgbDisplay(uint32_t r, uint32_t g, uint32_t b)
{
    analogWrite(RED, r, 255U);
    analogWrite(GREEN, g, 255U);
    analogWrite(BLUE, b, 255U);
}
