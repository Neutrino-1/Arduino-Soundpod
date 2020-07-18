# Arduino-Soundpod
An Arduino based MP3 player which uses a 1.3" OLED display along with DFPlayer.

![Soundpod final build](https://github.com/Neutrino-1/Arduino-Soundpod/blob/master/Circuit%20diagram/SoundPod.png)

### Getting Started

Open **soundpod.ino** with arduino IDE [Tested on Arudino IDE 1.8.10 above]
all the other files will open along with it.

### Prerequisites

Arduino Libraries for DFplayer and 1.3inch oled display

* [DFRobotDFplayerMini](https://github.com/DFRobot/DFRobotDFPlayerMini) - by DFRobot
* [U8g2lib](https://github.com/olikraus/u8g2) - by olikraus

### Installing

Open the Arduino IDE and follow the below steps:
```
Sketch -> include library -> ManageLibrary -> *Search for the above library*
```
Or
follow the instructions on respective library repository.

### Python Script

To ransfer files to DFPlayer, the folders needs to be named 01,02.. and files needs to be named 001,002,.. 
This python script should help you in transfering the files and folders without manually renaming the files.
It also output's a 000.txt file, where all the original file names under each folder is stored.

![Soundpod final build](https://github.com/Neutrino-1/Arduino-Soundpod/blob/master/DFPlayer_Helper/DFplayer%20Helper.png)

## License

This project is licensed under the MIT License - see the [LICENSE.md](https://github.com/Neutrino-1/Arduino-Soundpod/blob/master/LICENSE) file for details

## Acknowledgments

* [Stefan Wagner](https://easyeda.com/wagiminator/attiny85-tinydfplayer-smd) Refered his code for file and folder queries.
* [kaushikrao77](https://github.com/kaushikrao77) helped in the python script
