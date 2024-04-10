#ARMGCC = /c/ST/STM32CubeIDE_1.8.0/STM32CubeIDE/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.9-2020-q2-update.win32_2.0.0.202105311346/tools/bin/arm-none-eabi-gcc.exe
ARMGCC = arm-none-eabi-gcc

all: app

app: startup_stm32f10x_ld.s main.c slots.c 
	$(ARMGCC) -O1 -g $^ --specs=nosys.specs -T stm32_flash.ld -o $@

clean:
	$(RM) app

