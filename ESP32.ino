#include <WiFi.h>  
   
 #define LED  2 
   
 // specifying the objects for the server/ client  
 WiFiServer server(80);  
 WiFiClient client;  
   
 const char* ssid   = "ESP32";   // This is the SSID for ESP32
 const char* password = "123456789";    // password should be atleast 8 characters as per the settings  
   
 // Create the global variable  
 String http;  
 String Ledcondition = "off";  
   
 void setup() {  
  Serial.begin(115200);  
  pinMode(LED, OUTPUT);  
  digitalWrite(LED, LOW);  
  Serial.print("Connecting ");  
  Serial.println(ssid);  
   
  // Create an access point for ESP32  
 

  WiFi.softAP(ssid, password);  
   
  Serial.println( "..." );  
  Serial.println( "WiFi AP is connected" );  
  Serial.println( "IP address: " );  
  Serial.println( WiFi.softAPIP() );  
   
  // Start our ESP32 server  
  server.begin();  
 }  
   
 void loop(){  
    
  if ( client = server.available() ) {  // this step is for checking if a new client is trying to connect to the server 
   Serial.println("New Client.");  
   String clientData = "";  
   while ( client.connected() ) {    // Wait until the client finish sending HTTP request  
    if ( client.available() ) {     // If the set up had finished and there is information,  
     char c = client.read();      //  read one character  
     http += c;            //  then parse it  
     Serial.write(c);    
     if (c == '\n') {         // If the character is carriage return,   
                      //  it means end of http request from client  
      if (clientData.length() == 0) { //  Now that the clientData is cleared,  
       sendResponse();        //    perform the necessary action  
       updateLED();  
       updateWebpage();  
       break;  
      } else {  
       clientData = "";       //  First, clear the previous clientData  
      }  
     } else if (c != '\r') {      // Or if the character is NOT new line  
      clientData += c;        //  store the character to the clientData variable  
     }  
    }  
   }   
   http = "";  
   client.stop();            // Disconnect the client.  
   Serial.println("Client disconnected.");  
   Serial.println("...");  
  }  
 }  
   
 void sendResponse() {  
  // Send the HTTP response headers  
  client.println("HTTP/1.1 200 OK");  
  client.println("Content-type:text/html");  
  client.println("Connection: closed");  
  client.println();   
 }  
   
 void updateWebpage() {  
  // Now we will display / update the webpage by sending the HTML to the connected client  
  //  the HTML hyperlinks are used in the buttons on the webpage    
  //  When a button is pressed, it will send a signal to the web server to perform the action
  // Send the whole HTML  
  
  client.println("<!DOCTYPE html><html>");  
  client.println("<head>");  
  client.println("<title>ESP32 WiFi Station</title>");  
  client.println("</head>");  
    
  // Web Page Heading  
  client.println("<body><h1>ESP32 Web Server to control a simple LED circuit</h1>");  
   
  // Display buttons for the LED  
  client.println("<p>1. LED is " + Ledcondition + "</p>");    
  if (Ledcondition == "off") {  
   client.println("<p><a href=\"/LED/on\"><button>Turn ON</button></a></p>");  
  } else {  
   client.println("<p><a href=\"/LED/off\"><button>Turn OFF</button></a></p>");  
  }   
   
  client.print("<hr>");  
   
  client.println("</body></html>");  
  client.println();  
 }  
   
 void updateLED() {  
  // Now we use the GET function to check HTTP request of the connected client 
  //  Then the ESP32 turns the LED on/off depending on the signal 
  if    (http.indexOf("GET /LED/on") >= 0) {  
   Serial.println("LED is on");  
   Ledcondition = "on";  
   digitalWrite(LED, HIGH);  
  } else if (http.indexOf("GET /LED/off") >= 0) {  
   Serial.println("LED is off");  
   Ledcondition = "off";  
   digitalWrite(LED, LOW);  
  }   
    
 }
