#include <string>
#include "ledsControl.h"

const char *white(std::string &state)
{
  rgbDisplay(255, 255, 255);
  state.assign("white");
  return state.c_str();
}

const char *off(std::string &state)
{
  rgbDisplay(0, 0, 0);
  state.assign("off");
  return state.c_str();
}

const char *redUp(std::string &state)
{
  rgbDisplay(255, 0, 0);
  state.assign("red");
  return state.c_str();
}

const char *greenUp(std::string &state)
{
  rgbDisplay(0, 255, 0);
  state.assign("green");
  return state.c_str();
}

const char *blueUp(std::string &state)
{
  rgbDisplay(0, 0, 255);
  state.assign("blue");
  return state.c_str();
}
