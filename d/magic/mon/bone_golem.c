/*
  bone_golem.c
  
  Animal companion clone for pale lord.
  
  -- Tlaloc --
*/

inherit WEAPONLESS;

#include <daemons.h>
#include "/d/magic/mon/summoned_monster.h"

#define SAVEDIR "/d/save/summons/" + owner->query_name() + "/bonegolem/"

object owner;

string saved_short,
       saved_long;

int setup,
    bonus;

int set_owner(object ob) { owner = ob; return 1; }
object query_owner()     { return owner; }

void create(){
    ::create();
    set_name("companion");
    set_id(({"companion", "greater summon", "bone golem", "golem"}));
    set_short("%^RESET%^%^CRST%^%^C144%^A towering %^C255%^bo%^C252%^n%^C255%^e %^C144%^golem%^CRST%^");
    set_long("%^RESET%^%^CRST%^%^C144%^The golem is comprised of so many different skeletons, reorganized into this giant humanoid. Four arms spread from a tangled mess of %^C255%^ri%^C252%^b%^C255%^s%^C144%^, %^C250%^femurs%^RESET%^%^C144%^, and other misplaced %^C255%^bo%^C253%^n%^C255%^e%^C252%^s%^RESET%^%^C144%^, with %^C058%^antlers %^C144%^and %^C059%^horns %^RESET%^%^C144%^protruding from its limbs like vicious talons, all bound together by wisps of %^C118%^e%^C112%^ld%^C106%^r%^C118%^i%^C112%^tc%^C106%^h %^C118%^e%^C112%^ne%^C106%^r%^C118%^g%^C112%^y%^RESET%^%^C144%^. A gigantic %^C255%^minotaur skull %^C144%^tops off the monstrosity, its eye sockets aglow with sparks of %^C039%^b%^C045%^al%^C051%^e%^C039%^f%^C045%^ul %^C051%^b%^C039%^l%^C045%^ue %^C051%^f%^C039%^l%^C045%^am%^C051%^e %^RESET%^%^C144%^above a %^C244%^r%^C246%^i%^C248%^c%^C244%^t%^C246%^u%^C248%^s %^C244%^g%^C246%^r%^C248%^i%^C244%^n%^RESET%^%^C144%^.%^CRST%^");
    set_race("undead");
    set_long("");
    set_hd(4,1);
    set_hp(40);
    set_exp(1);
    set_damage(2, 6);
    set_size(2);
    set_gender("neuter");
    //set_property("function and attack",1);
    //set_funcs( ({ "special_attack" }) );
    //set_func_chance(35);
}

int is_undead() { return 1; }

void init()
{
    ::init();
    
    if(this_player() != owner)
        return;
    
    saved_short = read_file(SAVEDIR + "short");
    saved_long = read_file(SAVEDIR + "long");
    
    //Used read_file here - don't want to save whole object for 2 variables
    if(!strlen(saved_short) && !strlen(saved_long))
    {
        mkdir("/d/save/summons/" + this_player()->query_name());
        mkdir(SAVEDIR);
    }
    else
    {
        set_short(saved_short);
        set_long(saved_long);
    }
    
    add_action("golem_command", "golem");
}

int golem_command(string str)
{
    string *input;
    
    if(this_player() != owner)
        return 0;
    
    input = explode(str, " ");
    
    if(sizeof(input) < 1)
    {
        tell_object(this_player(), "Syntax : golem [long/short/follow].");
        return 1;
    }
    
    if(sizeof(input) < 2 && (input[0] == "long" || input[0] == "short"))
    {
        tell_object(this_player(), "Syntax : golem [long/short] [input].");
        return 1;
    }
    
    switch(input[0])
    {
        case "short":
        this_object()->set_short(implode(input[1..], " "));
        tell_object(this_player(), "Your Bone Golem will now be seen as: \n" + query_short());
        rm(SAVEDIR + "short");
        write_file(SAVEDIR + "short", query_short());
        break;
        case "long":
        this_object()->set_long(implode(input[1..], " "));
        tell_object(this_player(), "Your Bone Golem will now be described as: " + query_long());
        rm(SAVEDIR + "long");
        write_file(SAVEDIR + "long", query_long());
        break;
        case "command":
        command(implode(input[1..], " "));
        break;
        case "follow":
        tell_object(this_player(), "Your Bone Golem is now following you.");
        this_player()->add_follower(this_object());
        return 1;
        default:
        tell_object(this_player(), "Please select 'long', 'short', 'follow' or 'command' as options.");
        return 1;
        break;
    }
    
    return 1;
}
    

void heart_beat()
{

    object *attackers,
           room;
           
    ::heart_beat();
    
    room = environment(this_object());
    
    if(!room || !objectp(room))
        return;
    
    //This should stay the same for anything using this template
    if(!objectp(owner) || owner->query_property("animal_companion") != this_object())
    {
        this_object()->remove();
        return;
    }
    
    //Faithful companion finds his master
    if(objectp(owner) && room != environment(owner))
    {
        this_object()->move(environment(owner));
        owner->add_follower(this_object());
    }
    
    //Companion hides if master is hiding
    if(!this_object()->query_invis())
    {
        if(owner->query_hidden() || owner->query_invis())
        {
            this_object()->set_invis(1);
            tell_object(owner, "Your bone golem glistens and fades from sight.");
        }
    }
    else
    {
        if(!owner->query_hidden() && !owner->query_invis())
            this_object()->set_invis(0);
    }
    
    attackers = owner->query_attackers();
    
    //Doesn't really do anything on this mob. Templated for cloning.
    this_object()->add_damage_bonus(-bonus);
    this_object()->add_attack_bonus(-bonus);
    
    if(sizeof(attackers))
    {
        foreach(object ob in attackers)
            this_object()->kill_ob(ob);
    }
    else
    {
        add_hp(query_max_hp() / 20);
        bonus = 0;
    }
    
    if(query_hp() < query_max_hp() / 2 && present("vial", this_object()))
        command("drink vial");
    
    //See above
    this_object()->add_damage_bonus(bonus);
    this_object()->add_attack_bonus(bonus);
    
    //Do the specials if the attacker is valid
    if(this_object()->query_current_attacker() && !random(3))
        special_attack(this_object()->query_current_attacker());
}

void special_attack(object target)
{
    string tname, aname, mess;
    object room;
    int scale, dam;
    mapping attacks;
    
    if(!target || !objectp(target))
        return;
    
    tname = target->query_name();
    aname = capitalize(this_object()->query_name());
    room = environment(this_object());
    
    if(environment(target) != room)
        return;
    
    scale = 1 + this_object()->query_level() / 10;
    attacks = ([  ]);
    
    //AC is relevant
    if(!BONUS_D->process_hit(this_object(), target, 1, 0, 0, 0))
        return;
    
    tname = target->QCN;
    dam = scale * roll_dice(1, 8);
    dam = target->cause_typed_damage(target, target->return_target_limb(), dam, "piercing");
    
    if(!dam || !target)
        return;
    
    switch(random(3))
    {
        case 0:
        tell_room(room, "%^RESET%^%^CRST%^%^C144%^The golem shivers, releasing a %^C196%^barrage %^C144%^of %^C255%^bone shards %^C144%^at " + tname + "%^RESET%^%^CRST%^%^C144%^!%^CRST%^", ({ target }));
        tell_object(target, "%^RESET%^%^CRST%^%^C144%^The golem shivers, releasing a %^C196%^barrage %^C144%^of %^C255%^bone shards %^C144%^at you!%^CRST%^");   
        break;
        case 1:
        tell_room(room, "%^RESET%^%^CRST%^%^C144%^Lunging forward on misshapen legs, the bone golem %^C196%^swipes %^C144%^at " + tname + "%^RESET%^%^CRST%^%^C144%^ with its %^C255%^talons%^C144%^!%^CRST%^", ({ target }));
        tell_object(target, "%^RESET%^%^CRST%^%^C144%^Lunging forward on misshapen legs, the bone golem %^C196%^swipes %^C144%^at you with its %^C255%^talons%^C144%^!%^CRST%^"); 
        break;
        default:
        tell_room(room, "%^RESET%^%^CRST%^%^C144%^The golem ducks low and charges, %^C196%^impaling " + tname + "%^RESET%^%^CRST%^%^C144%^ on a multitude of %^C255%^bone shards%^C144%^!%^CRST%^", ({ target }));
        tell_object(target, "%^RESET%^%^CRST%^%^C144%^The golem ducks low and charges, %^C196%^impaling you %^RESET%^%^CRST%^%^C144%^on a multitude of %^C255%^bone shards%^C144%^!%^CRST%^"); 
        break;
    }
    
    return;
}
    
void die(object ob)
{
    //"/daemon/yuck_d"->save_inventory(this_object(), SAVEDIR + "bonegolem");
    owner && tell_object(owner, "%^RED%^Your bone golem seems to cave in on itself into a pile of bones!%^RESET%^");
    owner && owner->remove_property("animal_companion");
    owner && owner->remove_property("has_elemental");
    remove();
}

int remove()
{
    //"/daemon/yuck_d"->save_inventory(this_object(), SAVEDIR + "bonegolem");
    //all_inventory(this_object())->remove();
    owner && owner->remove_property("animal_companion");
    owner && owner->remove_property("has_elemental");
    ::remove();
}
