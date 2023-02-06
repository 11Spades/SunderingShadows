// Shard of Divine Wrath - LoKi

#include <std.h>
#include <daemons.h>
#include <teleport.h>

inherit "/d/common/obj/weapon/giant_bastard.c";


void create()
{
    ::create();
    set_name("giant platinum sword");
    set_id(({ "sword","giant platinum sword", "shard of divine wrath" }));
    set_obvious_short("%^C254%^gi%^C246%^a%^C254%^"+
	"nt p%^C243%^l%^C254%^atin%^C242%^u%^C254%^m "+
	"s%^C242%^w%^C254%^ord%^CRST%^");
    set_short("%^C254%^Sha%^C154%^r%^C254%^d of %^C154%^D%^C254%^i%^C154%^vine Wra%^C254%^t%^C154%^h%^CRST%^");
    set_long("%^C254%^This sword, easily twelve feet from "+
	"%^C008%^hilt%^C254%^ to tip, is a monstrous thing fit "+
	"only for a giant. The %^C008%^hilt%^C254%^ has been "+
	"crafted from %^C136%^solid oak%^C254%^ and ends in a "+
	"%^C008%^pommel%^C254%^ of an %^C254%^unc%^C153%^u%^C254%^t "+
	"di%^C153%^a%^C254%^mond%^C254%^. The hilt has been made "+
	"from %^C008%^steel%^C254%^ and forms an elegant cross. "+
	"The blade itself is a thing of beauty, forged from "+
	"%^C253%^platinum%^C254%^ and %^C123%^gleaming%^C254%^ "+
	"in the light. A single %^C052%^groove%^C254%^ runs the "+
	"length of the blade and a series of %^C141%^runes%^C254%^ "+
	"decorates at the blade's base.%^CRST%^\n");

    set_value(250000);
    set_lore("%^C109%^\nThe great cleaver of mountains, "+
	"Rozkaros of the Cloud Giants was an early adherent to "+
	"Cevahir after the silence and an extremely vocal and "+
	"active warrior for them. Rumor was that he was working "+
	"with the Warlord for years before the silence, arranging "+
	"forces deep in the mountains. His blade is rumored to be "+
	"able to slice through weak points between planes."+
		        " \n%^C094%^- Father Belanos, The "+
				"Weapons of Light%^CRST%^");

   set_property("lore",20);
   set_property("no curse",1);
   set_property("enchantment",7);

   set_item_bonus("attack bonus",7);
   set_item_bonus("constitution",6);
   set_flag_required("boss avatar");
   set_wield((:TO,"wield_func":));
   set_unwield((:TO,"unwield_func":));
   set_hit((:TO,"extra_hit":));
}

init()
{
    ::init();
    add_action("plane_slice", "slice");
}

string color_me(string str) { return  str = CRAYON_D->color_string(str, "sierra"); }

int plane_slice(string arg)
{
    string destination, *destination_names = ({}), destination_file;
    mapping locations = ([]);
    object destination_room;
    int power, bonus;
    
    if(!arg)
    {
        tell_object(this_player(),"You need to specify a destination");
        return 1;
    }
    
    if(this_player()->query_current_attacker())
    {
        tell_object(this_player(), "You are a little busy for that right now!");
        return 1;
    }

    if(this_player()->query_bound() || this_player()->query_tripped() || this_player()->query_paralyzed())
    {
        this_player()->send_paralyzed_message("info",TP);
        return 1;
    }
    
    if(this_player()->cooldown("plane slice"))
    {
        tell_object(this_player(), "You're not ready to slice the planes yet.");
        return 1;
    }

    locations = this_player()->query_rem_rooms();
    if(!mapp(locations) || !sizeof(keys(locations)))
    {
        tell_object(this_player(),"You don't seem to have any locations remembered");
        return 1;
    }

    destination_names = keys(locations);
    destination = arg;

    if(member_array(destination, destination_names) == -1)
    {
        tell_object(this_player(),"You don't have a location named "+destination+" remembered");
        return 1;
    }

    destination_file = locations[destination];

    if(catch(call_other(destination_file,"??")))
    {
        tell_object(this_player(),"There seems to be an error with the destination room.");
        return 1;
    }

    destination_room = find_object_or_load(destination_file);

    if(!objectp(destination_room) || !destination_room->is_room())
    {
        tell_object(this_player(), "Your destination doesn't seem to be a room.");
        return 1;
    }

    if(!TELEPORT->object_can_be_teleported(this_player(),destination_room, this_player()->query_level() + roll_dice(1, 20)))
    {
        tell_object(this_player(),"You notice some kind of interference preventing you from shadow jumping.");
        return 1;
    }

    this_player()->clear_followers();
    this_player()->setAdminBlock();

    tell_object(this_player(),color_me("You heft your blade in a mighty swing, slicing through the very fabric of reality."));
    tell_object(this_player(),color_me("The blade makes a clean slice and a rift appears in the air in front of you. You step through to another place..."));

    tell_room(destination_room,"A vertical slice appears in the air and opens downward, revealing another place beyond.",this_player());

    call_out("move_caster",1, destination_room, this_player());
    return 1;
}

void move_caster(object dest, object player)
{
    if(!objectp(player))
        return;

    if(!objectp(dest))
    {
        tell_object(player,color_me("Something has gone wrong with the destination.."));
        tell_object(player,color_me("The rift in reality closes itself up."));
        tell_object(player,color_me("You remain where you were standing."));
        tell_room(dest,"There's a slight flicker in the air.",player);
        return;
    }

    player->move(dest);
    player->removeAdminBlock();
    player->force_me("look");
    tell_object(player,color_me("You can feel a rush of sensation you step through the rift to your destination."));
    tell_object(player,color_me("You step silently from the rift."));
    tell_room(dest, player->query_cap_name() + " steps silently from the rift.", player);
    tell_object(player,color_me("You have arrived at your destination."));
    this_player()->add_cooldown("plane slice", 60);
    return;
}

int wield_func()
{
    if (!objectp(ETO) || !objectp(EETO)) {
        return 0;
    }
    tell_object(ETO, "%^C088%^You grip the sword tight, feeling a rush of "+
	"power thrum through your body.%^CRST%^");
    tell_room(EETO, "%^C088%^As " + ETO->QCN + "%^C088%^ wields "+
	"the " + query_short() + ",%^C088%^ you see their posture straighten.%^CRST%^", ETO);
    return 1;
}

int unwield_func()
{
    if (!objectp(ETO) || !objectp(EETO)) {
        return 0;
    }
    tell_object(ETO, "%^C088%^Setting the sword aside, you feel the power "+
	"flee your body.%^CRST%^");

    tell_room(EETO, ETO->QCN + "%^C088%^ releases the " + query_short() + "%^C088%^, almost"
              + " reluctantly flexing " + ETO->QP + "%^C088%^ fingers.%^CRST%^", ETO);
    return 1;
}

int special_damage()
{
    int sdamage;
    string bonus_stat;

    bonus_stat = "strength";
    
    sdamage = TO->query_wc() + (int)this_object()->query_property("enchantment") + (int)ETO->query_damage_bonus() + (int)BONUS_D->new_damage_bonus(ETO, ETO->query_stats(bonus_stat));
    return sdamage;
}

int extra_hit(object targ)
{
    int rand, size;
    object head;
    rand = roll_dice(1, 12);

    if (!objectp(targ)) {
        return 0;
    }
    if (!objectp(ETO)) {
        return 0;
    }
    if (!objectp(EETO)) {
        return 0;
    }
  
    if (!random(2)) {
        switch (random(10)) {
        case 0..3:
            tell_object(ETO, "%^C070%^You turn your weight and swing the sword "+
			"against " + targ->QCN + "%^C070%^!%^CRST%^");
            tell_object(targ, "%^C070%^" + ETO->QCN + " %^C070%^spins " + ETO->QP + " "+
			"%^C070%^giant sword and turns " + ETO->QP + " %^C070%^body, using the "+
			"momentum to hit you with devastating force!%^CRST%^");
            tell_room(EETO, "%^C070%^" + ETO->QCN + "%^C070%^ "+
			"spins " + ETO->QP + "%^C070%^ giant sword quickly and "+
			"turns " + ETO->QP + "%^C070%^ body, using the momentum to "+
			"hit " + targ->QCN + " %^C070%^with a devastating blow!%^CRST%^", ({ targ, ETO }));
            targ->cause_typed_damage(targ, targ->return_target_limb(), TO->special_damage(), "divine");
            break;

        case 4..5: 
            tell_object(ETO, "%^C196%^You thrust your sword viciously at " + targ->QCN + "%^C196%^!%^CRST%^");
            tell_object(targ, "%^C196%^Turning suddenly, " + ETO->QCN + " %^C196%^thrusts "+
			"their sword into you!%^CRST%^");
            tell_room(EETO, "%^C196%^" + ETO->QCN + " %^C196%^turns and thrusts their "+
			"sword into " + targ->QCN + "%^C196%^!%^CRST%^", ({ targ, ETO }));
            targ->cause_typed_damage(targ, targ->return_target_limb(), TO->special_damage() * 150 / 100, "divine");
            break;

        case 6..7:
            tell_object(ETO, "%^C196%^You slam the pommel of your sword against " + targ->QCN + "%^C196%^'s head!%^CRST%^");
            tell_object(targ, "%^C196%^Jumping forward, " + ETO->QCN + " %^C196%^slams the "+
			"pommel of their sword on your head!%^CRST%^");
            tell_room(EETO, "%^C196%^" + ETO->QCN + " %^C196%^slams the the pommel of "+
			"their blade on " + targ->QCN + "%^C196%^'s head!%^CRST%^", ({ targ, ETO }));
            targ->set_paralyzed(roll_dice(1, 10) + 10, "%^GREEN%^You are struggling "+
			"to stand up!%^CRST%^");
            break;

        case 8..9:
            tell_object(ETO, "%^C102%^With a laugh you launch a barrage of attacks "+
			"against " + targ->QCN + "%^C102%^!%^CRST%^");
            tell_object(targ, "%^C102%^With a laugh resounding in your "+
			"ear, " + ETO->QCN + " %^C102%^leaps at you and attacks several times!%^CRST%^");
            tell_room(EETO, "%^C102%^" + ETO->QCN + " %^C102%^laughs and "+
			"launches at " + targ->QCN + " %^C102%^and launches more "+
			"attacks!%^CRST%^", ({ targ, ETO }));
            if (sizeof(ETO->query_attackers())) {
                ETO->execute_attack();
                ETO->execute_attack();
            }
            break;

        }
    }
    return 0;
}
