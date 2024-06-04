# LoRa-ESP32
 - The documentation for LoRa is hard to find for ESP32.
 - Went down many rabbit holes mixing and mashing things together.
 - I have come up with this pre-alpha example of how to proper send LoRa messages VIA UART.
 - This obviously requires a UART capable chipset, most guides I have found are for i2c or SPI.
 - UART modules work like a modem using [AT] commands, AFAIK the serial ignores any messages not starting with [AT].
 - As such it is okay still to spam serial with debug info.
 - Downside is you cannot upload program with USB unless first disconnect the serial jumpers.
 - Much love for this guy! Subscribe his channel: https://www.youtube.com/watch?v=LiWlPERp1ec

