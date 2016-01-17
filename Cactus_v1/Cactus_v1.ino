#include <SPI.h>
#include <Ethernet.h>
#include <dht.h>
//#include <SD.h>
#define DHT11_PIN 5 //dht 5.pinde

//File dosya;
dht DHT;

/*
Röleler:
- Light 1 --> pin 6
- Light 2 --> pin 7
- Led --> pin 5
*/


#include <Servo.h>
Servo myservo;  //servo kullanmak istersek

byte mac[] = { 
  0x90, 0xA2, 0xDA, 0x0F, 0x4A, 0x57 }; //mac address
byte ip[] = { 
  10, 0, 4, 11 }; // seçilen ip
EthernetServer server(80);
byte gateway[] = { 
  10, 0, 0, 253 }; 
byte subnet[] = { 
  255, 255, 248, 0 }; 
String readString;

//////////////////////

void setup(){

  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(5, OUTPUT);
  //pinMode(10, OUTPUT); //karışmayın sd için gerekli
  Ethernet.begin(mac, ip, gateway, subnet); //ethernet başlangıç
  server.begin();
  Serial.begin(9600);
  Serial.println("loop");
  Serial.print("SD kurulamadı");
  /*
  if (!SD.begin(4)) {
   Serial.println("sd fatal erol");
   return;
   }
   Serial.println("sd tamam");
   dosya = SD.open("erolsd.txt", FILE_WRITE);
   
   if (dosya) {
   Serial.print("texte yazılıyor");
   dosya.println("Arduino'ya Reset atıldı");
   dosya.close();
   Serial.println("sd yazma tamam.");
   } else {
   // if the file didn't open, print an error:
   Serial.println("dosya açılamadı fatal erol");
   }
   
   dosya = SD.open("erolsd.txt");
   if (dosya) {
   Serial.println("test.txt:");
   
   // read from the file until there's nothing else in it:
   while (dosya.available()) {
   Serial.write(dosya.read());
   }
   // close the file:
   dosya.close();
   } else {
   // if the file didn't open, print an error:
   Serial.println("dosya açılamadı fatal erol");
   }
   */
}

void loop(){
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        //read char by char HTTP request
        if (readString.length() < 100) {

          //store characters to string
          readString += c;
          //Serial.print(c);
        }
        if(readString.indexOf("?lighton") >0)//checks for on
        {
          digitalWrite(6, LOW);    // set pin 4 high
          Serial.println("Led On");
        }
        else{
          if(readString.indexOf("?lightoff") >0)//checks for off
          {
            digitalWrite(6, HIGH);    // set pin 4 low
            Serial.println("Led Off");
          }
        }
        if(readString.indexOf("?light2on") >0)//checks for on
        {
          digitalWrite(7, LOW);    // set pin 4 high
          Serial.println("Led On");
        }
        else{
          if(readString.indexOf("?light2off") >0)//checks for off
          {
            digitalWrite(7, HIGH);    // set pin 4 lo
            Serial.println("Led Off");
          }
        }

        if(readString.indexOf("?ledon") >0)//checks for on
        {
          digitalWrite(5, LOW);    // set pin 4 high
          Serial.println("Led On");
        }
        else{
          if(readString.indexOf("?ledoff") >0)//checks for off
          {
            digitalWrite(5, HIGH);    // set pin 4 low
            Serial.println("Led Off");
          }
        }
        
          if (c == '\n') {

          ///////////////
          Serial.println(readString);

          client.println("HTTP/1.1 200 OK"); //send new page
          client.println("Content-Type: text/html");
          client.println();

          client.print("Light 1: ");
           if (digitalRead(6) == HIGH) {
           client.print("is OFF");
           }
           else {
           client.print("is ON.");
           }
           
           client.println("<br />");
           client.print("Light 2: ");
           if (digitalRead(7) == HIGH) {
           client.print("is OFF.");
           }
           else {
           client.print("is ON.");
           }
           
            client.println("<br />");
           client.print("Led's : ");
           if (digitalRead(5) == HIGH) {
           client.print("are OFF.");
           }
           else {
           client.print("are ON.");
           }
           



          client.println("<HTML>");
          client.println("<HEAD>");
          client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
          client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
          client.println("<link rel='stylesheet' type='text/css' href='http://homeautocss.net84.net/a.css' />");
          client.println("<TITLE>Control Panel</TITLE>");
          client.println("</HEAD>");
          client.println("<BODY>");
          client.println("<H1>Hisar CS Room Automation Control Panel</H1>");
          client.println("<br />");
          client.println("Software Version : v1.3beta2");
          client.println("<hr />");
          client.println("<br />");
          client.println(Ethernet.localIP());
          client.println("<br />");
          client.println("<br />");
          client.println("<a href=\"/?lighton\"\">Turn On Light</a>");
          client.println("<a href=\"/?lightoff\"\">Turn Off Light</a><br />");
          client.println("<br />");
          client.println("<a href=\"/?light2on\"\">Turn On Light 2</a>");
          client.println("<a href=\"/?light2off\"\">Turn Off Light 2</a><br />");
          client.println("<br />");
          client.println("<a href=\"/?ledon\"\">Turn On Leds</a>");
          client.println("<a href=\"/?ledoff\"\">Turn Off Leds</a><br />");
          client.println("<br />");   

          client.print("Light 1: ");
          if (digitalRead(6) == HIGH) {
            client.print("is OFF");
          }
          else {
            client.print("is ON.");
          }
          
          client.println("<br />");
          client.print("Light 2: ");
          if (digitalRead(7) == HIGH) {
            client.print("is OFF.");
          }
          else {
            client.print("is ON.");
          }
          
          client.println("<br />");
          client.print("Led's : ");
          if (digitalRead(5) == HIGH) {
          client.print("are OFF.");
          }
          else {
          client.print("are ON.");
          }

          /*client.println("<br />");
          client.print("Nem ");
          client.println(DHT.humidity, 1);
          client.print("Sicaklik ");
          client.println(DHT.temperature, 1);
*/
          client.println("</BODY>");
          client.println("</HTML>");

          delay(1);

          client.stop();//bağlantı fin.


          readString="";


        }
      }
    }
  }
}


