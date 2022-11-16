#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

int wLedPin = 1;
int eLedPin = 2;
int heatModePin = 3;
int acModePin = 4;
int heatRelayPin = 5;
int acRelayPin = 6;

int gmt = -5;
int mode = 0;                             //0 = OFF | 1 = Heat | 2 = Ac
int u = 0;                                //0 = Celcuis | 1 = Farenheit 
int maxTemp[] = {49,120}                  //MAX TEMP A DHT SHOULD RETURN TO ELIMINATE ERRORS!
int minTemp[] = {0,32}                    //MIN TEMP A DHT SHOULD RETURN TO ELIMINATE ERRORS!
int acSetTo[] = {22,72}                   //AC TEMP SET TO 
int heatSetTo [] = {21,70}                //HEAT TEMP SET TO
int currentTemp [] = {0,0}                //CURRENT TEMPERATURE
int currentHumd = 0;                      //CURRENT HUMIDITY
bool lampMode = true;                     //IF TRUE, THERE IS NO COMMUNICATION BETWEEN THE MODULE AND THE SERVO
unsigned long maxMillis = 4294967295;     //THE MAX VALUE AN UNSIGNED LONG CAN HAVE BEFORE GOING TO 0
unsigned long nextDht = 0;                //THE TIME IN MILLIS WHERE THE DHT CAN UPDATE ITS VALUES
unsigned long nextCycle = 0;              //THE TIME IN MILLIS WHERE THE HEATER OR AC CAN GO FROM ON - OFF OR OFF - ON
unsigned long lastClient = 0;
unsigned long lastupdate = 0;
int cycle = 5;                            //THE NUMBER OF MINUTES BEFORE CYCLING 
int update = 60000;                       //THE MIN TIME THE PROGRAM SHOULD ALLOW THE DHT BEFORE GETTING ANOTHER READING
WiFiServer server(80);      // Set web server port number to 80
String header;                // Variable to store the HTTP request
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

const char *ssid     = "REPLACE_WITH_YOUR_SSID";
const char *password = "REPLACE_WITH_YOUR_PASSWORD";

bool connectToWifi() 
{
  int counter = 0;
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) 
  {
    counter++;
    delay(1000);
    Serial.println(".");
    if (counter > 30)
      return false; 
  }
  digitalWrite(wLed, HIGH);               //Turn on the Wifi LED status indicator
  return true;

}

void updateDht()
{
  float newTemp = dht.readTemperature();
  int newHumd = dht.readHumidity();
  if(isnan(newTemp)|| (newTemp > maxTemp) || (newTemp < minTemp))
    Serial.println("Dht Temp Error!");
  else:
  {
    currentTemp[0] = (int)newTemp;
    currnetTemp[1] = (int)(newTemp*1.8)+32; 
    currentHumd = newHumd;
  }
  if (millis()>=nextCycle)
  {
    if(digitalRead(heatRelayPin))
      digitalWrite(heatRelayPin, LOW);
    else if(digitalRead(acRelayPin))
      digitalWrite(acRelayPin, LOW);
    else if ((mode == 1) && (currentTemp[u] < heatSetTo[u]))
      digitalWrite(heatRelayPin, HIGH);
    else if ((mode == 2) && (currentTemp[u] > acSetTo[u]))
      digitalWrite(acRelayPin, HIGH);
    else 
      return;
    nextCycle += (update*cycle);
    nextCycle = maxMillis % nextCycle;
  }
}

void lamp()
{
  int acSetTo[] = {22,72}
  int heatSetTo [] = {21,70}
}

void setup() 
{
  timeClient.begin();
  timeClient.setTimeOffset(3600*gmt);
  Serial.begin(9600);
  dht.begin();
  if (connectToWifi())
    lampMode = false;  

}

void loop() 
{
  if (millis()>= nextDht)
  {
    udpateDht();
    nextDht += update;
    nextDht = nextDht % maxMillis;    
  }
  WiFiClient client = server.available();   // Listen for incoming clients
  if (client)
  {
    timeClient.update();
    lastClient = timeClient.getEpochTime();
    



    
  }

















}
