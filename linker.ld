ENTRY(_start)

MEMORY
{
  FLASH (rx)      : ORIGIN = 0x08000000, LENGTH = 0x10000 /*32KiB*/
  RAM (xrw)       : ORIGIN = 0x20000000, LENGTH = 0x02000 /*8KiB*/
}

SECTIONS
{
  .isr_vectors : { *(.isr_vectors) } > FLASH

  .text : { KEEP(*(.text)) } > FLASH
}
