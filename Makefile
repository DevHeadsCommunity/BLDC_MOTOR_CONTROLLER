TARGET = main

DEBUG = 1
OPT = -Os

BUILD_DIR = build

C_SOURCES = \
src/main.c \
src/gpio_driver.c \
src/usart_driver.c \
src/utils.c \
src/system_stm32f1xx.c \
src/spi_driver.c \
src/max6675_driver.c \
src/timer4.c \
src/uart.c \
src/adc.c \
src/eeprom.c \
src/custom_init.c \
src/gsm.c \
src/i2c.c \
src/buck.c \
src/timer2.c\
src/timer3.c\
 FreeRTOS/list.c \
 FreeRTOS/queue.c \
 FreeRTOS/tasks.c \
 FreeRTOS/portable/MemMang/heap_4.c \
 FreeRTOS/portable/GCC/ARM_CM3/port.c

ASM_SOURCES = \
startup_stm32f103xb.s

PREFIX = arm-none-eabi-

CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size

HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

CPU = -mcpu=cortex-m3

MCU = $(CPU) -mthumb

C_DEFS = \
-DSTM32F103xB

C_INCLUDES = \
-Iinc \
-ICMSIS_STM32F1 \
-IFreeRTOS/include \
-IFreeRTOS/portable/GCC/ARM_CM3

ASFLAGS = $(MCU) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif

LDSCRIPT = STM32F103XB_FLASH.ld

LIBS = -lc -lm -lnosys
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin

OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@

clean:
	-rm -fR $(BUILD_DIR)

-include $(wildcard $(BUILD_DIR)/*.d)
