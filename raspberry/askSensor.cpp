/*######################################################################################################
##Open sensor program for grow project
##Name of the file : askSensor.cpp
##Autor : wecreate
##Purpose : send a request to the sensor using NRF24L01 module and store the data in a structure 
## input : id_send char of 8 byte, pipeTX : adress to send the request, pipeRX adress to receive
## output : none
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

void askSensorData (char id_send[8], char[6] pipeTX)
{

  radio.openWritingPipe(pipeTX);

  printf("ask for value\n");
  radio.stopListening(); // have to stop the listening to be able to send a message
  if(!radio.write(&id_send, sizeof(id_send))) // send the name of the sensor that we want the value, if he reconize the name he send back the value
    {
    printf("send -- Error\n"); // if the NRF can't send the data an error appear
    }
  else
  {
    printf("sending to ");
    printf(id_send);
  }
  radio.startListening(); // restart listening to receive the sensor data

  if(radio.available()) // wait a transmission 
  {
    while (radio.available()) // when a transmission come, read the data transmit
    {
      radio.read( &dataToSend, sizeof(dataToSend) ); // put the data received in the structure
    }
      // print of the data received, mainly for debugging
      printf("\nreceived data\n");
      printf("node id = ");
      printf(dataToSend.id);
      printf("\nbattery level = ");
      printf("%d\n",dataToSend.batLevel);
      printf("soil moisture = ");
      printf("%d\n",dataToSend.soilMoisture);
      printf("light = ");
      printf("%d\n",dataToSend.light);
      printf("temperature = ");
      printf("%d\n", dataToSend.temperature);
   }
}
