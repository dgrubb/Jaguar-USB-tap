MEMORY
{
  ram (rwx) :   ORIGIN = 0x20000000, LENGTH = 6K
  rom (rx) :    ORIGIN = 0x08000000, LENGTH = 32K
}

ram_top = ORIGIN(ram) + LENGTH(ram);
ENTRY(boot_entry)

SECTIONS
{
    .text : {
        KEEP(*(.irq-vectors))
        *(.text*)
        *(.rodata*)
        _etext = .;
    } >rom

    .data :
    {
        _data = .;
        *(.data*)
        _edata = .;
    } >ram AT > rom

    .bss : {
        _bss = .;
        *(.bss)
        _ebss = .;
    } >ram

    end = .;

    stack_entry = ram_top;
}
