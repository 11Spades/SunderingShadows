#include <std.h>
#include "../antioch.h"
inherit ROOM;

void create()
{
	::create();
   set_terrain(CITY);
   set_travel(PAVED_ROAD);
	set_property("indoors",0);
	set_property("light",2);
	set_short("Apple Street");
	set_long(
	"You are on Apple street.\n"+
	"To the northeast Apple street continues and branches to"+
	" the east. It also looks like there may be a shop further"+
	" up the street on the west hand side. To the south is the"+
	" intersection with Cherry and Pine street. There is also"+
	" a stables there, and the sounds and smells of the horses"+
	" can be easily detected from here."
	);
	set("night long",
	"You are on Apple street.\n"+
	"The street lights to the south and northeast shed light"+
	" on this section, keeping the streets of Antioch fairly well"+
	" lit. This street continues on to the northeast and"+
	" branches to the right a ways up ahead. It looks like there"+
	" may be a shop on the west hand side. To the south is the"+
	" intersection with Cherry and Pine. There is also a stables"+
	" on the western side of the intersection. The lovely smell"+
	" of horses drifts to you on the breeze and you can hear"+
	" them stomping about in their stalls."
	);
	set_smell("default","The smell of horses drifts in from the"+
	" south.");
	set_listen("default","Horses can be heard stomping restlessly"+
	" in their stalls.");
	set_items(([
	"street sign" : "This is Apple street.",
	({"street","cobblestones","cobbles","road","path"}) : "The"+
	" street is paved with cobblestones.",
	"sign" : "There is a wooden sign with the symbol of a stables"+
	" hanging over the doorway of the large building to the"+
	" south.",
	({"stables","building"}) : "There appears to be a stables"+
	" to the south on the west hand side.",
	"shop" : "It looks like there's a shop a little ways up"+
	" ahead.",
	]));
	set_exits(([
	"northeast" : ROOMS+"street8",
	"south" : ROOMS+"street6",
	]));
}
