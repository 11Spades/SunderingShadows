#include <std.h>

inherit ROOM;


void create(){
      ::create();
	set_property("light",3);
	set_property("indoors",0);
	set_terrain(BEACH);
	set_travel(FRESH_BLAZE);
    set_short("%^ORANGE%^A s%^BOLD%^a%^WHITE%^ndb%^ORANGE%^a%^RESET%^%^ORANGE%^r south of A%^BOLD%^r%^RESET%^%^ORANGE%^a%^BOLD%^m%^WHITE%^a%^ORANGE%^n%^BLACK%^t%^RESET%^%^ORANGE%^h %^BOLD%^I%^RESET%^%^ORANGE%^s%^BOLD%^l%^WHITE%^a%^BLACK%^n%^RESET%^%^ORANGE%^d.%^RESET%^");
    set_long("%^ORANGE%^A s%^BOLD%^a%^WHITE%^ndb%^ORANGE%^a%^RESET%^%^ORANGE%^r south of A%^BOLD%^r%^RESET%^%^ORANGE%^a%^BOLD%^m%^WHITE%^a%^ORANGE%^n%^BLACK%^t%^RESET%^%^ORANGE%^h %^BOLD%^I%^RESET%^%^ORANGE%^s%^BOLD%^l%^WHITE%^a%^BLACK%^n%^RESET%^%^ORANGE%^d.%^RESET%^
%^ORANGE%^You are standing at the %^CYAN%^e%^BOLD%^dg%^RESET%^%^CYAN%^e o%^BOLD%^f t%^WHITE%^h%^CYAN%^e %^RESET%^%^CYAN%^s%^BOLD%^ea %^RESET%^%^ORANGE%^on a large sandbar. %^CYAN%^The o%^BOLD%^%^WHITE%^ce%^RESET%^%^CYAN%^a%^BOLD%^n %^RESET%^%^CYAN%^s%^BOLD%^%^WHITE%^p%^CYAN%^rout%^RESET%^%^CYAN%^s en%^WHITE%^d%^BOLD%^%^CYAN%^le%^RESET%^%^CYAN%^s%^BOLD%^%^WHITE%^s%^RESET%^%^CYAN%^ly %^BOLD%^%^WHITE%^b%^RESET%^%^CYAN%^e%^BOLD%^fo%^RESET%^%^CYAN%^r%^BOLD%^%^WHITE%^e %^RESET%^%^CYAN%^y%^BOLD%^ou%^RESET%^%^CYAN%^. %^ORANGE%^The rocky coast of Aramanth Island lies to the west and across deeper waters north. Enormous jagged %^RED%^f%^WHITE%^o%^RED%^rmati%^WHITE%^o%^RED%^ns %^ORANGE%^of %^RED%^r%^WHITE%^o%^RED%^c%^WHITE%^k%^RED%^s %^ORANGE%^juts from the water.%^BOLD%^%^BLACK%^
");    
    set_listen("default", "The ocean waves are somewhat relaxing as they lap against the sand..");
       set_exits(([
    "northeast" : "/d/islands/common/aramanth/room13",
    "south" : "/d/islands/common/aramanth/room31",
    "west" : "/d/islands/common/aramanth/room28",
]));
       set_items(([
    "formations" : "Jagged formations of natural rock tower all around you.",
    "channel" : "The waters are very shallow, are crystal clear, and move at a snail's pace.",
    "water" : "It is crystal clear.",
    "rocks" : "The rocks here are very jagged.",
    "formation" : "It looks almost perfectly like a sobbing boy if you look at it from just the right angle.",
    "clouds" : "The clouds seem to take various shapes before your eyes.",
    "shapes" : "A slug on fire, A large blob, A fat lady coughing up a wicker chair, A dog with 3 legs, A glob,  A table with some object stuck to the bottom of it, A dead squid, and A bunch of grapes.",
    "shale" : "Tiny sharp rock fragments and dust cover the ground.",
    "ground" : "Tiny sharp rock fragments and dust cover the ground."
]));
	
}
void init() {
  ::init();
  do_random_encounters(({"/d/islands/common/mon/seadragon"}),35,1);
}
