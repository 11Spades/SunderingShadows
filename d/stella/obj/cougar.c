
#include <std.h>
#include <daemons.h>
#include "/d/stella/short.h"

inherit OBJECT;

void init(){
	::init();
	}
	
void create(){
	::create();
	
	set_name("A Statue");
	set_id(({"statue","cougar statue","cougar"}));
        set_short("A Cougar Statue");
        set_long("You are looking at a fantastic statue of a cougar crouched ready to pounce.  "
		 "It is 10 feet tall and is carved in astounding detail. ");
	set_weight(100000);
	set_value(100000);
	}

