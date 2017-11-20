#ifndef listSensor
#define listSensor
std::list readCSVSensor();

class SensorID
{
  private:
  std::string nodeName;
  char pipeTX[6]; //Pipe to send data to the sensor
  char pipeRX[6]; //Pipe to receive data from the sensor
  std::string sensorURL // URL to send sensor data to farmos

  public:
  //setter
  void setNodeName(std::string name)
  {
    nodeName = name;
  }
  void setPipeTX(char name)
  {
    pipeTX = name;
  }
  void setPipeTX(char MainNodeName)
  {
    PiPeRX = MainNodeName;
  }
  void setURL(std::string sensorURL)
  {
    setRUL = sensorURL;
  }

  //accessor
  std::string getNodeName()
  {
    return nodeName;
  }
  char getPipeTX()
  {
    return pipeTX;
  }
  char getpipeRX()
  {
    return pipeRX;
  }
  std::string getURL()
  {
    return sensorURL;
  }
}

#endif
