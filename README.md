# speedfanreader
 
Written in C++, reads the shared memory area of Speedfan 4.5.2 and extracts the temperatures dynamically, original code by Christopher Vagnetoft. 
Modified by Dean Beedell and Harry Whitfield. We are not claiming this code as our own, the reason it is being posted here is that we cannot find it anywhere on the web anymore. 

SpeedFanReader only reads the first 8 sensors currently, it is quite capable of reading up to 32 with only small changes.

You will find two versions of the code here. One is Vagnetoft's, the other is CapnBry's code, untried and untested. 

Built using: 

Embaracadero Dev C++ 6.3

I use this program in conjunction with Speedfan 4.52 and my Steampunk CPU/GPU Thermometers widget that you can find here:
https://github.com/yereverluvinunclebert/Steampunk-CPU_GPU-Speedfan-Thermometer

A picture of same below:

![steampunk_cpu_gpu_thermometer_widget_for_speedfan_by_yereverluvinuncleber_d4lri07-375w-2x](https://github.com/yereverluvinunclebert/speedfan-shared-memory-reader-C--/assets/2788342/c89110ec-0f26-4d46-b1d8-0b1b6e051366)

Usage:

The shared memory area as created by Speedfan, does not display the names of the sensors so you have to derive this yourself. In order to do this you need to enable Speedfan logging. In Speedfan, select configuration - log and click the check box to enable logging. This creates a logging file containing the speedfan sensor names as identified by Speedfan:

speedfansens.cfg

Use this file to correlate the temperature data as received from Speedfan.

"SpeedFan Information Tool 1.0
Retrieves temperature information from SpeedFan and outputs it to the console.

Note: This is probably the only sample available on the internet on how to
access SpeedFans shared memory using C++. Disturbing, isn't it?"

PS. I just found another here: https://forum.kodi.tv/printthread.php?tid=52446

