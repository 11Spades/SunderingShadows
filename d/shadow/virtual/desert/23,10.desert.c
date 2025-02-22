#include <std.h>

inherit ROOM;

int is_virtual(){ return 1; }

void create(){
    ::create();
    set_terrain(DESERT);
    set_travel(FOOT_PATH);
    set_indoors(0);
    set_light(3);
    set_name("A vast desert");
    set_short("%^ORANGE%^You are in a vast desert.%^RESET%^");
    set_long("%^RESET%^%^ORANGE%^You are in a vast desert.\n%^RESET%^Miles of sand stretches out to in every direction except for the one south, where an overgrown Senzokuan styled elven gate stands at the end of a vague pathway with vines and plant life growing all along the gate and into the sand, where it looks like it might one day even come to cover all of the dunes. The sun beats down on your head");
    set_exits(([
        "east":"/d/shadow/virtual/desert/23,11.desert",
        "west":"/d/shadow/virtual/desert/23,9.desert",
        "north":"/d/shadow/virtual/desert/22,10.desert",
        "south":"/d/magic/temples/edea/temple_n"
        ]));
    set_smell("default","%^RESET%^%^CRST%^%^C136%^The dry desert air mixes with a faint floral scent in your nostrils.%^CRST%^");
    set_listen("default","%^RESET%^%^CRST%^%^C034%^You can hear the leaves blowing in the wind, it is so quiet here.%^CRST%^");
    set_items(([
        ]));
}

query_weather(){ return "%^BOLD%^%^WHITE%^It is oppressively hot and dry.%^RESET%^"; }