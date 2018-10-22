//*************************************************
//library used: painless mesh
//credits: 
//library used : DHTLib
//credits:
//*************************************************

# include "painlessMesh.h"
# include "DHT.h"

#define MESH_SSID "ESPMesh"
#define MESH_PASS "24041990"
#define MESH_PORT 5555
#define DHTPIN 0
#define DHTTYPE DHT11

//create instanse of scheduler 
Scheduler userScheduler;

//create instance of painless mesh
painlessMesh mesh;

//create temp and humid variables
float temperature;
float humidity;

//create DHT timer
unsigned long DHTTimer = 0;
unsigned long DHTInterval =3000;


//size_t is unsigned integer type
size_t serverId =0;

//prototype methods
void taskCallback();
void onReceiveCallback(uint32_t from, String &msg);

// create a task instance; par1: time ; par2: TASK_FOREVER can't be interupted; par3: callback
Task myLoggingTask(10000,TASK_FOREVER, &taskCallback);


//create DHT instance
DHT dht(DHTPIN,DHTTYPE);

void setup() {
  
Serial.begin(115200);
Serial.setTimeout(2000);//time to waitfor before recieving any serial data

for(uint8_t t=4; t>0; t--){
          Serial.printf("[SETUP] WAIT %d...\n", t);
        Serial.flush();
        delay(1000);
  }

dht.begin();

if(millis()-DHTTimer <= DHTInterval);

//setup message debug types
mesh.setDebugMsgTypes(ERROR | STARTUP | CONNECTION);

//initialise the mesh
mesh.init(MESH_SSID,MESH_PASS, &userScheduler,MESH_PORT,WIFI_AP_STA,6);

//call the onReceive callback
mesh.onReceive(&onReceiveCallback);

//addTask tothe scheduler
userScheduler.addTask(myLoggingTask);

//enable the task
myLoggingTask.enable();
}


void loop() {
/*if(millis()-DHTTimer <= DHTInterval){
    DHTTimer =millis();
    temperature= dht.readTemperature();
    humidity= dht.readHumidity();
    if (isnan(temperature)&&isnan(humidity)) {
      temperature=31.00;
      humidity=85.00;
      return;
    }
  }*/
  
userScheduler.execute();
mesh.update();
}

//callback for task
void taskCallback(){  
  
   DynamicJsonBuffer jsonBuffer;
   JsonObject &root = jsonBuffer.createObject();
   
   root["client1"] = "room2";
   
   JsonArray &temp = root.createNestedArray("temp1");
   JsonArray &humid =root.createNestedArray("humid1");

   temp.add(String(dht.readTemperature(),1));
   humid.add(String(dht.readHumidity(),1));

  String json;
  root.printTo(json);

  if(serverId == 0){
     mesh.sendBroadcast(json);
    }else{
      mesh.sendSingle(serverId, json);}
   root.printTo(Serial);
   Serial.println();
  }
  
//callback for onReceived function
//par1: id of sender
//par2: message received  
void onReceiveCallback(uint32_t from, String &msg){
   Serial.printf("logClient: Received from %u msg=%s\n", from, msg.c_str());

  // Saving logServer
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(msg);
  if (root.containsKey("topic")) {
      if (String("logServer").equals(root["topic"].as<String>())) {
          // check for on: true or false
          serverId = root["nodeId"];
          Serial.printf("logServer detected!!!\n");
      }
      Serial.printf("Handled from %u msg=%s\n", from, msg.c_str());
  }
  }


