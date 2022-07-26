// Chernobog (6/14/22)
// Pet - altered familiar by Tlaloc

inherit WEAPONLESS;

#include <daemons.h>
#include "/d/magic/mon/summoned_monster.h"

object owner, pet_bracelet;

void create(){
    ::create();
    set_name("pet");
    set_id(({"pet", "pet summon"}));
    set_short("A generic pet");
    set_hd(4,1);
    set_hp(40);
    set_exp(1);
    set_size(1);
    set_gender("neuter");
    set_property("no fight", 1);
    set_property("no animate", 1);
    set_property("no random treasure", 1);
}

void init(){
    ::init();
    if(this_player() != owner) return;
    add_action("pet_command", "pet");
}

void setup_pet(object player, object bracelet, string petname, string petrace, string shortdesc, string longdesc){
    owner = player;
    pet_bracelet = bracelet;
    set_name(petname);
    add_id(petname);
    set_race(petrace);
    set_short(shortdesc);
    set_long(longdesc);
}

int pet_command(string str){
    string *input, new_desc;
    object player = this_player();

    if(player != owner) return 0;
    if(!str){
        tell_object(player, "Syntax : pet [long/short/order/follow].\nPlease include race or name in the short.");
        return 1;
    }

    input = explode(str, " ");
    if(sizeof(input) < 2 && (input[0] == "long" || input[0] == "short")){
        tell_object(player, "Syntax : pet [long/short] [input].\nPlease include race or name in the short.");
        return 1;
    }

    switch(input[0]){
        case "short":
            new_desc = implode(input[1..], " ");
            this_object()->set_short(new_desc);
            tell_object(player, "Your familiar will now be seen as: \n" + query_short());
            pet_bracelet->save_descriptions(query_name(), new_desc, "void");
            break;
        case "long":
            new_desc = implode(input[1..], " ");
            this_object()->set_long(new_desc);
            tell_object(player, "Your familiar will now be described as: \n" + query_long());
            pet_bracelet->save_descriptions(query_name(), "void", new_desc);
            break;
        case "command":
            command(implode(input[1..], " "));
            break;
        case "follow":
            tell_object(player, "Your pet is now following you.");
            player->add_follower(this_object());
        return 1;
            default:
            tell_object(player, "Please select 'long', 'short', 'follow' or 'command' as options.\nPlease include race or name in the short.");
            return 1;
            break;
    }

    return 1;
}

void heart_beat(){
    object *attackers, room;

    ::heart_beat();

    room = environment(this_object());
    if(!room || !objectp(room)) return;
    if(!objectp(owner) || !owner->query_property("pet_summoned")){
        this_object()->remove();
        return;
    }

    //Faithful companion finds his master
    if(objectp(owner) && room != environment(owner)){
        this_object()->move(environment(owner));
        owner->add_follower(this_object());
    }
}

void die(object ob){
    tell_room(environment(this_object()), "%^RED%^The creature vanishes in a %^WHITE%^%^BOLD%^flash %^RESET%^%^RED%^of %^BOLD%^%^WHITE%^light!%^RESET%^");
    command("drop all");
    owner && owner->remove_property("pet_summoned");
    remove();
}

int remove(){
    owner && owner->remove_property("pet_summoned");
    if(query_property("sapient")) message("environment", "%^RESET%^%^CRST%^%^C208%^It lets out a %^C124%^s%^C160%^tr%^C196%^a%^C160%^n%^C124%^g%^C160%^l%^C196%^e%^C160%^d %^C124%^c%^C160%^r%^C124%^y%^RESET%^%^C208%^, trying to %^C202%^flee %^C208%^before the light tightens its hold and drags them back into the bracelet.%^CRST%^", environment(this_object()));
    ::remove();
}

void receive_given_item(object obj){
    string ids;
    object player = this_player();

    tell_object(player, "%^RESET%^%^CRST%^%^C059%^It has nowhere to keep that, and drops it.%^CRST%^");
    ids = obj->query_id();
    command("drop "+ids[0]);
    return;
}

