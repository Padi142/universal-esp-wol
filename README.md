
# ESP32/ESP  Wake on LAN Telegram Bot

Easy-to-setup Telegram bot, running on a cheap esp based microcontroller that can turn on your PC remotely!


##  Libraries
For this project to work, you need the following libraries:
  - [WakeOnLan](https://www.arduino.cc/reference/en/libraries/wakeonlan/): for sending magic packets
  - [UniversalTelegramBot](https://www.arduino.cc/reference/en/libraries/universaltelegrambot/): for using the Telegram API
  - (*optional*) [ESP8266Ping](https://github.com/dancol90/ESP8266Ping) **OR** [ESP32Ping](https://github.com/marian-craciunescu/ESP32Ping) for checking the status of your device  ((Download as zip from Github and import them to ARDUINO IDE))


Also ESP32/ESP8266 board libraries are needed. Add following lines to `Aditional boards urls` field in ARDUINO IDE:

    http://arduino.esp8266.com/stable/package_esp8266com_index.json,https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

## Setup

- Create a new Telegram bot and configure your `BOT_TOKEN` and `ALLOWED_ID`  
  _You can use [@Botfather](https://t.me/botfather) to create a new bot and [@flop_flop_bot](https://t.me/flop_flop_bot) to get your ID_
- Fill your _WiFi configuration_ and the _MAC address_ of the PC you want to turn on
- (*optional*) Fill your local ip and uncomment few lines
- Compile and flash

##  Usage

- Use `/start` to get a list of the available commands
- Use the `/start_pc` command or press the physical button to turn on your PC
- Use the `/ping` command to check if the bot is online
- Use the `/is_on` command to check the status of your computer

## CREDITS

-  [daniele-salvagni's esp 32 WOL project](https://github.com/daniele-salvagni/wol-bot-esp32) 
-  [Universal Telegram bot library for examples](https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot) 
