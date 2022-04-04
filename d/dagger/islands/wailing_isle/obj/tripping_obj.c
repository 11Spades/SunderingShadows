// Chernobog (12/1/21)
// Magic Mushroom Trip

#include <std.h>
#include <daemons.h>
inherit OBJECT;

int timer, duration, goodtrip, choking;

void create(){
    ::create();
    set_name("tripping_obj");
    set_id(({"tripping_obj"}));
    set_weight(0);
    set_property("no animate",1);
    set_hidden(1);
    duration = 5;
    timer = 1;
    goodtrip = (random(4));
    choking = 0;
    set_heart_beat(1);
}

void init(){
    object tripping, victim;
    tripping = this_object();
    victim = environment(tripping);
    
    if(!objectp(tripping)) return;
    if(!objectp(victim)) return;
    if(!objectp(environment(victim))) return;
    if(!living(victim)) return;
    
    add_action("look_fun","look");
    add_action("who_fun","who");
    add_action("say_fun","say");
    
    ETO->set_property("tripping", 1);
}

void heart_beat(){
    object tripping, victim;
    tripping = this_object();
    victim = environment(tripping);
    
    if(!objectp(tripping)) return;
    if(!objectp(victim)) return;
    if(!objectp(environment(victim))) return;
    if(!living(victim)) return;
    
    if(timer != 6){
        timer++;
        return;
    }
    
    if(goodtrip){
        switch(random(7)){
            case 0 :
                tell_object(victim, "%^RESET%^%^CRST%^%^C226%^Everything looks %^C230%^bright%^C226%^, the colors %^C040%^v%^C046%^ib%^C040%^r%^C046%^an%^C040%^t %^C226%^and %^C212%^b%^C206%^ea%^C212%^u%^C206%^ti%^C212%^f%^C206%^ul%^C226%^. The world is lovely and you feel wrapped in %^C208%^warmth%^C226%^.%^CRST%^\n");
                break;
            case 1 :
                tell_object(victim, "%^RESET%^%^CRST%^%^C033%^The %^C045%^answers %^C033%^to all of life's problems float through your %^C039%^m%^C045%^i%^C039%^n%^C045%^d%^C033%^... they're %^C051%^perfect %^C033%^and %^C087%^beautiful%^C033%^, but just out of reach...%^CRST%^\n");
                break;
            case 2 :
                tell_object(victim, "%^RESET%^%^CRST%^%^C042%^Things sound and feel so %^C046%^i%^C082%^nt%^C076%^e%^C046%^n%^C082%^se%^C076%^l%^C046%^y%^C042%^, as if you've never truly experienced them before. It is a %^C226%^heady %^C042%^and %^C220%^exuberant %^C042%^experience, and you want so much more.%^CRST%^\n");
                break;
            case 3 :
                tell_object(victim, "%^RESET%^%^CRST%^%^C084%^Strange winds blow across your skin in a %^C044%^c%^C050%^om%^C038%^f%^C044%^o%^C050%^rt%^C038%^i%^C044%^n%^C050%^g b%^C038%^r%^C044%^e%^C050%^ez%^C038%^e%^C084%^, refreshing you.%^CRST%^\n");
                break;
            case 4 :
                tell_object(victim, "%^RESET%^%^CRST%^%^C226%^The colors around you seem to %^C230%^animate%^C226%^, swirling towards you in a %^C192%^g%^C228%^l%^C222%^e%^C192%^e%^C228%^f%^C222%^u%^C192%^l %^C228%^d%^C222%^a%^C192%^n%^C228%^c%^C222%^e%^C226%^. %^RESET%^C212%^Maybe they will be your %^C200%^friend%^C212%^!%^CRST%^\n");
                break;
            case 5 :
                tell_object(victim, "%^RESET%^%^CRST%^%^C208%^All is %^C196%^warmth %^C208%^and %^C202%^comfort%^C208%^, and completely relaxing. You could fall asleep right now and drift away into this %^C203%^pe%^C204%^ac%^C203%^ef%^C204%^ul %^C205%^bliss%^C208%^.%^CRST%^\n");
                break;
            case 6 :
                tell_object(victim, "%^RESET%^%^CRST%^%^C033%^You are amazed by an %^C045%^epiphany%^C033%^... everything is connected. You, nature, the very world around you, and the %^C039%^re%^C045%^v%^C039%^el%^C045%^a%^C039%^ti%^C045%^o%^C045%^n %^C033%^leaves you %^C051%^breathless%^C033%^.%^CRST%^\n");
                break;
        }
    }
    if(!goodtrip){
        switch(random(7)){
            case 0 :
                tell_object(victim, "%^RESET%^%^CRST%^%^C244%^It is %^C059%^dark%^C244%^, and what few lights you see glow with %^C196%^mal%^C199%^e%^C196%^vol%^C199%^e%^C196%^nce%^C244%^. You sense things watching from the %^C059%^shadows%^C244%^, waiting to %^C125%^spring %^C244%^and %^C124%^attack%^C244%^.%^CRST%^\n");
                break;
            case 1 :
                tell_object(victim, "%^RESET%^%^CRST%^%^C067%^Everything seems to %^C060%^blur %^C067%^in a dizzying spin that leaves you %^C076%^n%^C070%^a%^C064%^u%^C076%^s%^C070%^e%^C064%^o%^C076%^u%^C070%^s%^C067%^. Your stomach %^C065%^tightens%^C067%^, trying to rebel against you.%^CRST%^\n");
                break;
            case 2 :
                tell_object(victim, "%^RESET%^%^CRST%^%^C059%^All sound seems to grow %^C244%^faint %^C059%^and %^C244%^muted%^C059%^. You can hear your %^C124%^heartbeat %^C059%^racing, speeding up as sweat beads on your forehead.%^CRST%^\n");
                break;
            case 3 :
                tell_object(victim, "%^RESET%^%^CRST%^%^C058%^Something is %^C136%^cr%^C130%^a%^C136%^wl%^C130%^i%^C136%^ng %^C058%^all over your skin. You can't see it, but you can FEEL it, thousands of %^C059%^tiny little bodies %^C058%^swarming up and down your limbs.%^CRST%^\n");
                break;
            case 4 :
                tell_object(victim, "%^RESET%^%^CRST%^%^C065%^Ugh... it %^C084%^itches%^C065%^. Everything itches! It feels like a %^C072%^c%^C066%^r%^C072%^aw%^C066%^l%^C072%^in%^C066%^g %^C072%^wa%^C066%^v%^C072%^e %^C065%^washing up and down your body, driving you crazy!%^CRST%^\n");
                break;
            case 5 :
                tell_object(victim, "%^RESET%^%^CRST%^%^C060%^The shadows start to %^C244%^whisper%^C060%^, and they're getting %^C061%^louder%^C060%^, and %^C062%^LOUDER%^C060%^, until the noise breaks into %^C250%^l%^C255%^aug%^C250%^h%^C255%^te%^C250%^r%^C060%^, all of it directed at %^C196%^YOU%^C060%^.%^CRST%^\n");
                break;
            case 6 :
                tell_object(victim, "%^RESET%^%^CRST%^%^C065%^Everything seems to %^C071%^shift %^C065%^beneath your feet in a %^C072%^disgusting %^C066%^r%^C072%^o%^C066%^i%^C072%^l%^C066%^i%^C072%^n%^C066%^g %^C072%^wave%^C065%^, throwing you completely off balance.%^CRST%^\n");
                break;
        }
        switch(random(5)){
            case 0 :
                if(choking){
                    tell_object(victim, "%^RESET%^%^CRST%^%^C059%^The tenebrous %^C244%^tentacles %^C125%^w%^C124%^r%^C125%^i%^C124%^t%^C125%^h%^C124%^e %^RESET%^%^C059%^over your body, tightening their grip!%^CRST%^");
                    break;
                }
                tell_object(victim, "%^RESET%^%^CRST%^%^C059%^The %^C244%^shadows %^C059%^grow long, leaping out like %^C244%^tentacles %^C059%^and %^C124%^w%^C125%^r%^C124%^a%^C125%^p%^C124%^p%^C125%^i%^C124%^n%^C125%^g %^RESET%^%^C059%^around your throat!%^CRST%^");
                start_choke();
                break;
            case 1 :
                if(choking) end_choke();
                stab_fun();
                break;
            case 2 :
                if(choking) end_choke();
                attack_fun();
                break;
            case 3 :
                if(choking) end_choke();
                break;
            case 4 :
                if(choking) end_choke();
                break;
        }
    }
    
    timer = 1;
    duration--;
    if(duration < 0) end_trip();
    return;
}

void start_choke(){
    object victim;
    victim = environment(this_object());
    victim->set_static("spell interrupt", "%^RESET%^%^CRST%^%^C059%^The inky %^C244%^tentacles %^C059%^are tight about your throat!%^CRST%^");
    victim->set_property("spell interrupt", "%^RESET%^%^CRST%^%^C059%^The inky %^C244%^tentacles %^C059%^are tight about your throat!%^CRST%^");
    choking = 1;
    return;
}

void end_choke(){
    object victim;
    victim = environment(this_object());
    if(choking){
        victim->set_static("spell interrupt", 0);
        victim->remove_property("spell interrupt");
        choking = 0;
        tell_object(victim, "%^RESET%^%^CRST%^%^C059%^The %^C244%^tentacles %^C059%^finally %^C040%^r%^C046%^ele%^C040%^a%^C046%^s%^C040%^e %^C059%^you, slinking back into the pools of %^C244%^shadow%^C059%^.%^CRST%^");
    }
    return;
}

void stab_fun(){
    int max_hp, cur_hp;
    object tripping, victim;
    tripping = this_object();
    victim = environment(tripping);
    
    if(!objectp(tripping)) return;
    if(!objectp(victim)) return;
    
    max_hp = victim->query_max_hp();
    cur_hp = roll_dice(6, 6);
    tell_object(victim, "%^RESET%^%^CRST%^%^YELLOW%^Someone stabs you in the back!\n%^RED%^Hp: %^RESET%^"+cur_hp+"    "+(cur_hp*100/max_hp)+"%");
}

void attack_fun(){
    object *players, victim;
    object fake_player;
    
    victim = environment(this_object());
    players = filter_array(all_inventory(environment(victim)),"is_non_immortal_player",FILTERS_D);
    players -= ({victim});
    if (sizeof(players) <= 0) return;
    
    fake_player = players[random(sizeof(players))];
    tell_object(victim, "%^RESET%^%^CRST%^%^BOLD%^%^RED%^"+fake_player->QCN+" %^RESET%^%^CRST%^%^BOLD%^%^RED%^attacks you!%^RESET%^");
    return;
}

void end_trip(){
    object tripping, victim;
    tripping = this_object();
    victim = environment(tripping);
    
    end_choke();
    tell_object(victim, "\n%^RESET%^%^CRST%^%^C144%^Everything comes back into focus, and you feel more like yourself.%^CRST%^");
    victim->remove_property("tripping");
    tripping->remove();
    return;
}

int look_fun(string str){
    object victim;
    victim = environment(this_object());
    
    if(goodtrip){
        tell_object(victim, "%^RESET%^%^CRST%^%^C226%^The colors are %^C230%^bright %^C226%^and %^C046%^v%^C040%^i%^C046%^b%^C040%^r%^C046%^a%^C040%^n%^C046%^t %^C226%^and %^C212%^c%^C206%^he%^C212%^e%^C206%^rf%^C212%^u%^C206%^l%^C226%^!%^CRST%^");
        return 0;
    }
    
    if(str){
        tell_object(victim, "%^RESET%^%^CRST%^%^C059%^It seems strange and unfamiliar. And %^C124%^threatening%^C059%^...%^CRST%^");
        return 0;
    }
    tell_object(victim, "%^RESET%^%^CRST%^%^C060%^Everything is %^C244%^hazy%^C060%^, %^C059%^dark%^C060%^, and %^C061%^dreary%^C060%^. The ground seems to wiggle and writhe beneath you, putting you off balance. The longer you look at anything, the more %^C065%^foreign %^C060%^and %^C065%^disgusting %^C060%^it appears, oozing a strange %^C059%^black ichor %^C060%^that pools and spreads towards you...");
    return 1;
}

int who_fun(string str){
    if(goodtrip) return 0;
    
    tell_object(environment(this_object()), "%^BOLD%^%^GREEN%^--=< %^RESET%^There are %^BOLD%^%^RED%^0 %^RESET%^adventurers online! %^BOLD%^%^GREEN%^>=--\n%^BOLD%^%^BLACK%^No     -----    %^RED%^You                                     %^RESET%^%^BLUE%^It's...\n%^BOLD%^%^BLACK%^One    -----          %^RED%^Are                               %^RESET%^%^BLUE%^..all..\n%^RESET%^%^MAGENTA%^ likes %^BOLD%^%^BLACK%^-----                %^RED%^Completely                  %^RESET%^%^BLUE%^...your\n%^RESET%^%^MAGENTA%^ you   %^BOLD%^%^BLACK%^-----                             %^RED%^Alone          %^RESET%^%^BLUE%^.fault.\n\n");
    return 1;
}

int say_fun(string str){
    object victim;
    victim = environment(this_object());
    
    if(goodtrip) return 0;
    
    if(choking){
        tell_object(victim, "%^RESET%^%^CRST%^%^C059%^You try to speak but those %^C244%^tentacles %^C059%^squeeze even %^C196%^tighter%^C059%^...%^CRST%^");
        tell_room(environment(victim), "%^RESET%^%^MAGENTA%^"+victim->query_cap_name()+" %^RESET%^%^MAGENTA%^lets out a breathless %^BOLD%^%^BLACK%^gu%^RESET%^%^CYAN%^r%^BOLD%^%^BLACK%^gli%^RESET%^%^CYAN%^n%^BOLD%^%^BLACK%^g %^RESET%^%^MAGENTA%^noise...%^RESET%^", victim);
        return 1;
    }
    return 0;
}

int save_me(string file){ return 1;}
int is_invincible(){ return 1;}
int is_detectable(){ return 0;}

