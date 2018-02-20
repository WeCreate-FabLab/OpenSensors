#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <string.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 3 /*-(Connect to Pin 2 )-*/
OneWire ourWire(ONE_WIRE_BUS);
/* Tell Dallas Temperature Library to use oneWire Library */
DallasTemperature sensors(&ourWire);





RF24 radio(9,10);  // make sure this corresponds to the pins you are using

const uint64_t pipes[2] = {
0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };





   
typedef struct{
  char id[8];
  int16_t batLevel;
  int16_t soilMoisture;
  int16_t light;
  int16_t temperature;





}SensorDataStruct;

    int sensorPin = A0; // select the input pin for LDR
    int sensorValue = 0; // variable to store the value coming from the sensor
 
char id_send[8];
	 
SensorDataStruct dataToSend; 

	 
void setup()
{
  Serial.begin(57600);
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);
  radio.startListening();
  
  // node id
  strcpy(dataToSend.id, "node_01");
  strcpy(id_send, "node_00");




}

 
void loop(void)
{
  // wait for incoming transmission
  if(radio.available())
  {
    while(radio.available())
    {
      radio.read(&id_send, sizeof(id_send));
    }
    Serial.println(F("-#-"));
    if(1)//(strcmp(id_send,dataToSend.id) == 0)
    {
      Serial.println(F("gght"));
      // Read sensor value
      dataToSend.batLevel = 60;



    // for the soil humidity sensor
    int moisSens = analogRead(A4);
   // print out the value you read:
   Serial.println(moisSens);



    //for the light sensor  
    int LuxSens = analogRead(sensorPin); // read the value from the sensor
    Serial.println(LuxSens); //prints the values coming from the sensor on the screen

    // int LightSens = analogRead(A0);
    // Serial.println(LightSens);





sensors.requestTemperatures();
Serial.print(sensors.getTempCByIndex(0));




      
      dataToSend.soilMoisture = moisSens ;
      dataToSend.light = LuxSens;
      dataToSend.temperature = sensors.getTempCByIndex(0);
      // end of analog reading
     
      // send data
      radio.stopListening();
      if(!radio.write( &dataToSend, sizeof(dataToSend) ))
        {
        Serial.println(F("send -- Error"));
        }
      radio.startListening();
    }
  }
}
