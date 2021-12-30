// Ring of Magic Protection (exploding test)
// Thorn@ShadowGate
// 970225
// mr_ring.c
// modified to grant a set amount, and fixed to ETO wear/remove. nienne, 08/07.
// reduced duration to 2-3 rounds and only able to carry one -Chernobog

#include <std.h>

inherit "/d/common/obj/jewelry/ring.c";

int uses, old, resamt, counter;
object protect;

int resist_magic();
int takeoff();



create(){
    ::create();
    set_property("ring of magic protection", 1);
    set_name("ring");
    set_id(({"ring of magic protection", "ring","golden ring", "gold ring", "mr_ring"}));

    set("short","a golden ring");
    set_long("This is a simple looking gold ring, worth a few gold pieces at the market.  Looking carefully at it, you notice a few illegible scratchings on the inside of the band, but nothing else.");
    set_lore("This ring is rumored to possess great power against those who wield magic.  The battered appearance of the ring is a disguise to keep some authorities from recognizing the ring for what it is.  At one time, such a ring had been banned in Azha for its ability to keep the law-enforcing magic users from apprehending certain criminals.  This particular ring seems only able to offer a small amount of magic resistance.");

    set_property("lore difficulty",7);
    set("value", 25);
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
        if((string)stuff[i]->query_type() == "ring" && stuff[i]->query_property("ring of magic protection")){
            onering = stuff[i];
            flag = 1;
            break;
        }
    }

    if(flag){
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

    protect = ETO;
    resamt = 5;
    protect->set_property("magic resistance",resamt);
    protect->set_property("raised resistance",1);

    tell_object(ETO, "%^BOLD%^The ring glows for a brief instant on your finger and then fades.%^RESET%^");

    TO->set_short("a %^YELLOW%^glowing%^RESET%^ golden ring");
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
    TO->set_short("a golden ring");
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
                    sacks[i]->remove();
                }
            }
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