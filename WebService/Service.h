/*
web service manager
*/
#ifndef WEBSERVICE_h
#define WEBSERVICE_h

#include "Arduino.h"
#include <YunServer.h>
#include <YunClient.h>

class WebService
{
    public:

    YunClient InitClient(Thermistor trm);
    void Init();
    void ProcessRequest(YunClient client);

    private:

    YunServer server;
    Thermistor thermistor;
    void digitalCommand(YunClient client);
    void analogCommand(YunClient client); 
    void modeCommand(YunClient client);
};
#endif

void WebService::Init()
{
    server.listenOnLocalhost();
    server.begin();
}

YunClient WebService::InitClient(Thermistor trm)
{
    thermistor = trm;
    return server.accept();
}

void WebService::ProcessRequest(YunClient client) 
{
  String command = client.readStringUntil('/');
  command.trim();
  
  if (command == "digital") 
  {
    digitalCommand(client);
  }
  if (command == "analog") 
  {
    analogCommand(client);
  }
  if (command == "mode") 
  {
    modeCommand(client);
  }
}   
    
void WebService::digitalCommand(YunClient client) 
{
  int pin, value;
  pin = client.parseInt();

  if (client.read() == '/') 
  {
    value = client.parseInt();
    digitalWrite(pin, value);
  }
  else 
  {
    value = digitalRead(pin);
  }

  client.println(value);
}
    
void WebService::analogCommand(YunClient client) 
{
  int pin, value;

  pin = client.parseInt();

  if (client.read() == '/') 
  {
    value = client.parseInt();
    analogWrite(pin, value);

    client.println(value);
  }
  else 
  {
    value = analogRead(pin);
    if (pin == 0)
    {
       value = thermistor.GetTemperatureValue(value);
    }
   
    client.println(value);
  }
}
    
void WebService::modeCommand(YunClient client) 
{
  int pin;
  
  pin = client.parseInt();
  if (client.read() != '/') 
  {
    client.println(F("error"));
    return;
  }
 
  String mode = client.readStringUntil('\r');

  if (mode == "input") 
  {
    pinMode(pin, INPUT);
    
    client.print(pin);
    return;
  }

  if (mode == "output") 
  {
    pinMode(pin, OUTPUT);
    
    client.print(pin);
    return;
  }
 
  client.print(mode);
}