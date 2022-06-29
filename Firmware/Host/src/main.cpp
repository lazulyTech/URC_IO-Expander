#include <M5Stack.h>
// #include <esp_now.h>
// #include <WiFi.h>
#include <EspNow.h>
// #include <Audio.h>
#include <Address.h>

// Audio* audio;

typedef struct test_struct {
  int mode;
} test_struct;
test_struct test;
test_struct myData = {0};

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    char macStr[18];
    Serial.print("Packet to: ");
    // Copies the sender mac address to a string
    snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
            mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
    Serial.print(macStr);
    Serial.print(" send status:\t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
    memcpy(&myData, incomingData, sizeof(myData));
}

EspNow* espNow;

void setup() {
    M5.begin();
    M5.Power.begin();
    M5.Speaker.begin();
    M5.Speaker.mute();
    M5.Speaker.setVolume(1);
    Serial.begin(115200);

    /*--------------------------------------------*/
    /*              ESP-NOW Settings              */
    /*--------------------------------------------*/
    espNow = new EspNow;
    espNow->Init(MEMBER, OnDataSent, OnDataRecv);
    for (int i = 0; i < sizeof(stickAddress)/6; i++){
        if(!espNow->addPeer(stickAddress[i])){
            Serial.println("Failed to add peer");
            return;
        }
    }
    
    // if(!espNow->addPeer(stickAddress[0])){
    //     Serial.println("Failed to add peer");
    //     return;
    // }
    
}

int mode = 0;
void loop() {
    M5.update();
    if (M5.BtnA.wasPressed()){
        myData.mode--;
    }
    if (M5.BtnC.wasPressed()){
        myData.mode++;
    }
    if(myData.mode <= -1) myData.mode = 0;
    if(myData.mode >=  3) myData.mode = 2;
    if (M5.BtnB.wasPressed()){
        switch (myData.mode) {
            case 0:
                M5.Lcd.fillScreen(RED);
                break;
            case 1:
                M5.Lcd.fillScreen(GREEN);
                break;
            case 2:
                M5.Lcd.fillScreen(BLUE);
                break;
            default:
                break;
        }
        espNow->send(0, myData);
    }
    delay(10);
}
