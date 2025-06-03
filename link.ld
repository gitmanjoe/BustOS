/* filepath: c:\Users\User\Documents\GitHub\BustOS\link.ld */
ENTRY(_start)
SECTIONS
{
  . = 0x7e00;
  .text : { *(.text) }
  .data : { *(.data) }
  .bss  : { *(.bss) }
}