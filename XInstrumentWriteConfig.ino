
//#include <Preferences.h>
#include "Xinstruments.h"
#include "EEPROM.h"
/*
#define XI_Max_Indicators  8
#define XI_Max_Inputs   4

struct XI_indicatorDescription {
  uint16_t canDataType;
  uint8_t   indicator_type;
  uint8_t   controlNum;
  uint8_t   pie_size;
  float   min_value;
  float   max_value;
  float   conversion_factor;
  int     extraInfo1; // backstop for pie steppers

};

struct XI_inputDescription {
  uint16_t canDataType;
  uint8_t   input_type;
  uint8_t   controlNum;
};

typedef struct XI_instrumentDescription {     // generic configuration struct will be stored in eprom
  char  name[6];
  uint8_t controlerType;
  uint8_t controlerHwVersion;
  uint8_t driverType;
  uint8_t driverHwVersion;
  uint8_t softwareVersion;
  uint8_t maxVersions;    // max number of versions of this instrument in a panel, like for engine gauges
  uint8_t defaultVersion;   // default version of this instrument , for example 0= first engine   [XI_Max_Indicators]
  XI_indicatorDescription indicator[XI_Max_Indicators];
  XI_inputDescription input[XI_Max_Inputs];
};
/*
XI_instrumentDescription myInstrumentInfo = {
  "FEULG",
  2,
  1,
  3,
  1,
  1,
  1,
  0,
  {
    {123,1,1,120,0,26,0.3674371033,-10},
    {124,1,2,120,0,26,0.3674371033,-10},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0}
  },
  {
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,0}
  }
};
*/
XI_instrumentDescription readInfo;

EEPROMClass  SETUPINFO("eeprom", sizeof(XI_instrumentDescription));

void setup() {
  Serial.begin(115200);
  Serial.println("Testing EEPROMClass\n");
  // put your setup code here, to run once:
  if (!SETUPINFO.begin(SETUPINFO.length())) {
    Serial.println("Failed to initialise NAMES");
    Serial.println("Restarting...");
    delay(1000);
    ESP.restart();
  }


  SETUPINFO.writeBytes(0, &myInstrumentInfo,sizeof(XI_instrumentDescription));
  SETUPINFO.commit();
  Serial.println("info saved to ram");  

  SETUPINFO.readBytes(0, &readInfo,sizeof(XI_instrumentDescription));
  Serial.println("info read from ram");  
  Serial.print("Name              : ");   Serial.println(readInfo.name);
  Serial.print("controlerType     : ");   Serial.println(readInfo.controlerType);
  Serial.print("controlerHwVersion: ");   Serial.println(readInfo.controlerHwVersion);
  Serial.print("driverType        : ");   Serial.println(readInfo.driverType);
  Serial.print("driverHwVersion   : ");   Serial.println(readInfo.driverHwVersion);
  Serial.print("softwareVersion   : ");   Serial.println(readInfo.softwareVersion);
  Serial.print("maxVersions       : ");   Serial.println(readInfo.maxVersions);    
  Serial.print("defaultVersion    : ");   Serial.println(readInfo.defaultVersion);
  for (int i =0 ;i<8;i++)
  {
    Serial.print("Indicator ->CanID: ");   Serial.print(readInfo. indicator[i].canDataType);
    Serial.print(":");   Serial.print(readInfo. indicator[i].indicator_type);
    Serial.print(":");   Serial.print(readInfo. indicator[i].controlNum);
    Serial.print(":");   Serial.print(readInfo. indicator[i].pie_size);
    Serial.print(":");   Serial.print(readInfo. indicator[i].min_value);
    Serial.print(":");   Serial.print(readInfo. indicator[i].max_value);
    Serial.print(":");   Serial.print(readInfo. indicator[i].conversion_factor);
    Serial.print(":");   Serial.print(readInfo. indicator[i].extraInfo1);
    Serial.println("<"); 
  }

  
}

void loop() {
  // put your main code here, to run repeatedly:

}
