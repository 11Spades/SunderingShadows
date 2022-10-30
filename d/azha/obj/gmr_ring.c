// Ring of Greater Magic Protection
// Thorn@ShadowGate
// 970225
// gmr_ring.c
// modified to grant a set amount, and fixed to ETO wear/remove. nienne, 08/07.
//Added some color - Octothorpe 12/5/09
// reduced duration to 2-3 rounds and only able to carry one -Chernobog

#include <std.h>
inherit "/d/common/obj/jewelry/ring.c";

int uses, old, resamt, counter;
object protect;

int resist_magic();
int takeoff();
void create()
{
    ::create();
    set_property("ring of magic protection", 1);
    set_property("magic", 1);
    set_name("ring");
    set_id(({"band", "ring of greater magic protection","metal band", "tarnished band",
        "platinum ring", "ring", "glowing platinum ring", "mr_ring"}));
    set_short("%^BOLD%^%^WHITE%^a t%^YELLOW%^a%^WHITE%^rn%^YELLOW%^i%^WHITE%^sh%^YELLOW%^e%^WHITE%^d band of metal%^RESET%^");
    set_long("%^BOLD%^On your finger is revealed a glowing platinum ring pulsing with a field of magic that seems to charge even the air around it.  Runes of power glow on the surface where you originally saw what you thought were nicks.%^RESET%^");
    set_lore("This ring is rumored to possess great power against those who wield magic.  The battered appearance of the ring is a disguise to keep some authorities from recognizing the ring for what it is.  At one time, such a ring had been banned in Azha for its ability to keep the law-enforcing magic users from apprehending certain criminals.  This particular ring seems able to offer more magic resistance than others.");

    set_property("lore difficulty",7);
    set_value(125);
    set_wear((:TO,"do_wear":));
    set_remove((:TO,"takeoff":));
    uses = random(4) + 6;
    set_heart_beat(1);
    counter = 0;
}

int do_wear(){
    object *stuff, onering, env;
    int i,j, flag;

    stuff = ETO->all_armour();
    j = sizeof(stuff);

    for(i=0;i<j;i++)
    {
        if((string)stuff[i]->query_type() == "ring" && stuff[i]->query_property("ring of magic protection"))
        {
            onering = stuff[i];
            flag = 1;
            break;
        }
    }

    if(flag)
    {
        write("The magic of this ring reacts with the one already worn...\n"+
            "and they repel violently!");
        env = environment(ETO);
        onering->move(env);
        return 0;
    }

    if(ETO->query_property("raised resistance")){
        tell_object(ETO,"The magical spell protecting you conflicts with the magic in the ring, and it "
            "forcefully repels your hand!");
        return 0;
    }

    if((int)ETO->query_highest_level() < 15){
        tell_object(ETO,"You aren't powerful enough to use this item yet!");
        return 0;
    }

    protect = ETO;
    resamt = 15;
    protect->set_property("magic resistance",resamt);
    protect->set_property("raised resistance",1);

    tell_object(ETO, "%^BOLD%^The ring %^YELLOW%^flashes %^WHITE%^brightly for a brief instant %^BOLD%^on your finger and then fades to a steady glow.%^RESET%^");
    TO->set_short("%^BOLD%^%^WHITE%^a %^YELLOW%^glowing %^BOLD%^%^WHITE%^platinum ring%^RESET%^");
    TO->set_long("%^BOLD%^On your finger is revealed a %^YELLOW%^glowing %^WHITE%^platinum ring pulsing with a field of magic that seems to charge even the air around it.  Runes of power glow on the surface where you originally saw what you thought were nicks.%^RESET%^");

    return 1;
}

void heart_beat(){
    object ob;
    
    if(!objectp(TO->query_worn())) TO->takeoff();
    if(!objectp(ETO)) return;
    
    if((ob = present("mr_ring",ETO)) && living(ETO) && ob != TO){
        tell_object(ETO,"The rings start to interact and shake and quiver.");
        tell_room(environment(ETO),"The rings held by "+ETO->query_cap_name()+" quiver and shake.",ETO);
        tell_room(environment(ETO),"%^BOLD%^%^CYAN%^They explode in a brilliant burst of light and fire.");
        ETO->do_damage("torso",roll_dice(3,50));
        ETO->add_attacker(TO);
        ETO->continue_attack();
        ob->remove();
        TO->remove();
    }
    else{
        mr_ring_check();
    }
    if(!TO->query_worn()) return 1;

    if(uses <= 0){
        tell_object(protect, "%^BOLD%^The ring flashes and suddenly is no more!%^RESET%^");
        set_heart_beat(0);
        takeoff();
        if(!TO->remove()) destruct(TO);
        return 1;
    }

    if(!ETO->is_monster()) { uses--; }

    tell_object(protect, "%^BOLD%^The ring flashes for a moment.%^RESET%^");
    return 1;
}

int takeoff(){
    if(objectp(protect)){
        protect->set_property("magic resistance",(-1)*resamt);
        protect->set_property("raised resistance",-1);
    }

    TO->set("short","%^BOLD%^%^WHITE%^a t%^YELLOW%^a%^WHITE%^rn%^YELLOW%^i%^WHITE%^sh%^YELLOW%^e%^WHITE%^d band of metal");

    TO->set_long("%^BOLD%^This band of metal looks like it was used for the ring to a beggar's bed curtains.  It is tarnished and nicked in a few places and seems to have a greasy look to it.  This looks like the sort of thing that mothers warn their children about bringing in the house.%^RESET%^");

    protect = 0;
    return 1;
}

void mr_ring_check(){
    object *inv,*deep_inv,*mr_rings=({}),*sacks=({});
    int i,j,damage;

    if(!objectp(TO)) return;
    if(!objectp(ETO)) return;
    if(!living(ETO)) return;

    inv = all_inventory(ETO);

    if(!sizeof(inv)) return;

    for(i=0;i<sizeof(inv);i++)
    {
        if(!objectp(inv[i])) { continue; }
        if(!inv[i]->is_container()) { continue; }
        deep_inv = all_inventory(inv[i]);
        if(!sizeof(deep_inv)) { continue; }
        for(j=0;j<sizeof(deep_inv);j++)
        {
            if(!objectp(deep_inv[j])) { continue; }
            if(deep_inv[j]->is_mr_ring()) 
            { 
                mr_rings += ({ deep_inv[j] });
                TO->add_counter(1);
                deep_inv[j]->add_counter(1);
                sacks += ({ inv[i] });
            }
        }
    }

    sacks = distinct_array(sacks);

    if(!sizeof(mr_rings)) 
    { 
        TO->add_counter(-1);
        return;
    }

    switch(counter)
    {
    case 0..19: break;
    case 20:
        if(objectp(ETO) && living(ETO))
        {
            tell_object(ETO,"%^RESET%^%^GREEN%^Your "+TO->query_short()+" begins to get warm to the touch.%^RESET%^");
            tell_object(ETO,"You can feel something in your sacks start to vibrate.");
        }
        break;
    case 21..99: break;
    case 100:
        if(objectp(ETO) && living(ETO))
        {
            tell_object(ETO,"%^RESET%^%^YELLOW%^Your "+TO->query_short()+" is painfully hot to the touch now!%^RESET%^");
            tell_object(ETO,"%^RESET%^%^BOLD%^The vibration in your sacks increases to a dull hum!");
        }
        break;
    case 101..199: break;
    default:
        if(objectp(ETO) && living(ETO) && objectp(EETO))
        {
            tell_object(ETO,"%^RED%^Your "+TO->query_short()+" suddenly explodes in a violent shower of fragments!");
            tell_room(EETO,"%^RED%^"+ETO->QCN+"'s "+TO->query_short()+" suddenly explodes in a violent shower of fragments!",ETO);
            this_object()->remove();
            /*
            damage = roll_dice(10,10);
            if(sizeof(sacks))
            {
                for(i=0;i<sizeof(sacks);i++)
                {
                    if(!objectp(sacks[i])) { continue; }
                    tell_object(ETO,"%^RED%^Your "+sacks[i]->query_short()+" rips apart in a violent "
                        "explosion sending debris everywhere!");
                    tell_room(EETO,"%^RED%^"+ETO->QCN+"'s "+sacks[i]->query_short()+" rips apart in "
                        "a violent explosion sending debris everywhere!",ETO);
                    deep_inv = all_inventory(sacks[i]);
                    if(!sizeof(deep_inv)) { continue; }
                    for(j=0;j<sizeof(deep_inv);j++)
                    {
                        if(!objectp(deep_inv[j])) { continue; }
                        if(deep_inv[j]->is_mr_ring())
                        {
                            damage += roll_dice(10,10);
                            deep_inv[j]->remove();
                            continue;
                        }
                        deep_inv[j]->repairMe(-1*(roll_dice(10,10)));
                        if(objectp(deep_inv[j]))
                        {
                            deep_inv[j]->move(environment(ETO));
                        }
                    }
                }
            }
            */
        }
        ETO->set_property("magic",1);
        ETO->do_damage("torso",damage);
        ETO->set_property("magic",-1);
        TO->remove();
        return;
    }

    return;
}

int add_counter(int num){
    if(!counter || counter < 0){ counter = 0; }
    counter += num;
}

int is_mr_ring(){ return 1; }
