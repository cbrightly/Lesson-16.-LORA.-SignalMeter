#include <M5Stack.h>
#include <M5LoRa.h>
#include <M5_UI.h>

#define LORA_CS_PIN   5
#define LORA_RST_PIN  26
#define LORA_IRQ_PIN  36

/* RootVar's for UI elements (note: not edit manually) */
String UITextbox_9e6l9ae = "Lesson 16. LORA";
String UITextbox_1h59zg5 = "S i g n a l M e t r";
String UIButton_sezk44 = "";
String UIInputbox_qh1d8dd = "";

bool working = false;
uint32_t counter = 0;

/* User functions: */
void Run(String* rootVar) {
  working = !working;
  if (working)
  {
    UIIcon((uint16_t*)ICON_16_24, &UIButton_sezk44);
    UICaption("Stop transmit", &UIButton_sezk44);
  }
  else
  {
    UIIcon((uint16_t*)ICON_30_24, &UIButton_sezk44);
    UICaption("Start transmit", &UIButton_sezk44);
    counter = 0;
  }
}

/* Function for layer default: */
void LayerFunction_default(String* rootVar) {
 /* UI Elements */
 UITextbox(25,42,280,20,0x0000,"default",&UITextbox_9e6l9ae);
 UITextbox(67,75,230,20,0x0000,"default",&UITextbox_1h59zg5);
 UIButton(17,128,286,"default","Run transmit",(uint16_t*)ICON_30_24,Run,&UIButton_sezk44);
 UIInputbox(18,163,284,"default","Status",0,&UIInputbox_qh1d8dd);
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
  if (working)
  {
    UISet(&UIInputbox_qh1d8dd, counter);
    // send packet
    LoRa.beginPacket();
    LoRa.print("hello ");
    LoRa.print(counter);
    LoRa.endPacket();
    counter++;
    delay(500);
  }
}
