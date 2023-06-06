
#include "gps_nmea.h"


int gps_checksum(char *nmea_str)
{
    char check[3];
    char checkcalcstr[3];
    int i;
    int calculated_check;

    i=0;
    calculated_check=0;

    // Check to make sure that the NMEA string starts with a $
    if(nmea_str[i] == '$')
        i++;
    else
        return 0;

    //If No NULL reached, 75 char largest possible NMEA message, no '*' reached
    while((nmea_str[i] != 0) && (nmea_str[i] != '*') && (i < 75)){
        calculated_check ^= nmea_str[i];// Calculate the checksum
        i++;
    }

    if(i >= 75){
        return 0;// The string is too long return an error
    }

    if (nmea_str[i] == '*'){
        check[0] = nmea_str[i+1];    //put hex chars in check string
        check[1] = nmea_str[i+2];
        check[2] = 0;
    }
    else
        return 0;// Return error if no checksum string found

    sprintf(checkcalcstr,"%02X",calculated_check);
    return((checkcalcstr[0] == check[0])
        && (checkcalcstr[1] == check[1])) ? 1 : 0 ;
}

void parse_gps_data (char* nmea_str, GPS* gps_data)
{
    // Define the prefix and delimiter for GPGGA string
    const char* gpggaPrefix = "$GPGGA";
    const char* delimiter = "\n";
    // Find the start of GPGGA string in nmea_str
    const char* gpggaStart = strstr((char*) nmea_str, gpggaPrefix);

    if (gpggaStart != NULL) 
    {
        // Find the end of GPGGA string
        const char* gpggaEnd = strchr(gpggaStart, '\n');
        // Calculate the length of GPGGA string
        int gpggaLength = gpggaEnd - gpggaStart;

        // Allocate memory for GPGGA string
        char* gpggaString = (char*)malloc((gpggaLength + 1) * sizeof(char));
        // Copy the GPGGA string into gpggaString
        strncpy(gpggaString, gpggaStart, gpggaLength);
        gpggaString[gpggaLength] = '\0';

        printf("\nExtracted GPGGA string: %s\n", gpggaString);
         // Check if the GPGGA string has a valid checksum
         if (gps_checksum (gpggaString))
        {
            printf ("Checksum: Valid");
        }
            
        else
        {
            printf ("Checksum: Invalid");
        }
       
            
    // Parse the GPGGA string and store the values in gps_data

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
            
            free(gpggaString); // Free the memory allocated for GPGGA string
    }
                        
            else {
        printf("\nGPGGA string not found in the data buffer.\n");
    }
}
