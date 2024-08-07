
# How to run emulator  

Install [openocd](https://github.com/openocd-org/openocd) on your system and add to path.  

From ./openOCD, run the "runOCD_mdr" script, which will launch the tcl server on the localhost:6666.  

Then run the "TCP_task_trace"- LV virtual instrument. After successfully connecting to localhost:6666, it will configure openOCD, some MCU components and start another server on localhost:6665. After that, the virtual instrument needed to process keyboard events. 

Then run the "main" LV virtual instrument. After successfully connecting to localhost:6665, it will poll the input trace packet and display this data on the screen.
