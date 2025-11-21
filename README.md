# Vehicle-Diagnostics-System
An embedded OBD system for an electric vehicle using the PIC16F877A. It monitors temperature, battery voltage, and speed using ADC and CCP modules, then sends real-time diagnostic data via USART. Developed with MPLAB X (XC8) and simulated in Proteus.

## 📌 Overview  
This project consists of designing and implementing a basic **Onboard Diagnostics (OBD)** system for an electric vehicle (EV).  
The system monitors essential sensors, detects abnormal conditions, and transmits diagnostic data to a PC through serial communication (USART).

The project was developed using:
- **PIC16F877A microcontroller**
- **MPLAB X IDE (XC8 compiler)**
- **Proteus 8 simulation**
- Custom C firmware (ADC reading, capture module, USART communication)

---

## 🎯 Objectives  
- Develop a simplified diagnostics unit for EVs.  
- Read and process data from multiple sensors:
  - Temperature (LM35)
  - Battery/voltage level (potentiometer simulation)
  - Speed sensor (signal generator to CCP1 module)
- Generate and send readable diagnostic values through serial communication.
- Simulate and validate the embedded system in Proteus.

---

## ⚙️ Features  
### ✔ Sensor Monitoring  
- **Temperature Sensor (LM35)**  
  - Read from AN4  
  - Convert ADC value to temperature  
  - Send temperature to the serial terminal  

- **Battery Voltage Sensor**  
  - Read from AN0  
  - Convert value to volts and percentage  

- **Speed Measurement**  
  - CCP1 capture module detects rising edges  
  - Timer1 measures the period between pulses  
  - Frequency and speed are computed based on a wheel with **48 teeth**  
  - Linear speed computed assuming **wheel radius = 30 cm**  

### ✔ Serial Communication  
- Real-time values displayed through USART (9600 baud).  
- Human-readable formatting for voltage, temperature, and speed.

### ✔ Fault Detection *(optional future extension)*  
- Threshold-based detection system for overheating, low voltage, etc.  

---

## 🧩 System Architecture  
### **Hardware (Simulated in Proteus)**  
- PIC16F877A  
- LM35 temperature sensor  
- Potentiometer (battery simulation)  
- Signal generator (speed sensor)  
- Virtual terminal (USART communication)  

### **Software Components**  
- ADC configuration and reading  
- Timer1 configuration  
- CCP1 capture interrupt  
- USART driver  
- Speed calculation algorithm  

---

## 📂 Repository Structure  
/Vehicle-Diagnostics-System
/Code
   config.h
   USART_lib.h
   LCD_LIB_4bits.h
   ADC.c
   Main_Code.c
   USART_lib.c
   LCD_LIB_4bits.c

Proteus_image.PNG

/Documentation
   MINI PROJECT REPORT.pdf
README.md


---

## 🖥️ How It Works  
### 1️⃣ Temperature Measurement  
The LM35 output is sampled using the PIC ADC module:  
Temperature (°C) = (ADC_value × ConversionFactor) – Offset

csharp
Copy code

### 2️⃣ Voltage Measurement  
Battery voltage is scaled to a 0–5V input using a potentiometer.

### 3️⃣ Speed Measurement  
- CCP1 captures rising edges  
- Timer1 measures period  
- Frequency is computed:  
frequency = 1 / period

csharp
Copy code
- Speed is derived from wheel parameters.

### 4️⃣ Data Output (USART)  
Values are displayed as:  
ADC1=xxxx
Temp=xx °C
ADC2=xxxx
Voltage=x.xx V
Speed=xx km/h

yaml
Copy code

---

## 🧪 Simulation Results  
- Successful acquisition of all three parameters:  
  ✔ Temperature  
  ✔ Battery voltage  
  ✔ Wheel speed  
- Real-time output visible on virtual terminal.  
- Stable interrupt-based capture for speed measurement.

---

## 📘 Conclusion  
This mini-project provides a functional EV diagnostic prototype capable of:  
- Monitoring temperature, voltage, and speed  
- Processing sensor data  
- Communicating results in real time  

The project improved skills in **embedded C**, **ADC/Capture modules**, **Proteus simulation**, and **PIC microcontroller programming**.

---

## 👤 Authors  
- **Mohamed DAGMOUMI ESSAFI**  
- **Zaid EL FILALI**

Supervised by **Dr. Tajeddin EL HAMADI**  
Mecatronics Master • 2024-2025  
