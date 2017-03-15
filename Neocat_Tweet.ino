#include <SPI.h>
#include <Ethernet.h>
#include <Twitter.h> //https://github.com/NeoCat/ArduinoTweetLib-server
#include <dht.h>
#include <credentials.h> // your own file containing your neocat twitter code as #define NEOCAT_TWITTER "abcdefghijk"
#define DHT11_PIN 5
dht DHT;//Tillaert
int temp = 0; 
int humid = 0; 
int i=1;
char buf[100];
byte mac[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 };
//byte ip[] = { 192, 168, 1, 102};    not necessary if using DHCP
Twitter twitter(NEOCAT_TWITTER); //your NeocatTwitter Token

void setup()
{
  Ethernet.begin(mac); // Ethernet.begin(mac, ip)    if using static IP
  Serial.begin(9600);
}


void tweet(char msg[]){
  
   Serial.println("connecting ...");
  if (twitter.post(msg)) {
    int status = twitter.wait(&Serial);
    if (status == 200) {
      Serial.println("OK.");
    } else {
      Serial.print("failed : code ");
      Serial.println(status);
    }
  } else {
    Serial.println("connection failed.");
  }

}

void loop()
{
int chk=DHT.read11(DHT11_PIN);
humid=DHT.humidity;
temp=DHT.temperature;
  sprintf(buf, "Room Temp: %dC Humidity: %d%%  TestTweetNo: %d via Neocat", temp, humid, i );
    Serial.print( buf);
    tweet (buf);
    i++; 
  
  delay(60000);
}
