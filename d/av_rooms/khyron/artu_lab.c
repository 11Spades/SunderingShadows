// File created with /daemon/persistent_room_d.c
#include <std.h>

inherit "/cmds/avatar/avatar_room.c";

void create()
{
    ::create();
    set_name("artu_lab");
    set_property("indoors",1);
    set_property("light",5);
    set_property("no teleport",1);
    set_terrain("stone building");
    set_travel("slick floor");
    set_climate("temperate");

    set_short("%^C195%^A %^C201%^c%^C208%^h%^C046%^a%^C057%^o%^C196%^t%^C226%^i%^C021%^c%^CRST%^ %^C159%^l%^C195%^ab%^CRST%^");

    set_long("%^C195%^After recovering from the initial %^C036%^c%^C042%^h%^C047%^e%^C046%^m%^C042%^ic%^C036%^al s%^C042%^t%^C040%^en%^C042%^c%^C036%^h%^C195%^, you find that this is only a lab in the broadest sens"
	"e of the word. Its got all of the %^C214%^e%^C220%^qu%^C226%^ip%^C214%^ment%^C195%^ one would expect of an actual l%^C123%^a%^C195%^borat%^C159%^o%^C195%^ry, but it's strewn across what looks to be a "
	"%^C094%^k%^C136%^i%^C094%^tch%^C136%^e%^C094%^n%^C195%^, a %^C094%^d%^C136%^i%^C094%^n%^C136%^i%^C094%^ng r%^C136%^o%^C094%^om%^C195%^, and a %^C136%^l%^C178%^ibrar%^C136%^y%^C195%^. In fact, the smal"
	"l remains of %^C246%^b%^C251%^i%^C246%^ts of w%^C251%^a%^C246%^ll%^C195%^ and the three %^C094%^d%^C136%^i%^C178%^s%^C094%^c%^C136%^r%^C178%^e%^C094%^e%^C136%^t%^C195%^ %^C255%^ty%^C247%^p%^C242%^e%^C"
	"255%^s%^C195%^ of %^C088%^fl%^C160%^o%^C088%^or%^C196%^i%^C088%^ng%^C195%^ indicate that they were once all separate.%^CRST%^"
	);

    set_smell("default","
%^C030%^You are immediately hit by a wall of %^C095%^dry,%^C036%^ %^C093%^u%^C129%^n%^C165%^n%^C201%^a%^C165%^t%^C129%^u%^C093%^ral,%^C036%^ o%^C041%^i%^C047%^l%^C036%^-a%^C042%^d%^C047%^j%^C036%^a%^C041%^c%^C047%^e%^C036%^n%^C041%^t%^C036%^ %^C047%^s%^C036%^m%^C041%^e%^C047%^l%^C036%^l%^C041%^s%^C036%^.%^CRST%^");
    set_listen("default","%^C094%^Your ears are b%^C172%^e%^C214%^s%^C209%^i%^C202%^e%^C172%^g%^C094%^ed by a %^C129%^c%^C165%^a%^C129%^c%^C165%^a%^C153%^p%^C147%^h%^C141%^o%^C135%^n%^C129%^y%^C094%^ of a%^C100%^n%^C106%^i%^C100%^ma%^C094%^list%^C100%^i%^C106%^c%^C094%^ ch%^C106%^i%^C094%^tt%^C106%^e%^C094%^r%^C106%^i%^C094%^ng, %^C195%^b%^C159%^e%^C195%^ak%^C159%^e%^C123%^r%^C195%^s b%^C159%^l%^C087%^u%^C123%^b%^C159%^b%^C195%^in%^C159%^g%^C195%^,%^C094%^ and %^C214%^t%^C215%^o%^C221%^o%^C220%^l%^C221%^s%^C214%^ t%^C215%^i%^C221%^c%^C214%^k%^C215%^i%^C221%^n%^C214%^g%^C094%^ n' clicking.%^CRST%^");

    
set_items(([ 
	"flooring" : "The flooring of the room is divided evenly into three different styles: one third is just marble, another is patterned hardwood, and the other is soft red carpet.",
	"beakers" : "Scattered across the laboratory are several beakers containing various different quantities of liquid. Notably, not every beaker is made of glass; several appear to be fashioned from large chunks of precious stone, others from exotic looking woods. Whatever solutions they contain are quite loud, filling the room with bubbling and frothing sounds.",
	({ "bits of wall", "wall" }) : "Bordering the distinct differences in flooring are the small remains on what you'd guess to be a wall. The don't really rise high enough to be noticable unless you're looking for them, but still pose a danger to exposed toes.",
	({ "instruments", "tools" }) : "Accenting the beakers and the enclosures are several strange instruments. Most of them are artful compositions of mithril and arandur and the like, occasionally dotted with glowing gems. Rarely, you spot tools made of more common materials, such as brass -- those don't seem to bear jewels, most of the time. The one commonality between all of these intruments, however, is that their workings and purposes are completely undecipherable.",
	({ "cages", "enclosures" }) : "The northeastern corner of the room is occupied by several enclosures which contain, for the most part, living and chittering animals. Looking over some of the specimens makes it clear that these are no ordinary creatures, though they look as though they could be related to critters one might find in a forest. The colors of their fur are often unnatural, their sizes off by worrying margins...",
	]));

    set_exits(([ 
		"out" : "/d/shadow/city/room/shadway2",
	]));

}