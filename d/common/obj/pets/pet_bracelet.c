// Chernobog (6/13/22)
// Pet Bracelet

#include <std.h>

inherit ARMOUR;

string owner, *pet_list;
mapping pets;
object active_pet;
int pet_slots, counter;

void create(){
    ::create();
    set_name("pet bracelet");
    set_id(({"bracelet", "pet bracelet", "silver bracelet", "dimensional bracelet", "pet_bracelet_x"}));
    set_short("%^RESET%^%^CRST%^%^C096%^a %^C245%^s%^C247%^i%^C249%^lv%^C247%^e%^C245%^r b%^C247%^r%^C249%^a%^C251%^ce%^C249%^l%^C247%^e%^C245%^t %^RESET%^%^C096%^wreathed in %^C039%^g%^C045%^l%^C039%^o%^C045%^w%^C051%^i%^C045%^n%^C039%^g r%^C045%^u%^C051%^n%^C045%^e%^C039%^s%^CRST%^");
    set_long("%^RESET%^%^CRST%^%^C096%^Strange %^C039%^r%^C045%^u%^C051%^n%^C045%^e%^C039%^s %^C096%^hover over the surface of this otherwise simple %^C245%^s%^C247%^i%^C249%^lv%^C247%^e%^C245%^r b%^C247%^r%^C249%^a%^C251%^ce%^C249%^l%^C247%^e%^C245%^t%^RESET%^%^C096%^. The glowing sigils occasionally spin about the circumference, before slowing down in a completely different order, hinting at letters that you could possibly %^C090%^read%^C096%^.%^CRST%^");
    set_weight(2);
    set_value(0);
    set_type("ring");
    set_limbs(({"left arm","right arm"}));
    set_ac(0);
    set_lore("%^RESET%^%^CYAN%^These bracelets were designed for adventurers who wished to bring their animal friends with them in comfort. Each is enchanted with small pocket dimensions tailored to a particular pet, both caring for them as well as offering protection whenever the adventurer encounters danger in their explorations. The magics can also be used to form new bonds with some creatures, adding them to the stable of pets. These bracelets can be further enhanced to contain multiple pockets for a wide array of pets.%^RESET%^");
    set_read("%^RESET%^%^CRST%^%^C089%^Words seem to shift into view atop the bracelet: %^C255%^dismiss pet, list pets, call, tame, gift, release.%^CRST%^");
    set_property("lore difficulty", 35);
    set_property("repairtype", ({ "jewel" }));
    set_remove((:this_object(), "remove_fun":));
    
    pets = ([ ]);
    pet_list = ({ });
    pet_slots = 1;
}

void init(){
    ::init();
    add_action("summon_fun", "call");
    add_action("dismiss_fun", "dismiss");
    add_action("list_fun", "list");
    add_action("tame_fun", "tame");
    add_action("exchange_fun", "gift");
    add_action("abandon_fun", "release");
}

int abandon_fun(string str){
    object player, room;
    player = this_player();
    
    if(!str){
        tell_object(player, "Syntax: <release PET>");
        return 1;
    }
    if(player->query_name() != owner){
        tell_object(player, "%^RESET%^%^CRST%^%^C196%^This bracelet isn't bound to you, and refuses your will.%^CRST%^");
        return 1;
    }
    if(member_array(str, pet_list) == -1){
        tell_object(player, "%^RESET%^%^CRST%^%^C059%^You don't seen to have that type of pet.%^CRST%^");
        return 1;
    }
    
    room = environment(player);
    tell_object(player, "%^RESET%^%^CRST%^%^C089%^The %^C039%^r%^C045%^u%^C051%^n%^C045%^e%^C039%^s %^RESET%^%^C089%^along your bracelet %^C087%^flare brightly%^C089%^, %^C196%^bu%^C124%^r%^C196%^ni%^C124%^n%^C196%^g %^RESET%^%^C089%^away the bond you had with "+str+"%^RESET%^%^CRST%^%^C089%^.%^CRST%^");
    tell_room(room, "%^RESET%^%^CRST%^%^C089%^The %^C039%^r%^C045%^u%^C051%^n%^C045%^e%^C039%^s %^RESET%^%^C089%^along "+player->query_cap_name()+"%^RESET%^%^CRST%^%^C089%^'s bracelet %^C087%^flare brightly%^C089%^ for a moment.%^CRST%^", player);
    remove_pet(str);
    return 1;
}

int exchange_fun(string str){
    string real_name, pet_name, target_name, filename, pet_race, short_desc, long_desc, *input;
    object player_bracelet, target_bracelet, player, target, room;
    if(!str) return 0;
    
    input = explode(str, " to ");
    player = this_player();
    room = environment(player);
    
    if(sizeof(input) < 2){
        tell_object(player, "Syntax: <gift PET to TARGET>");
        return 1;
    }
    if(player->query_name() != owner){
        tell_object(player, "%^RESET%^%^CRST%^%^C196%^This bracelet isn't bound to you, and refuses your will.%^CRST%^");
        return 1;
    }
    
    pet_name = input[0];
    target_name = input[1];
    input = explode(pet_name, " ");
    filename = implode(input, "_");
    
    if(player->query_property("pet_summoned")){
        tell_object(player, "%^RESET%^%^CRST%^%^C059%^You cannot gift a pet when one is summoned.%^CRST%^");
        return 1;
    }
    if(member_array(pet_name, pet_list) == -1){
        tell_object(player, "%^RESET%^%^CRST%^%^C059%^You don't seen to have that type of pet.%^CRST%^");
        return 1;
    }
    real_name = lower_case((string)player->realName(target_name));
    if(!target = present(real_name, room)){
        tell_object(player, "%^RESET%^%^CRST%^%^C059%^You don't see that person here.%^CRST%^");
        return 1;
    }
    target = find_player(real_name);
    if(!target_bracelet = present("pet_bracelet_x", target)){
        tell_object(player, "%^RESET%^%^CRST%^%^C059%^"+target->query_cap_name()+"%^RESET%^%^CRST%^%^C059%^ doesn't seem to have a pet bracelet.%^CRST%^");
        return 1;
    }
    if(!target_bracelet->check_slots(pet_name)){
        tell_object(player, "%^RESET%^%^CRST%^%^C059%^"+target->query_cap_name()+"%^RESET%^%^CRST%^%^C059%^ is unable to accept this pet.%^CRST%^");
        return 1;
    }
    
    pet_race = pets[filename]["race"];
    short_desc = pets[filename]["short"];
    long_desc = pets[filename]["long"];
    remove_pet(pet_name);
    target_bracelet->add_pet(pet_name, pet_race, short_desc, long_desc);
    
    tell_object(player, "%^RESET%^%^CRST%^%^C030%^An %^C036%^o%^C042%^r%^C036%^b %^C030%^of %^C036%^l%^C042%^igh%^C036%^t %^RESET%^%^C030%^leaves your bracelet, flying through the air and being %^C024%^absorbed %^C030%^by "+target->query_cap_name()+"%^RESET%^%^CRST%^%^C030%^'s bracelet.%^CRST%^");
    tell_object(target, "%^RESET%^%^CRST%^%^C030%^An %^C036%^o%^C042%^r%^C036%^b %^C030%^of %^C036%^l%^C042%^igh%^C036%^t %^RESET%^%^C030%^leaves "+player->query_cap_name()+"%^RESET%^%^CRST%^%^C030%^'s bracelet, flying through the air and being %^C024%^absorbed %^C030%^by your bracelet.%^CRST%^");
    tell_room(room, "%^RESET%^%^CRST%^%^C030%^An %^C036%^o%^C042%^r%^C036%^b %^C030%^of %^C036%^l%^C042%^igh%^C036%^t %^RESET%^%^C030%^leaves "+player->query_cap_name()+"%^RESET%^%^CRST%^%^C030%^'s bracelet, flying through the air and being %^C024%^absorbed %^C030%^by "+target->query_cap_name()+"%^RESET%^%^CRST%^%^C030%^'s bracelet.%^CRST%^", ({player, target}));
    
    return 1;
}

void remove_fun(){
    object player = environment(this_object());
    string pet_name;
    
    if(player->query_property("pet_summoned")){
        pet_name = active_pet->query_short();
        tell_room(environment(player), ""+pet_name+" %^RESET%^%^CRST%^%^C039%^g%^C045%^l%^C051%^o%^C045%^w%^C039%^s %^C036%^briefly before returning to "+player->query_cap_name()+"%^RESET%^%^CRST%^%^C036%^'s bracelet.%^CRST%^", player);
        tell_object(player, ""+pet_name+" %^RESET%^%^CRST%^%^C039%^g%^C045%^l%^C051%^o%^C045%^w%^C039%^s %^C036%^briefly before returning to your bracelet.%^CRST%^");
        active_pet->move("/d/shadowgate/void");
        active_pet->remove();
        player->remove_property("pet_summoned");
    }
    if(player->query_property("taming")){
        tell_object(player, "%^RESET%^%^CRST%^%^C059%^The runes dim as you remove the bracelet, disrupting your attempt.%^CRST%^");
        player->remove_property("taming");
    }
    return 1;
}

int list_fun(string str){
    int i;
    string *input, filename;
    if(!str) return 0;
    if(str != "pets") return 0;
    
    if(this_player() != environment(this_object())){
        write("%^RESET%^%^CRST%^%^C059%^The bracelet is too far away for you to inspect it.%^CRST%^");
        return 1;
    }
    if(!sizeof(pet_list)){
        write("%^RESET%^%^CRST%^%^C059%^There are no pets bound to this bracelet.%^CRST%^");
        return 1;
    }
    write("%^RESET%^%^CRST%^%^C096%^Gazing into the %^C039%^g%^C045%^l%^C039%^o%^C045%^w%^C051%^i%^C045%^n%^C039%^g r%^C045%^u%^C051%^n%^C045%^e%^C039%^s %^RESET%^%^C096%^of the bracelet, you are granted visions of:%^CRST%^\n");
    for(i = 0; i < sizeof(pet_list); i++){
        input = explode(pet_list[i], " ");
        filename = implode(input, "_");
        write("%^BOLD%^%^RED%^"+pet_list[i]+"%^RESET%^");
        write(""+pets[filename]["short"]+"%^RESET%^%^CRST%^");
        write(""+pets[filename]["long"]+"%^RESET%^%^CRST%^\n");
        continue;
    }
    write("%^RESET%^%^CRST%^%^C089%^There is enough room for "+(pet_slots - sizeof(pet_list))+" more pets.%^CRST%^");
    return 1;
}

int summon_fun(string str){
    string *input, pet_name, filename;
    object player, pet;
    int i, found = 0;
    
    player = this_player();
    if(!this_object()->query_worn()){
        tell_object(player, "%^RESET%^%^CRST%^%^C059%^You have to be wearing the bracelet.%^CRST%^");
        return 1;
    }
    if(!str){
        tell_object(player, "Syntax: <call PET>");
        return 0;
    }
    if(player->query_name() != owner){
        tell_object(player, "%^RESET%^%^CRST%^%^C196%^This bracelet isn't bound to you, and refuses your will.%^CRST%^");
        return 1;
    }
    if(member_array(str, pet_list) == -1){
        tell_object(player, "%^RESET%^%^CRST%^%^C059%^You don't seen to have that type of pet.%^CRST%^");
        return 1;
    }
    if(this_player()->query_property("pet_summoned")){
        tell_object(player, "%^RESET%^%^CRST%^%^C059%^You can only have one pet summoned at a time.%^CRST%^");
        return 1;
    }
    
    input = explode(str, " ");
    filename = implode(input, "_");
    pet_name = pets[filename]["name"];
    pet = new("/d/common/obj/pets/pet");
    pet->setup_pet(player, this_object(), pets[filename]["name"], pets[filename]["race"], pets[filename]["short"], pets[filename]["long"]);
    pet->move(environment(player));
    tell_room(environment(player), "%^RESET%^%^CRST%^%^C036%^There is a faint %^C045%^g%^C051%^l%^C045%^o%^C039%^w %^C036%^from "+player->query_cap_name()+"%^RESET%^%^CRST%^%^C036%^'s bracelet, and "+pet->query_short()+"%^RESET%^%^CRST%^%^C036%^ appears before you.%^CRST%^", player);
    tell_object(player, "%^RESET%^%^CRST%^%^C036%^There is a faint %^C045%^g%^C051%^l%^C045%^o%^C039%^w %^C036%^from your bracelet, and "+pet->query_short()+"%^RESET%^%^CRST%^%^C036%^ appears before you.\n\n%^RESET%^%^CRST%^%^C089%^(Please use the <pet> command to interact with your summoned pet.)%^CRST%^");
    player->add_follower(pet);
    active_pet = pet;
    player->set_property("pet_summoned", 1);
    return 1;
}

int dismiss_fun(string str){
    object player = this_player();
    string pet_name;
    
    if(!str) return 0;
    if(str != "pet") return 0;
    if(!this_object()->query_worn()){
        tell_object(player, "%^RESET%^%^CRST%^%^C059%^You have to be wearing the bracelet.%^CRST%^");
        return 1;
    }
    if(!player->query_property("pet_summoned")){
        tell_object(player, "%^RESET%^%^CRST%^%^C059%^You do not have a pet summoned.%^CRST%^");
        return 1;
    }
    pet_name = active_pet->query_short();
    tell_room(environment(player), ""+pet_name+" %^RESET%^%^CRST%^%^C039%^g%^C045%^l%^C051%^o%^C045%^w%^C039%^s %^C036%^briefly before returning to "+player->query_cap_name()+"%^RESET%^%^CRST%^%^C036%^'s bracelet.%^CRST%^", player);
    tell_object(player, ""+pet_name+" %^RESET%^%^CRST%^%^C039%^g%^C045%^l%^C051%^o%^C045%^w%^C039%^s %^C036%^briefly before returning to your bracelet.%^CRST%^");
    active_pet->move("/d/shadowgate/void");
    active_pet->remove();
    player->remove_property("pet_summoned");
    return 1;
}

void set_owner(object target){
    owner = target->query_name();
    return;
}

void add_pet(string pet_name, string pet_race, string short_desc, string long_desc){
    string *input, filename;
    
    if(!check_slots(pet_name)) return;
    
    input = explode(pet_name, " ");
    filename = implode(input, "_");
    pets[filename] = ([ "name":pet_name, "race":pet_race, "short":short_desc, "long":long_desc ]);
    pet_list += ({ pet_name });
    return;
}

void remove_pet(string pet_name){
    object player = this_player();
    if(member_array(pet_name, pet_list) == -1){
        tell_object(player, "%^RESET%^%^CRST%^%^C059%^You don't seen to have that type of pet.%^CRST%^");
        return 1;
    }
    pet_list -= ({ pet_name });
}

void save_descriptions(string pet_name, string short_desc, string long_desc){
    string *input, filename;
    input = explode(pet_name, " ");
    filename = implode(input, "_");
    if(short_desc != "void") pets[filename]["short"] = short_desc;
    if(long_desc != "void") pets[filename]["long"] = long_desc;
    return;
}

void add_slots(int new_slots){
    pet_slots += new_slots;
    return;
}

int check_slots(string pet_name){
    string *input, filename;
    object player = environment(this_object());
    
    input = explode(pet_name, " ");
    filename = implode(input, "_");
    
    if(!userp(player)){
        tell_object(player, "\n%^RESET%^%^CRST%^%^C089%^You need to be holding the bracelet.%^CRST%^\n");
        return 0;
    }
    if(member_array(pet_name, pet_list) != -1){
        tell_object(player, "\n%^RESET%^%^CRST%^%^C089%^You already have that kind of pet bound to your bracelet.%^CRST%^\n");
        return 0;
    }
    if(sizeof(pet_list) >= pet_slots){
        tell_object(player, "\n%^RESET%^%^CRST%^%^C089%^You don't have any available room for another pet.%^CRST%^\n");
        return 0;
    }
    return 1;
}

// Taming DCs: Low - 10, Mid - 25, High - 40, Epic - 55
// Types of DCs: "survival" for wild creatures (snakes, rats, stags, spiders, etc...)
//               "spellcraft" for magical creatures (elementals, sprites, will o wisp, etc...)
//               "dungeoneering" for constructs (clockwork creatures, golems, etc...)
int tame_fun(string str){
    object target, player, room;
    int tame_DC;
    string DC_type, target_name;
    
    if(!str){
        tell_object(player, "Syntax: <tame TARGET>");
        return 0;
    }
    player = this_player();
    room = environment(player);
    if(!target = present(str, room)){
        tell_object(player, "%^RESET%^%^CRST%^%^C059%^You don't see that here.%^CRST%^");
        return 1;
    }
    if(!target->is_tamable()){
        tell_object(player, "%^RESET%^%^CRST%^%^C059%^The bracelet isn't reacting... you don't think that creature can bond with it.%^CRST%^");
        return 1;
    }
    if(player->query_property("taming")){
        tell_object(player, "%^RESET%^%^CRST%^%^C059%^ are already trying to tame something!%^CRST%^");
        return 1;
    }
    if(!this_object()->query_worn()){
        tell_object(player, "%^RESET%^%^CRST%^%^C059%^You have to be wearing the bracelet.%^CRST%^");
        return 1;
    }
    target_name = lower_case(target->query_name());
    if(!check_slots(target_name)) return 1;
    
    tame_DC = target->query_tame_DC();
    DC_type = target->query_DC_type();
    tell_object(player, "%^RESET%^%^CRST%^%^C096%^You hold your hand out towards the "+str+", focusing your will through the magic of the bracelet...%^CRST%^\n");
    tell_room(room, "%^RESET%^%^CRST%^%^C096%^"+player->query_cap_name()+"%^RESET%^%^CRST%^%^C096%^ holds their hand out towards the "+str+", and the runes of their bracelet flare to life...%^CRST%^\n", player);
    player->set_property("taming", 1);
    counter = 0;
    call_out("taming_in_process", 5, str, player, target, tame_DC, DC_type);
    return 1;
}

void taming_in_process(string str, object player, object target, int tame_DC, string DC_type){
    int skill;
    string pet_name, pet_race, short_desc, input, input_check, *input_b, *long_desc;
    object room = environment(player);
    
    if(!player->query_property("taming")) return;
    if(!present(str, environment(player))){
        tell_object(player, "\n%^RESET%^%^CRST%^%^C059%^The "+str+"%^RESET%^%^CRST%^%^C059%^ isn't here anymore.%^CRST%^\n");
        player->remove_property("taming");
        return;
    }
    
    if(target->query_hp() < target->query_max_hp()){
        tell_object(player, "\n%^RESET%^%^CRST%^%^C124%^The "+str+"%^RESET%^%^CRST%^%^C124%^ is too injured to tame.%^CRST%^\n");
        player->remove_property("taming");
        return;
    }
    
    skill = player->query_skill(DC_type);
    if((skill + roll_dice(1, 20)) < (tame_DC + 10)){
        tell_object(player, "%^RESET%^%^CRST%^%^C090%^The %^C039%^r%^C045%^u%^C051%^n%^C045%^e%^C039%^s %^RESET%^%^C090%^encircling your bracelet %^C051%^f%^C087%^lar%^C051%^e b%^C087%^rightl%^C051%^y %^RESET%^%^C090%^before winking out suddenly, and the "+str+" shakes itself free and charges at you!%^CRST%^\n");
        tell_room(room, "%^RESET%^%^CRST%^%^C090%^The %^C039%^r%^C045%^u%^C051%^n%^C045%^e%^C039%^s %^RESET%^%^C090%^encircling "+player->query_cap_name()+"%^RESET%^%^CRST%^%^C090%^'s bracelet %^C051%^f%^C087%^lar%^C051%^e b%^C087%^rightl%^C051%^y %^RESET%^%^C090%^before winking out suddenly, and the "+str+" shakes itself free and charges at "+player->query_objective()+"!%^CRST%^\n", player);
        target->command("kill "+player->query_name()+"");
        player->remove_property("taming");
        return;
    }
    
    counter++;
    switch(counter){
        case 1 :
            tell_object(player, "%^RESET%^%^CRST%^%^C097%^Small %^C039%^p%^C045%^ul%^C039%^se%^C045%^s %^C097%^of %^C051%^light %^C097%^seem so reach out from your bracelet, tracing a path towards the "+str+".%^CRST%^\n");
            tell_room(room, "%^RESET%^%^CRST%^%^C097%^Small %^C039%^p%^C045%^ul%^C039%^se%^C045%^s %^C097%^of %^C051%^light %^C097%^seem to reach out from "+player->query_cap_name()+"%^RESET%^%^CRST%^%^C097%^'s bracelet, tracing a path towards the "+str+".%^CRST%^\n", player);
            call_out("taming_in_process", 5, str, player, target, tame_DC, DC_type);
            break;
        case 2 :
            tell_object(player, "%^RESET%^%^CRST%^%^C098%^You let out a slow breath, bending your will against the "+str+"'s, slowly taking steps closer to it...%^CRST%^\n");
            tell_room(room, "%^RESET%^%^CRST%^%^C098%^"+player->query_cap_name()+"%^RESET%^%^CRST%^%^C098%^ lets out a slow breath, slowly taking steps closer to the "+str+"...%^CRST%^\n", player);
            call_out("taming_in_process", 5, str, player, target, tame_DC, DC_type);
            break;
        case 3 :
            tell_object(player, "%^RESET%^%^CRST%^%^C099%^The %^C039%^r%^C045%^u%^C051%^n%^C045%^e%^C039%^s %^RESET%^%^C099%^of your bracelet seem to %^C093%^calm%^C099%^, matching the %^C093%^mood%^RESET%^%^C099%^ of the "+str+". Its entire being %^C087%^glows%^C099%^, brightening to an almost blinding radiance before disappearing!%^CRST%^");
            tell_room(room, "%^RESET%^%^CRST%^%^C099%^The %^C039%^r%^C045%^u%^C051%^n%^C045%^e%^C039%^s %^RESET%^%^C099%^of "+player->query_cap_name()+"%^RESET%^%^CRST%^%^C099%^'s bracelet seem to %^C093%^calm%^C099%^, matching the %^C093%^mood%^RESET%^%^C099%^ of the  "+str+". Its entire being %^C087%^glows%^C099%^, brightening to an almost blinding radiance before disappearing!%^CRST%^", player);
            
            pet_name = lower_case(target->query_name());
            pet_race = target->query_race();
            short_desc = target->query_short();
            input = target->query_long();
            input_check = "You look over the "+target->query_race()+".";
            input_b = explode(input, input_check);
            long_desc = explode(input_b[1], "They are in top shape.");
            add_pet(pet_name, pet_race, short_desc, long_desc[0]);
            target->remove();
            player->remove_property("taming");
            break;
    }
    return;
}

void isMagic(){
	::isMagic();
	return 3;
}