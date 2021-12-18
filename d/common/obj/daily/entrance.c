#include <std.h>
#include <daemons.h>

inherit ROOM;

object *current_travelers = ({  });

string *query_current_travelers()
{
    return current_travelers;
}

string *add_traveler(object ob)
{
    current_travelers += ({ ob });
    
    return current_travelers;
}

string *remove_traveler(object ob)
{
    current_travelers -= ({ ob });
    
    return current_travelers;
}

void create()
{   
    ::create();
    set_property("indoors",1);
    set_property("light",1);
    set_property("no sticks",1);
    //set_no_clean(1);

    set_short("Entrance to the Demiplanes");
    set_long("%^RESET%^%^CRST%^%^C025%^Worn %^C130%^wo%^C124%^o%^C130%^de%^C124%^n %^C130%^pl%^C124%^a%^C130%^nk%^C124%^s %^C025%^line the floor of this laboratory, smooth and uneven from years of use. The center of the room is taken up by a mass of %^C111%^le%^C117%^vi%^C123%^ta%^C111%^ti%^C117%^ng %^C244%^stones%^C025%^, each marked with a softly %^C118%^gl%^C154%^ow%^C148%^in%^C118%^g s%^C154%^ig%^C148%^il %^RESET%^%^C025%^and floating near to its brethren in the vague impression of an %^C244%^archway%^C025%^. Faint %^C118%^te%^C154%^nd%^C148%^ri%^C118%^ls %^C154%^of %^C148%^en%^C118%^er%^C154%^gy %^C025%^pulse from the circle of sigils, drawn away to %^C023%^disappear %^RESET%^%^C025%^in the center, the air crackling with potential. %^C130%^Desks %^C025%^and %^C131%^bookshelves %^C025%^ring the rest of the room, covered in piles of notes on %^C229%^yellowing parchment %^C025%^and open %^C137%^tomes %^C025%^sprouting cloth bookmarks along their aged spines.%^CRST%^\n");
    set_smell("default","The air is full of a strange scent.");
    set_listen("default","You hear nothing but your own thoughts.");
    set_heart_beat(1);
    set_items(([
        ({"stones","archway"}):"%^RESET%^%^CRST%^%^C025%^The %^C244%^stones %^C025%^are small, about the size of a human fist. They %^C111%^h%^C117%^o%^C123%^v%^C111%^e%^C117%^r %^C025%^in the air in the shape of an arch, and seem to radiate a charge of potential. Each has been marked by one of several strange %^C118%^gl%^C154%^ow%^C148%^in%^C118%^g s%^C154%^ig%^C148%^il%^C118%^s%^C025%^.%^CRST%^",
        "desks":"%^RESET%^%^CRST%^%^C025%^These %^C130%^wooden desks %^C025%^have been covered in %^C137%^tomes%^C025%^, some left open while others sprout a collection of cloth bookmarks. There are %^C124%^singe marks %^C025%^on some of pieces of furniture, and some legs seem to have been completely replaced.%^CRST%^",
        ({"bookshelves","notes","tomes"}):"%^RESET%^%^CRST%^%^C025%^The entirety of these %^C131%^shelves %^C025%^have been utilized, either by %^C137%^books%^C025%^, stacks of %^C229%^notes%^C025%^, or odd pieces of %^C118%^c%^C154%^r%^C148%^y%^C118%^s%^C154%^t%^C148%^a%^C118%^l%^C025%^.%^CRST%^",
        ]));
    set_exits(([
        "east" : "/d/shadow/room/pass/pass23",
        ]));
}

void init()
{
    ::init();
    
    add_action("close", "close");
    add_action("open", "open");
}

void reset(){
    ::reset();
    if(!present("lopos")) new("/d/common/obj/daily/lopos")->move(TO);
}

int open(string str)
{
    object compiler;
    
    if(str != "demiplane")
    {
        write("Perhaps you'd like to <open demiplane> ?");
        return 1;
    }
    if(member_array(this_player(), current_travelers) >= 0)
    {
        write("You already have a demiplane open. Type <close demiplane> to close it.");
        return 1;
    }   
    if(this_player()->cooldown("daily demiplane") && !avatarp(this_player()))
    {
        write("You need to wait to open another demiplane. Type <cooldowns> to see your cooldowns.");
        return 1;
    }
    
    write("Initiating demiplane teleport...");
    
    if(catch(compiler = new("/d/common/obj/daily/compiler")))
    {
        write("Demiplane compile error!");
        return 1;
    }
    
    this_player()->set_property("demiplane compiler", compiler);
    compiler->compile_plane(this_player());
    add_traveler(this_player());
    //once per day
    if(!avatarp(this_player()))
        this_player()->add_cooldown("daily demiplane", 86400); //commented out for testing purposes
    
    return 1;
}

int close(string str)
{
    if(str != "demiplane")
    {
        write("Perhaps you'd like to <close demiplane> ?");
        return 1;
    }

    if(member_array(this_player(), current_travelers))
    {
        write("You don't have a demiplane open.");
        return 1;
    }
        
    write("Are you sure you want to close the demiplane? Your demiplane will collapse and cease to exist [y/n]: ");
    input_to("finish_leave");
    return 1;
}

int finish_leave(string str)
{   
    object compiler;
    
    if(str != "y" && str != "Y" && str != "yes" && str != "Yes")
    {
        write("You decide to leave the demiplane open.");
        return 1;
    }
    
    write("You decide to close the demiplane.");
    compiler = this_player()->query_property("demiplane compiler");
    
    if(objectp(compiler))
        compiler->destroy_plane(this_player());

    write("You close the demiplane.");
    
    return 1;
}

