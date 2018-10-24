# ESPMeshClient2
##  Mesh Network
A mesh network (or simply Meshnet) is a local network topology in which the infrastructure nodes (i.e. bridges, switches and other infrastructure devices) connect directly, dynamically and non-hierarchically to as many other nodes as possible and cooperate with one another to efficiently route data from/to clients.
Mesh networks dynamically self-organize and self-configurable. Mesh networks can relay messages using either a flooding technique or a routing technique. With routing, the message is propagated along a path by hopping from node to node until it reaches its destination.

## Introduction
We have created a Mesh network or a star network. Our architecture consists of two cients and one server. Clients or nodes continuously braodcast
the temperature and humidity values to the different nodes in the network. Values relayed by clients are fetched by server. The server parse
these values and post it to cloud. We are making use of [painlessMesh](https://gitlab.com/BlackEdder/painlessMesh) library. This library provide us easy and user friendly ways to create a mesh network.
There are different ways by which we can creat a energy efficient and reliable mesh nework. This library uses different other libraries like [TaskScheduler](https://github.com/arkhipenko/TaskScheduler),
[Arduino Json](https://github.com/bblanchon/ArduinoJson) and [AsyncESPTCP](https://github.com/me-no-dev/ESPAsyncTCP) to serve this operation.

## Hardware Specification 
  
 - ESP8266-01 (2 No.s)
 - NodeMcu Esp8266 12E
 - DHT 11 (2 No.s)

## How it works
 
 - All the nodes in the mesh network share the same ssid and pass. All the nodes communicate using these credentials.
 - these nodes do not set any TCP or UDP link or any kind of HTTP link between them. These node have there unique id's they communicate using these ids
 - This client in mesh listen to all other nodes in mesh using a call back called mesh.onReceiveCallback(from, &msg). The first parameter is id from where we are recieving the data  and msg is the message we got from the node in JSON format for eg. in this case we are receiving the node id from server we are just parsing the json and storing that node id in static variable
 - Now we are using TaskScheduler to schedule the task. This task will send the sensor readings to the server. We are running this task for 10sec. This task will perform N number of iteration in the span of 10 seconds.
 - We are sending humidity and temperature values from DHT11 sensor in JSON format to the server.
 - nodes in the mesh will transfer the message in two ways
   1. send.single(serverId, msg)- Send to a single node
   2. send.Broadcast(msg)- Broadcast to all the available nodes in mesh
 - mesh.init() method is used to initialise the mesh which takes ssid of mesh, pass of mesh, callback to scheduler, WiFI MODE(AP_STA), channel id
 
 ## How the server works?
 
  On the server side, We are just parsing the temperature and humidity values that we got from different nodes and these values arethen sent to cloud. We are using NodeREd mqtt broker tofetch those values. More on Server can be found here [ESPMeshServer](https://github.com/vbshightime/ESPMeshServer)
 
 ## Usage
   
   # Coming Soon
   
   
 ## Profile
 
   # Coming Soon
   
 ## Credits
  
  - [Painless Mesh](https://gitlab.com/BlackEdder/painlessMesh)
  - [DHT LIB](https://github.com/adafruit/DHT-sensor-library)
  - [TaskScheduler](https://github.com/arkhipenko/TaskScheduler)
  - [Arduino JSON](https://github.com/bblanchon/ArduinoJson)
  - [NodeRed](https://nodered.org/)
 
 
 
 
