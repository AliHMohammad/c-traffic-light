# make: Compile to ./build
# make upload: Upload .hex to arduino
# make clean: Cleans ./build

MCU = atmega328p
F_CPU = 16000000UL
BAUD = 115200
PORT = COM3 # Change this to your Arduino's COM port

CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os
OBJCOPY = avr-objcopy

TARGET = main
BUILD_DIR = build

# Automatically create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir $(BUILD_DIR)

all: $(BUILD_DIR) $(BUILD_DIR)/$(TARGET).hex

# Compile to the build directory
$(BUILD_DIR)/%.o: %.c
	avr-gcc $(CFLAGS) -c $< -o $@

# Link to the build directory
$(BUILD_DIR)/$(TARGET).elf: $(BUILD_DIR)/$(TARGET).o
	avr-gcc $(CFLAGS) $< -o $@

# Create the HEX file in the build directory
$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

# Upload to Arduino
upload: $(BUILD_DIR)/$(TARGET).hex
	avrdude -c arduino -p $(MCU) -P $(PORT) -b $(BAUD) -D -U flash:w:$(BUILD_DIR)/$(TARGET).hex:i

# Clean the build directory
clean:
	del /Q $(BUILD_DIR)\*
