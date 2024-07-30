# Doom on Milandr

This is a fork of this [repository](https://github.com/potat-dev/milandr-doom)

With gui emulation on PC:

![main.vi](./doc/main.vi.gif "main.vi")  

The mcu is connected via st-link to a PC with an OpenOCD server running. LabVIEW virtual instruments provides packet exchange with cortex m debug trace. They process keystrokes on the keyboard (WASD+ENTER) and render data to the display.