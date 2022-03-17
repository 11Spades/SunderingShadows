// Updated with tp proof querying - Octothorpe 12/15/09
// locked to new 'tools of the trade' feat for thieves and bards. N, 4/15.
// Cleaned up and added to common files - Chernobog (3/17/22)

#include <std.h>
#include <daemons.h>

inherit OBJECT;

string baseloc, baseroom;
void set_origin(string str);

void create(){
    ::create();
    set_name("black orb");
    set_id(({"orb", "black orb", "bomb", "smokebomb", "smoke bomb"}));
    set_short("%^BOLD%^%^BLACK%^Smo%^RESET%^%^ORANGE%^k%^BOLD%^%^BLACK%^ebomb%^RESET%^");
    set_obvious_short("%^BOLD%^%^BLACK%^glossy black orb%^RESET%^");
    set_long((:this_object(), "long_desc":));
    set_weight(5);
    set_value(2000);
    set_origin("torm");
}

void init(){
    ::init();
    set_long((:this_object(),"long_desc":));
    add_action("light_func","light");
}

string long_desc(){
    string mydesc;
    object player;
    player = this_player();
    
    mydesc = "%^RESET%^The %^BOLD%^%^BLACK%^jet-black surface %^RESET%^of this orb is glossy enough to see your face reflected in. It is a %^CYAN%^perfect sphere%^RESET%^, just the right size to fit in a person's hand, and unmarked except at what must be the top and underside. At the top, a small hole allows %^ORANGE%^slender braided threads %^RESET%^to protrude, woven together and coated in some kind of resin or oil.";
    if(player->is_class("thief") || player->is_class("bard")) mydesc += " Upon the underside are %^GREEN%^letters %^RESET%^scrawled to represent the "+baseloc+" thieves guild. You've seen items like this before. If you %^YELLOW%^light%^RESET%^ the orb and cast it down, you can make a quick getaway.\n";
    else mydesc += " Upon the underside are %^GREEN%^letters %^RESET%^scrawled in an unknown hand.\n";
    return mydesc;
}

int light_func(string str){
    object bomb, player, room, destination;
    bomb = this_object();
    player = environment(bomb);
    room = environment(player);
    
    if(!str || !bomb->id(str)){
        notify_fail ("Light what?\n");
        return 0;
    }
    if(player->query_bound() || player->query_unconscious()){
        player->send_paralyzed_message("info",player);
        return 1;
    }
    if(userp(player) && !FEATS_D->usable_feat(player,"tools of the trade")){
        tell_object(player,"You wouldn't know how to use that!");
        return 1;
    }
    if((int)player->is_retinue()){
        tell_object(player,"You wouldn't know how to use that!");
        return 1;
    }
    if(player->query_paralyzed()) return notify_fail(player->query_paralyze_message()+"\n");
    
    destination = find_object_or_load(baseroom);
    if(room->query_property("teleport proof")){
        if((int)room->query_property("teleport proof") > (player->query_highest_level() + random(20))){
            tell_object(player,"You strike a %^YELLOW%^light %^RESET%^to the end of the fuse and cast it down before you as it starts spewing %^BOLD%^%^BLACK%^thick smoke%^RESET%^. But when the smoke clears... you are still standing there. So much for a quick getaway?");
            tell_room(room,""+player->query_cap_name()+" strikes a light to the end of the orb's fuse and casts it down as it starts spewing %^BOLD%^%^BLACK%^thick smoke%^RESET%^. But when the smoke clears... "+player->query_subjective()+" is still standing there.", player);
            bomb->remove();
            return 1;
        }
    }
    if(room->query_property("no teleport") || destination->query_property("no teleport")){
        tell_object(player,"You strike a %^YELLOW%^light %^RESET%^to the end of the fuse and cast it down before you as it starts spewing %^BOLD%^%^BLACK%^thick smoke%^RESET%^. But when the smoke clears... you are still standing there. So much for a quick getaway?");
        tell_room(room,""+player->query_cap_name()+" strikes a light to the end of the orb's fuse and casts it down as it starts spewing %^BOLD%^%^BLACK%^thick smoke%^RESET%^. But when the smoke clears... "+player->query_subjective()+" is still standing there.", player);
        bomb->remove();
        return 1;
    }
    
    tell_object(player,"You strike a %^YELLOW%^light %^RESET%^to the end of the fuse and cast it down before you as it starts spewing %^BOLD%^%^BLACK%^thick smoke%^RESET%^.");
    tell_room(room,""+player->query_cap_name()+" strikes a light to the end of the orb's fuse and casts it down as it starts spewing %^BOLD%^%^BLACK%^thick smoke%^RESET%^. But when the smoke clears... "+player->query_subjective()+" is gone!", player);
    player->move_player(baseroom);
    tell_object(player,"When the smoke clears, you find yourself emerging safely from the shadows back near the guild.");
    tell_room(room,""+player->query_cap_name()+" steps from the shadows, smelling faintly of %^BOLD%^%^BLACK%^smoke%^RESET%^.", player);
    bomb->remove();
    return 1;
}

void set_origin(string str){
    if(!str) return 0;
    if(str != "torm" && str != "tharis" && str != "juran" && str != "seneca") return 0;
    baseloc = str;
    switch(baseloc) {
        case "torm": baseroom = "/d/dagger/Torm/city/warehouse"; break;
        case "tharis": baseroom = "/d/tharis/newtharis/rooms/thief_tailor"; break;
        case "juran": baseroom = "/d/shadow/juran/city/a3"; break;
        case "seneca": baseroom = "d/attaya/newseneca/rooms/bar_storage"; break;
    }
}

string query_origin() { return baseloc; }
