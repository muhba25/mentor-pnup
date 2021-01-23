## Installation  
**Arduino IDE** <img src="https://camo.githubusercontent.com/647cefc4a331bc5ab2a760d3c731b9d0b3f1259b/68747470733a2f2f7777772e61726475696e6f2e63632f66617669636f6e2e69636f" width="20">  
1. Install ESP8266 Core for Arduino. For more information please refer to the ESP8266 Core for Arduino's [installation manual](https://github.com/esp8266/Arduino#installing-with-boards-manager)
2. Download the latest release and add this library into Arduino IDE (Sketch > Include Library > Add .ZIP Library...)  

## Examples
Please note that `MentorStoreSecure` and `MentorGetLatestSecure` are preferred than `MentorStoreData` and `MentorGetLatestSecure` because they use HTTPS (port 8443) rather than HTTP (port 8080).  

* **MentorCreateDevice** - Deploy a device into a project  
* **MentorGetAllData** - Fetch all data stored in a project device 
* **MentorGetLatestData** - Fetch the latest data stored in a project device
* **MentorGetLatestSecure** - Fetch the latest data stored in a project device through HTTPS  
* **MentorStoreData** - Deploy data into a project device
* **MentorStoreSecure** - Deploy data into a project device through HTTPS  
