/*######################################################################################################
##Open sensor program for grow project
##Name of the file : sendFarmos.cpp
##Autor : Wecreate
##Purpose : Send data of sensors over HTTP to farmos website
## input : URL string : url of the sensor on farmos website
## output : none
##
## Date : 18/05/2017
######################################################################################################*/
#include <string>
#include <cstring>
#include <unistd.h>
#include <curl/curl.h>
#include <cstdlib>
#include <iostream>
#include <sstream>

// variables for sending url
//struct curl_slist *header = NULL;
//std::string dataToSendURL;
// variable needed to convert the value received to be able to send them on HTTP
std::stringstream convertMoisture, convertLight, convertTemperature, convertBatLevel;

void sendFarmosURL(std::string URL)
{
    // sending data to farmos
    // url format "http://farmos.sustainable.ie/farm/sensor/listener/8183710d9449f7377cbd7f4ea08bba10?private_key=6e738f3ebbdae5c5e8acaa9f497cbb83"

    // init CURL things
    CURL *curl;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    struct curl_slist *header = NULL;


    if(curl)
    {
      CURLcode res; // to manage the error

      // set the url
      curl_easy_setopt(curl, CURLOPT_URL, URL);

      // specify that we want to post data
      curl_easy_setopt(curl, CURLOPT_POST, 1L);

      // add the header to the request
      header = curl_slist_append(header, "Content-Type: application/json");
      curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);

      // ******************************
      // set the data to send to farmos
      // ******************************

      // convert the value received in string
      convertMoisture << dataToSend.soilMoisture;
      convertTemperature << dataToSend.temperature;
      convertLight << dataToSend.light;
      convertBatLevel << dataToSend.batLevel;

      // make the frame to send to farmos
      dataToSendURL =  "{\"lw\":\"" + convertLight.str() + "\",";
      dataToSendURL = dataToSendURL + "\"SOIL1\":\"";
      dataToSendURL = dataToSendURL + convertMoisture.str() + "\",";
      dataToSendURL = dataToSendURL + "\"SOILT\":\"";
      dataToSendURL = dataToSendURL + convertTemperature.str() + "\",";
      dataToSendURL = dataToSendURL + "\"BAT\":\"";
      dataToSendURL = dataToSendURL + convertBatLevel.str();
      dataToSendURL = dataToSendURL + "\"}";

      printf("\nsend to farmos\n");

      // create the post field to send the data
      curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE,dataToSendURL.length());
      curl_easy_setopt(curl, CURLOPT_POSTFIELDS, dataToSendURL.c_str());

      // perform the request
      res = curl_easy_perform(curl);
      if(res != CURLE_OK)
      {
        printf("CURL ERROR");
      }

      // clear the variable
      curl_slist_free_all(header);
      curl_easy_cleanup(curl);

      convertMoisture.str("");
      convertLight.str("");
      convertTemperature.str("");
      convertBatLevel.str("");
      dataToSendURL = "";
    }
}
