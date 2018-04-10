#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMesh.h>

#include "String.h"

extern "C" {
#include <user_interface.h>
}

unsigned int request_i = 0;
unsigned int response_i = 0;
unsigned int ssid = ESP.getChipId();

String stringpage = string;

String manageRequest(String request);

String str, decodedmsg;
ESP8266WebServer server(80); //Server on port 80
/* Create the mesh node object */
ESP8266WiFiMesh mesh_node = ESP8266WiFiMesh(ssid, manageRequest);

/**
 * Callback for when other nodes send you data
 *
 * @request The string received from another node in the mesh
 * @returns The string to send back to the other node
 */
void handleString(){
server.send(200,"text/html",stringpage);

  String str = server.arg("mensahe");
  
  decodedmsg = str;
  decodedmsg.replace("+"," ");
  
  if(decodedmsg.length()>0)
  {
  Serial.print("Message:");
  Serial.println(decodedmsg);
  }
  
}
String manageRequest(String request)
{
  /* Print out received message */
  Serial.print("received: ");
  Serial.println(request);

  /* return a string to send back */
  char response[60];
  sprintf(response, "---------------Acknowledged SUPERNODE %d",ESP.getChipId());
  return response;
}

void setup()
{
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.println();
  Serial.println("Setting up mesh node...");
  
  Serial.println("HTTP server started");
  server.on("/msg",handleString);
  server.begin();
  mesh_node.begin();
}

void loop()
{
      server.handleClient();
 
}



