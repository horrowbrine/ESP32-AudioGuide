# ESP32-Audio Guide
使用ESP32(含Wifi功能)、DFPlayer模組、SD卡，製作簡易語音導覽的攜帶裝置

所需設備:
ESP32至少兩個、DFPlayer Mini MP3模組、小容量SD卡、小喇叭(如果想要聲音大聲一點，可以另外購買Amplifier)

# 整體系統架構
使用者會攜帶一個包含ESP32、DFPlayer Mini MP3模組以及擴音器的裝置，當接近導覽地點時，使用者的裝置會自動發出該地點對應的導覽語音。

# 前置作業
在每個導覽地點各放置一個ESP32，並使用ESP32內建的網路功能設置網路Access Point(AP)；
準備好的導覽語音mp3放入SD卡，將各個音檔取名為0001.mp3、0002.mp3等(也可以在後面加上英文名稱，但開頭一定要是**小於256的四碼數字**)，最後將SD卡格式化成FAT或FAT32格式後裝進去DFPlayer Mini就可以了。

# DFPlayer Mini MP3模組接角
<img width="641" height="379" alt="miniplayer_pin_map" src="https://github.com/user-attachments/assets/abc9518f-1bb7-4a95-98e5-995da95fec39" />


# 程式碼說明
ESP32_Set_AP:此程式碼給各個導覽地點的ESP32使用。用於設置AP名稱。

RecivedMsgFromOtherESPAndPlayAudio:此程式會燒錄製使用者攜帶的ESP32。功能為根據當前ESP32可搜尋到的AP點，若AP名稱符合且訊號強度達到門檻，就會播放對應的導覽語音。
