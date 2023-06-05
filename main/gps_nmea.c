
#include "gps_nmea.h"


int gps_checksum(char *nmea_str)
{
    char check[3];
    char checkcalcstr[3];
    int i;
    int calculated_check;

    i=0;
    calculated_check=0;

    // check to ensure that the string starts with a $
    if(nmea_str[i] == '$')
        i++;
    else
        return 0;

    //No NULL reached, 75 char largest possible NMEA message, no '*' reached
    while((nmea_str[i] != 0) && (nmea_str[i] != '*') && (i < 75)){
        calculated_check ^= nmea_str[i];// calculate the checksum
        i++;
    }

    if(i >= 75){
        return 0;// the string was too long so return an error
    }

    if (nmea_str[i] == '*'){
        check[0] = nmea_str[i+1];    //put hex chars in check string
        check[1] = nmea_str[i+2];
        check[2] = 0;
    }
    else
        return 0;// no checksum separator found there for invalid

    sprintf(checkcalcstr,"%02X",calculated_check);
    return((checkcalcstr[0] == check[0])
        && (checkcalcstr[1] == check[1])) ? 1 : 0 ;
}

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
         if (gps_checksum (gpggaString))
        {
            printf ("Checksum: Valid");
        }
            
        else
        {
            printf ("Checksum: Invalid");
        }
       
            

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
