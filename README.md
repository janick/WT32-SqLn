# WT32-SqLn
Getting started with Wireless Tag's WT32-SC01 Plus using SquareLine Studio and LVGL

## Overview
I recently bought a WT32-SC01 Plus but quickly grew frustrated when it came time to use it.
I found plenty of YouTube videos demonstrating it's amazing screen and performance,
all in an under-$30 device. After plenty of digging and experiments and frustrating hours,
here's a detailed description of what I learned. Further contributions welcomed.

## What you need to know right now

1. It uses a ESP32-C3 WROVER, not a ESP32 VROOM.
1. It is not supported by the latest Arduino IDE
1. You can't program it using the USB-C port
1. You can't power it using the USB-to-serial board only

## What you'll need

1. A WT32-SC01 Plus board: https://www.aliexpress.us/item/3256803559528956.html
1. A 3.3V USB-to-Serial communication board: https://www.aliexpress.us/item/3256803764808791.html
1. 7-pin MX1.25 PicoBlade dongle: https://www.aliexpress.us/item/3256804401152079.html (get some 8-pin ones too if you plan on using GPIOs)
1. 2.54mm/0.1" pin header with 3-pin and 1-pin female connector housing: 4-pin and 1-pin female
1. ESP-IDF v5.0: https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html
1. SquareLine Studio: https://squareline.io
1. USB-C 2A power supply

## Programming

Unlike other ESP32 development boards, you can't program the WT32-SC01 Plus using the USB-C port.
That port is only for suppling power.
You *HAVE TO* use the serial port and trigger the programming mode using EN and GPIO0.
Furtunately, *that* bit is identical to all other ESP32 products.

Using a 7-pin MX1.25 PicoBlade dongle and a 3-pin 2.54mm/0.1" pin header connector housing,
create a cable to connect the TX, RX, and GND pins on the Debug Interface
to the RX, TX, and GND pins respectively on your USB-to-serial communication board,
and using a *separate* 1-pin connector housing, connect the GPIO0 pin on the Debug Interface
to a *second* exposed GND pin on your USB-to-serial communication board.
It is important that it be possible to disconnect the GPIO0 wire from the USB-to-serial board
without disconnecting the other wires.

### Debug Interface on WT32-SC01 Plus
| Pin | Description | ESP32 Pin | Voltage Range | Remark
| --- | ----------- | --------- | ------------- | ------
| 1 | +5V | | 5V |
| 2 | +3.3V | | 3.3V | For reference, not for power input
| 3 | ESP_TXD | TXD0 | 3.3V TTL |
| 4 | ESP_RXD | RXD0 | 3.3V TTL |
| 5 | EN | EN | 0-3.3V |
| 6 | BOOT | GPIO 0 | 0-3.3V | 
| 7 | GND | | 0V |

### To enter programming mode

todo

### To enter monitor mode

todo

### To run program

todo

## ToDo

*
* Get my code configurable using menuconfig
* Add my code