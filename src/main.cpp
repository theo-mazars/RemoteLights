#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <string>
#include <iostream>
#include <exception>

#include "ledsControl.h"
#include "colors.h"
#include "GPIO.h"

std::string state = std::string("off");

AsyncWebServer server(80);

const char index_html[] = "<!DOCTYPE html><html> <head> <title>Remote Lights</title> <meta name='viewport' content='width=device-width, initial-scale=1'/> <style>input[type='range']{overflow: hidden; width: 80px; -webkit-appearance: none; background-color: #dddddd;}input[type='range']::-webkit-slider-thumb{-webkit-appearance: none; width: 25px; height: 25px; cursor: ew-resize; background: #dddddd; border-radius: 10em;}.slider{max-width: 300px; margin: auto; -webkit-appearance: none; width: 100%; height: 25px; outline: none; opacity: 0.7; -webkit-transition: 0.2s; transition: opacity 0.2s; border: 0; border-radius: 10em;}input[type='range'].slider.red::-webkit-slider-thumb{box-shadow: -7010px 0 0 7000px #ff7b7b;}input[type='range'].slider.green::-webkit-slider-thumb{box-shadow: -7010px 0 0 7000px #bdff7b;}input[type='range'].slider.blue::-webkit-slider-thumb{box-shadow: -7010px 0 0 7000px #7b7dff;}.slider:hover{opacity: 1;}.slider::-webkit-slider-thumb{-webkit-appearance: none; appearance: none; width: 25px; height: 25px; background: #99ff33; cursor: pointer; border-radius: 10em;}.slider.red::-webkit-slider-thumb{background: #ff3333;}.slider.green::-webkit-slider-thumb{background: #90ff20;}.slider.blue::-webkit-slider-thumb{background: #3347ff;}.slider::-moz-range-thumb{width: 25px; height: 25px; background: #99ff33; cursor: pointer;}</style> </head> <body> <div style='max-width: 300px; margin: auto'> <input type='range' min='0' max='255' value='255' id='red' class='slider red' style='width: 100%' oninput='handleChange()'/> </div><div style='max-width: 300px; margin: auto'> <input type='range' min='0' max='255' value='255' id='green' class='slider green' style='width: 100%' oninput='handleChange()'/> </div><div style='max-width: 300px; margin: auto'> <input type='range' min='0' max='255' value='255' id='blue' class='slider blue' style='width: 100%' oninput='handleChange()'/> </div><script>function handleChange(){let red=document.getElementById('red').value; let green=document.getElementById('green').value; let blue=document.getElementById('blue').value; if (!(red % 5) && !(green % 5) && !(blue % 5)){console.log('test'); let xhr=new XMLHttpRequest(); xhr.open( 'GET', '/update?red=' + red + '&green=' + green + '&blue=' + blue ); xhr.send();}}</script> </body></html>";

void setup()
{
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  Serial.begin(9600);
  Serial.println();

  WiFi.begin("bipbip", "0609687285");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address:");
  Serial.println(WiFi.localIP());
  off(state);
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/plain", off(state));
  });
  server.on("/white", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/plain", white(state));
  });

  server.on("/red", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/plain", redUp(state));
  });
  server.on("/green", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/plain", greenUp(state));
  });

  server.on("/blue", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/plain", blueUp(state));
  });

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", index_html);
  });

  server.on("/update", HTTP_GET, [](AsyncWebServerRequest *request) {
    String colorRed = "0";
    String colorGreen = "0";
    String colorBlue = "0";

    if (request->hasParam("red") && request->hasParam("green") && request->hasParam("blue"))
    {
      colorRed = request->getParam("red")->value();
      colorGreen = request->getParam("green")->value();
      colorBlue = request->getParam("blue")->value();
      try
      {
        rgbDisplay((uint32_t)atoi(colorRed.c_str()), (uint32_t)atoi(colorGreen.c_str()), (uint32_t)atoi(colorBlue.c_str()));
      }
      catch (std::exception err)
      {
        std::cerr << err.what() << std::endl;
      }
    }
    request->send(200, "text/plain", "OK");
  });

  server.begin();
}

void loop()
{
}