#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <switch.h>
#include "unistd.h"

int main(int argc, char **argv)
{
    // Console init
    consoleInit(NULL);
    spsmInitialize();
    
    // HID init
    padConfigureInput(8, HidNpadStyleSet_NpadStandard);
    PadState pad;
    padInitializeAny(&pad);
    
    // Std output
    printf("\n  Safe Reboot / Shutdown                        kempa aka dezem gzk_47\n\n\n\n");
    printf("- Press [L] to Shutdown\n\n");
    printf("- Press [R] to Reboot\n\n\n\n");
    printf("- Press [B] to Exit\n\n");
    consoleUpdate(NULL);
	
	// Check shutdown or reboot
	bool reboot = true;
	bool abort = false;
    
    // Main loop
    while(appletMainLoop())
    {
        padUpdate(&pad);
        u64 kDown = padGetButtonsDown(&pad);

        if (kDown & HidNpadButton_L) {
            reboot = false;
            break; 
        }
        if (kDown & HidNpadButton_R) {
            reboot = true;
            break; 
        }
        if (kDown & HidNpadButton_B) {
            abort = true;
            break; 
        }
    }
    
    // Console deinit
    consoleExit(NULL);
    
    // Check if User has aborted shutdown or reboot
	if (abort == false) {
        //sleep
        usleep(3000000);
        // AMS safe shutdown or reboot
        spsmShutdown(reboot);
    } else {
        spsmExit();
    }
}
