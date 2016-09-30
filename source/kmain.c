    #include "fb.h"
    #include "sp.h"
    #include "io.h"
    #include "gtd.h"
    #include "idt.h"
    #include "interrupt.h"
    #include "kb.h"
    #include "multiboot.h"


	void kmain(/* additional arguments */unsigned int ebx) {

        gdt_install();
        idt_install();

        fb_init();
        serial_configure(COM1);

        multiboot_info_t *mbinfo = (multiboot_info_t *) ebx;
        unsigned int address_of_module = mbinfo->mods_addr;

        clear_screen();
        fb_write_text("\n                                    `mMMs`                            \n                                     -dMMm:                           \n                                      `+NMMh:                         \n  `+smmh+`        :hmh-  -ohmmd/        `hMMMd/       .oymmh/         \n     -dMMm-        :MMh:ys:..sMN.     :ymhoomMMm/        :NMMh`       \n     `sMMMN:       /MMN+`    +No`   -dNo`    :dMMy`      .dMMMm.      \n   `+Nh:yMMM/      /MMs   -oho.    :NM/       `sMM/    `sNs:dMMN-     \n  :dm:  `yMMM:     /MMs`:mMm-      yMM/        /Mm.   /Nd-  `dMMm.    \n`yMN-   .oNMMM/    +MMy  :dMMh:`   :NMMy:.`.:odNs`  -hMm`  `-yMMMm-   \n-hNMNddds:`oNMMy: `hMMh    -yNMmo-  .odNMMMNds:`    :dMMNddho-`yMMNs- \n  ``..`     `....  `..`      `.`       ``.``          `...`     ....`\n");
        fb_write_text("\nWelcome to ARDA!\n");
        serial_write(COM1, "It's working... it's working!");

        
        fb_write_text("\nTesting CPU interrupt handlers:\n");
        __asm__ __volatile__ ("int $0x3");
        __asm__ __volatile__ ("int $0x4");
        

        keyboard_install();

		return;
	}