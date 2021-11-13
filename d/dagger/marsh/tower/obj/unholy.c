// fixed wear/unwear to use ETO, added obvious short-last change was 7/01  *Styx* 8/2003
// Updated to new desc, abilities, lore, etc by Circe 9/6/04
// Additions of specific creatures for each god. Nienne, 2/05 //
// Added Auppenser and Kelemvor - Cythera 8/05
// Updated to include new pantheon - Chernobog 11/5/21

#include <std.h>
#include <daemons.h>
inherit "/d/common/obj/weapon/longsword.c";

#define AIDTIME 120
#define DISPELTIME 120

int aid_time;
int dispel_time;

object owned;

void init(){
    ::init();
    if(interactive(ETO) && !owned) owned = ETOQN;
    add_action("heal_em","aid");
    add_action("dispel_em","disrupt");
}

void create(){
    ::create();
    set_name("avenger");
    set_id(({"unholy avenger","avenger","sword"}));
    set_obvious_short("%^BOLD%^%^BLACK%^A flawless darkened sword%^RESET%^");
    set_short("%^BOLD%^%^BLACK%^Unholy Avenger%^RESET%^");
    set_long("%^BOLD%^%^BLACK%^A palpable presence of %^RESET%^%^GREEN%^malignancy %^BOLD%^%^BLACK%^arises from this frightening weapon.  Over six feet in length, the blade appears to be composed of %^GREEN%^souls %^BLACK%^tempered into a metallic form.  They writhe and twist in a sickening %^RESET%^%^RED%^dance %^BOLD%^%^BLACK%^as waves of spirit essence climb in a spiral across the blade.  The blade holds a wickedly %^WHITE%^gleaming edge %^BLACK%^while the forms of the souls continuously shape into %^RED%^barbs %^BLACK%^as they lash out with their own %^WHITE%^teeth %^BLACK%^and %^RED%^talons%^BLACK%^.  Multitudes of precious colorless gems %^BLACK%^are seamlessly joined together as the hilt, with two protrusions of colorless gems %^BLACK%^curved out into crosspieces.  Slick with fresh %^RED%^blood%^BLACK%^, the hilt appears dangerous to handle.%^RESET%^");
    set_lore("Created as a mocking answer to the swords wielded by holy paladins, the swords known as the unholy avengers were commissioned originally by the archlich Vecna during the last stages of what most consider his true life.  In his quest to gain eternal life, the archmage Vecna met a 'noble' paladin of Helm named Jairus who stood against Vecna's interest in necromancy.  After much toil and a battle lasting many years, Vecna finally stripped the Holy Avenger from the paladin's lifeless body and cackled as he returned to his lab.  When he reemerged two years later, the first Unholy Avenger was in his hands.");
    set_read(
@CIRCE
    %^BOLD%^%^BLACK%^The blackened heart may ask for %^BLUE%^aid
    %^BLACK%^When blood has seaped along your blade
  The holy one's magic you may call to %^RED%^disrupt
 %^BLACK%^So long as your heart is truly corrupt
  The wicked warrior may send forth a %^YELLOW%^call
     %^WHITE%^To summon a mount, the bane of all
CIRCE
    );
    set_weight(15);
    set_size(2);
    set_value(10000);
    set_wc(1,8);
    set_large_wc(1,12);
    set_type("slashing");
    if((int)TO->query_property("enchantment") < 5){
        remove_property("enchantment");
        set_property("enchantment",5);
    }
    set_item_bonus("sight bonus",2);
    set_prof_type("medium blades");
    set_wield((:TO,"paladin":));
    set_unwield((:TO,"removeme":));
    set_hit((:TO,"extra_hit":));
    set_heart_beat(1);
}

int paladin(){
    string god;
    string GEM;
    object player;
    player = environment(this_object());
    player && god = player->query_deity();
  
    if(!player) return 0;
    switch(god){
        case "lysara" :
            GEM = "%^RESET%^%^CRST%^%^C250%^m%^C255%^o%^C250%^o%^C045%^n%^C250%^st%^C051%^o%^C045%^n%^C250%^e%^CRST%^%^RESET%^";
            break;
        case "kreysneothosies" :
            GEM = "%^RESET%^%^CRST%^%^C027%^s%^C021%^ap%^C027%^p%^C021%^hi%^C027%^r%^C021%^e%^CRST%^%^RESET%^";
            break;
        case "kismet" :
            GEM = "%^RESET%^%^CRST%^%^C084%^peridot%^CRST%^%^RESET%^";
            break;
        case "jarmila" :
            GEM = "%^RESET%^%^CRST%^%^C196%^ru%^C197%^b%^C196%^y%^CRST%^%^RESET%^";
            break;
        case "lord_shadow" :
            GEM = "%^RESET%^%^CRST%^%^C244%^on%^C250%^y%^C244%^x%^CRST%^%^RESET%^";
            break;
        case "nimnavanon" :
            GEM = "%^RESET%^%^CRST%^%^C226%^a%^C220%^m%^C214%^b%^C220%^e%^C226%^r%^CRST%^%^RESET%^";
            break;
        case "callamir" :
            GEM = "%^RESET%^%^CRST%^%^C045%^a%^C051%^qua%^C045%^m%^C051%^ari%^C045%^n%^C051%^e%^CRST%^%^RESET%^";
            break;
        case "cevahir" :
            GEM = "%^RESET%^%^CRST%^%^C105%^a%^C099%^met%^C105%^h%^C099%^ys%^C105%^t%^CRST%^%^RESET%^";
            break;
        case "khyron" :
            GEM = "%^RESET%^%^CRST%^%^C059%^obs%^C244%^i%^C059%^dia%^C244%^n%^CRST%^%^RESET%^";
            break;
        case "nilith" :
            GEM = "%^RESET%^%^CRST%^%^C124%^blo%^C126%^o%^C124%^dsto%^C126%^n%^C124%^e%^CRST%^%^RESET%^";
            break;
        case "seija" :
            GEM = "%^RESET%^%^CRST%^%^C034%^e%^C040%^m%^C046%^er%^C040%^a%^C046%^l%^C040%^d%^CRST%^%^RESET%^";
            break;
        case "the_faceless_one" :
            GEM = "%^RESET%^%^CRST%^%^C250%^s%^C244%^m%^C250%^o%^C255%^k%^C250%^y %^C244%^q%^C250%^u%^C255%^a%^C250%^r%^C244%^t%^C250%^z%^CRST%^%^RESET%^";
            break;
        default :  GEM = "colorless gem";
            break;
    }
    if(!player->is_class("paladin") && !player->is_class("inquisitor") && !player->is_class("cleric"))
    {
        tell_object(player,"You may not wield this weapon!");
        return 0;
    }
    if((int)player->query_true_align() != 3 && (int)player->query_true_align() != 2 && (int)player->query_true_align() != 5 && (int)player->query_true_align() != 6) {
        tell_object(ETO,"You may not wield this weapon!");
        return 0;
    }
    if((string)ETOQN != owned && (string)ETOQN != "angel") {
        tell_object(ETO,"The sword fails to bond with you and vanishes!");
        TO->remove();
        return 0;
    }
    if((int)ETO->query_level() < 25) {
        tell_object(ETO,"You are too inexperienced to wield this weapon!");
        return 0;
    }
    tell_object(ETO,"%^BOLD%^%^BLACK%^The %^GREEN%^souls %^BLACK%^trapped in the blade shriek and the gems %^B_RED%^%^WHITE%^%^FLASH%^flash %^RESET%^%^BOLD%^%^BLACK%^into "+GEM+" %^BOLD%^%^BLACK%^as you wield the blade!\n%^BOLD%^%^RED%^You feel an unholy aura encompass you!");
    tell_room(EETO, "%^BOLD%^%^BLACK%^The %^GREEN%^souls %^BLACK%^trapped in the blade shriek and the gems %^B_RED%^%^WHITE%^%^FLASH%^flash %^RESET%^%^BOLD%^%^BLACK%^ into "+GEM+" %^BOLD%^%^BLACK%^as "+ETOQCN+" %^BOLD%^%^BLACK%^wields the blade!",ETO);
    set_long("%^BOLD%^%^BLACK%^A palpable presence of %^RESET%^%^GREEN%^malignancy %^BOLD%^%^BLACK%^arises from this frightening weapon.  Over six feet in length, the blade appears to be composed of %^GREEN%^souls %^BLACK%^tempered into a metallic form.  They writhe and twist in a sickening %^RESET%^%^RED%^dance %^BOLD%^%^BLACK%^as waves of spirit essence climb in a spiral across the blade.  The blade holds a wickedly %^WHITE%^gleaming edge %^BLACK%^while the forms of the souls continuously shape into %^RED%^barbs %^BLACK%^as they lash out with their own %^WHITE%^teeth %^BLACK%^and %^RED%^talons%^BLACK%^.  Multitudes of precious "+GEM+" gems %^BLACK%^are seamlessly joined together as the hilt, with two protrusions of "+GEM+" gems %^BLACK%^curved out into crosspieces.  Slick with fresh %^RED%^blood%^BLACK%^, the hilt appears dangerous to handle.%^RESET%^");
    ETO->set_property("evil item",1);
    return 1;
}

int removeme(){
    string god = ETO->query_diety();
    string GEM;
    switch(god){
        case "lysara" :
            GEM = "%^RESET%^%^CRST%^%^C250%^m%^C255%^o%^C250%^o%^C045%^n%^C250%^st%^C051%^o%^C045%^n%^C250%^e%^CRST%^%^RESET%^";
            break;
        case "kreysneothosies" :
            GEM = "%^RESET%^%^CRST%^%^C027%^s%^C021%^ap%^C027%^p%^C021%^hi%^C027%^r%^C021%^e%^CRST%^%^RESET%^";
            break;
        case "kismet" :
            GEM = "%^RESET%^%^CRST%^%^C084%^peridot%^CRST%^%^RESET%^";
            break;
        case "jarmila" :
            GEM = "%^RESET%^%^CRST%^%^C196%^ru%^C197%^b%^C196%^y%^CRST%^%^RESET%^";
            break;
        case "lord_shadow" :
            GEM = "%^RESET%^%^CRST%^%^C244%^on%^C250%^y%^C244%^x%^CRST%^%^RESET%^";
            break;
        case "nimnavanon" :
            GEM = "%^RESET%^%^CRST%^%^C226%^a%^C220%^m%^C214%^b%^C220%^e%^C226%^r%^CRST%^%^RESET%^";
            break;
        case "callamir" :
            GEM = "%^RESET%^%^CRST%^%^C045%^a%^C051%^qua%^C045%^m%^C051%^ari%^C045%^n%^C051%^e%^CRST%^%^RESET%^";
            break;
        case "cevahir" :
            GEM = "%^RESET%^%^CRST%^%^C105%^a%^C099%^met%^C105%^h%^C099%^ys%^C105%^t%^CRST%^%^RESET%^";
            break;
        case "khyron" :
            GEM = "%^RESET%^%^CRST%^%^C059%^obs%^C244%^i%^C059%^dia%^C244%^n%^CRST%^%^RESET%^";
            break;
        case "nilith" :
            GEM = "%^RESET%^%^CRST%^%^C124%^blo%^C126%^o%^C124%^dsto%^C126%^n%^C124%^e%^CRST%^%^RESET%^";
            break;
        case "seija" :
            GEM = "%^RESET%^%^CRST%^%^C034%^e%^C040%^m%^C046%^er%^C040%^a%^C046%^l%^C040%^d%^CRST%^%^RESET%^";
            break;
        case "the_faceless_one" :
            GEM = "%^RESET%^%^CRST%^%^C250%^s%^C244%^m%^C250%^o%^C255%^k%^C250%^y %^C244%^q%^C250%^u%^C255%^a%^C250%^r%^C244%^t%^C250%^z%^CRST%^%^RESET%^";
            break;
        default :  GEM = "colorless gem";
            break;
    }
    tell_object(ETO,"%^BOLD%^%^BLACK%^You hear soft sighs as you unwield the sword and watch the "+GEM+" gems lose all color once more.");
    tell_room(EETO, "%^BOLD%^%^BLACK%^A wind whips through the area as "+ETOQCN+" lowers "+ETO->QP+" sword and the gems in the hilt lose their color.",ETO);
    set_long("%^BOLD%^%^BLACK%^A palpable presence of %^RESET%^%^GREEN%^malignancy %^BOLD%^%^BLACK%^arises from this frightening weapon.  Over six feet in length, the blade appears to be composed of %^GREEN%^souls %^BLACK%^tempered into a metallic form.  They writhe and twist in a sickening %^RESET%^%^RED%^dance %^BOLD%^%^BLACK%^as waves of spirit essence climb in a spiral across the blade.  The blade holds a wickedly %^WHITE%^gleaming edge %^BLACK%^while the forms of the souls continuously shape into %^RED%^barbs %^BLACK%^as they lash out with their own %^WHITE%^teeth %^BLACK%^and %^RED%^talons%^BLACK%^.  Multitudes of precious colorless gems %^BLACK%^are seamlessly joined together as the hilt, with two protrusions of colorless gems %^BLACK%^curved out into crosspieces.  Slick with fresh %^RED%^blood%^BLACK%^, the hilt appears dangerous to handle.%^RESET%^");
   ETO->set_property("evil item",-1);
   return 1;
}

void failure(){
   tell_object(ETO,"The sword must regain its power before it can attempt that again.");
   return 1;
}

int extra_hit(){
    object ob;
    int dam,FLAG,align;
    FLAG = 0;
    ob=ETO->query_current_attacker();
    align = ob->query_alignment();
    if(!objectp(ob)) return random(5);
    if(random(6) > 3) return 1;
    if(random(100)>40){
        if(align == 7 || align == 4 || align == 1) {
            FLAG = 1;
            dam = dam + random(5) + 1;
        }
        else{
            dam = dam + random(2) - random(2);
        }
    }
    if(random(100) > 50) {
        dam = dam + random(6) + 2;
    }
    else{
        dam = dam + random(3) + 1;
    }
    switch(random(30)){
        case 0..19 :
            tell_object(ETO,"%^BOLD%^%^BLACK%^The sword channels your %^RED%^unholy energy%^BLACK%^ into its swing!\n%^BOLD%^%^RED%^A bright %^GREEN%^flash%^RED%^ is seen as you slash at "+ob->QCN+"!%^RESET%^");
            if(FLAG == 1){
                tell_object(ETO,"\n%^BOLD%^%^RED%^The Avenger tells you: I detect the weakness of a good soul in our foe.%^RESET%^\n%^RED%^"+ob->QCN+" screams as the avenger sinks into "+ob->QP+" holy flesh!%^RESET%^");
                FLAG = 0;
            }
            tell_room(EETO,"%^BOLD%^%^BLACK%^The sword wielded by "+ETOQCN+" %^RED%^echoes %^BLACK%^with the voices of the hells!\n%^BOLD%^%^RED%^A bright %^GREEN%^flash%^RED%^ is seen as "+ETOQCN+" slashes at "+ob->QCN+"!%^RESET%^",({ETO,ob}));
            tell_object(ob,"%^BOLD%^%^BLACK%^The sword wielded by "+ETOQCN+" %^RED%^echoes %^BLACK%^with the voices of the hells!\n%^BOLD%^%^RED%^A bright %^GREEN%^flash%^RED%^ is seen as "+ETOQCN+" slashes at you!%^RESET%^");
            break;
        case 20..28 :
            tell_object(ETO,"%^BOLD%^%^BLACK%^The %^GREEN%^souls %^BLACK%^in your sword call fervently to "+capitalize(ETO->query_diety())+" and draw their gaze to you!\n%^RED%^A voice utters%^RESET%^: Be well, my warrior.\n%^BOLD%^%^RED%^You see the souls' barbs steal "+ob->QCN+"'s life away!");
            tell_object(ob,"%^BOLD%^%^GREEN%^The barbs on "+ETOQCN+"'s sword pierce you and steal your life away!");
            tell_room(EETO,"%^BOLD%^%^BLACK%^"+ETOQCN+" strikes "+ob->QCN+" as the %^GREEN%^souls %^BLACK%^within "+ETO->QP+" sword sprout %^RED%^barbs%^BLACK%^!",({ob,ETO}));
            ETO->add_hp(dam);
            break;
        case 29 :
            tell_object(ETO,"%^BOLD%^%^BLACK%^The sword begins to vibrate in your hands, then sends forth a %^BLUE%^cloud of pure malevolence %^BLACK%^at "+ob->QCN+"!");
            tell_object(ob,"%^BOLD%^%^BLACK%^"+ETOQCN+" points the sword at you, and an %^BLUE%^inky black cloud %^BLACK%^rolls over you!");
            tell_room(EETO,"%^BOLD%^%^BLACK%^"+ETOQCN+" points the sword at "+ob->QCN+", causing an %^BLUE%^inky black cloud %^BLACK%^to roll over "+ob->QO+"!",({ETO,ob}));
            if(random(22) > (int)ob->query_stats("constitution")){
                ob->set_blind(1);
            }
            break;
      default:  break;
    }
    return dam;
}

void heart_beat(){
    object *live;
    object targ;
    int align, i, counter;
    if(!objectp(TO)) return;
    if(!objectp(ETO)) return;
    if(!living(ETO)) return;
    if(!objectp(EETO)) return;
    live = all_living(EETO);
    live = filter_array(live, "is_non_immortal_player", FILTERS_D);
    if(TO->query_wielded()){
        if(!random(20)){
            for(i=0;i<sizeof(live);i++){
                targ = live[i];
                if(!objectp(targ)) continue;
                align = targ->query_alignment();
                if((align == 1) || (align == 4) || (align == 7)){
                    tell_object(ETO,"%^BOLD%^%^BLACK%^Your sword darkens as it senses the presence of a good heart.");
                    tell_room(EETO,"%^BOLD%^%^BLACK%^The sword held by "+ETOQCN+" darkens.",ETO);
                    continue;
                }
            }
        }
    }
}

int heal_em(string str){
    object ob;
    if (ETO->query_bound() || ETO->query_unconscious() || ETO->query_paralyzed()) {
        ETO->send_paralyzed_message("info",ETO);
    }
    if(!str){
        tell_object(ETO,"You may ask your deity for aid through your sword - <aid me>");
        return 1;
    }
    if(!TO->query_wielded()){
        tell_object(ETO,"You must be wielding the sword to call on its power.");
        return 1;
    }
    if(AIDTIME > (time() - aid_time)) {
        failure();
        return 1;
    }
    if(str == "me"){
        aid_time = time();
        tell_object(ETO,"%^BOLD%^%^BLACK%^You hear whispering voices as the souls swirl and you feel your wounds heal.");
        tell_room(EETO,"%^BOLD%^%^BLACK%^The souls in "+ETOQCN+"'s sword swirl and whisper.",ETO);
        ETO->set_hp(ETO->query_max_hp());
        ETO->heal(1);
        return 1;
    }
    tell_object(ETO,"You may only ask the sword to <aid me>.");
    return 1;
}

int dispel_em(string str){
    object ob;
    if (ETO->query_bound() || ETO->query_unconscious() || ETO->query_paralyzed()) {
        ETO->send_paralyzed_message("info",ETO);
    }
    if(!str){
        tell_object(ETO,"You may ask your sword to <disrupt target>.");
        return 1;
    }
    if(!TO->query_wielded()){
        tell_object(ETO,"You must be wielding the sword to call on its power.");
        return 1;
    }
    if(!(ob = present(str, ETP))) return notify_fail("You do not see that!\n");
    if(DISPELTIME > (time() - dispel_time)) {
        failure();
        return 1;
    }
    dispel_time = time();
    tell_room(EETO,"%^BOLD%^%^BLACK%^"+ETOQCN+" sneers as "+ETO->QS+" turns to face "+ob->QCN+" and utters a dark command!",ETO);
    tell_object(ETO,"%^BOLD%^%^BLACK%^You face "+ob->QCN+" with a sneer and utter the dark command of "+capitalize(ETO->query_diety())+"!");
    new("/cmds/spells/d/_dispel_magic")->use_spell(TP,ob,45,100,"cleric");
    TP->set_paralyzed(3,"You are channelling your deity through the sword!");
    return 1;
}

