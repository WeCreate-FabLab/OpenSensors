/*######################################################################################################
##Open sensor program for grow project
##Name of the file : listSensor.cpp
##Autor : Wecreate
##Purpose : read a CSV file and create a list of object with sensor informations
## input : none
## output : listsensor List : liste of the sensor with there data
##
## Date : 18/05/2017
######################################################################################################*/
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <list>

std::list readCSVSensor()
{
  ifstream csvFile ("nodedata.csv"); // load the csv file
  std::stringstream lineStream; // create the variable to put the line data
  std::string nodeNameFile, nodeURL; // Create the variable to stock the value read
  std::list<SensorID> listSensor; // create the list to stock the sensor object

  while(file.good())
  {
    getline(file, lineStream); // get the entire line
    getline(linestream, nodeNameFile,','); // take the sensor name
    getline(linestream, nodeURL); // take the URL

    SensorID nodeNameFile.str(); // create the object of the sensor

    // put the data og the sensor in it's object
    nodeNameFile.str().setNodeName(nodeNameFile); 
    nodeNameFile.str().setPipeTX(nodeNameFile);
    nodeNameFile.str().setPipeRX("raspN"); // to confirm
    nodeNameFile.str().setURL(nodeURL);

    listSensor.push_back(nodeNameFile.str()); // put the sensor in the list
  }

return listSensor;
}
