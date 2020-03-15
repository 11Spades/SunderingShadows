#include <std.h>
inherit "/d/laerad/wsland";

void create(){
    ::create();
    set_long(
      "%^ORANGE%^A sandy wasteland shore\n "
       "You are on a barren shore alongside the %^CYAN%^Sa%^BOLD%^"
	   "%^WHITE%^a%^RESET%^%^CYAN%^krune S%^BOLD%^%^WHITE%^e%^RESET%^"
	   "%^CYAN%^a%^ORANGE%^.  The earth appears cracked and dead with "
	   "no vegetation other than an occasional unusually large cactus.  "
	   "A wicked wind bites at your face, blowing sand into your eyes.  "
	   "Here and there a %^YELLOW%^sulfurous mist %^RESET%^%^ORANGE%^"
	   "spews from a new fissure in the ground.  The lifeless wasteland "
	   "continues for what seems like leagues towards the east.\n "
    );
    set_exits( ([
        "north":"/d/laerad/wasteland/waste28",
        "east":"/d/laerad/wasteland/waste38",
        "west":"/d/laerad/wasteland/waste11"
    ]) );

}

reset()
{
    ::reset();
    new("/d/laerad/mon/paladin")->move(this_object());
}

int clean_up(){return 1;}
