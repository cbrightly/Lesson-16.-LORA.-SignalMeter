#include <M5Stack.h>
#include <M5LoRa.h>
#include <M5_UI.h>

#define LORA_CS_PIN   5
#define LORA_RST_PIN  26
#define LORA_IRQ_PIN  36

/* RootVar's for UI elements (note: not edit manually) */
String UITextbox_9e6l9ae = "Lesson 16. LORA";
String UITextbox_1h59zg5 = "S i g n a l M e t r";
String UIProgressbar_3s5hxtm = "0";
String UIInputbox_qh1d8dd = "";
String UIInputbox_as2e3ef = "";

/* Function for layer default: */
void LayerFunction_default(String* rootVar) {
 /* UI Elements */
 UITextbox(25,22,280,20,0x0000,"default",&UITextbox_9e6l9ae);
 UITextbox(67,55,230,20,0x0000,"default",&UITextbox_1h59zg5);
 UIProgressbar(17,100,286,"default","Signal strength, dB",&UIProgressbar_3s5hxtm);
 UIInputbox(18,163,140,"default","Status",0,&UIInputbox_qh1d8dd);
 UIInputbox(168,163,140,"default","RSSI, dB",0,&UIInputbox_as2e3ef);
 /* To open this layer use: */
 UILayer("default");
}

void setup() {
  M5.begin();
  LoRa.setPins(LORA_CS_PIN, LORA_RST_PIN, LORA_IRQ_PIN);

  if (!LoRa.begin(433E6)) {
    UISet(&UIInputbox_qh1d8dd, "failed");
    while (1);
  }

  LoRa.setSyncWord(0x69);
  // Lora.enableCrc();
  
  UISet(&UIInputbox_qh1d8dd, "success");
  
  /* Prepare UI */
  UIBegin();
  LayerFunction_default(0);
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String str = "";
    while (LoRa.available()) {
      str += (char)LoRa.read(); 
    }
    int packetRSSI = LoRa.packetRssi();
    UISet(&UIInputbox_qh1d8dd, str);
    UISet(&UIInputbox_as2e3ef, packetRSSI);
    UISet(&UIProgressbar_3s5hxtm, packetRSSI + 110);
  }  
}
