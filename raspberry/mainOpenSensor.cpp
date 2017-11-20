/*######################################################################################################
##Open sensor program for grow project
##Name of the file : mainOpenSensor
##Autor : wecreate
##Purpose : Main file of the program, setup the radio and call the functions to 
##          Read CSV file, ask each sensor the value, and send the value over HTTP
##          to farmos
##
##date : 18/05/2017
######################################################################################################*/
#include <cstdlib>
#include <iostream>
#include <sstream>
//#include "nRF24L01.h"
#include <RF24/RF24.h>
#include <string>
#include <cstring>
#include <unistd.h>
#include <curl/curl.h>
#include <list>
#include "sendFarmos.h"
#include "askSensor.h"
//#include "listSensor.h"
 
RF24 radio(22,0);   // make sure this corresponds to the pins you are using

char pipeRX[6] = "MSENS"; // pipe to receive the data on the raspberry, TX on the arduino
//const uint64_t pipeB=  0xF0F0F0F0D2LL;
// define the pipe between main node and sensor


// strucure for the data transmitting by the NRF, maximum 32bytes long
typedef struct{
  char id[8];
  int16_t batLevel;
  int16_t soilMoisture;
  int16_t light;
  int16_t temperature;
}SensorDataStruct;

 
SensorDataStruct dataToSend; // create a structure for the data transmiting from the arduino

std::list<SensorID> listSensor; // list of the sensor object

char nodeToContact[8]; // have to find a way to use the id from the list
std::string URL;
URL = "http://farmos.sustainable.ie/farm/sensor/listener/8183710d9449f7377cbd7f4ea08bba10?private_key=6e738f3ebbdae5c5e8acaa9f497cbb83";
//float temperatureFloat = 0.0;

int main(int argc, char** argv)
{
  
  printf("GO GO GO\n");

  // ******************************
  // init of the radio transmission
  // ******************************
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);

  radio.openReadingPipe(1,pipeRX);
  radio.startListening();
  // end of radio init
  //*******************************

  // ******************************
  // initialisation of the sensor data
  // ******************************
  //strcpy(id_send, "node_01");
  strcpy(dataToSend.id, "SEN000"); // 5 char to identify the sensor, it's convert into a byte of 64 bits
  dataToSend.batLevel = 0;
  dataToSend.soilMoisture = 0 ;
  dataToSend.light = 0;
  dataToSend.temperature = 0.0;
  // ******************************

  // ##### add call to listSensor
  // this call the function to read the csv file and return a list with all sensor as object
  //listSensor = readCSVSensor();

  // main loop
  while(1)
  {
 
    //for(std::list<SensorID>::iterator it = listSensor.begin();it != listSensor.end();it++)
    //{
      //nodeToContact = it.getNodeName; // take the node name to contact in bits
      //strcpy(idString,it.getNodeName); // take the name of the node in char
      //urlOfNode = it.getURL; // take the url to send to farmos

      // write the code that read the list to contact each sensor
      // ##### add call to askSensor
    
      // ask a sensor the value measured
      askSensorData("SEN001","SEN001") //(idString,idString, pipeRX);

      // ##### add call to sendFarmos
      sendFarmosURL(URL); // have to complete that

    // sending to farmos


   }
  sleep(5); // sleep 5 seconds have o find a way to restart each hours
 
  }
  return 0;
}
