// Chernobog (4/15/22)
// The Zephyr's Talon

#include <std.h>
#include "../defs.h"
#define HIT_INTERVAL 4

inherit "/d/common/obj/weapon/longsword";

int counter, charges;

void create(){
    ::create();
    set_name("jeweled cutlass with a basket hilt");
    set_id(({ "cutlass", "jeweled cutlass", "zephyr", "Zephyr", "zephyr's talon", "Zephyr's Talon", "talon", "Talon", "sword" }));
    set_obvious_short("%^RESET%^%^CRST%^%^C039%^j%^C045%^ewele%^C039%^d %^C153%^cutlass %^C101%^with a %^C144%^b%^C136%^a%^C144%^s%^C136%^k%^C144%^e%^C136%^t %^RESET%^%^C144%^h%^C136%^i%^C144%^l%^C136%^t%^CRST%^");
    set_short("%^RESET%^%^CRST%^%^C144%^T%^C101%^he %^C144%^Z%^C101%^ephyr's %^C144%^T%^C101%^alon%^CRST%^");
    set_long((:this_object(), "long_fun":));
    set_lore("%^RESET%^%^CYAN%^This cutlass, often referred to as the Zephyr's Talon, was an heirloom held by a merchant household of the Tsarven Empire. There are rumors that this was a gift from the djinn, imbued strongly with the winds they so favor and fashioned by their hidden techniques to grow exponentially stronger when invested with further magic. It is said that the gemstones will awaken in a skilled hand, allowing one to %^BOLD%^focus on the breeze %^RESET%^%^CYAN%^or %^BOLD%^the wind %^RESET%^%^CYAN%^to call for aid. %^RESET%^");
    set_property("lore difficulty", 30);
    set_value(1000);
    set_hit((:this_object(),"hit_fun":));
    set_wield((:this_object(), "wield_fun":));
    set_unwield((:this_object(), "unwield_fun":));
    set_property("no curse", 1);
    set_property("no alter", 1);
    set_property("enchantment", 4);
    counter = 0;
}

void long_fun(){
    string longdesc;
    
    longdesc = "%^RESET%^%^CRST%^%^C101%^This is a faintly curved cutlass made of %^C153%^steel%^C101%^. Woven bands of %^C214%^b%^C220%^ras%^C214%^s %^RESET%^%^C101%^wrap about the grip in a %^C144%^b%^C136%^a%^C144%^s%^C136%^k%^C144%^e%^C136%^t %^RESET%^%^C144%^h%^C136%^i%^C144%^l%^C136%^t%^RESET%^%^C101%^, decorated with swirls and other curled designs etched into the surface like stylized winds. Three %^C039%^b%^C045%^lu%^C039%^e t%^C045%^opa%^C039%^z g%^C045%^emstone%^C039%^s %^RESET%^%^C101%^have been placed around the circumference of the hilt, their azure hue reminiscent of a clear sky.%^CRST%^";
    switch(charges){
        case 1 :
            longdesc += "\n%^RESET%^%^CRST%^%^C101%^One of the %^C039%^g%^C045%^emstone%^C039%^s %^C101%^is radiating a soft %^C051%^glow%^C101%^.%^CRST%^";
            break;
        case 2 :
            longdesc += "\n%^RESET%^%^CRST%^%^C101%^Two of the %^C039%^g%^C045%^emstone%^C039%^s %^C101%^are softly %^C051%^glowing%^C101%^.%^CRST%^";
            break;
        case 3 :
            longdesc += "\n%^RESET%^%^CRST%^%^C101%^All three of the %^C039%^g%^C045%^emstone%^C039%^s %^C101%^are quietly %^C051%^glowing%^C101%^.%^CRST%^";
            break;
    }
    
    return longdesc;
}

void init(){
    ::init();
    add_action("focus_fun", "focus");
}

int focus_fun(string str){
    object zephyr, player, room;
    if(!str) return 0;
    
    zephyr = this_object();
    player = environment(zephyr);
    room = environment(player);
    if(str == "on the breeze" || str == "on breeze" || str == "breeze"){
        if(charges < 3){
            tell_object(player, "%^RESET%^%^CRST%^%^C124%^The cutlass doesn't respond to your wishes.%^CRST%^");
            return 1;
        }
        mistform_fun(player, room);
        return 1;
    }
    if(str == "on the wind" || str == "on wind" || str == "wind"){
        if(charges < 3){
            tell_object(player, "%^RESET%^%^CRST%^%^C124%^The cutlass doesn't respond to your wishes.%^CRST%^");
            return 1;
        }
        fodder_fun(zephyr, player, room);
        return 1;
    }
    return 0;
}

void fodder_fun(object zephyr, object player, object room){
    object dustdevil;
    int strength;
    
    tell_object(player, "%^RESET%^%^CRST%^%^C101%^The %^C039%^g%^C045%^emstone%^C039%^s %^RESET%^%^C101%^in your cutlass %^C244%^darken %^C101%^as a strange wind whips about the area, gathering debris and spinning it about in a small %^C144%^wh%^C252%^i%^C255%^r%^C144%^lw%^C101%^i%^C144%^n%^C255%^d!%^CRST%^");
    tell_room(room, "%^RESET%^%^CRST%^%^C101%^The %^C039%^g%^C045%^emstone%^C039%^s %^RESET%^%^C101%^in "+player->query_cap_name()+"%^RESET%^%^CRST%^%^C101%^'s cutlass %^C244%^darken %^C101%^as a strange wind whips about the area, gathering debris and spinning it about in a small %^C144%^wh%^C252%^i%^C255%^r%^C144%^lw%^C101%^i%^C144%^n%^C255%^d!%^CRST%^", player);
    
    strength = zephyr->query_property("enchantment");
    
    dustdevil = new(MON"dustdevil");
    dustdevil->set_powerlevel(strength);
    dustdevil->move(room);
    dustdevil->set_property("minion", player);
    player->add_follower(dustdevil);
    player->add_protector(dustdevil);
    charges = 0;
    return;
}

void mistform_fun(object player, object room){
    object zephyr;
    int strength, heal;
    zephyr = this_object();
    strength = zephyr->query_property("enchantment");
    
    tell_object(player, "%^RESET%^%^CRST%^%^C144%^The %^C039%^g%^C045%^emstone%^C039%^s %^RESET%^%^C144%^in your cutlass %^C244%^darken %^C144%^as your body begins to %^C250%^f%^C248%^a%^C246%^d%^C244%^e%^RESET%^%^C144%^, becoming ephemeral like a %^C051%^breeze%^C144%^...%^CRST%^");
    tell_room(room, "%^RESET%^%^CRST%^%^C144%^The %^C039%^g%^C045%^emstone%^C039%^s %^RESET%^%^C144%^in "+player->query_cap_name()+"%^RESET%^%^CRST%^%^C144%^'s cutlass darken as their body begins to %^C250%^f%^C248%^a%^C246%^d%^C244%^e%^RESET%^%^C144%^, becoming ephemeral like a %^C051%^breeze%^C144%^...%^CRST%^", player);
    player->set_missChance(player->query_missChance() + 65);
    if(strength > 8){
        heal = player->query_max_hp() / 10;
        tell_object(player, "A wellspring of energy flows through you as you become like the wind.");
        player->cause_typed_damage(player, "torso", heal, "positive");
    }
    charges = 0;
    call_out("mistform_end", 4, player);
    return;
}

void mistform_end(object player){
    object room;
    room = environment(player);
    
    tell_object(player, "%^RESET%^%^CRST%^%^C101%^Your body %^C100%^solidifies%^C101%^, growing heavy once more.%^CRST%^");
    tell_room(room, "%^RESET%^%^CRST%^%^C101%^"+player->query_cap_name()+"%^RESET%^%^CRST%^%^C101%^'s body %^C100%^solidifies%^C101%^, growing heavy once more.%^CRST%^", player);
    player->set_missChance(player->query_missChance() - 65);
    return;
}

int wield_fun(){
    object player;
    player = environment(this_object());
    
    if(player->query_property("zephyr")){
        tell_object(player, "%^RESET%^%^CRST%^%^C100%^As you try to wield both swords, a strange wind rises up and prevents you from doing so.%^CRST%^");
        return 0;
    }
    
    tell_object(player, "%^RESET%^%^CRST%^%^C101%^The %^C144%^blade %^C101%^is unnaturally light in your hand.%^CRST%^");
    player->set_property("zephyr", 1);
    adapt_weapon();
    return 1;
}

int unwield_fun(){
    object player, room;
    player = environment(this_object());
    room = environment(player);
    
    player->remove_property("zephyr");
    if(charges == 1) tell_room(room, "%^RESET%^%^CRST%^%^C101%^The %^C039%^g%^C045%^emston%^C039%^e %^RESET%^%^C101%^fades, becoming %^C244%^inert%^C101%^.%^CRST%^");
    if(charges > 1) tell_room(room, "%^RESET%^%^CRST%^%^C101%^The %^C039%^g%^C045%^emstone%^C039%^s %^RESET%^%^C101%^fade, becoming %^C244%^inert%^C101%^.%^CRST%^");
    charges = 0;
    return 1;
}

void adapt_weapon(){
    object zephyr;
    int strength;
    
    zephyr = this_object();
    strength = zephyr->query_property("enchantment") - 4;
    zephyr->set_item_bonus("attack bonus", strength);
    zephyr->set_item_bonus("damage bonus", strength);
    return;
}

int hit_fun(object target){
    object player, room, zephyr;
    int damage, strength;
    string playername, targetname;
    
    zephyr = this_object();
    player = environment(zephyr);
    room = environment(player);
    
    if(!living(player) || !living(target) || !room) return 0;
    
    counter++;
    if(counter < HIT_INTERVAL) return 0;
    counter = 0;
    
    playername = player->query_cap_name();
    targetname = target->query_cap_name();
    strength = zephyr->query_property("enchantment");
    damage = 0;
    
    switch(random(10)){
        case 0..1 : // extra hit
            tell_object(player, "%^RESET%^%^CRST%^%^C144%^A %^C255%^mys%^C250%^t%^C255%^er%^C250%^i%^C255%^ous wi%^C250%^n%^C255%^d %^RESET%^%^C144%^seems to pick up, propelling you forward and %^C141%^spe%^C147%^ed%^C153%^ing %^C144%^up your movements!%^CRST%^");
            tell_room(room, "%^RESET%^%^CRST%^%^C144%^A %^C255%^mys%^C250%^t%^C255%^er%^C250%^i%^C255%^ous wi%^C250%^n%^C255%^d %^RESET%^%^C144%^seems to pick up, propelling "+playername+"%^RESET%^%^CRST%^%^C144%^ forward and %^C141%^spe%^C147%^ed%^C153%^ing %^C144%^up their movements!%^CRST%^", player);
            player->execute_attack();
            if(strength > 8) player->execute_attack();
            break;
        case 2..7 : // extra damage and gem charge
            tell_object(player, "%^RESET%^%^CRST%^%^C144%^Your blade seems driven by %^C255%^the wi%^C250%^n%^C255%^d%^RESET%^%^C144%^, a gale following your %^C159%^slash %^RESET%^%^C144%^through "+targetname+"%^RESET%^%^CRST%^%^C144%^!%^CRST%^");
            tell_object(target, "%^RESET%^%^CRST%^%^C144%^"+playername+"%^RESET%^%^CRST%^%^C144%^'s blade seems driven by the %^C255%^the wi%^C250%^n%^C255%^d%^RESET%^%^C144%^, a gale following their %^C159%^slash %^RESET%^%^C144%^through you!%^CRST%^");
            tell_room(room, "%^RESET%^%^CRST%^%^C144%^"+playername+"%^RESET%^%^CRST%^%^C144%^'s blade seems driven by the %^C255%^the wi%^C250%^n%^C255%^d%^RESET%^%^C144%^, a gale following their %^C159%^slash %^RESET%^%^C144%^through "+targetname+"%^RESET%^%^CRST%^%^C144%^!%^CRST%^", ({ player, target }));
            add_charge(player, room);
            damage = roll_dice(strength, 6);
            break;
        case 8..9 : // trip
            tell_object(player, "%^RESET%^%^CRST%^%^C144%^With a %^C124%^feint %^C144%^to the side, you quickly spin about and knock "+targetname+"%^RESET%^%^CRST%^%^C144%^ to the %^C101%^ground%^C144%^!%^CRST%^");
            tell_object(target, "%^RESET%^%^CRST%^%^C144%^With a %^C124%^feint %^C144%^to the side, "+playername+"%^RESET%^%^CRST%^%^C144%^ quickly spins about and knocks you to the %^C101%^ground%^C144%^!%^CRST%^");
            tell_room(room, "%^RESET%^%^CRST%^%^C144%^With a %^C124%^feint %^C144%^to the side, "+playername+"%^RESET%^%^CRST%^%^C144%^ quickly spins about and knocks "+targetname+"%^RESET%^%^CRST%^%^C144%^ to the %^C101%^ground%^C144%^!%^CRST%^", ({ player, target }));
            target->set_tripped(roll_dice(1, 3), "%^RESET%^%^CRST%^%^C124%^You're still scrambling back to your feet!%^CRST%^");
            break;
    }
    return damage;
}

void add_charge(object player, object room){
    if(charges > 2) return;
    
    switch(charges){
        case 0 :
            tell_object(player, "\n%^RESET%^%^CRST%^%^C101%^A %^C039%^g%^C045%^e%^C039%^m %^RESET%^%^C101%^on the hilt of your cutlass starts to %^C051%^glow%^C101%^.%^CRST%^\n");
            tell_room(room, "%^RESET%^%^CRST%^%^C101%^A %^C039%^g%^C045%^e%^C039%^m %^RESET%^%^C101%^on the hilt of "+player->query_cap_name()+"%^RESET%^%^CRST%^%^C101%^'s cutlass starts to %^C051%^glow%^C101%^.%^CRST%^", player);
            break;
        case 1 :
            tell_object(player, "\n%^RESET%^%^CRST%^%^C101%^A %^C039%^s%^C045%^econ%^C039%^d %^C039%^g%^C045%^e%^C039%^m %^RESET%^%^C101%^on the hilt of your cutlass starts to %^C051%^glow%^C101%^.%^CRST%^\n");
            tell_room(room, "%^RESET%^%^CRST%^%^C101%^A %^C039%^s%^C045%^econ%^C039%^d %^C039%^g%^C045%^e%^C039%^m %^RESET%^%^C101%^on the hilt of "+player->query_cap_name()+"%^RESET%^%^CRST%^%^C101%^'s cutlass starts to %^C051%^glow%^C101%^.%^CRST%^", player);
            break;
        case 2 :
            tell_object(player, "\n%^RESET%^%^CRST%^%^C101%^All %^C039%^t%^C045%^hre%^C039%^e g%^C045%^em%^C039%^s %^RESET%^%^C101%^on the hilt of your cutlass are %^C051%^glowing%^C101%^.%^CRST%^\n");
            tell_room(room, "%^RESET%^%^CRST%^%^C101%^All %^C039%^t%^C045%^hre%^C039%^e g%^C045%^em%^C039%^s %^RESET%^%^C101%^on the hilt of "+player->query_cap_name()+"%^RESET%^%^CRST%^%^C101%^'s cutlass are %^C051%^glowing%^C101%^.%^CRST%^", player);
            break;
    }
    charges++;
    return;
}

