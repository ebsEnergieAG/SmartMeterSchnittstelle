# Datenspeicherung (Entwurf)
Für die Datenspeicherung kann ein Mqtt server mit Datenbank und Visualisierung verwendet werden. 
Hierfür werden in diesem Beispiel 4 Docker Container auf einem Linux installiert. 

Die Installation ist ohne Passwörter und somit nur für eine Lokale Installation epfohlen, da jeder der Zugriff auf das Netzwerk hat, auch auf die Daten zugreifen kann!!
Bei der Installation der Container können weitere Massnahmen zur Sicherheit konfiguriert werden. (Dies eventuell später)

Diese Anleitung setzt grundlegendes Wissen wie auf ein Linux verbunden wird voraus. 
Auch die Installation der einzelnen Systeme wird nicht erklärt. 
Hier gibt es genügend Anleitungen im Netz. 

## Hardware
Ich verwende für meine Umsetzung ein Orange Pi Zero 3 vom Chinesen meines Vertrauens. 
Es kann aber grundsätzlich jede Hardware verwendet werden, welche eine Installation von Containern unterstützt. 
Für die Speicherung ist ein Dauerbetrieb der Hardware nötig, wobei der Energieverbrauch hier eine Rolle spielt. ;-)

Mögliche Hardware:
* Raspberry Pi 
* Orange Pi 
* Banana Pi 
* Andere Singleboard Computer 
* Windows 10 / 11 / Server mit Docker 
* NAS - System hier bitte die Angaben der Hersteller beachten. 

## Docker Installation 
Um die Docker Container auf dem Linux zu installieren, muss Docker selbst vorhanden sein. um diesen zu Installieren, müssen wir das System zuerst upgraden.
```
sudo apt update
```
```
sudo apt upgrade
```
```
sudo apt install docker 
```
## MQTT Installation 
```
sudo docker volume create mosquitto_data
sudo docker volume create mosquitto_log
sudo docker volume create mosquitto_conf

sudo docker run -it -d \
	-p 1883:1883 \
	-p 9001:9001 \
	-v mosquitto_conf:/mosquitto/config \
	-v mosquitto_data:/mosquitto/data \
	-v mosquitto_log:/mosquitto/log \
	--restart=always \
	--name=mosquitto-server \
	eclipse-mosquitto:latest
```
## Node-Red Installation 
```
docker volume create node_red_data

docker run -it -d \
	-p 1880:1880 \
	-v node_red_data:/data \
	--name=nodered \
	--restart=always \
	nodered/node-red:latest
```

## InfluxDB Installation 
```
sudo docker volume create influxdb

sudo docker run -it -d \
	-p 8086:8086 \
	-v influxdb:/var/lib/influxdb \
	--name=influxdb \
	--restart=always \
	influxdb:latest
```
Anschliessend den Befehl 
```
sudo docker ps -a 
```
Die ID vom Container influxdb inten ohne <> eingeben es gibt kein l(L) das ist eine 1(eins) ;-) 
Der Befehl unten öffnet den Container 
```
docker exec <ID> /bin/bash
```
mit dem Befehl Influx öffen wir den Datenbank Zugriff 
```
influx
```
Mit diesem Befehl wird die Datenbank EnergyData erstellt. 
```
create database EnergyData
```
## Grafana  Installation 
```
docker volume create grafana

docker run -it -d \
	-p 3000:3000 \
	--name=grafana \
	-v grafana:/var/lib/grafana \
	--name=grafana \
	--restart=always \
	grafana/grafana:latest
```

## MQTT einrichten
Sobald alle Container laufen, können diese eingerichtet werden. 

Auf dem Tasmota kann unter "Configuration" -> "Configure MQTT" der MQtt Server eingegeben. 
Hier einfach die IP des Servers eingeben. 

![image](https://github.com/ebsEnergieAG/SmartMeterSchnittstelle/assets/7451747/56a8985a-05d3-4a43-bbab-0c8ea8d8eef7)

Um die Daten zu Überprüfen würde ich den MQTT explorer empfehlen, dort wird auch das Topic(Adresse) der Daten angezeigt. 

![image](https://github.com/ebsEnergieAG/SmartMeterSchnittstelle/assets/7451747/5b66c6d8-3cc9-47ea-9b16-1bafb43e5f92)
![image](https://github.com/ebsEnergieAG/SmartMeterSchnittstelle/assets/7451747/be4fd094-e568-4c5b-bbe7-b2ee6b793b35)


## Node Red 
Um NodeRed einzurichten einfach die IP des Servers gefolgt von :1880 eingeben im Browser 
z.B http://192.168.1.159:1880

Hier müssen die Nodes eingerichtet werden. 
Als erstes den MQTT Eingang hinein ziehen. 

![image](https://github.com/ebsEnergieAG/SmartMeterSchnittstelle/assets/7451747/02643b52-8e8c-4d36-89bf-2c6d3e3a9681)
![image](https://github.com/ebsEnergieAG/SmartMeterSchnittstelle/assets/7451747/a8c949c2-000b-429a-b002-cbabdac0cb24)
![image](https://github.com/ebsEnergieAG/SmartMeterSchnittstelle/assets/7451747/80301a00-f1b8-45a3-b62e-6c495347bd11)

Danach eine Funktion einfügen 

![image](https://github.com/ebsEnergieAG/SmartMeterSchnittstelle/assets/7451747/cd6876fd-0346-4e39-8910-8295ef0d2cac)
![image](https://github.com/ebsEnergieAG/SmartMeterSchnittstelle/assets/7451747/2d16b3b6-5f90-4eb1-82ef-1df459cc09ca)
![image](https://github.com/ebsEnergieAG/SmartMeterSchnittstelle/assets/7451747/0605bc95-fa24-49cd-b3d1-75b92b201848)

Den Folgenden Code einfügen 
```
var test = msg.payload;
var arr = test[""]

if (arr.hasOwnProperty("Verbrauch_L1")) {
    var verbrauch_L1 = { payload: arr.Verbrauch_L1 };
}

if (arr.hasOwnProperty("Verbrauch_L2")) {
    var verbrauch_L2 = { payload: arr.Verbrauch_L2 };
}

if (arr.hasOwnProperty("Verbrauch_L3")) {
    var verbrauch_L3 = { payload: arr.Verbrauch_L3 };
}

if (arr.hasOwnProperty("Verbrauch_Total")) {
    var verbrauch_Total = { payload: arr.Verbrauch_Total };
}

if (arr.hasOwnProperty("Abgabe_L1")) {
    var abgabe_L1 = { payload: arr.Abgabe_L1 };
}

if (arr.hasOwnProperty("Abgabe_L2")) {
    var abgabe_L2 = { payload: arr.Abgabe_L2 };
}

if (arr.hasOwnProperty("Abgabe_L3")) {
    var abgabe_L3 = { payload: arr.Abgabe_L3 };
}
if (arr.hasOwnProperty("Abgabe_Total")) {
    var abgabe_Total = { payload: arr.Abgabe_Total };
}
if (arr.hasOwnProperty("I_L1")) {
    var i_L1 = { payload: arr.I_L1 };
}
if (arr.hasOwnProperty("U_L1")) {
    var u_L1 = { payload: arr.U_L1 };
}
if (arr.hasOwnProperty("I_L2")) {
    var i_L2 = { payload: arr.I_L2 };
}
if (arr.hasOwnProperty("U_L2")) {
    var u_L2 = { payload: arr.U_L2 };
}
if (arr.hasOwnProperty("I_L3")) {
    var i_L3 = { payload: arr.I_L3 };
}
if (arr.hasOwnProperty("U_L3")) {
    var u_L3 = { payload: arr.U_L3 };
}
if (arr.hasOwnProperty("Bezug")) {
    var bezug = { payload: arr.Bezug };
}
if (arr.hasOwnProperty("Abgabe")) {
    var abgabe = { payload: arr.Abgabe };
}
return [verbrauch_L1,verbrauch_L2,verbrauch_L3,verbrauch_Total,abgabe_L1,abgabe_L2,abgabe_L3,abgabe_Total,i_L1,u_L1,i_L2,u_L2,i_L3,u_L3,bezug,abgabe];
```

Influx DB 
![image](https://github.com/ebsEnergieAG/SmartMeterSchnittstelle/assets/7451747/c8727075-a4bf-4903-9dc2-da57b2648525)
![image](https://github.com/ebsEnergieAG/SmartMeterSchnittstelle/assets/7451747/3235d226-6551-4bf5-a764-daff1e279c6f)
![image](https://github.com/ebsEnergieAG/SmartMeterSchnittstelle/assets/7451747/c9ae1b54-8043-42df-9cf0-ac4023beb246)
![image](https://github.com/ebsEnergieAG/SmartMeterSchnittstelle/assets/7451747/15d6e27a-8463-4337-a873-5c3477e91325)
![image](https://github.com/ebsEnergieAG/SmartMeterSchnittstelle/assets/7451747/3113dc18-6f56-48ea-bbaf-dde8307fe5d9)

![image](https://github.com/ebsEnergieAG/SmartMeterSchnittstelle/assets/7451747/5fad862a-8b4a-4287-8226-a0d9efe2bb26)
Fertiger Node

![image](https://github.com/ebsEnergieAG/SmartMeterSchnittstelle/assets/7451747/3b7e308d-ce4e-431d-989d-e9fb45b8d10a)

## Grafana einstellen 
Um Grafana einzurichten einfach die IP des Servers gefolgt von :3000 eingeben im Browser 
z.B http://192.168.1.159:3000

![image](https://github.com/ebsEnergieAG/SmartMeterSchnittstelle/assets/7451747/6fef7a26-c30e-4d31-b203-b48280d7d940)
![image](https://github.com/ebsEnergieAG/SmartMeterSchnittstelle/assets/7451747/7bbca90b-c816-4497-b666-7d73592f00ff)
![image](https://github.com/ebsEnergieAG/SmartMeterSchnittstelle/assets/7451747/349f421c-be48-4099-8830-d9e284c0f2ae)

![image](https://github.com/ebsEnergieAG/SmartMeterSchnittstelle/assets/7451747/14d5425a-578e-4b37-909d-05de433bfe69)

![image](https://github.com/ebsEnergieAG/SmartMeterSchnittstelle/assets/7451747/0c1390b4-db52-49ff-b151-ee35fc8eb142)
![image](https://github.com/ebsEnergieAG/SmartMeterSchnittstelle/assets/7451747/af5607f9-a8ae-4a06-9d78-cb15bcde1c5a)
![image](https://github.com/ebsEnergieAG/SmartMeterSchnittstelle/assets/7451747/490ae787-73f4-42f1-a128-4d3e1fac761a)




