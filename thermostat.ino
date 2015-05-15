#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>
#include <string.h>
#include "TM1637.h"

#include "Thermistor/Thermistor.h"
#include "Device/InitPorts.h"
#include "Display/Display.h"
#include "ConfigManager/ConfigManager.h"
#include "Parser/XmlParser.h"
#include "WebService/Service.h"

InitPorts initPorts;
Thermistor thermistor;
ConfigManager configManager;
WebService webservice;

int temperature = 0;
int temperature_old = 0;

TM1637 disp(clkPin,dioPin);
int8_t tempDisp[] = {0x00,0x00,0x00,0x00};

// Listen on default port 5555
//YunServer server;

void setup()
{
  initPorts.SetPorts();
  
  configManager.Begin();

  //Init 4 Digit Display
  disp.set();
  disp.init();

  //For debugging purposes
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);
  
  Bridge.begin();

  webservice.Init();
}

void loop()
{
  //################ ARDUINO SECTION #################

  //configManager.WriteFile("PROVA WRITE OK!");
  //Serial.println(configManager.ReadFile());

  if(digitalRead(sw) == 1)
  {
     digitalWrite(ledOn,1);
     digitalWrite(ledOff,0);
     
     disp.display(tempDisp);
     temperature =  thermistor.GetTemperatureValue(analogRead(tempSensor));
    
     if (temperature != temperature_old)
     {
       temperature_old = temperature;
       updateDisplay();
       disp.display(tempDisp);
     }

    delay(1000);
    //Serial.println(temperature);    
  }
  else
  { 
     digitalWrite(ledOn,0);
     digitalWrite(ledOff,1);
     
     disp.init();
  }
  
  //################ WERSERVICE SECTION ##############
  
  YunClient client = webservice.InitClient(thermistor);
   
  if (client) 
  {
    webservice.ProcessRequest(client);
    client.stop();
  }
  delay(20);
}
     
void updateDisplay(void)
{
  tempDisp[2] = temperature / 10;
  tempDisp[3] = temperature % 10;
}   



