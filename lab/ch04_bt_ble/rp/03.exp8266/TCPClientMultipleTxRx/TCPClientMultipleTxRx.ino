/**
 * @example TCPClientMultiple.ino
 * @brief The TCPClientMultiple demo of library WeeESP8266. 
 * @author Wu Pengfei<pengfei.wu@itead.cc> 
 * @date 2015.02
 * 
 * @par Copyright:
 * Copyright (c) 2015 ITEAD Intelligent Systems Co., Ltd. \n\n
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version. \n\n
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "ESP8266.h"

#define SSID        "KOSTA10"
#define PASSWORD    "akswhreh100"
//#define HOST_NAME   "192.168.219.104"
//#define HOST_NAME   "192.168.219.114"
#define HOST_NAME   "192.168.0.130"
//#define HOST_PORT   (23)
//#define HOST_PORT   (8090)
#define HOST_PORT   (10000)

SoftwareSerial mySerial(2, 3); /* RX:D2(ESP8266_Tx), TX:D3(ESP8255_Rx) */
//ESP8266 wifi(mySerial, 115200);
ESP8266 wifi(mySerial);   //9600

void setup(void)
{
    Serial.begin(9600);
    Serial.print("setup begin\r\n");

    Serial.print("FW Version: ");
    Serial.println(wifi.getVersion().c_str());    
    
    if (wifi.setOprToStationSoftAP()) {
        Serial.print("to station + softap ok\r\n");
    } else {
        Serial.print("to station + softap err\r\n");
    }

    if (wifi.joinAP(SSID, PASSWORD)) {
        Serial.print("Join AP success\r\n");
        Serial.print("IP: ");       
        Serial.println(wifi.getLocalIP().c_str());
    } else {
        Serial.print("Join AP failure\r\n");
    }
  
    if (wifi.enableMUX()) {
        Serial.print("multiple ok\r\n");
    } else {
        Serial.print("multiple err\r\n");
    } 
    Serial.print("setup end\r\n");
}

void loop(void)
{
    uint8_t buffer[128] = {0};
    uint8_t mux_id = 0;
    static uint8_t cnt = 0;
    
    if (wifi.createTCP(mux_id, HOST_NAME, HOST_PORT)) {
        Serial.print("create tcp ");
        Serial.print(mux_id);
        Serial.println(" ok");
    } else {
        Serial.print("create tcp ");
        Serial.print(mux_id);
        Serial.println(" err");
    }

    char hello[100]={0,};
    sprintf(hello, "Hello_from_client_%d!!", ++cnt);
    Serial.print("Send_to_Server=>");
    Serial.println(hello);
    delay(100);
    if (wifi.send(mux_id, (const uint8_t*)hello, strlen(hello))) {
        Serial.println("send ok");
    } else {
        Serial.println("send err");
    }
    uint32_t len = wifi.recv(mux_id, buffer, sizeof(buffer), 10000);
    if (len > 0) {
        Serial.print("Received:[");
        for(uint32_t i = 0; i < len; i++) {
            Serial.print((char)buffer[i]);
        }
        Serial.print("]\r\n");
    }

#if 0
    if(cnt%10 == 0) {
      if (wifi.releaseTCP(mux_id)) {
        Serial.print("release tcp ");
        Serial.print(mux_id);
        Serial.println(" ok");
      } else {
        Serial.print("release tcp ");
        Serial.print(mux_id);
        Serial.println(" err");
      }
    }
 #endif 
    delay(3000);
}

