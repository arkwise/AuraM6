////////////////////////////////////////////////////////////////////////////////
//
//  Terminal
//
//  Copyright (c) Aura GUI m6 Terminal. System Tools v2
//
////////////////////////////////////////////////////////////////////////////////

#include <dpmi.h>
#include <go32.h>
#include <dos.h>     // Required for union REGS and int86()
#include "command.h"  // Including the header so the Printf function is recognized

/*updates

002 basic dpmi information
003 added more calls to functions in dpmi. this is for additional information


*/


void display_memory_info() {
    _go32_dpmi_meminfo meminfo;

    if (_go32_dpmi_get_free_memory_information(&meminfo)) {
        Printf(&Me, "Failed to retrieve memory information.\n");
        return;
    }

    Printf(&Me, "=========================================\n");
    Printf(&Me, "=  meminfo 0.0.3 doscore 2007-2023.     =\n");
    Printf(&Me, "=========================================\n\n");

    Printf(&Me, "-----------------------------------------\n");
    Printf(&Me, "| Available memory:            %.2f MB |\n", meminfo.available_memory / 1048576.0);
    Printf(&Me, "| Largest available block:     %.2f MB |\n", (meminfo.available_lockable_pages * 4096) / 1048576.0);
    Printf(&Me, "| Total linear space by CPU:   %.2f MB |\n", (meminfo.linear_space * 4096) / 1048576.0);
    Printf(&Me, "| Free linear space:           %.2f MB |\n", (meminfo.free_linear_space * 4096) / 1048576.0);
    Printf(&Me, "-----------------------------------------\n\n");

    Printf(&Me, "-----------------------------------------\n");
    Printf(&Me, "| Available pages:            %7lu   |\n", meminfo.available_pages);
    Printf(&Me, "| Total unlocked pages:       %7lu   |\n", meminfo.unlocked_pages);
    Printf(&Me, "| Available physical pages:   %7lu   |\n", meminfo.available_physical_pages);
    Printf(&Me, "| Total physical pages:       %7lu   |\n", meminfo.total_physical_pages);
    Printf(&Me, "| Max pages in paging file:   %7lu   |\n", meminfo.max_pages_in_paging_file);
    Printf(&Me, "-----------------------------------------\n\n");

    // Uncomment below if you wish to display the reserved values:
    /*
    Printf(&Me, "-----------------------------------------\n");
    Printf(&Me, "| Reserved value 1:           %7lu   |\n", meminfo.reserved[0]);
    Printf(&Me, "| Reserved value 2:           %7lu   |\n", meminfo.reserved[1]);
    Printf(&Me, "| Reserved value 3:           %7lu   |\n", meminfo.reserved[2]);
    Printf(&Me, "-----------------------------------------\n\n");
    */

    // Retrieve TSR data
    union REGS regs;     // Define a union for registers
    int86(0x1C, &regs, &regs);  // Call interrupt 0x1C
    int tsr_data = regs.x.ax;   // TSR returned value in ax

    Printf(&Me, "TSR Data: %d\n", tsr_data);  // Display the value from the TSR

}
