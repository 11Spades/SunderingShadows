// Chernobog (7/11/22)
// Player House Boat - Ship Object

/*

Be sure to customize all of these.

set_id - be sure to include the name of the ship, to give it a unique ID in case there are multiple boats/ships/etc at the dock
set_short/set_long - either include the name of the ship in the short (i.e. - The Gull, a slender ship with golden embellishments) or be sure to mention it in the long description
set_main_deck - this is what attaches the ship to its deck

*/

#include <std.h>

inherit OBJECT;

string main_deck;

void create(){
    ::create();
    set_name("house boat");
    set_id(({ "ship", "boat" }));
    set_short("small boat");
    set_long("This boat appears sea-worthy despite its small size. It is manned by a small crew of sailors who take orders from the owner alone. It may be used to transport people and goods across the sea. There is a gangplank present in order to <board> the boat.");
    set_weight(100000);
    set_property("no animate", 1);
    set_no_clean(1);
    
    set_main_deck("/std/housing/main_deck");
}

void init(){
    ::init();
    add_action("board_fun","board");
}

int board_fun(string str){
    object player, room, ship;
    
    if(!str) return 0;
    if(!id(str)) return 0;
    
    player = this_player();
    room = environment(this_object());
    ship = find_object_or_load(main_deck);
    
    message("info", "%^RESET%^%^CRST%^%^C027%^You step across the gangplank and board the ship.%^CRST%^\n", player, room);
    message("info", "%^RESET%^%^CRST%^%^C027%^"+player->query_cap_name()+"%^RESET%^%^CRST%^%^C027%^ steps across the gangplank and boards the ship.%^CRST%^", room, player);
    player->move_player(ship);
    return 1;
}

void set_main_deck(string str){
    main_deck = str;
    return;
}

