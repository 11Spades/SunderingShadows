// Chernobog (2/15/22)

#include <std.h>
inherit ROOM;

int is_virtual(){ return 1; }

void create(){
    ::create();
    set_terrain(DESERT);
    set_travel(FOOT_PATH);
    set_indoors(0);
    set_light(3);
    set_name("a vast desert");
    set_short("%^RESET%^%^CRST%^%^C136%^a lee between dunes in a vast desert%^CRST%^");
    set_long("%^RESET%^%^CRST%^%^C136%^The %^C214%^dunes %^C136%^seem lower here, with several twisting gently towards each other to create a protected lee. The breeze here almost feels relaxing, calmly blowing across with a faint hint of moisture.%^CRST%^\n");
    set_smell("default","The dry desert air fills your nostrils.");
    set_listen("default","You can hear the breeze blowing over the sand, it is so quiet here.");
    set_items(([
        ({"sand", "dunes"}) : "%^RESET%^%^CRST%^%^C136%^Pristine layers of sand shift and blow in the %^C045%^co%^C039%^o%^C045%^l bre%^C039%^ez%^C045%^e%^C136%^. It shifts lightly under your feet, though the rising crests of the desert are much more shallow here. There is a %^C058%^darkened patch %^C136%^of sand in the hollow between two of the dunes.%^CRST%^",
        ({"patch", "lee"}) : "%^RESET%^%^CRST%^%^C136%^The sand is %^C058%^dark%^C136%^... and %^C027%^wet%^C136%^. You could try %^C214%^digging %^C136%^a bit to find the source.%^CRST%^",
        ]));
    set_exits(([
        "east":"/d/shadow/virtual/desert/25,11.desert",
        "west":"/d/shadow/virtual/desert/25,9.desert",
        "north":"/d/shadow/virtual/desert/24,10.desert",
        "south":"/d/shadow/virtual/desert/26,10.desert"
        ]));
}

query_weather(){
    return "%^BOLD%^%^WHITE%^It is oppressively hot and mostly dry.";
}

void init(){
    ::init();
    add_action("dig_fun", "dig");
}

int dig_fun(string str){
    object player;
    player = this_player();
    
    if((str != "patch") && (str != "sand")) return 0;
    
    tell_object(player, "%^RESET%^%^CRST%^%^C144%^As you dig into the %^C136%^sand%^C144%^, you realize it's very shallow here. There is %^C214%^solid bedrock %^C144%^just below the surface. Brushing %^C058%^wet clumps of sand %^C144%^aside, you realize there is a %^C059%^cr%^C243%^ac%^C059%^k %^C144%^in the rock, revealing a tiny %^C039%^sp%^C045%^r%^C033%^i%^C039%^ng %^C045%^o%^C033%^f %^C039%^wa%^C045%^t%^C033%^e%^C039%^r %^RESET%^%^C144%^running freely.%^CRST%^");
    tell_room(environment(player), "%^RESET%^%^CRST%^%^C144%^"+player->query_cap_name()+"%^RESET%^%^CRST%^%^C144%^ kneels down to dig in the %^C136%^sand%^C144%^.%^CRST%^", player);
    return 1;
}

