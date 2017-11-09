/*****************************************************************************************
* FILENAME :        prjsettings.h          
*
* DESCRIPTION :
*       Header file to define project specific settings
*
* PUBLIC FUNCTIONS :
*       N/A
*
* NOTES :
*
* Copyright (c) [2017] [Stephan Wink]
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
vAUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*****************************************************************************************/
#ifndef PRJSETTINGS_H
#define PRJSETTINGS_H

/****************************************************************************************/
/* Imported header files: */

/****************************************************************************************/
/* Global constant defines: */
#define FW_IDENTIFIER             "00002FW" // Firmware identification
#define FW_VERSION                "006"     // Firmware Version
#define FW_DESCRIPTION            "Temperature & Humidity Sensor"

#define MQTT_PUB_TEMPERATURE      "/temp_hum/temp" // temperature data
#define MQTT_PUB_HUMIDITY         "/temp_hum/hum" // humidity data
#define MQTT_PUB_BATTERY          "/temp_hum/bat" // battery capacity data
#define MQTT_REPORT_INTERVAL      5000 //(ms) - 5 seconds between reports

#define POWER_SAVE                1   // 1 = activated
#define POWER_SAVE_TIME           10 // = 10 seconds power save time
#define MAX_PUBS_TILL_POWER_SAVE  3
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
