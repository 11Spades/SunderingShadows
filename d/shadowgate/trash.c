/*
  trash.c
  
  Void moves sticky objects here to crush them once and for all.
  
  -- Tlaloc --
*/

#include <std.h>

inherit CONTAINER;

void create()
{
    ::create();
    set_short("trash incinerator");
}
    
  
  