#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include "Arduino.h"
#include <FileIO.h>
#include <string.h>

const char* filename = "/mnt/sd/arduino/config/config.txt";

class ConfigManager 
{
    public:

    void Begin();
    bool WriteFile(String value);
    String ReadFile();
};
#endif

void ConfigManager::Begin()
{
	FileSystem.begin();
}

bool ConfigManager::WriteFile(String value)
{
	File dataFile = FileSystem.open(filename, FILE_APPEND);
    
    if (dataFile) 
    {
    	dataFile.println(value);
    	dataFile.close();
    }

    return dataFile;
}

String ConfigManager::ReadFile()
{
    String fileContent;

    File dataFile = FileSystem.open(filename);

    if (dataFile) 
    {    
      while (dataFile.available()) 
      {
        fileContent =fileContent + (char)dataFile.read();
      }

      dataFile.close();
    }

    return fileContent;
}



