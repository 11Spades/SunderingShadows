// updated cha bonus from the new system. Nienne, 09/07.
#include <std.h>
#include <daemons.h>
#include <magic.h>

inherit "/d/common/obj/weapon/whip.c";


void create()
{
    ::create();

    set_id(({"moonlit fire","whip","firewhip","whip of fiery moon","enrapture"}));

    set_name("%^BOLD%^%^RED%^En%^RESET%^%^RED%^r%^BOLD%^ap%^RESET%^%^RED%^t%^BOLD%^u%^RESET%^%^RED%^re%^RESET%^");

    set_obvious_short("%^RESET%^%^MAGENTA%^A %^CYAN%^hypnotically %^MAGENTA%^beautiful whip with long %^RED%^f%^BOLD%^i%^RESET%^%^RED%^e%^BOLD%^r%^RESET%^%^RED%^y str%^BOLD%^a%^RESET%^%^RED%^nds%^RESET%^");

    set_short("%^BOLD%^%^RED%^En%^RESET%^%^RED%^r%^BOLD%^ap%^RESET%^%^RED%^t%^BOLD%^u%^RESET%^%^RED%^re%^RESET%^");

    set_long("%^RESET%^%^CYAN%^The handle of this beautifully crafted whip has been encrusted with more"
        " %^RESET%^s%^BOLD%^h%^RESET%^i%^BOLD%^mm%^RESET%^er%^BOLD%^i%^RESET%^ng %^BOLD%^mo%^CYAN%^o%^WHITE%^n%^RESET%^s"
        "%^BOLD%^t%^CYAN%^o%^WHITE%^n%^RESET%^e%^BOLD%^s %^RESET%^%^CYAN%^and %^BOLD%^%^RED%^d%^RESET%^%^RED%^e%^BOLD%^"
        "e%^RESET%^%^RED%^p, %^BOLD%^ruby red %^RESET%^%^RED%^f%^BOLD%^i%^RESET%^%^RED%^re op%^BOLD%^a"
        "%^RESET%^%^RED%^ls %^CYAN%^than"
        " a person could ever hope to count.  Woven around each of the gems in an %^MAGENTA%^intricate pattern %^CYAN%^of"
        " %^RED%^hearts %^CYAN%^and %^MAGENTA%^trellises%^CYAN%^, a single strand of %^MAGENTA%^exotic %^YELLOW%^g%^RESET%^"
        "%^ORANGE%^o%^YELLOW%^ld%^RESET%^%^ORANGE%^e%^YELLOW%^n lace %^RESET%^%^CYAN%^weaves its way from the tip of the"
        " handle to the base.  Extending from the handle, the whip itself is composed of several %^RESET%^s%^BOLD%^i%^RESET%^"
        "lky tend%^BOLD%^r%^RESET%^ils %^CYAN%^that are deceptively %^MAGENTA%^beautiful %^CYAN%^in appearance.  Ranging from"
        " an %^RESET%^o%^BOLD%^pa%^RESET%^le%^BOLD%^sce%^RESET%^nt s%^BOLD%^i%^RESET%^lv%^BOLD%^e%^RESET%^r"
        " %^CYAN%^resembling the finest of the %^BOLD%^%^WHITE%^moons rays %^RESET%^%^CYAN%^on a %^MAGENTA%^magical"
        " %^BOLD%^%^BLACK%^e%^RESET%^%^MAGENTA%^v%^BOLD%^%^BLACK%^en%^RESET%^%^MAGENTA%^i%^BOLD%^%^BLACK%^ng"
        " %^RESET%^%^CYAN%^to the %^BOLD%^%^RED%^d%^RESET%^%^RED%^ee%^BOLD%^p%^RESET%^%^RED%^est of reds %^CYAN%^found"
        " in the finest %^RED%^s%^BOLD%^i%^RESET%^%^RED%^lks%^CYAN%^, the colors of each of the twelve strands seem to"
        " dance with their own %^MAGENTA%^magnetic beauty.  %^CYAN%^Both %^BOLD%^enchanting %^RESET%^%^CYAN%^and"
        " %^MAGENTA%^hypnotic %^CYAN%^at once, this whip has obviously been a collaborative effort of many talented"
        " %^MAGENTA%^artisans.%^RESET%^");

    set_lore("%^RESET%^%^RED%^This whip is said to be wielded only by those favored by Lady Firehair, and only those fair enough to be worthy of such a blessing.");

    set_value(100000);

    set_property("no curse",1);
    set_property("enchantment",7);

    set_wield((:TO,"wield_func":));
    set_hit((:TO,"hit_func":));

    set_item_bonus("charisma",6);
    set_item_bonus("damage bonus",7);

    set_property("quest required","%^BOLD%^%^RED%^Defeated the great red wyrm Klauth!%^RESET%^");
    set_property("level required",35);

}


int wield_func()
{
    if((int)ETO->query_stats("charisma") < 14)
    {
        tell_object(ETO,"%^RESET%^%^RED%^Disappointment overcomes you as you realize you cannot yet master such a fine weapon.");
            return 0;
    }

    tell_room(EETO,"%^RESET%^%^RED%^"+ETOQCN+" seems to become even more attractive as "+ETO->QS+" wraps "+ETO->QO+" slender fingers around the handle of the whip.%^RESET%^",ETO);
    tell_object(ETO,"%^RESET%^%^RED%^You can't help but to feel more sensual and calm as your fingers wrap around the beautiful whip.%^RESET%^");
    return 1;
}


int hit_func(object targ)
{
    int i;
    object *weapons;
    string *ids;

    if(!objectp(targ)) { return 1; }

    if(random(1000) < 500)
    {
        switch(random(10))
        {
        case 0..3:

            tell_room(EETO,"%^RESET%^%^RED%^"+ETO->QCN+" raises the whip in "+ETO->QO+" hand above "+ETO->QO+" head and swings it around in a graceful, hypnotic arch before snapping it quickly forward, causing each of its twelve strands to inflict a shower of grevious wounds upon "+targ->QCN+"!%^RESET%^",({targ,ETO}));
            tell_object(ETO,"%^RESET%^%^RED%^You bring the whip in your hand above your head and swing it around in a graceful, hypnotic arch before snapping it quickly forward, causing each of its twelve strands to inflict a shower of grevious wounds upon "+targ->QCN+"!%^RESET%^",targ);
            tell_object(targ,"%^RESET%^%^RED%^"+ETO->QCN+" raises the whip in "+ETO->QO+" hand above "+ETO->QO+" head and swings it around in a graceful, hypnotic arch before snapping it quickly forward, causing each of its twelve strands to inflict a shower of grevious wounds upon you!%^RESET%^");
            return roll_dice(8,8)+20;

        case 4..6:

            tell_room(EETO,"%^RESET%^%^BLUE%^"+ETOQCN+" lashes out at "+targ->QCN+" and wraps the twelves strands around "+targ->QO+" wrist, spinning "+targ->QO+" around... "+ETOQCN+" quickly strikes the now exposed back!",({targ,ETO}));
            tell_object(ETO,"%^RESET%^%^BLUE%^You lash out at "+targ->QCN+" and wrap all twelve strands around "+targ->QO+" wrist and spin "+targ->QO+" around... Then you quickly strike the now exposed back!",targ);
            tell_object(targ,"%^RESET%^%^BLUE%^"+ETOQCN+" lashes out at you and wraps all twelve strands of the whip around your wrist, spinning you around... and then quickly strikes at your now exposed back!");
            return roll_dice(8,8)+20;

        case 7:

            tell_room(EETO,"%^RESET%^%^CYAN%^"+ETOQCN+" cracks the whip with a smooth snap of the wrist then tries to relieve "+targ->QCN+" of "+targ->QO+" weapon!",({targ,ETO}));
            tell_object(ETO,"%^RESET%^%^CYAN%^You crack the whip with a smooth snap of the wrist then do your best to disarm "+targ->QCN+"!",targ);
            tell_object(targ,"%^RESET%^%^CYAN%^"+ETOQCN+" cracks the whip with a smooth snap of the wrist then tries to disarm you!");

            weapons = targ->query_wielded();

            for (i=0;i<sizeof(weapons);i++)
            {
                ids = weapons[i]->query_id();
                targ->force_me("unwield "+ids[0]);
                targ->remove_property("disarm time");
                targ->set_property("disarm time",time()+(ROUND_LENGTH*roll_dice(1,4)));
            }

        case 8..9:

            tell_room(EETO,"%^RESET%^%^MAGENTA%^As "+ETOQCN+" swings the whip towards "+targ->QCN+", it begins to glow soothingly, leaving "+targ->QO+" standing there unmoving.",({targ,ETO}));
            tell_object(ETO,"%^RESET%^%^MAGENTA%^As you swing the whip towards "+targ->QCN+", it begins to glow soothingly, leaving "+targ->QO+" standing there unmoving.%^RESET%^",targ);
            tell_object(targ, "%^RESET%^%^MAGENTA%^As "+ETOQCN+" swings the whip towards you, it begins to glow soothingly, leaving the image of "+ETO->query_name()+"'s seductive eyes burnt in your mind.");
            targ->set_paralyzed(20,"%^BOLD%^%^MAGENTA%^You cant get the image of those eyes out of your mind.");
            return roll_dice(2,4)+20;
        }
    }
}
