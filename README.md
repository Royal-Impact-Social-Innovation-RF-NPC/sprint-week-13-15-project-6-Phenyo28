# Smart-Waste-Bin-Project

This project is a prototype of a Smart Waste Bin, an automated system designed to detect, classify, and manage waste efficiently using sensors, servo motors, and an ESP32 microcontroller. It demonstrates how embedded systems and AI can improve recycling, and promote sustainability.

The Smart Waste Bin uses an ESP32-CAM to capture images of waste items and classify them using a trained Edge Impulse AI model. Based on the classification result, the system automatically opens the corresponding bin lid using servo motors. While LED indicators and an OLED display provide real-time feedback to the user.

This prototype combines automation, artificial intelligence, and hardware integration to create a cleaner, smarter, and more sustainable approach to waste management.

Key Features:
- AI-powered image classification using the ESP32-CAM and Edge Impulse.
- Automatic lid opening and closing via servo motors.
- LED and OLED as indicators for real-time user feedback.
- Compact, modular design built for demonstration and further development.

---
## Repository Contents

| Folder / File | Description |
|---------------|-------------|
| `code/`       | Contains all source code for the ESP32, ESP32-CAM, servo motors, ultrasonic sensor, and LED control. |
| `hardware/`   | Circuit diagrams, breadboard layouts, and component schematics. |
| `CAD/`        | Onshape design files, 3D models, and assembly drawings for the bin mechanism. |
| `images/`     | Project photos, screenshots of the prototype, and wiring setup. |
| `README.md/`       | README, bill of materials, system overview, and test reports. |
| `AI/`         | Edge Impulse models or training datasets used for waste classification with the ESP32-CAM. |

---
## Bill Of Materials
| Component Name                                | Purpose in Project                                                                                                      | Quantity |
| --------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------- | -------- |
| **ESP32 Dev Board**                            | Main microcontroller used to control sensors, servos, and LEDs. It processes input signals and executes programmed actions. | 1        |
| **ESP32-CAM**                                  | Captures images of waste items for classification using the AI model built with Edge Impulse.                           | 1        |
| **Servo Motors**                               | Controls the movement of sorting flaps or lids to direct different types of waste into the correct bins.                | 3        |
| **Resistors**                                  | Protect LEDs and manage current flow in the circuit.                                                                    | 3        |
| **LEDs**                                       | Each LED represents a type of waste (plastic, paper, or electronic) and lights up to show where the item is being sorted. | 3        |
| **Jumper Wires**                               | Connects all components to the breadboard and ESP32.                                                                    | 15+      |
| **Breadboard**                                 | For building and testing the circuit.                                                                                   | 1        |
| **USB Cable**                                  | Provides power to the ESP32 and components during operation or testing.                                                 | 1        |
| **OLED Display**                               | Displays real-time feedback such as waste type and sorting status.                                                      | 1        |
| **Battery Holder**                             | Holds the rechargeable batteries that power the system.                                                                 | 1        |
| **Li-ion Batteries**                           | Provide portable power to the system.                                                                                   | 4        |
| **5V DC-DC Step-Down Regulator (Buck Converter)** | Powers the ESP32 and sensors from the battery pack.                                                                     | 1        |
| **On/Off Rocker Switch**                       | Acts as a power switch for the entire system.                                                                           | 1        |
## Circuit Diagram Overview
The circuit connects the ESP32 to three servo motors, three LEDs (with resistors), and the ESP32-CAM. Power is supplied through a 5V DC-DC buck converter regulated from a Li-ion battery pack.

- OLED - SDA,22 ; SCL, 21; GND, 3.3V
- Servo 1, 2, 3 - GPIO 12, 13, 14
- LEDs (Red, Green, Blue) - GPIO 25, 26, 27
- ESP32-CAM - GND, 5V

---
## AI Model
The Smart Waste Bin uses an Edge Impulse image classification model to identify the type of waste item detected by the ESP32-CAM.
| **Parameter**              | **Description**                                        |
| -------------------------- | ------------------------------------------------------ |
| **Model Type**             | Image Classification                                   |
| **Input Data**             | 46×46 color images captured by the ESP32-CAM           |
| **Output Labels**          | Plastic, Paper, Electronic                             |
| **Framework**              | Edge Impulse (trained and deployed using EON Compiler) |
| **Target Device**          | ESP32-CAM                                              |
| **Communication Protocol** | ESP-NOW (for transmitting results to ESP32 Dev Board)  |

### Model Performance Summary
| **Metric**                     | **Value** |
| ------------------------------ | --------- |
| **Validation Accuracy**        | 71.4%     |
| **Test Accuracy**              | 65.63%    |
| **Precision (non-background)** | 0.74      |
| **Recall (non-background)**    | 0.97      |
| **F1 Score (non-background)**  | 0.84      |

### Training Settings
- Training Cycles: 100
- Learning Rate: 0.005
- Training Processor: CPU
- Data Augmentation: Enabled
- Model Version: Quantized (int8)

#### Dataset
<img width="1920" height="978" alt="image" src="https://github.com/user-attachments/assets/5ca542f0-d57e-44d1-a966-f06b6dcbb41b" />

#### Raw data
<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/47b937dc-79a5-4591-907f-8b6fa92d80f6" />

#### Image data
<img width="1920" height="972" alt="image" src="https://github.com/user-attachments/assets/272fca0c-a128-4450-b82d-a6a00b5accca" />

#### Model Training Results
<img width="1034" height="479" alt="image" src="https://github.com/user-attachments/assets/a07218c3-e160-49ce-9c9f-788f4a8a60bc" />

#### Model Testing Results
<img width="1034" height="522" alt="image" src="https://github.com/user-attachments/assets/0c60e545-a707-432b-ac3a-cc1fe0e53c1b" />


---
## Software Workflow
The Smart Waste Bin operates through seamless communication between two ESP32 boards: the ESP32-CAM and the ESP32 Dev Board, using the ESP-NOW wireless protocol for efficient data exchange.

Libraries Used: 
-	esp_now
-	WiFi
-	ESP32Servo
-	Wire
-	Adafruit_GFX
-	Adafruit_SSD1306

### System Interaction Overview
- ESP32-CAM captures images of waste items and performs AI inference using a trained Edge Impulse model to identify the waste type.
- The classification result (`plastic`, `paper`, or `electronic`) is transmitted wirelessly to the ESP32 Dev Board using the ESP-NOW protocol.
- The ESP32 Dev Board receives this data and triggers the appropriate actions:
  - LEDs light up to indicate the detected waste category.
  - Servo motors open the corresponding bin lid automatically.
- Both boards are powered through a shared regulated 5V DC power supply, enabling fully synchronized, cable-free communication.

This workflow eliminates the need for serial wiring between microcontrollers, improving flexibility and scalability while maintaining fast, low-latency communication between devices.

---
## Perfomance Flow of the project

**1. Power On**
- The ESP32-CAM and ESP32 controller initialize.
- All LEDs and servo motors are set to their default (off/closed) state.
- •	Switch on using a Rocker Switch
  
**2. Image Capture**
- When an item is placed near the bin’s opening, the ESP32-CAM captures an image of the waste.

**3. Waste Detection**
- The captured image is processed by the trained Edge Impulse AI model.
- The model identifies the type of waste (plastic, paper, or electronic).

**4. Signal Transmission**
- The ESP32-CAM sends a signal to the main ESP32 board indicating which waste type was detected.

**5. LED Indication**
- The corresponding LED (red, blue, or yellow) turns on to show which bin category is being accessed.

**6. Servo Door Activation**
- The servo motor linked to that specific category’s door rotates to open the bin.
- A short delay allows the user to drop the waste in.

**7. Door Closure**
- After the delay, the servo motor returns to its original position, closing the bin door automatically.

**8. System Reset**
- The LED turns off and the system resets, ready for the next item.

**9. Continuous Operation**
- The process repeats for every new waste item detected by the ESP32-CAM.

## Prototype Images & Videos

### CAD
<img width="1034" height="503" alt="image" src="https://github.com/user-attachments/assets/17804e82-f186-4403-b5bf-d332d5141f75" />

### Circuit 
<img width="915" height="545" alt="image" src="https://github.com/user-attachments/assets/8f6b35fc-faaa-41cc-a3e6-5f7314a48d26" />

### Prorotype
<img width="1034" height="775" alt="image" src="https://github.com/user-attachments/assets/d8011859-db43-46ae-b492-6a9316b9548e" />
