/*****************************************************************************************
* FILENAME :        prjsettings.h         
*
* DESCRIPTION :
*       application based settings 
*
* NOTES :...
*       
*
*       Copyright A.N.Other Co. 2017.  All rights reserved.
* 
* AUTHOR :    Stephan Wink        START DATE :    01.10.2017
*
*
* REF NO  VERSION DATE    WHO     DETAIL
* 000       16.10         SWI     migration from template      
* 004       05.11         SWI     First version transmitting temperature and humidity
* 005       05.11         SWI     switch off the DHT while not reading the sensor
*
*****************************************************************************************/
#ifndef PRJSETTINGS_H
#define PRJSETTINGS_H

/****************************************************************************************/
/* Imported header files: */

/****************************************************************************************/
/* Global constant defines: */
#define FW_IDENTIFIER             "00001FW" // Firmware identification
#define FW_VERSION                "005"     // Firmware Version
#define FW_DESCRIPTION            "Temperature & Humidity Sensor"

#define MQTT_PUB_TEMPERATURE      "/temp_hum/temp" // temperature data
#define MQTT_PUB_HUMIDITY         "/temp_hum/hum" // humidity data
#define MQTT_PUB_BATTERY          "/temp_hum/bat" // battery capacity data
#define MQTT_REPORT_INTERVAL      60000 //(ms) - 60 seconds between reports
// used pins
//#define BUTTON_INPUT_PIN        0  // D3 used by template
#define DHTPIN                    5  // D1
#define DHT_PWR                   4  // D2

// unused pins
#define UNUSED_12                 12 // D6
#define UNUSED_14                 14 // D5
#define UNUSED_16                 16 // D0
#define UNUSED_15                 15 // D8

#define POWER_SAVE_TIME           60  // 60secs
#define TEMPERATURE_CORR_FACTOR   (1.00)
#define HUMIDITY_CORR_FACTOR      (1.23)
#define DHTTYPE                   DHT22 // DHT11 or DHT22
#define SERIAL_DEBUG

/****************************************************************************************/
/* Global function like macro defines (to be avoided): */

/****************************************************************************************/
/* Global type definitions (enum, struct, union): */

/****************************************************************************************/
/* Global data allusions (allows type checking, definition in c file): */

/****************************************************************************************/
/* Global function prototypes: */

#endif /* PRJSETTINGS_H */
/****************************************************************************************/
