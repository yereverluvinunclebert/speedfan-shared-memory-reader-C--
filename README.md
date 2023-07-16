# speedfanreader
 
Written in C++, reads the shared memory area of Speedfan 4.5.2 and extracts the temperatures dynamically, original code by Christopher Vagnetoft. 
modified by Dean Beedell and Harry Whitfield.

I use this program in conjunction with Speedfan 4.5.2 and my Steampunk CPU/GPU Thermometers widget that you can find here:
https://github.com/yereverluvinunclebert/Steampunk-CPU_GPU-Speedfan-Thermometer

A picture of same below:

![steampunk_cpu_gpu_thermometer_widget_for_speedfan_by_yereverluvinuncleber_d4lri07-375w-2x](https://github.com/yereverluvinunclebert/speedfan-shared-memory-reader-C--/assets/2788342/c89110ec-0f26-4d46-b1d8-0b1b6e051366)

/*
 * SpeedFan Information Tool 1.0
 *
 * Retrieves temperature information from SpeedFan and outputs it to the console.
 *
 * (c) 2008, Christopher Vagnetoft
 * Free to use and reuse under the GNU Public License (GPL) v2.
 *
 * Note: This is probably the only sample available on the internet on how to
 * access SpeedFans shared memory using C++. Disturbing, isn't it? 
 */

	#include <stdio.h>
	#include <windows.h>

	// pragma pack is included here because the struct is a pascal Packed Record,
	// meaning that fields aren't aligned on a 4-byte boundary. 4 bytes fit 2
	// 2-byte records.
	#pragma pack(1)

	// This is the struct we're using to access the shared memory.
	struct SFMemory {
	  WORD version;
	  WORD flags;
	  int MemSize;
	  int handle;
	  WORD NumTemps;
	  WORD NumFans;
	  WORD NumVolts;
	  signed int temps[32];
	  signed int fans[32];
	  signed int volts[32];
	};

	// Name of filename and memory map name to open.
	const char* filename = "SFSharedMemory_ALM";
	const char* mapname  = "SFSharedMemory_ALM";
	UINT nSize = sizeof(SFMemory);

	int main() {

	  // Store our recalculated values here
	  int temp[32];

	  // Open file
	  HANDLE file = (HANDLE)CreateFile(filename,GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	  // Create file mapping
	  HANDLE filemap = (HANDLE)CreateFileMapping(file,NULL,PAGE_READWRITE,0,nSize,mapname);
	  // Get pointer
	  SFMemory* sfmemory = (SFMemory*)MapViewOfFile(filemap, FILE_MAP_READ, 0, 0, nSize);

	  if (sfmemory) {
	    // Grab the first n values.
	        for (int n = 0; n < 32; n++) {
	            temp[n] = (int)(sfmemory->temps[n]/100);
	        }
	    printf("Speedfan Quick Reader by Christopher Vagnetoft, modified by Dean Beedell and Harry Whitfield");
	        printf("\n");
	        if (temp[0] == 0 && temp[1] == 0 &&  temp[2] == 0 &&  temp[3] == 0 &&  temp[4] == 0 &&  temp[5] == 0 &&  temp[6] == 0 &&  temp[7] == 0 ) {
	           printf("Speedfan not yet running ");  
	           printf("\n"); 
	           printf("no temperatures");  
	           printf("\n"); 
	                 
	        }
	        else {
	           printf("%i ", sfmemory->NumTemps);           
	           printf("\n");
	           //printf("GPU: %ic  HD0: %ic  HD1:  %ic  Core1: %ic  Core2: %ic  Ambient:  %ic ",temp[0],temp[1],temp[2],temp[3],temp[4],temp[5],temp[6],temp[7]);

	           printf(" %ic%*ic%*ic%*ic%*ic%*ic%*ic%*ic%  ",temp[0],5,temp[1],5,temp[2],5,temp[3],5,temp[4],5,temp[5],5,temp[6],5,temp[7]);
	       printf("\n");
	        }
	  } else {
	    printf("Speedfan Quick Reader by Dean Beedell and Harry Whitfield");
	        printf("\n");
	    printf("Failed to open shared memory.");
	  }

	  // Close the handles we opened.
	  CloseHandle(filemap);
	  CloseHandle(file);

	}
