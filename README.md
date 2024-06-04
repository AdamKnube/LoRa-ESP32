# LoRa-ESP32
 - The documentation for LoRa is hard to find for ESP32.
 - Went down many rabbit holes mixing and mashing things together.
 - I have come up with this pre-alpha example of how to proper send LoRa messages VIA UART.
 - This obviously requires a UART capable chipset, most guides I have found are for i2c or SPI.
 - UART modules work like a modem using [AT] commands.
 - AFAIK the serial ignores any messages not starting with [AT], as such it is okay still to spam serial with debug info.
 - Downside is you cannot upload program with USB unless first disconnect the serial jumpers.
 - More information to follow, I'm still learning. Will include required libraries with the info. 
 - So far testing has been able to deliver 13 bytes every 4-5 seconds as limited by the DHT sensor.
 - The [client] example uses a DHT22 sensor and sends temperature/humidity to a [server].
 - The server just spams what its sees for now, but future will use MQTT and WiFi to publish LoRa readings.
 - Much love for this guy! Subscribe his channel: https://www.youtube.com/watch?v=LiWlPERp1ec

