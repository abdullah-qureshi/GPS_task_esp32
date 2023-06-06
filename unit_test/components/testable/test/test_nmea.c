#include "unity.h"
#include "testable.h"

GPS gps_data;

TEST_CASE("GGA Data decoding from NMEA","[valid]")

{
    memset(&gps_data, 0, sizeof(GPS));
    const char* nmea_str = "$GPGGA,1234.56,6543.21,N,4321.09,E,1,10,1.5,100.5,M";

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
            &gps_data.utc_time, 
            &gps_data.nmea_latitude, 
            &gps_data.ns, 
            &gps_data.nmea_longitude, 
            &gps_data.ew, &gps_data.lock, 
            &gps_data.sattelites, 
            &gps_data.hdop,
            &gps_data.msl_altitude,
            &gps_data.msl_units);   
            free(gpggaString);
    }

    // Use Unity assertion macros to check the expected values
    TEST_ASSERT_EQUAL_FLOAT(1234.56, gps_data.utc_time);
    TEST_ASSERT_EQUAL_FLOAT(6543.21, gps_data.nmea_latitude);
    TEST_ASSERT_EQUAL_STRING('N', gps_data.ns);
    TEST_ASSERT_EQUAL_FLOAT(4321.09, gps_data.nmea_longitude);
    TEST_ASSERT_EQUAL_STRING('E', gps_data.ew);
    TEST_ASSERT_EQUAL_INT(1, gps_data.lock);
    TEST_ASSERT_EQUAL_INT(10, gps_data.satellites);
    TEST_ASSERT_EQUAL_FLOAT(1.5, gps_data.hdop);
    TEST_ASSERT_EQUAL_FLOAT(100.5, gps_data.msl_altitude);
    TEST_ASSERT_EQUAL_STRING('M', gps_data.msl_units);

}

TEST_CASE("Parse GGA data from invalid NMEA string","[invalid]")

{
    memset(&gps_data, 0, sizeof(GPS));
    char invalid_nmea_str[] = "$GPGGA,1234.56,6543.21,N,4321.09,E,1,10,1.5,100.5";

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
            &gps_data.utc_time, 
            &gps_data.nmea_latitude, 
            &gps_data.ns, 
            &gps_data.nmea_longitude, 
            &gps_data.ew, &gps_data.lock, 
            &gps_data.sattelites, 
            &gps_data.hdop,
            &gps_data.msl_altitude,
            &gps_data.msl_units);   
            free(gpggaString);
    }

   // Verify that the GPGGA string was not found
    // by checking if the GPS data values are unchanged
    TEST_ASSERT_EQUAL_FLOAT(0.0, gps_data.utc_time);
    TEST_ASSERT_EQUAL_FLOAT(0.0, gps_data.nmea_latitude);
    TEST_ASSERT_EQUAL_STRING('\0', gps_data.ns);
    TEST_ASSERT_EQUAL_FLOAT(0.0, gps_data.nmea_longitude);
    TEST_ASSERT_EQUAL_STRING('\0', gps_data.ew);
    TEST_ASSERT_EQUAL_INT(0, gps_data.lock);
    TEST_ASSERT_EQUAL_INT(0, gps_data.satellites);
    TEST_ASSERT_EQUAL_FLOAT(0.0, gps_data.hdop);
    TEST_ASSERT_EQUAL_FLOAT(0.0, gps_data.msl_altitude);
    TEST_ASSERT_EQUAL_STRING('\0', gps_data.msl_units);

}