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
docker exec <ID> /bin/bash

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

Auf dem Tasmota kann unter Einstellungen der MQtt Server eingegeben. 
Hier einfach die IP des Servers eingeben. 

Um die Daten zu Überprofen würde ich den MQTT explorer empfehlen, dort wird auch das Topic(Adresse) der Daten angezeigt. 

## Node Red 
Um NodeRed einzurichten einfach die IP des Servers gefolgt von :1880 eingeben im Browser 
z.B http://192.168.1.55:1880

Hier müssen die Nodes eingerichtet werden. 
als erstes den MQTT Eingang hinein ziehen. 
Danach eine Funktion einfügen 

// Weitere Punkte folgen 

## Grafana einstellen 

