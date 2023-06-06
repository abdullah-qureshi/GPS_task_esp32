/* Example application which uses testable component.

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include "esp_random.h"
#include "testable.h"

/* This application has a test subproject in 'test' directory, all the
 * interesting things happen there. See ../test/main/example_idf_test_runner_test.c
 * and the makefiles in ../test/ directory.
 *
 * This specific app_main function is provided only to illustrate the layout
 * of a project.
 */

void app_main(void)
{
    GPS myData; //Struct containing UTC, Lat, Long data.
    uint8_t* data = (uint8_t*) malloc (RX_BUF_SIZE+1); //Data buffer
    const char* nmea_str = "$GPGGA,1234.56,6543.21,N,4321.09,E,1,10,1.5,100.5,M";

    parse_gps_data (nmea_str, &myData); //Parse data buffer and decode the GGA string.
    printf("\r\nTime: %f\nLat: %f %c\nLon: %f %c\nAlt: %f m\nSatellites: %d\nHDOP: %f\r\n",myData.utc_time, myData.nmea_latitude/100, myData.ns, myData.nmea_longitude/100, myData.ew, myData.msl_altitude, myData.sattelites, myData.hdop);


    free(data);
}
