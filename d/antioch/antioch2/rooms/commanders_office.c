//Added to give Commander Greenshield somewhere to work. Currently contains the symbol of Kreysneothosies, consider removing the symbol if the situation in Antioch changes. Kismet. 
//Ready to be installed. Proper path is: /d/antioch/antioch2/rooms/commanders_office Kismet.

#include <std.h>
#include "../antioch.h" 
inherit CVAULT;

void create()
{
	::create();
	set_terrain(WOOD_BUILDING);
	set_travel(PAVED_ROAD);
    set_property("indoors",1);
    set_property("light",2);
    set_short("The Commander's Office");
    set_long("The Commander's Office\n"+
"This balcony houses the commander's office. It contains a large and neatly organized oak desk and several well-used wooden chairs. A bookshelf stands along the north wall, filled with books, folders and various scrolls. The large window set in the eastern wall offers a view of the city gates and lets some much needed natural light into this otherwise drab place. Torches along the wall light up the office during night-time. Two shields hang upon the back wall, one bares the Insignia of the King of Antioch, while the other holds the holy symbol of Kreysneothosies. A narrow doorway leads into a private chamber to the west."
        );
	set_smell("default","It smells of sweat and tobacco.");
    if(query_night() == 1) {
        set_listen("default","It is quite silent. Perhaps you can hear a prisoner cry far below.");
        }
    else {
        set_listen("default","The chatter of the guards from below fills the room.");
        }
    set_items(([
        ({"shield","shields"}) : "There are two shields hanging on the wall: One holds the insignia of the King of Antioch and the other shows the holy symbol of Kreysneothosies: A sword crossing a sheaf of wheat.",
        "desk" : "The oak desk is kept tidy, even during busy days and troubled times.",
		"bookshelf" : "The bookshelf contains books on the subjects of law, magic and religion, as well as regional maps and various documents.", 
		"door" : "A narrow doorway leads into a private chamber.", 
        ]));
    set_exits(([
        "down" : ROOMS+"jail_main",
		"west" : ROOMS+"commanders_private", 
        ]));
        set_door("door",ROOMS+"commanders_private","west",0); //Ideally, this door should have a lock on it, but I do not know how they work yet. Kismet.
}
