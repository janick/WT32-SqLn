# WT32-SqLn
Getting started with Wireless Tag's WT32-SC01 Plus using SquareLine Studio, LVGL, and OTA updates.

## Overview
I recently bought a WT32-SC01 Plus but quickly grew frustrated when it came time to use it.
I found plenty of YouTube videos demonstrating it's amazing screen and performance,
all in an under-$30 device. After plenty of digging and experiments and frustrating hours,
here's a detailed description of what I learned. Further contributions welcomed.

* [What you need to know right now](#what-you-need-to-know-right-now)
* [What you'll need](#what-youll-need)
* [Programming](#programming)
  * [Using your own USB-to-serial board](#using-your-own-usb-to-serial-board)
  * [Using the WT programmer](#using-the-wt-programmer)
* [OTA updates](#ota-updates)
* [Squareline Studio](#squareline-studio)
* [3D-printed cases](#3d-printed-cases)

## What you need to know right now

1. It uses a ESP32-S3 WROVER, not a ESP32 VROOM.
1. It is not supported by the latest Arduino IDE
1. You can't program it using the USB-C port
1. You can't power it using the USB-to-serial board only

## What you'll need

1. A [WT32-SC01 Plus board with programmer](https://www.alibaba.com/product-detail/Upgrade-WT32-SC01-plus-16MB-hmi_1600609718238.html)
1. [8-pin MX1.25 PicoBlade dongles](https://www.aliexpress.us/item/3256804401152079.html) if you plan on using GPIOs

or

1. A [WT32-SC01 Plus board](https://www.aliexpress.us/item/3256803559528956.html) without programmer
1. A [3.3V USB-to-Serial communication board](https://www.aliexpress.us/item/3256803764808791.html)
1. [7-pin MX1.25 PicoBlade dongles](https://www.aliexpress.us/item/3256804401152079.html (get some 8-pin ones too if you plan on using GPIOs)
1. [2.54mm/0.1" pin header with suitable female connector housings](https://www.amazon.com/gp/product/B077X8XV2J)

and:

1. [ESP-IDF v5.0](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html)
1. [SquareLine Studio](https://squareline.io)
1. USB-C 2A power supply

## Programming

Unlike other ESP32 development boards, you can't program the WT32-SC01 Plus using the USB-C port.
That port is only for supplying power.
You *HAVE TO* use the serial port and trigger the programming mode using EN and GPIO0.
As the programmer wasn't included with the board, it was a particularly frustrating step.

If you bought the version that includes the programmer, you can skip to the "[Using the WT programmer](#using-the-wt-programmer)" section.

### Using your own USB-to-serial board

Using a 7-pin MX1.25 PicoBlade dongle and a 2.54mm/0.1" pin header connector housing that matches your board,
create a cable to connect the TX, RX, and GND pins on the Debug Interface
to the RX, TX, and GND pins respectively on your USB-to-serial communication board,
and using a *separate* 1-pin connector housing, connect the GPIO0 pin on the Debug Interface
to a *second* exposed GND pin on your USB-to-serial communication board.
It is important that it be possible to disconnect the GPIO0 wire from the USB-to-serial board
without disconnecting the other wires.

##### Debug Interface on WT32-SC01 Plus
| Pin | Description | ESP32 Pin | Voltage Range | Remark
| --- | ----------- | --------- | ------------- | ------
| 1 | +5V | | 5V |
| 2 | +3.3V | | 3.3V | For reference, not for power input
| 3 | ESP_TXD | TXD0 | 3.3V TTL |
| 4 | ESP_RXD | RXD0 | 3.3V TTL |
| 5 | EN | EN | 0-3.3V |
| 6 | BOOT | GPIO 0 | 0-3.3V | 
| 7 | GND | | 0V |

![WT32-SC01 Plus Back](assets/wt32_sc01_plus.png)

Here's my DIY programming cable.
I did connect the 5V line so I could easily identify which side of the connector was "up": the red wire goes with the VCC pin.
Notice how the white "GPIO0" wire is connected to a separate exposed GND pin on the programmer.

![WT32-SC01 Plus DIY Programmer Cable](assets/diy_programmer.jpg "DIY Programmer Cable")

The following steps assume you have an application succesfully compiled using `idf.py build` (see TBD).
To program, then run your application with the serial monitor, power the WT32-SC01 Plus via its own
USB-C port as well as connecting your serial board to a USB port on your computer.

1. To enter programming mode, connect the GPIO0 wire to the GND pin, then press the `RST` button on the back
of the WT32-SC01 Plus.

1. Flash your application using the command `idf.py flash`. Wait until the flashing process completes with a `Hard resetting via RTS pin...` message.
   Skip to step 5 if you are not using the serial monitor to debug your application.

1. Leave the GPIO0 wire connected to the GND pin and reset the WT32-SC01 Plus again.

1. Start the serial monitor using the command `idf.py monitor`. Wait until the monitor is running indicated by the following message:

```
--- idf_monitor on /dev/cu.wchusbserial54340143141 115200 ---
--- Quit: Ctrl+] | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
```

5. To run your application, disconnect the GPIO0 wire, then reset the WT32-SC01 Plus again.

### Using the WT programmer

If you were fortunate enough to order a WT32-SC01 Plus that came with its own custom programmer, TBD

## OTA Updates

Todo

## Squareline Studio

To add support for the WT32-SC01 Plus, copy the content of the `SquareLine/boards` directory into your Squareline Studio installation using the command

```
$ cp -r SquareLine/boards/* <Path to Squareline Studio installation>/boards
```

e.g. on my Mac:

```
$ cp -r SquareLine/boards/* /Applications/Squareline_Studio.app/Contents/boards
```

## ToDo

*
* Get my code configurable using menuconfig
* Add my code

## 3D-Printed Cases

In the 3Dprint directory, you'll find STL files for 3D-printable cases

* BatteryCase: Compact case that can fit the WT32-SC01 Plus, a [3.7V lithium-ion battery](https://www.aliexpress.us/item/3256803919111184.html), a [charger module](https://www.aliexpress.us/item/3256804193670438.html), and a [power switch](https://www.aliexpress.us/item/2251832642923360.html).
  The USB-C opening and tabs to hold the charger module still need some tweaking.
