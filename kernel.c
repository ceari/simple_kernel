#include "standard.h"
#include "textmode.h"

void kmain( void* mbd, unsigned int magic )
{
    textmode_clear();
    textmode_updatecursor();
    if ( magic != 0x2BADB002 )
    {
        textmode_puts("Wrong magic number, halting");
        return;
    }

    /* You could either use multiboot.h */
    /* (http://www.gnu.org/software/grub/manual/multiboot/multiboot.html#multiboot_002eh) */
    /* or do your offsets yourself. The following is merely an example. */ 
    char * boot_loader_name =(char*) ((long*)mbd)[16];

    textmode_puts("Hello World!\nSimple Kernel started");

}
