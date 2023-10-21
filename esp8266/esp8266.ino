#include <ESP8266WiFi.h>

#include <WiFiClientSecure.h>
#include "WiFiUDP.h"

#include "WakeOnLan.h"
#include "UniversalTelegramBot.h"
#include "ArduinoJson.h"

//Library for pinging your machine
//Uncomment if out want to use it
#include <ESP8266Ping.h>

// Telegram Bot Token
#define BOT_TOKEN  "0000000000:xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
#define ALLOWED_ID "000000000"

// WiFi configuration
#define WIFI_SSID ""
#define WIFI_PASS ""

// MAC address of the target device
#define MAC_ADDR "FF:FF:FF:FF:FF:FF"

//Local ip of you machine
//You can leave this commented if you dont plan to use the /is_on command
IPAddress local_ip (192, 168, 0, 1);

WiFiUDP UDP;
WakeOnLan WOL(UDP);

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure secured_client;

const unsigned long BOT_MTBS = 1000; // mean time between scan messages
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime; // last time messages' scan has been done

void handleMessages(int numNewMessages) {
  Serial.print("handling messages ");
  Serial.println(numNewMessages);

  for (int i = 0; i < numNewMessages; i++) {
    Serial.println(bot.messages[i].from_id);
    if (bot.messages[i].from_id != ALLOWED_ID) continue;
    
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;

    if (text == "/start_pc") {
      
      WOL.sendMagicPacket(MAC_ADDR); 
      delay(300);
      bot.sendMessage(chat_id, "PC started! 🤩", "");

    } else if (text == "/ping") {

      bot.sendMessage(chat_id, "Pong.", "");

    //This command pings you pc
    //You can comment out this section from # to ##
    //#
    } else if(text == "/is_on"){

      bot.sendMessage(chat_id, "Your PC seems to be: ", "");
      bool status = Ping.ping(local_ip);

      if(status){
        bot.sendMessage(chat_id, "ON! ✅", "");
      }else{
        bot.sendMessage(chat_id, "OFF! ❌", "");
      }
    //##
    }
    else if (text == "/start") {

      String welcome = "✨ Welcome to **WoL Bot** ✨ \n";
      welcome += "/start_pc : Wakes your PC\n";
      welcome += "/ping : Check the bot status\n";
      welcome += "/is_on : Check status of your PC\n";
      bot.sendMessage(chat_id, welcome, "Markdown");

    }
  }
}




void setup(){
  // Configure WiFI
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Add root certificate for api.telegram.org
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);

  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  Serial.print("...");
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println("Connected");

  // Attention: 255.255.255.255 is denied in some networks
  WOL.calculateBroadcastAddress(WiFi.localIP(), WiFi.subnetMask()); 

  configTime(0, 0, "pool.ntp.org"); // get UTC time via NTP
  time_t now = time(nullptr);
  while (now < 24 * 3600) {
    Serial.print(".");
    delay(150);
    now = time(nullptr);
  }
  Serial.println(now);
  
}



void loop() {
  if (millis() - bot_lasttime > BOT_MTBS) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while (numNewMessages) {
      Serial.println("Message received");
      handleMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    bot_lasttime = millis();
  }

  delay(10);
}