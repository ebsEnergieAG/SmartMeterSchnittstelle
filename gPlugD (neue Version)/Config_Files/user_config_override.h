/*
  user_config_override.h - user configuration overrides my_user_config.h for Tasmota

  Copyright (C) 2021  Theo Arends

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _USER_CONFIG_OVERRIDE_H_
#define _USER_CONFIG_OVERRIDE_H_

/*****************************************************************************************************\
 * USAGE:
 *   To modify the stock configuration without changing the my_user_config.h file:
 *   (1) copy this file to "user_config_override.h" (It will be ignored by Git)
 *   (2) define your own settings below
 *
 ******************************************************************************************************
 * ATTENTION:
 *   - Changes to SECTION1 PARAMETER defines will only override flash settings if you change define CFG_HOLDER.
 *   - Expect compiler warnings when no ifdef/undef/endif sequence is used.
 *   - You still need to update my_user_config.h for major define USE_MQTT_TLS.
 *   - All parameters can be persistent changed online using commands via MQTT, WebConsole or Serial.
\*****************************************************************************************************/

/*
Examples :

// -- Master parameter control --------------------
#undef  CFG_HOLDER
#define CFG_HOLDER        4617                   // [Reset 1] Change this value to load SECTION1 configuration parameters to flash

// -- Setup your own Wifi settings  ---------------
#undef  STA_SSID1
#define STA_SSID1         "YourSSID"             // [Ssid1] Wifi SSID

#undef  STA_PASS1
#define STA_PASS1         "YourWifiPassword"     // [Password1] Wifi password

// -- Setup your own MQTT settings  ---------------
#undef  MQTT_HOST
#define MQTT_HOST         "your-mqtt-server.com" // [MqttHost]

#undef  MQTT_PORT
#define MQTT_PORT         1883                   // [MqttPort] MQTT port (10123 on CloudMQTT)

#undef  MQTT_USER
#define MQTT_USER         "YourMqttUser"         // [MqttUser] Optional user

#undef  MQTT_PASS
#define MQTT_PASS         "YourMqttPass"         // [MqttPassword] Optional password

// You might even pass some parameters from the command line ----------------------------
// Ie:  export PLATFORMIO_BUILD_FLAGS='-DUSE_CONFIG_OVERRIDE -DMY_IP="192.168.1.99" -DMY_GW="192.168.1.1" -DMY_DNS="192.168.1.1"'

#ifdef MY_IP
#undef  WIFI_IP_ADDRESS
#define WIFI_IP_ADDRESS     MY_IP                // Set to 0.0.0.0 for using DHCP or enter a static IP address
#endif

#ifdef MY_GW
#undef  WIFI_GATEWAY
#define WIFI_GATEWAY        MY_GW                // if not using DHCP set Gateway IP address
#endif

#ifdef MY_DNS
#undef  WIFI_DNS
#define WIFI_DNS            MY_DNS               // If not using DHCP set DNS IP address (might be equal to WIFI_GATEWAY)
#endif

#ifdef MY_DNS2
#undef  WIFI_DNS2
#define WIFI_DNS2           MY_DNS2              // If not using DHCP set DNS IP address (might be equal to WIFI_GATEWAY)
#endif

// !!! Remember that your changes GOES AT THE BOTTOM OF THIS FILE right before the last #endif !!!
*/
// Enable essential features
#ifndef USE_SCRIPT
  #define USE_SCRIPT
#endif

#ifndef USE_SML_M
  #define USE_SML_M
#endif

#ifdef USE_RULES
  #undef USE_RULES
#endif

#ifndef USE_SCRIPT_TIMER
  #define USE_SCRIPT_TIMER
#endif

#ifndef USE_SCRIPT_GLOBALVARS
  #define USE_SCRIPT_GLOBALVARS
#endif

#ifndef USE_SCRIPT_SERIAL
  #define USE_SCRIPT_SERIAL
#endif

#ifndef USE_SCRIPT_WEB_DISPLAY
  #define USE_SCRIPT_WEB_DISPLAY
#endif

#ifndef SCRIPT_FULL_WEBPAGE
  #define SCRIPT_FULL_WEBPAGE
#endif

#ifndef USE_UFILESYS
  #define USE_UFILESYS
#endif

// Enable Google Charts support
#ifndef USE_GOOGLE_CHARTS
  #define USE_GOOGLE_CHARTS
#endif

// Enable Wi-Fi configuration tool
#ifdef WIFI_CONFIG_TOOL
  #undef WIFI_CONFIG_TOOL
#endif
#define WIFI_CONFIG_TOOL WIFI_MANAGER

#ifdef USE_DISPLAY_TM1621_SONOFF
  #undef USE_DISPLAY_TM1621_SONOFF
#endif

#ifdef APP_TIMEZONE
  #undef APP_TIMEZONE
#endif

#define APP_TIMEZONE 99

#ifdef MY_LANGUAGE
  #undef MY_LANGUAGE
#endif

#define MY_LANGUAGE de_DE 



// Disable unnecessary features to minimize firmware size
// #ifdef USE_AUTOCONF
//   #undef USE_AUTOCONF
// #endif

// #ifndef USE_BERRY
//   #undef USE_BERRY
// #endif

// #ifdef USE_WEBCLIENT_HTTPS
//   #undef USE_WEBCLIENT_HTTPS
// #endif
// #ifdef USE_MQTT_TLS
//   #undef USE_MQTT_TLS
// #endif

// #ifdef USE_NETWORK_LIGHT_SCHEMES
//   #undef USE_NETWORK_LIGHT_SCHEMES
// #endif

// #ifdef USE_GPIO_VIEWER
//   #undef USE_GPIO_VIEWER
// #endif

// #ifdef USE_ESP32_SENSORS
//   #undef USE_ESP32_SENSORS
// #endif

// #ifdef USE_MQTT_AWS_IOT
//   #undef USE_MQTT_AWS_IOT
// #endif

// #ifdef USE_MQTT_AZURE_IOT
//   #undef USE_MQTT_AZURE_IOT
// #endif

#ifdef USE_TELEGRAM
  #undef USE_TELEGRAM
#endif

#ifdef USE_KNX
  #undef USE_KNX
#endif


#ifdef USE_KNX_WEB_MENU
  #undef USE_KNX_WEB_MENU
#endif

// #ifdef USE_WEBSEND_RESPONSE
//   #undef USE_WEBSEND_RESPONSE
// #endif

// #ifdef USE_DISCOVERY
//   #undef USE_DISCOVERY
// #endif

// #ifdef USE_DS18x20
//   #undef USE_DS18x20
// #endif

// #ifdef USE_DHT
//   #undef USE_DHT
// #endif

// #ifdef USE_I2C
//   #undef USE_I2C
// #endif

// #ifdef USE_SPI
//   #undef USE_SPI
// #endif

// #ifdef USE_ADC_VCC
//   #undef USE_ADC_VCC
// #endif

// #ifdef USE_LIGHT
//   #undef USE_LIGHT
// #endif

// #ifdef USE_SHUTTER
//   #undef USE_SHUTTER
// #endif

// #ifdef USE_COUNTER
//   #undef USE_COUNTER
// #endif

// #ifdef USE_HOTPLUG
//   #undef USE_HOTPLUG
// #endif

// #ifdef USE_DEEPSLEEP
//   #undef USE_DEEPSLEEP
// #endif

// #ifdef USE_PWM_DIMMER
//   #undef USE_PWM_DIMMER
// #endif

// #ifdef USE_EMULATION
//   #undef USE_EMULATION
// #endif

// #ifdef USE_DEVICE_GROUPS
//   #undef USE_DEVICE_GROUPS
// #endif

// #ifdef USE_SCRIPT_FATFS
//   #undef USE_SCRIPT_FATFS
// #endif

#ifdef USE_DOMOTICZ
  #undef USE_DOMOTICZ
#endif

#ifdef USE_HOME_ASSISTANT
  #undef USE_HOME_ASSISTANT
#endif

#ifdef USE_TASMESH
  #undef USE_TASMESH
#endif

#ifdef USE_INFLUXDB
  #undef USE_INFLUXDB
#endif

#ifdef USE_WEBCAM
  #undef USE_WEBCAM
#endif

#endif  // _USER_CONFIG_OVERRIDE_H_