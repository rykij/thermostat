#ifndef XMLPARSER_h
#define XMLPARSER_h

#include <string.h>
#include "Arduino.h"
#include <inttypes.h>
#include "libs/TinyXML.h"

const char* xmlfilename = "/test/test.xml";

uint8_t buffer[100];
uint16_t buflen = 100;

class XmlParser
{
    public:
    
    XmlParser();
    String Parse();
    void Init();
};
#endif

XmlParser::XmlParser(){}


void XmlParser::Init()
{
	TiXmlDocument doc(filename);
    doc.LoadFile();
}


String XmlParser::Parse()
{
    //TODO: parse file for temp offset
	TiXmlDocument doc(xmlfilename);
	bool loadOkay = doc.LoadFile();
	if (loadOkay)
	{
	  
    }    
    //return value;
}



