# ESP32-Wifi-Access-Point-and-HTTP-request
This is an arduino code that can be used to turn an ESP32 into a wifi access point through HTTP server. 
The code can be used to control the LEDs from anywhere as lomg as the esp and the controller device are connected to wifi.
First we include library Wifi.h.
Then we define thw wifi SSID and password 
Next we mention the IP address details followed by the codes related to the LED pins.
The code is written is such a way that a website with a user interface opens up on the controller device with on/off buttons and the LEDs turn on an off based on the user's command.
