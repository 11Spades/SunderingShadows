#include <std.h>
#include <daemons.h>

inherit "/d/common/obj/weapon/longsword.c";


void create()
{
    ::create();
    set_name("gold dragon");

    set_id(({ "sword", "gold dragon sword", "long sword", "weapon" }));

    set_obvious_short("An %^BOLD%^%^YELLOW%^or%^BOLD%^%^WHITE%^nat%^BOLD%^%^YELLOW%^e %^RESET%^long sword");

    set_short("%^BOLD%^%^YELLOW%^Avragtrael - the Gold Dragon%^RESET%^");

    set_long("This ornately crafted long sword is in near perfect condition.  "
        "The %^BOLD%^%^WHITE%^adamantite %^RESET%^blade has a %^BOLD%^%^YELLOW%^glowing "
        "gold %^RESET%^hue about it, tracing up the razor sharp edges. The hilt of the "
        "blade looks to be two %^BOLD%^%^YELLOW%^dragon %^RESET%^claws sitting apart "
        "from one another in a clutched grip. The handle of the blade is made of a set "
        "of flat %^BOLD%^%^YELLOW%^amber %^RESET%^that are layered in such a way to "
        "seem like you are gripping the scales of a dragon. The heavy pommel is made "
        "of dense %^BOLD%^%^BLACK%^volcanic%^RESET%^ rock, shaped into a eerily dark sphere.");

    set_lore("Crafted by the great Artificer, Carcascus, the dragon blades were a tribute "
        "to the fourth King of Asgard, Stararach, nearly six centuries ago. The swords "
        "were rumored to have the power to control dragons of a specific type as well "
        "as slay them. After the collapse of the kings reign, Stararach's precious "
        "weapons were lost to history.");

    set_property("no curse",1);
    set_property("enchantment",7);

    set_item_bonus("attack bonus",7);
    set_item_bonus("damage bonus",7);

    set_wield((:TO,"wield_func":));
    set_hit((:TO,"hit":));
    set_unwield((:TO,"unwield_func":));

    set_value(100000);

    set_property("quest required","%^BOLD%^%^RED%^Defeated the great red wyrm Klauth!%^RESET%^");
    set_property("level required",35);
}


int wield_func()
{
    tell_room(EETO,""+ETOQCN+" wields the weapon and "+ETOQCN+"'s pupils glow %^BOLD%^%^YELLOW%^gold%^RESET%^ for a moment.",ETO);
    tell_object(ETO,"%^BOLD%^%^YELLOW%^A surge of pride fills your heart but quickly fades, leaving a distant thirst for justice in your mind.");
    return 1;
}


int unwield_func()
{
    tell_room(EETO,""+ETOQCN+" struggles to unwield the weapon but finally succeeds.",ETO);
    tell_object(ETO,"%^BOLD%^%^YELLOW%^Grudgingly you free the sword of your grip. The thirst for justice leaves your mind, though you remember the taste.");
    return 1;
}


int hit(object targ)
{
    object obj,*inven,*live;
    int i;

    if(!objectp(TO)) return 1;
    if(!objectp(ETO)) return 1;
    targ = ETO->query_current_attacker();
    if(!objectp(targ)) return 1;

    if(random(1000) < 500)
    {
        switch(random(1000))
        {
        case 0..300:

            set_property("magic",1);
            tell_room(EETO,"%^BOLD%^%^WHITE%^"+ETOQCN+"'s longsword releases a bright white light!",({ETO,targ}));
            tell_object(ETO,"%^BOLD%^%^WHITE%^Your sword soothes your wounds!");
            tell_object(targ,"%^BOLD%^%^WHITE%^"+ETOQCN+"'s sword glows bright white!");
            ETO->add_hp(random(50)+40);
            remove_property("magic");
            break;

        case 301..600:

            tell_room(EETO,"%^BOLD%^%^BLACK%^"+ETOQCN+"'s stomps one foot and steps into one powerful swing! ",({ETO,targ}));
            tell_object(ETO,"%^BOLD%^%^BLACK%^You feel a burst of strength as you step into one powerful stroke of the sword!");
            tell_object(targ,"%^BOLD%^%^BLACK%^"+ETOQCN+" knocks you clean to the ground in one powerful stroke of the sword!");
            targ->set_paralyzed(15,"%^BOLD%^%^WHITE%^You are regaining your senses%^RESET%^.");
            break;

        case 601..800:

            set_property("magic",1);
            live = ETO->query_attackers();
            live = filter_array(live, "is_non_immortal", FILTERS_D);

            tell_object(ETO,"%^BOLD%^%^BLUE%^You send forward a shockwave, assaulting all who stand before you!");
            tell_room(EETO,"%^BOLD%^%^BLUE%^"+ETOQCN+" sends forward a shockwave, assaulting all who stand before it!",ETO);
            for(i=0;sizeof(live),i<sizeof(live);i++)
            {
                if(!objectp(live[i])) continue;
                if(live[i] == ETO) continue;
                tell_object(live[i],"%^BOLD%^%^BLUE%^Suddenly a wave of forc engulfs you!");
                live[i]->do_damage("torso",random(60)+60);
                remove_property("magic");
            }
            break;

        case 801..849:

            tell_room(EETO,"%^BOLD%^%^WHITE%^"+ETOQCN+" spins and slaps the blade against "+targ->QCN+"'s head!",({ETO,targ}));
            tell_object(ETO,"%^BOLD%^%^WHITE%^You slap your blade against "+targ->QCN+"'s head!");
            tell_object(targ,"%^BOLD%^%^WHITE%^"+ETOQCN+" slaps the blade against your head, concussing you!");
            targ->do_damage("torso",roll_dice(6,10));
            break;

        case 850..949:

            tell_room(EETO,"%^BOLD%^%^GREEN%^"+ETOQCN+" rolls to the side of "+targ->QCN+" and cuts across the back!",({ETO,targ}));
            tell_object(ETO,"%^BOLD%^%^GREEN%^You roll to the side of your opponent and cut across the back!");
            tell_object(targ,"%^BOLD%^%^GREEN%^"+ETOQCN+" rolls to the side of you and cuts you across the back!");
            targ->do_damage("torso",roll_dice(6,10));
            break;

        case 950..999:

            tell_room(EETO,"%^RESET%^%^MAGENTA%^"+ETOQCN+" calls out for %^BOLD%^%^YELLOW%^JUSTICE%^RESET%^%^MAGENTA%^!",({ETO,targ}));
            tell_object(ETO,"%^RESET%^%^MAGENTA%^YOu feel the urge to deliver %^BOLD%^%^YELLOW%^justice!");
            tell_object(targ,"%^RESET%^%^MAGENTA%^"+ETOQCN+" calls out for JUSTICE while striking you!");
            targ->do_damage("torso",roll_dice(6,20));
            break;

        }
    }
    return roll_dice(2,10);
}
