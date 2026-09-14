#include <WiFi.h>
#include "HardwareSerial.h"
#include "DFRobotDFPlayerMini.h"

const byte RXD2 = 19;
const byte TXD2 = 18;

HardwareSerial dfSD(1); // Use UART channel 1
DFRobotDFPlayerMini dfPlayer;

int Volume = 30;  //音量大小(0 ~ 30)

int isPlaying[3] = {1, 0, 0};
int audioNo = 0;        //接收到訊息"要"撥放的語音序號
int playingAudioNo = 0; //目前"正在撥放"的語音序號 

void setup() {
  Serial.begin(115200);
  
  //連結dfplayer mini
  Serial.println("Connecting dfplayer");
  Serial1.begin(9600, SERIAL_8N1, 18, 19);  // speed, type, TX, RX
  if(dfPlayer.begin(Serial1)){
    Serial.println("Connect success !");  
  }
  else{
    Serial.println("Connect fail !");  
  }
  delay(100);
  dfPlayer.setTimeOut(500); // Set serial communication time out 500ms
  dfPlayer.volume(Volume);  // Set volume value (0~30).
  dfPlayer.EQ(DFPLAYER_EQ_NORMAL);
  dfPlayer.outputDevice(DFPLAYER_DEVICE_SD);

  //delay(500);
  
}

void loop() {
  scanAP();
  delay(1000);

  Serial.println();
  if(audioNo != 0 && audioNo != playingAudioNo){
          
    //停止目前正在撥放的語音
    Serial.println("Audio pause.");
    dfPlayer.pause();
    isPlaying[playingAudioNo] = 0;
      
    //開始撥放新的語音
    Serial.print("Play audio No."); Serial.println(audioNo);
    dfPlayer.playMp3Folder(audioNo);
    isPlaying[audioNo] = 1;
    playingAudioNo = audioNo;
  }   
  else{ //此語音導覽正在播放 
    if(audioNo == 0)
      Serial.println("Please walk to the audio station.");
    else{
      Serial.print("Now is playing audio No."); Serial.println(audioNo);
    }
  }
}

void scanAP(void) {
  int n = WiFi.scanNetworks();
  delay(1000);
  Serial.println("scan Wi-Fi done");
  if (n == 0)
    Serial.println("no Wi-Fi networks found");
  else
  {
    Serial.print(n);
    Serial.println(" Wi-Fi networks found");
    Serial.println(" Only showing RSSI > -70 WiFi");
    
    for (int i = 0; i < n; ++i)
     {
      if(WiFi.RSSI(i) >= -75){
        String s = WiFi.SSID(i);
        Serial.println(WiFi.SSID(i));
        char c = s[0];
        if(c >= '0' && c <= '9' && (s.length() <= 2)){
          audioNo =  c - '0';
          break;
        }
      }
     }
  }
}
