
# How to run emulator  

Install [openocd](https://github.com/openocd-org/openocd) on your system and add to path.  

From ./OpenOCD, run the "runOCD_mdr" script, which will launch the tcl server on the local host:6666.  

Then run the "TCP_task_trace"- LV tool. After successfully connecting to localhost:6666, it will configure OpenOCD, some MCU components and start another server on localhost:6665. After that, the tool needed to process keyboard events. 

Then run the "main" LV tool. After successfully connecting to localhost:6665, it will poll the input trace packet and display this data on the screen.
