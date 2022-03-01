
#include <std.h>
#include "/d/common/common.h"
#include "../serakii.h"

inherit ROOM;

void create()
{
    ::create();
    set_property("no teleport", 1);
    set_properties((["light" : 2, "indoors" : 1]));
    set_short("Common Tools Storage");
    set_long("market storage.");
    set_had_players(3);
}


void reset()
{
    ::reset();


    if (!present("apple")) {
        new(OBJ"apple")->move(TO);
		new(OBJ"apple")->move(TO);
        new(OBJ"apple")->move(TO);
		new(OBJ"apple")->move(TO);
		new(OBJ"apple")->move(TO);
    }
    if (!present("bread")) {
        new(OBJ"bread")->move(TO);
		new(OBJ"bread")->move(TO);
		new(OBJ"bread")->move(TO);
    }
    if (!present("cheese")) {
        new(OBJ"cheese")->move(TO);
		new(OBJ"cheese")->move(TO);
		new(OBJ"cheese")->move(TO);
    }
    if (!present("pear")) {
        new(OBJ"pear")->move(TO);
		new(OBJ"pear")->move(TO);
		new(OBJ"pear")->move(TO);
    }
    if (!present("plum")) {
        new(OBJ"plum")->move(TO);
		new(OBJ"plum")->move(TO);
		new(OBJ"plum")->move(TO);
    }
    if (!present("pretzel")) {
        new(OBJ"pretzel")->move(TO);
		new(OBJ"pretzel")->move(TO);
		new(OBJ"pretzel")->move(TO);
    }
    if (!present("salad")) {
        new(OBJ"salad")->move(TO);
    }
    if (!present("smoked fish")) {
        new(OBJ"smoked_fish")->move(TO);
		new(OBJ"smoked_fish")->move(TO);
		new(OBJ"smoked_fish")->move(TO);
    }
    if (!present("stroopwafel")) {
        new(OBJ"stroopwafel")->move(TO);
		new(OBJ"stroopwafel")->move(TO);
		new(OBJ"stroopwafel")->move(TO);
}

}