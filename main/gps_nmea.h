#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    // GGA - Global Positioning System Fixed Data
    float nmea_longitude;
    float nmea_latitude;
    float utc_time;
    char ns, ew;
    int lock;
    int sattelites;
    float hdop;
    float msl_altitude;
    char msl_units;
} GPS;


void parse_gps_data (char* data_str, GPS* gps_data);
int gps_checksum(char *data_str);