import math
import serial
import time

# Fungsi untuk menghitung azimuth sesuai orientasi yang diberikan
def calculate_azimuth(drone_lat, drone_lon, antenna_lat, antenna_lon):
    drone_lat = math.radians(drone_lat)
    drone_lon = math.radians(drone_lon)
    antenna_lat = math.radians(antenna_lat)
    antenna_lon = math.radians(antenna_lon)
    
    delta_lon = drone_lon - antenna_lon
    x = math.sin(delta_lon) * math.cos(drone_lat)
    y = math.cos(antenna_lat) * math.sin(drone_lat) - (math.sin(antenna_lat) * math.cos(drone_lat) * math.cos(delta_lon))
    
    azimuth = math.atan2(x, y)
    azimuth = math.degrees(azimuth)
    azimuth = (azimuth + 360) % 360  # Menjaga agar azimuth tetap dalam rentang 0-360 derajat
    
    return azimuth

# Data GPS
drone_lat = -5.330584655499501
drone_lon = 105.32084200326408
antenna_lat = -5.330439409846701
antenna_lon = 105.32083424043755


# Hitung azimuth
azimuth = calculate_azimuth(drone_lat, drone_lon, antenna_lat, antenna_lon)
print(f"Azimuth: {azimuth} derajat")

# Komunikasi dengan Arduino
arduino = serial.Serial('COM3', 9600, timeout=1)
time.sleep(2)

# Mengirim data sudut ke Arduino
arduino.write(str(azimuth).encode())
arduino.close()
