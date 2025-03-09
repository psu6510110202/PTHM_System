import paho.mqtt.client as mqtt
import json
import time
import math
import random  # Import random module for noise generation

# MQTT Broker Configuration
BROKER = "localhost"  # Change this to your MQTT broker IP
TOPIC = "ecg/patient/000005"
client = mqtt.Client()
client.connect(BROKER, 1883, 60)

# Function to generate a realistic ECG waveform
def generate_ecg_waveform(t):
    heart_rate = 1.2  # Simulated heart rate factor

    # P-wave: small, smooth wave before the QRS complex
    p_wave = math.sin(t * heart_rate * 0.3) * 1.5

    # QRS complex: sharp, large spike (Q wave down, R wave up, S wave down)
    qrs_complex = (
        math.sin(t * heart_rate * 2) * 15 * math.exp(-((t % 50 - 25) ** 2) / 50)
    )

    # T-wave: larger smooth wave after the QRS complex
    t_wave = math.sin(t * heart_rate * 0.15) * 4

    # Baseline wander and random noise
    baseline_wander = math.sin(t * heart_rate * 0.02) * 0.5  # Slow baseline drift
    noise = random.uniform(-0.25, 0.25)  # Small random noise

    # Combine all components
    return p_wave + qrs_complex + t_wave + baseline_wander + noise


# MQTT Publisher Loop
t = 0  # Time step
while True:
    ecg_value = generate_ecg_waveform(t)
    payload = json.dumps({"value": round(ecg_value, 3)})  # Round for better readability
    client.publish(TOPIC, payload)
    print(f"Published: {payload}")
    
    t += 1
    time.sleep(0.1) 
