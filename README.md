# 💡 Remote Lights

This project is what we call a "Hub Experience" in EPITECH. The purpose is to discover something new, explore new technologies and try to learn things that are not in our studies.

With this project I'm discovering the world of the IoT and exploring the ESP32 with a simple program that controls a LED with a simple web interface.

![](./assets/20210317_200157.gif)

## 📃 Prerequisite

1. ESP32
2. Wires
3. Bread board
4. 220Ω resistor
5. RGB LED

## ℹ️ Informations

- Language: C++
- Software: VSCode
- Platform: PlatformIO
- Hardware: ESP32
- Technology: WiFi

## 🤓 Usage

The ESP32 has a WiFi module. I used it to provide a web server with some routes to change the color of the LED. Here are some routes you can use:

The basics:

- `/off`: turns the LED off
- `/white`: turns the LED on and set the color white
- `/red`: turns the LED on and set the color red
- `/green`: turns the LED on and set the color green
- `/blue`: turns the LED on and set the color blue

More complex:
- `/`: let you decide which color you want to set. (You can also turn off the LED)
- `/update?red=<0-255>&green=<0-255>&blue=<0-255>`: change the color of the LED with the values you set

## 🏷️ Author

- [Theo Mazars](https://github.com/theo-mazars)

## 🔓 License

This project is too simple to use a License. Feel free to reuse the code.
