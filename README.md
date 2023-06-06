# GPS-ESP32-Parse

A library for ESP-32 in C/C++ using esp-idf v5.0 stable for parsing GPS data in NMEA 0183 format.

Demo Video: [Drive Link]([https://pages.github.com/](https://drive.google.com/file/d/1o_tl3hhNDDJ66aGgahWG-NCp6bduiqka/view?usp=sharing))


<!-- Features -->
### Features

Display the Values of:

- Altitude
- Latitude, Longitude
- UTC
- Number of Satellite/HDOP

<!-- Getting Started -->
## 	Getting Started

I used a GPS Neo-6m with ESP-32 in order to receive the GPS values.

- GPS Neo-6M
- ESP32
- ESP-IDF v5.0

<!-- Schematic -->
### Schematic
Make the connections according to the table and schematic below.

* ESP32 and GPS Neo-6M.

| ESP32 | GPS Neo-6M |
| ----  | -----|
| 16    | TXD  |
| 17    | RXD  |
| 3V3    | VCC  |
| GND    | GND  |

![alt text](https://github.com/abdullah-qureshi/GPS_task_esp32/blob/master/img/schematic_esp_neo6m.png "ESP32 GPS NEO 6M V2" )

### Hardware

![alt text](https://github.com/abdullah-qureshi/GPS_task_esp32/blob/master/img/gps_hardware.jpg "Hardware" )

## Running

To run the code, open the source directory and run

```
idf.py build
idf.py - PORT flash monitor
...
```

![alt text](https://github.com/abdullah-qureshi/GPS_task_esp32/blob/master/img/terminal_display.png "Terminal Output" )




