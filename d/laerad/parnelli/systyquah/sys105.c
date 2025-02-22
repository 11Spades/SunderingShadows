//Coded by Bane//
#include <std.h>
inherit ROOM;

object ob;
object *monsArray;
int i;

void create(){
    ::create();
    //monsArray = allocate(3);
    set_terrain(WOOD_BUILDING);
    set_travel(FOOT_PATH);
    set_name("Systyquah's city wall");
    set_short("Systyquah's city wall");
    set_long(
	"%^BOLD%^Inside the city walls%^RESET%^
You have walked into the city walls of Systyquah.  A narrow pathway "+
	"continues to the north and south.  Troll guards run up and down the "+
	"pathway, keeping watch on the outside through peep holes and arrow "+
	"slots, making sure the city's defenses are sound.  A gate to the "+
	"west leads into the city."
    );
    set_property("indoors",1);
    set_property("light",2);
    set_smell("default","A terrible odor fills the narrow hall.");
    set_listen("default","You hear the occasional scream of a troll war party.");
    set_exits( ([
	"west":"/d/laerad/parnelli/systyquah/sys062",
	"north":"/d/laerad/parnelli/systyquah/sys106",
	"south":"/d/laerad/parnelli/systyquah/sys104"
    ]) );
}
void reset(){
    ::reset();
    /*for(i = 0;i < sizeof(monsArray);i++){
       	if(!objectp(monsArray[i])){
       		ob = new("/d/laerad/mon/trollg2");
    		ob->move(TO);
       		monsArray[i] = ob;
       	        if(random(5))  continue;
      		ob = new("/d/laerad/mon/trollt");
       		ob->move(TO);
		monsArray[i] = ob;
        }
    }*/
}
