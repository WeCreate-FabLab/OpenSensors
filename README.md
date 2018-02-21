# OpenSensors
Open sensors for soil measurement

* This project was designed to achieve 3 aims

An affordable multi-sensor unit with wireless mesh connectivity
Open source code base with integration to the open source farmos.org platform (farm asset management system)
Integration with the GROW Platform

Project development to date:

* 3D design for sensor unit housing, prototype printed using the open source ‘Ultimaker 2’ 3D printer
* Arduino and C++ code for reading, sending and receiving sensor data
* Visualisation and logging of data on the farmos.org platform
* Tested 200m range for the NRF24L01 transceiver
* Circuit board schematic and prototype board milled on a CNC machine

Components :

The sensor unit is built around the open source Arduino Nano. The Arduino code collects data from 3 sensors (light, temperature, moisture). The sensor sends the data via the NRF24L01 transceiver and is received by an NRF24L01 installed on a Raspberry Pi. The Raspberry Pi runs C++ code that sends the data to Farmos via ethernet. The sensor unit is powered by small solar panel and a lithium ion battery.

To do :

* Program :

  * Raspberry : 
    * Terminate the splitting of the functions ;
    * Test the ability to receive 5 sensors ;
    * Improve the function to send data to farmOS.
    * Data storage option
    * Integration with Smart Citizen Platform
  * Sensor : 
    * Split the code to put function in separate files ;
    * Add retry function ;
    * Add sleep mode to arduino.
    * Calibrate to parrot sensor. Scale
    * Rainfall Sensor
    * Test components for robustness (light and temperature)

* PCB :
  * Validate each component footprint ;
  * Generate the Gcode file to the CNC ;
  * Test the board ;
  * Integrate the component.

* BOX :
  * Take the real dimension of the component ;
  * Make the modification on the 3d file ;
  * Find a way to make the box waterproof

* FarmOs
  * Update Charts and auto refresh page
  * Improve the charts
