/*

Bloodwood Axe - LoKi

*/

#include <std.h>
#include <daemons.h>

#define HIT_INTERVAL 5

inherit "/d/common/obj/weapon/handaxe.c";

int count;
object owner;

void create()
{
    ::create();
    set_name(" ");
    set_id( ({ "bloodwood axe", "axe", "hand axe", "red metal hand axe", "metal axe", "Bloodwood Axe"}) );
    set_short("%^C052%^B%^C160%^l%^C052%^o%^C124%^o%^C196%^"+
	"d%^C052%^w%^C160%^o%^C052%^o%^C124%^d%^C052%^ %^C196%^a%^C052%^x%^C124%^e%^CRST%^");
    set_obvious_short("%^C088%^r%^C124%^ed met%^C088%^a%^C124%^"+
	"l %^C244%^ha%^C247%^n%^C244%^d %^C246%^a%^C244%^xe%^CRST%^");
    set_long("This small axe's %^C058%^handle %^CRST%^is formed "+
	"from a strange %^C130%^unknown wood%^CRST%^ that is %^C094%^dark brown%^CRST%^ "+
	"but with veins of %^C088%^red %^CRST%^in it, as if it had a strange "+
	"blood like sap. The handle is less than a foot long and curved slightly. "+
	"The %^C243%^head %^CRST%^of the %^C241%^axe %^CRST%^is attached securely "+
	"and is formed of a %^C241%^metal %^CRST%^with a %^C088%^reddish tint%^CRST%^. "+
	"The cutting edge of the axe is %^C228%^razor sharp%^CRST%^ and would be equally "+
	"capable of felling %^C094%^trees%^CRST%^ or %^C124%^limbs%^CRST%^.");
        set_lore("%^C066%^A hundred years ago the forest of the Bloodwood was a wild dangerous place, "+
		"but without the outsider influence woodsmen could patrol and keep "+
		"threats from getting out of hand. These woodsmen were normally devotees "+
		"of Mielikki or Silvanus. By the time of the silence most of these woodsmen "+
		"had disapeared and their axes have become sought after collectors pieces."+
        "\n%^RESET%^%^ORANGE%^  Watts Baragoff, Arms and Armor of Serakii%^RESET%^%^RESET%^");
    set_property("lore difficulty", 20);
    set_property("id difficulty", 20);

    // Enchantment and Bonuses
    set_property("enchantment", 6);
    set_item_bonus("strength", 4);
    switch (random(1)) {
    case 0: set_item_bonus("damage bonus", 4); break;
    case 1: set_item_bonus("attack bonus", 4); break;

    }

    // Wield and Unwield
    set_wield((: TO, "extra_wield" :));
    set_unwield((: TO, "extra_unwield" :));
    set_hit((: TO, "extra_hit" :));

}

int extra_wield()
{
    owner = environment(this_object());
     
    tell_object(owner, "You grip the axe in your hand with grim resolve.");
    tell_room(environment(owner), owner->query_cap_name() + " grips their axe.", owner);
    return 1;
}

int extra_unwield()
{
    
    tell_object(owner, "You release the axe.");
    tell_room(environment(owner), owner->query_cap_name() + " releases their axe.", owner);
    return 1;
}

int extra_damage(object ob)
{
    int bonus;
    
    bonus = this_object()->query_wc() + this_object()->query_property("enchantment") + owner->query_damage_bonus();
    bonus += BONUS_D->new_damage_bonus(this_object(), owner->query_stats("strength"));
    
    return bonus;
}

int extra_hit(object ob)
{
    object room, attackers;
    int bonus;
    string ename, oname, oposs;
    
    if(!objectp(ob) || !objectp(owner))
        return 0;
    
    room = environment(owner);
    
    if(!objectp(room))
        return 0;
    
    count++;
    
    if(count < HIT_INTERVAL)
        return 0;
    
    count = 0;
    ename = ob->query_cap_name();
    oname = owner->query_cap_name();
    oposs = owner->query_possessive();
    
    switch(random(2))
    {
        case 0:
        tell_object(owner, "%^C196%^As you strike " + ename + "%^C196%^ with the axe it the veins in the handle glow, fire drips off the axehead!");
        tell_object(ob, "%^C196%^As you are struck, you feel fire burn into you!%^RESET%^");
        ob->cause_typed_damage(ob, "torso", extra_damage(ob), "fire");
        break;
        case 1:
        tell_object(owner, "%^C059%^You cleave " + ename + " %^C059%^with your axe!%^CRST%^");
        tell_object(ob, oname + "%^C059%^ buries their axe deeply into you!%^CRST%^");
        ob->cause_typed_damage(ob, "torso", extra_damage(ob), "slashing%^CRST%^");
        break;
    }
    
    return (bonus + roll_dice(6, 4));
}   
    
