/* testable.h: Implementation of a testable component.

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#pragma once
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
/**
 * @brief Calculate arithmetic mean of integer values
 * @param values  array of values
 * @param count   number of elements in the array
 * @return arithmetic mean of values, or zero count is zero
 */

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


int testable_mean(const int* values, int count);


void parse_gps_data (char* nmea_str, GPS* gps_data)
{
    const char* gpggaPrefix = "$GPGGA";
    const char* delimiter = "\n";
    const char* gpggaStart = strstr((char*) nmea_str, gpggaPrefix);

    if (gpggaStart != NULL) {
        const char* gpggaEnd = strchr(gpggaStart, '\n');
        int gpggaLength = gpggaEnd - gpggaStart;

        char* gpggaString = (char*)malloc((gpggaLength + 1) * sizeof(char));
        strncpy(gpggaString, gpggaStart, gpggaLength);
        gpggaString[gpggaLength] = '\0';

        printf("\nExtracted GPGGA string: %s\n", gpggaString);   

        sscanf(gpggaString, "$GPGGA,%f,%f,%c,%f,%c,%d,%d,%f,%f,%c",
            &gps_data->utc_time, 
            &gps_data->nmea_latitude, 
            &gps_data->ns, 
            &gps_data->nmea_longitude, 
            &gps_data->ew, &gps_data->lock, 
            &gps_data->sattelites, 
            &gps_data->hdop,
            &gps_data->msl_altitude,
            &gps_data->msl_units);   
            free(gpggaString);
    }
                        
            else {
        printf("\nGPGGA string not found in the data buffer.\n");
    }
}
