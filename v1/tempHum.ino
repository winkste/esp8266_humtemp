/*****************************************************************************************
* FILENAME :        tempHum.c          
*
* DESCRIPTION :
*       File to support for DHT temperature and humidity sensor
*
* PUBLIC FUNCTIONS :
*       boolean tempHum_ProcessPublishRequests(void)
*       void tempHum_CallbackMqtt(char* p_topic, String p_payload)
*       void tempHum_InitializePins(void)
*       void tempHum_Reconnect() 
*
* NOTES :
*       
*       The tempHum implements the sensor interface to the DHT 11/22 temperature and
*       humidity sensor. It supports functions to publish the data to a MQTT 
*       server:
*         #define MQTT_PUB_TEMPERATURE      "/temp_hum/temp" // temperature data
*         #define MQTT_PUB_HUMIDITY         "/temp_hum/hum" // humidity data
*         #define MQTT_PUB_BATTERY          "/temp_hum/bat" // battery capacity data
*       
*       Note: battery capacity is currently not available
*
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
* 
* AUTHOR :    Stephan Wink        START DATE :    01.10.2017
*
*
* REF NO  VERSION DATE    WHO     DETAIL
* 000       16.10         SWI     migration from template      
* 005       05.11         SWI     First verion working with DHT22
* 006       06.11         SWI     Changed partnumber
*
*****************************************************************************************/

/*****************************************************************************************
 * Include Interfaces
*****************************************************************************************/
#include <ESP8266WiFi.h>
#include "WiFiManager.h" // local modified version          
#include <PubSubClient.h>
#include <EEPROM.h>
#include <DHT.h>
#include "gensettings.h"

#include "prjsettings.h"

/*****************************************************************************************
 * Local constant defines
*****************************************************************************************/

/*****************************************************************************************
 * Local function like makros 
*****************************************************************************************/

/*****************************************************************************************
 * Local type definitions (enum, struct, union):
*****************************************************************************************/

/*****************************************************************************************
 * Global data definitions (unlimited visibility, to be avoided):
*****************************************************************************************/

/****************************************************************************************/
/* Local function prototypes (always use static to limit visibility): 
*****************************************************************************************/
static char *f2s(float f, int p);

/*****************************************************************************************
 * Local data definitions:
 * (always use static: limit visibility, const: read only, volatile: non-optimizable) 
*****************************************************************************************/
static DHT                  dht(DHTPIN, DHTTYPE, 11); 
static float                humidity_f32st = 0.0;
static float                temperature_f32st = 0.0; 
static unsigned long        prevTime_u32st = 0;
/*****************************************************************************************
* Global functions (unlimited visibility): 
*****************************************************************************************/

/**---------------------------------------------------------------------------------------
 * @brief     This function processes the publish requests and is called cyclic.   
 * @author    winkste
 * @date      20 Okt. 2017
 * @return    This function returns 'true' if the function processing was successful.
 *             In all other cases it returns 'false'.
*//*-----------------------------------------------------------------------------------*/
boolean tempHum_ProcessPublishRequests(void)
{
  String tPayload;
  boolean ret = false;

  // the temperature and humidity publication is time interval based
  if(prevTime_u32st + MQTT_REPORT_INTERVAL < millis() || prevTime_u32st == 0)
  {
    prevTime_u32st = millis();
    Serial.println("reading temperature and humidity from DHT");

    // check the internal ADC
    //out = (unsigned int) analogRead(A0);

    // checking the DHT values
    TurnDHTOn();
    humidity_f32st = dht.readHumidity();
    temperature_f32st = dht.readTemperature();
    TurnDHTOff();

    // apply correction factor to both measurements
    humidity_f32st = humidity_f32st * HUMIDITY_CORR_FACTOR;
    temperature_f32st = temperature_f32st * TEMPERATURE_CORR_FACTOR;
    
    // Check if any reads failed and exit early (to try again).
    if (isnan(humidity_f32st) || isnan(temperature_f32st)) 
    {
      Serial.println("Failed to read from DHT sensor!");
    }
    else
    {      
      Serial.print("[mqtt] publish temperature: ");
      Serial.print(MQTT_PUB_TEMPERATURE);
      Serial.print("  :  ");
      ret = client_sts.publish(build_topic(MQTT_PUB_TEMPERATURE), f2s(temperature_f32st, 2), true);
      Serial.println(f2s(temperature_f32st, 2));
      
      Serial.print("[mqtt] publish humidity: ");
      Serial.print(MQTT_PUB_HUMIDITY);
      Serial.print("  :  ");
      ret = client_sts.publish(build_topic(MQTT_PUB_HUMIDITY), f2s(humidity_f32st, 2), true);
      Serial.println(f2s(humidity_f32st, 2));      
    }
  } 
  return ret;  
}

/**---------------------------------------------------------------------------------------
 * @brief     This callback function processes incoming MQTT messages and is called by   
 *              the PubSub client
 * @author    winkste
 * @date      20 Okt. 2017
 * @param     p_topic     topic which was received
 * @param     p_payload   payload of the received MQTT message
 * @param     p_length    payload length
 * @return    This function returns 'true' if the function processing was successful.
 *             In all other cases it returns 'false'.
*//*-----------------------------------------------------------------------------------*/
void tempHum_CallbackMqtt(char* p_topic, String p_payload) 
{

  Serial.print("[mqtt] unexpected topic: "); 
  Serial.println(p_topic); 
  Serial.print("[mqtt] unexpected command: "); 
  Serial.println(p_payload); 
}

/**---------------------------------------------------------------------------------------
 * @brief     This initializes the used input and output pins
 * @author    winkste
 * @date      20 Okt. 2017
 * @return    void
*//*-----------------------------------------------------------------------------------*/
void tempHum_InitializePins(void)
{
  // power up the DHT
  Serial.println("Power up DHT");
  pinMode(DHT_PWR, OUTPUT);
  digitalWrite(DHT_PWR, LOW);
  delay(500);
  
  // start dht
  dht.begin();
}

/**---------------------------------------------------------------------------------------
 * @brief     This function handles the connection to the MQTT broker. If connection can't
 *              be established after several attempts the WifiManager is called. If 
 *              connection is successfull, all needed subscriptions are done.
 * @author    winkste
 * @date      20 Okt. 2017
 * @return    n/a
*//*-----------------------------------------------------------------------------------*/
void tempHum_Reconnect() 
{ 
  // ... no subscriptions needed here
  
}

/****************************************************************************************/
/* Local functions (always use static to limit visibility): */
/****************************************************************************************/

/**---------------------------------------------------------------------------------------
 * @brief     This function converts a float value to a string
 * @author    winkste
 * @date      20 Okt. 2017
 * @param     f is the float to turn into a string
 * @param     p is the precision (number of decimals)
 * @return    return a string representation of the float
*//*-----------------------------------------------------------------------------------*/
static char *f2s(float f, int p)
{
  char * pBuff;                         // use to remember which part of the buffer to use for dtostrf
  const int iSize = 10;                 // number of buffers, one for each float before wrapping around
  static char sBuff[iSize][20];         // space for 20 characters including NULL terminator for each float
  static int iCount = 0;                // keep a tab of next place in sBuff to use
  pBuff = sBuff[iCount];                // use this buffer
  if(iCount >= iSize -1){               // check for wrap
    iCount = 0;                         // if wrapping start again and reset
  }
  else{
    iCount++;                           // advance the counter
  }
  return dtostrf(f, 0, p, pBuff);       // call the library function
}


/**---------------------------------------------------------------------------------------
 * @brief     This function turns on the DHT power pin and waits for a dedicated time.
 * @author    winkste
 * @date      20 Okt. 2017
 * @return    n/a
*//*-----------------------------------------------------------------------------------*/
void TurnDHTOn() 
{ 
  digitalWrite(DHT_PWR, HIGH);
  delay(500);
  
  // start dht
  dht.begin(); 

  delay(500);
}

/**---------------------------------------------------------------------------------------
 * @brief     This function turns off the DHT power pin.
 * @author    winkste
 * @date      20 Okt. 2017
 * @return    n/a
*//*-----------------------------------------------------------------------------------*/
void TurnDHTOff() 
{ 
  digitalWrite(DHT_PWR, LOW); 
}


/****************************************************************************************/
