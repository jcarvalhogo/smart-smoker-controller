# broker_mqtt_a1 — ESP32 Smoker Controller (Study Project)

This is a **study project** focused on building an embedded control system for a **smoker (defumador)** using an ESP32, MQTT and basic control logic.

The system controls:
- 🔥 **Gas valve** → controls flame intensity (temperature)
- 🌬️ **Air intake servo** → controls airflow (humidity / combustion)
- 🌡️ **Temperature** (DHT22)
- 💧 **Humidity** (DHT22)

All communication and testing are done via **MQTT**.

---

## 📌 Project Concept

This project simulates a **smart smoker controller**:

- Temperature is controlled by **gas flow**
- Humidity and combustion are influenced by **air intake**
- Control decisions are based on sensor readings
- MQTT is used for:
  - manual control
  - telemetry
  - future automation

This is an **educational project**, focused on:
- ESP-IDF
- FreeRTOS
- MQTT
- Embedded architecture
- Control systems concepts

---

## 📁 Project Structure (simplified)

```text
broker_mqtt_a1/
├── components/
│   ├── app/                # Application layer (tasks, mqtt, sensors, actuators)
│   ├── domain/             # Domain logic (servo math, future controller)
│   ├── ports/              # Abstractions / ports
│   └── platform_esp32/     # ESP32-specific drivers
├── main/
├── docker/                 # Docker Compose (MQTT broker + MQTTX)
├── CMakeLists.txt
└── README.md


🧰 Host Requirements

Recommended OS:

Ubuntu 22.04 / 24.04 (x86_64)

Basic packages:

sudo apt update
sudo apt install -y \
  git cmake ninja-build \
  python3 python3-pip python3-venv \
  flex bison gperf \
  ccache libffi-dev libssl-dev \
  dfu-util libusb-1.0-0


## Clone the Project

git clone https://github.com/jcarvalhogo/smart-smoker-controller.git
cd broker_mqtt_a1

If using submodules:

git submodule update --init --recursive


## 2️⃣ Install and Setup ESP-IDF
Recommended method (official ESP-IDF repository)

Choose a location to install ESP-IDF:


mkdir -p ~/esp
cd ~/esp


Clone ESP-IDF (stable release):
git clone -b release/v5.2 --recursive https://github.com/espressif/esp-idf.git
cd esp-idf

Run the installer:
./install.sh esp32


Load ESP-IDF environment (IMPORTANT)

Every time you open a new terminal:

. $HOME/esp/esp-idf/export.sh

(Optional) Automatically load on terminal startup:
echo '. $HOME/esp/esp-idf/export.sh' >> ~/.bashrc

Verify installation:
idf.py --version


## 3️⃣ Configure the ESP32 Target

Inside the project root:

idf.py set-target esp32


(Optional) Configuration menu:
idf.py menuconfig

## 4️⃣ Build, Flash and Monitor
Build

idf.py build



Find serial port
ls -l /dev/ttyUSB* /dev/ttyACM* 2>/dev/null

Flash firmware
idf.py -p /dev/ttyUSB0 flash

Monitor logs
idf.py -p /dev/ttyUSB0 monitor


## 5️⃣ Install Docker and Docker Compose
Install Docker Engine (Ubun

Add Docker repository:

sudo install -m 0755 -d /etc/apt/keyrings
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /etc/apt/keyrings/docker.gpg
sudo chmod a+r /etc/apt/keyrings/docker.gpg

echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.gpg] \
  https://download.docker.com/linux/ubuntu $(. /etc/os-release && echo $VERSION_CODENAME) stable" | \
  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null

Install Docker:
sudo apt update
sudo apt install -y docker-ce docker-ce-cli containerd.io docker-compose-plugin

Enable Docker:
sudo systemctl enable --now docker

Allow Docker without sudo (log out / log in required):
sudo usermod -aG docker $USER


Verify:
docker --version
docker compose version


docker-compose.yml
services:
  emqx:
    image: emqx:5.8.8
    container_name: emqx
    ports:
      - "1883:1883"     # MQTT TCP (ESP32 / clientes MQTT)
      - "8083:8083"     # MQTT over WebSocket
      - "18083:18083"   # Dashboard EMQX
    environment:
      - EMQX_ALLOW_ANONYMOUS=true
    restart: unless-stopped

  mqttx-web:
    image: emqx/mqttx-web:latest
    container_name: mqttx-web
    ports:
      - "8080:80"       # MQTTX Web no navegador
    restart: unless-stopped
    
    
    
    ###############################################################################
# MQTT – MONITORAR (SUB)
###############################################################################

# Tudo do namespace
mosquitto_sub -h 192.168.3.3 -t 'JC_GO/#' -v

# Air intake
mosquitto_sub -h 192.168.3.3 -t 'JC_GO/air/intake' -v

# Gas valve
mosquitto_sub -h 192.168.3.3 -t 'JC_GO/gas/valve' -v

# Temperature
mosquitto_sub -h 192.168.3.3 -t 'JC_GO/temperature' -v

# Humidity
mosquitto_sub -h 192.168.3.3 -t 'JC_GO/humidity' -v


###############################################################################
# MQTT – COMANDOS (PUB)
###############################################################################

# -----------------------
# AIR INTAKE (angle)
# -----------------------

# Fechar (0°)
mosquitto_pub -h 192.168.3.3 -t 'JC_GO/air/intake' -m '{"angle":0}'

# Meio termo (90°)
mosquitto_pub -h 192.168.3.3 -t 'JC_GO/air/intake' -m '{"angle":90}'

# Abrir totalmente (180°)
mosquitto_pub -h 192.168.3.3 -t 'JC_GO/air/intake' -m '{"angle":180}'


# -----------------------
# GAS VALVE (percent)
# -----------------------

# Fechar (0%)
mosquitto_pub -h 192.168.3.3 -t 'JC_GO/gas/valve' -m '{"percent":0}'

# Abrir 30%
mosquitto_pub -h 192.168.3.3 -t 'JC_GO/gas/valve' -m '{"percent":30}'

# Abrir 100%
mosquitto_pub -h 192.168.3.3 -t 'JC_GO/gas/valve' -m '{"percent":100}'


# -----------------------
# GAS VALVE (action)
# -----------------------

# Abrir
mosquitto_pub -h 192.168.3.3 -t 'JC_GO/gas/valve' -m '{"action":"open"}'

# Fechar
mosquitto_pub -h 192.168.3.3 -t 'JC_GO/gas/valve' -m '{"action":"close"}'


###############################################################################
# ESP32 – MONITOR SERIAL
###############################################################################

idf.py -p /dev/ttyUSB0 monitor


