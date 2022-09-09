// Chernobog (6/27/22)
// Player House Boat - Main Deck

/*

Be sure to customize all of these, the short and long descriptions, and the ship object as well. For KNOWN_DOCKS and DOCK_COORDS, make sure that each slot in the array corresponds to the same place.

KNOWN_DOCKS - these are the names for the destinations
DOCK_COORDS - the file names for the destinations
OWNERS - the names of the people who can sail the boat, be sure to keep it lowercase

set_ship_entrance - this is the message displayed to the room when the ship arrives
set_ship_departure - this is the message displayed to the room when the ship sails away
set_ship - the ship object that sits in the room when docked
set_home_dock - if the ship object isn't loaded, this is where it will be placed
 
Commands to reference in the room for players: <raise gangplank>, <lower gangplank>, <list destinations>, <sail DESTINATION>, <toggle sails>.
*/

#include <std.h>

inherit ROOM;

string ship_enters, ship_leaves, ship_file, home_dock, OWNERS, DOCK_DIR, *KNOWN_DOCKS, *DOCK_COORDS;
int gangplank, reduced_sails, counter, alerted;

void create(){
    ::create();
    set_travel(PAVED_ROAD);
    set_terrain(BOATS);
    set_property("indoors", 0);
    set_property("light", 2);
    set_property("no sticks", 0);
    set_short("main deck of a ship");
    set_long("This is the main deck of a ship. There's rope and masts and sails and stuff all around.");
    
    KNOWN_DOCKS = ({ "Home", "Shadow", "Torm" });
    DOCK_COORDS = ({ "/d/shadow/virtual/sea/wailing_isle.dock", "/d/shadow/virtual/sea/shadow.dock", "/d/shadow/virtual/sea/torm.dock" });
    OWNERS = ({ "chernobog" });
    
    set_ship_entrance("A boat sails into the area.");
    set_ship_departure("A boat sails away.");
    set_ship("/std/housing/house_boat");
    set_home_dock("/realms/chernobog/projects/house_boats/room/home_dock");
    
    gangplank = 0;
    reduced_sails = 0;
    counter = 0;
    alerted = 0;
}

void init(){
    ::init();
    add_action("lower_fun", "lower");
    add_action("raise_fun", "raise");
    add_action("list_fun", "list");
    add_action("sail_fun", "sail");
    add_action("set_sails", "toggle");
}

void reset(){
    ::reset();
    if(gangplank){
        gangplank = 0;
        remove_exit("gangplank");
    }
}

int set_sails(string str){
    object player;
    
    if(!str) return 0;
    if(str != "sails") return 0;
    
    player = this_player();
    if(!reduced_sails){
        message("environment", "%^RESET%^%^CRST%^%^C245%^The sails of the ship are reduced to %^C059%^half%^C245%^.%^CRST%^", environment(player));
        reduced_sails = 1;
    }
    else{
        message("environment", "%^RESET%^%^CRST%^%^C245%^The sails of the ship shift to %^C255%^full%^C245%^.%^CRST%^", environment(player));
        reduced_sails = 0;
    }
    return 1;
}

int sail_fun(string str){
    object ship, seas, destination, room, player;
    int i, found = 99;
    
    player = this_player();
    room = environment(player);
    
    if(!str){
        message("info", "%^RESET%^%^CRST%^%^C196%^The correct syntax is %^C255%^<sail LOCATION>%^CRST%^", player);
        return 0;
    }
    if(member_array(player->query_name(), OWNERS) == -1){
        message("info", "%^RESET%^%^CRST%^%^C059%^This is not your ship.", player);
        return 1;
    }
    found = member_array(str, KNOWN_DOCKS);
    if(found == -1){
        message("info", "%^RESET%^%^CRST%^%^C059%^That is not one of the docks listed.%^CRST%^", player);
        return 1;
    }
    
    ship = find_object_or_load(ship_file);
    if(base_name(environment(ship)) == DOCK_COORDS[found]){
        message("info", "%^RESET%^%^CRST%^%^C059%^The ship is already at that dock.%^CRST%^", player);
        return 1;
    }
    
    if(gangplank) raise_fun("gangplank");
    destination = find_object_or_load(DOCK_COORDS[found]);
    if(environment(ship)) message("environment", ship_leaves, environment(ship));
    if(base_name(environment(ship)) == "/d/player_houses/open_seas"){
        message("info", "%^RESET%^%^CRST%^%^C039%^The ship changes course.%^CRST%^", room);
        remove_call_out("traveling_fun");
    }
    else{
        message("environment", "%^RESET%^%^CRST%^%^C039%^The dock fades away as the ship begins its journey.%^CRST%^", this_object());
        seas = find_object_or_load("/d/player_houses/open_seas");
        ship->move(seas);
    }
    
    counter = 30;
    alerted = 0;
    call_out("traveling_fun", 60, ship, destination, room);
    return 1;
}

void traveling_fun(object ship, object destination, object room){
    object seas;
    
    if(!ship){
        ship = find_object_or_load(ship_file);
        seas = find_object_or_load("/d/player_houses/open_seas");
        ship->move(seas);
    }
    if(counter < 4 && !alerted){
        message("environment", "%^RESET%^%^CRST%^%^C033%^A voice from the crows nest calls out: %^C255%^\"Land ho!\"%^CRST%^", room);
        alerted = 1;
    }
    if(counter < 1){
        ship->move(destination);
        message("environment", ship_enters, environment(ship));
        message("environment", "%^RESET%^%^CRST%^%^C039%^The ship has arrived at its destination.%^CRST%^", room);
        return;
    }
    if(reduced_sails) counter--;
    else counter -= 3;
    switch(random(10)){
        case 0 : message("environment", "%^RESET%^%^CRST%^%^C110%^The %^C045%^s%^C051%^h%^C045%^r%^C051%^i%^C045%^l%^C051%^l %^C045%^c%^C051%^r%^C045%^i%^C051%^e%^C045%^s %^RESET%^%^C110%^of %^C255%^gu%^C252%^l%^C255%^l%^C252%^s %^RESET%^%^C110%^ring out as they follow in the ship's wake.%^CRST%^", room); break;
        case 1 : message("environment", "%^RESET%^%^CRST%^%^C110%^A %^C111%^s%^C117%^p%^C123%^r%^C117%^a%^C111%^y %^RESET%^%^C110%^of %^C111%^w%^C117%^a%^C123%^t%^C117%^e%^C111%^r %^RESET%^%^C110%^crashes up as the %^C033%^w%^C039%^a%^C045%^v%^C039%^e%^C033%^s %^C255%^br%^C252%^e%^C255%^a%^C252%^k %^RESET%^%^C110%^against the hull.%^CRST%^", room); break;
        case 2 : message("environment", "%^RESET%^%^CRST%^%^C110%^A %^C103%^muted %^C136%^wo%^C130%^o%^C136%^d%^C130%^e%^C136%^n %^C058%^creak %^C103%^rumbles %^RESET%^%^C110%^through the ship.%^CRST%^", room); break;
        case 3 : message("environment", "%^RESET%^%^CRST%^%^C110%^Something %^C106%^l%^C064%^o%^C106%^n%^C107%^g %^C110%^and %^C108%^s%^C107%^i%^C106%^n%^C064%^u%^C106%^o%^C107%^u%^C108%^s %^RESET%^%^C110%^briefly breaches the nearby %^C033%^w%^C039%^a%^C045%^v%^C039%^e%^C033%^s %^RESET%^%^C110%^before %^C059%^va%^C243%^n%^C059%^ish%^C243%^i%^C059%^n%^C243%^g %^RESET%^%^C110%^into the %^C032%^d%^C026%^e%^C020%^pt%^C026%^h%^C032%^s%^C110%^.%^CRST%^", room); break;
        case 4 : message("environment", "%^RESET%^%^CRST%^%^C110%^A pod of %^C250%^d%^C248%^o%^C246%^lphi%^C248%^n%^C250%^s %^RESET%^%^C110%^keep pace for a moment, leaping from %^C039%^w%^C045%^a%^C039%^v%^C033%^e %^RESET%^%^C110%^to %^C039%^w%^C045%^a%^C039%^v%^C033%^e%^C110%^.%^CRST%^", room); break;
    }
    call_out("traveling_fun", 60, ship, destination, room);
    return;
}

int list_fun(string str){
    object player;
    int i;
    
    if(!str) return 0;
    if(str != "destinations") return 0;
    
    player = this_player();
    message("info", "%^RESET%^%^CRST%^%^C196%^This ship can sail to: %^CRST%^", player);
    for(i = 0; i < sizeof(KNOWN_DOCKS); i++){
        message("info", "    %^RESET%^%^CRST%^%^C255%^"+KNOWN_DOCKS[i]+"%^CRST%^", player);
        continue;
    }
    if(reduced_sails) message("info", "\n%^RESET%^%^CRST%^%^C196%^The ship is currently at reduced sails.%^CRST%^", player);
    else message("info", "\n%^RESET%^%^CRST%^%^C196%^The ship is currently at full sails.%^CRST%^", player);
    return 1;
}

int raise_fun(string str){
    object player;
    
    if(!str) return 0;
    if(str != "gangplank" && str != "the gangplank") return 0;
    
    player = this_player();
    
    if(player->query_bound() || player->query_unconscious() || player->query_tripped()){
        player->send_paralyzed_message("info", player);
        return 1;
    }
    if(!gangplank){
        message("info", "%^RESET%^%^CRST%^%^C059%^The gangplank has already been raised.%^CRST%^", player);
        return 1;
    }
    
    gangplank = 0;
    message("environment", "%^RESET%^%^CRST%^%^C058%^You raise the %^C136%^gangplank%^C058%^.%^CRST%^", player);
    message("environment", "%^RESET%^%^CRST%^%^C058%^"+player->query_cap_name()+"%^RESET%^%^CRST%^%^C058%^ raises the %^C136%^gangplank%^C058%^.%^CRST%^", this_object(), player);
    remove_exit("gangplank");
    return 1;
}

int lower_fun(string str){
    object player, ship, ship_location;
    
    if(!str) return 0;
    if(str != "gangplank" && str != "the gangplank") return 0;
    
    player = this_player();
    if(gangplank){
        message("info", "%^RESET%^%^CRST%^%^C059%^The gangplank has already been lowered.%^CRST%^", player);
        return 1;
    }
    
    ship = find_object_or_load(ship_file);
    if(!environment(ship)){
        ship_location = find_object_or_load(home_dock);
        ship->move(ship_location);
        message("environment", ship_enters, ship_location);
    }
    ship_location = environment(ship);
    
    if(player->query_bound() || player->query_unconscious() || player->query_tripped()){
        player->send_paralyzed_message("info", player);
        return 1;
    }
    if(ship_location->is_open_seas()){
        message("info", "%^RESET%^%^CRST%^%^C059%^The ship is on the open seas.%^CRST%^", player);
        return 1;
    }
    
    gangplank = 1;
    message("environment", "%^RESET%^%^CRST%^%^C058%^You lower the %^C136%^gangplank%^C058%^.%^CRST%^", player);
    message("environment", "%^RESET%^%^CRST%^%^C058%^"+player->query_cap_name()+"%^RESET%^%^CRST%^%^C058%^ lowers the %^C136%^gangplank%^C058%^.%^CRST%^", this_object(), player);
    add_exit(base_name(ship_location), "gangplank");
    return 1;
}

void set_ship_entrance(string str){
    ship_enters = str;
    return;
}

void set_ship_departure(string str){
    ship_leaves = str;
    return;
}

void set_ship(string str){
    ship_file = str;
    return;
}

void set_home_dock(string str){
    home_dock = str;
    return;
}

int is_boat(){ return 1;}
int clean_up(){ return 1;}
