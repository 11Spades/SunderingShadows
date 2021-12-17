/*
  compiler.c
  
  Uses my basic compiler to create a virtual zone.
  Next iteration of alternative reality quest.
  
  -- Tlaloc -- 9.19.21
*/

/*
  This is, in my opinion, a simpler method of implementing an
  alternate reality kind of quest.
  
  The idea here is that, in the entrance room, a command exists to
  clone a compiler for that character and use it to build and destroy
  the plane.
  
  Essentially, this is a virtual object that clones a virtual area.
*/

/* This system consists of several components:
   -- This compiler object, which creates the rooms, adds the exits, and places monsters.
      ->This object is a clone specific to the player using the demiplane.
   -- The entrance room, or hub, where the player initiates the creation of the demiplane.
   -- The quest item, which is the goal of the player. This will be placed on a boss monster.
      ->When picked up, it will move the player to the hub and destroy the plane.
   -- The boss monster, which will be holding the said quest item.
*/

#include <daemons.h>
#include <security.h>

//X and Y Axis Limits
#define MAX_WIDTH 3
#define MAX_HEIGHT 10
#define PATH "/d/common/obj/daily/"
#define THEMES ({ "clockwork", "offal marsh", "deep caverns", "feywild" })

//rename_object() or compile() would have been the ideal method
//to do this. Without those funs, we will use a mapping instead.

mapping cloned_rooms;
       
string dest_room;
string *monsters_to_use;

void compile_plane(object owner)
{
    int x;
    string key, exit_key, short, long, theme;
    object room;
    
    if(!userp(owner))
        owner = previous_object();
    if(!userp(owner))
    {
        write("Owner identification failed!");
        return;
    }
    
    x = 0;
    cloned_rooms = ([  ]);

    short = get_room_short();
    //This gives us a list of filenames for monsters, based on level
    monsters_to_use = shuffle(CHAMPION_D->retrieve_monster_list(owner->query_level()));
    monsters_to_use = monsters_to_use[0..5];
    
    if(!sizeof(monsters_to_use))
    {
        write("Monster list compile fail...");
        return;
    }

    //Determine the demiplane theme
    theme = THEMES[random(sizeof(THEMES))];
    
    //Clone the rooms, clone the monsters
    while(get_eval_cost() > 10000 && x < MAX_WIDTH)
    {
        for(int y = 0; y < MAX_HEIGHT; y++)
        {
            key = (string)x + "x" + (string)y;
            
            if(load_object(PATH + key))
                room = find_object(PATH + key);
            else
                room = clone_object(PATH + "base_room");
            
            cloned_rooms += ([ key : room, ]);
                     
            if(!objectp(room))
            {
                write("Adding room failed: ["+x+"] ["+y+"]");
                //write("Adding room : " + file_name(room) + " to ["+x+"]["+y+"]");
                continue;
            }
            
            long = get_room_long(theme);
            short = get_room_short(theme);
            room->set_short(short);
            room->set_long(long);
            room->set_owner(owner);
            room->set_compiler(this_object());
            
            
            if(!place_monsters(x, y, theme, owner))
                continue;
        }
        x++;       
    }
  
    x = 0;

    write("Adding room exits...");
    
    //Arrange exits
    while(get_eval_cost() > 10000 && x < MAX_WIDTH)
    {
        if(!sizeof(cloned_rooms))
        {
            write("No mapping size");
            return;
        }
        
        for(int y = 0; y < MAX_HEIGHT; y++)
        {
            key = (string)x + "x" + (string)y;
        
            if(objectp(cloned_rooms[key]))
            {
            
                //write("Attempting to add exits to " + file_name(cloned_rooms[key]));
        
                //North
                if(y < MAX_HEIGHT - 1)
                {
                    exit_key = (string)x + "x" + (string)(y + 1);
                    if(load_object(PATH + exit_key))
                        dest_room = PATH + exit_key;
                    else
                        objectp(cloned_rooms[exit_key]) && dest_room = file_name(cloned_rooms[exit_key]);
                    
                    dest_room && cloned_rooms[key]->add_exit(dest_room, "north");
                }

                //South
                if(y > 0)
                {
                    exit_key = (string)x + "x" + (string)(y - 1);
                    if(load_object(PATH + exit_key))
                        dest_room = PATH + exit_key;
                    else
                        objectp(cloned_rooms[exit_key]) && dest_room = file_name(cloned_rooms[exit_key]);
                    
                    dest_room && cloned_rooms[key]->add_exit(dest_room, "south");
                }
        
                //East
                if(x < MAX_WIDTH - 1)
                {
                    exit_key = (string)(x + 1) + "x" + (string)y;
                    if(load_object(PATH + exit_key))
                        dest_room = PATH + exit_key;
                    else
                        objectp(cloned_rooms[exit_key]) && dest_room = file_name(cloned_rooms[exit_key]);
                    
                    dest_room && cloned_rooms[key]->add_exit(dest_room, "east");
                }

                //West
                if(x > 0)
                {
                    exit_key = (string)(x - 1) + "x" + (string)y;
                    if(load_object(PATH + exit_key))
                        dest_room = PATH + exit_key;
                    objectp(cloned_rooms[exit_key]) && dest_room = file_name(cloned_rooms[exit_key]);
                    
                    dest_room && cloned_rooms[key]->add_exit(dest_room, "west");
                }
        
                if(!sizeof(cloned_rooms[key]->query_exits()))
                {
                    write("No exits added to " + file_name(cloned_rooms[key]));
                    return;
                }
            }
        }
        
        x++;
    }
    
    write("Area Compiled Successfully!");
    
    if(!catch(owner->move_player(cloned_rooms["0x0"])))
        write("%^CYAN%^BOLD%^Demiplane teleport successful!%^RESET%^");
    
    call_out("check_plane", 60, owner);
}

void check_plane(object owner)
{
    //Check if they're still logged in
    if(!objectp(owner) || !userp(owner) || owner->query_ghost())
        destroy_plane(owner);
    
    //Check if they're still in the area
    if(!environment(owner)->is_demiplane_room())
        destroy_plane(owner);      
    
    call_out("check_plane", 60, owner);
}

void destroy_plane(object owner)
{
    string file;
    
    object *rooms, ob;
    
    if(!sizeof(cloned_rooms))
    {
        write("No rooms in the mapping.");
        return;
    }
    
    if(objectp(owner) && environment(owner)->is_demiplane_room())
    {
        owner->move_player(PATH + "entrance");
        tell_object(owner, "%^BOLD%^You are whisked away to safety as the plane collapses!%^RESET%^");
    }
    
    foreach(string str in keys(cloned_rooms))
    {
        ob = cloned_rooms[str];
        
        if(!objectp(ob))
            continue;
        
        /*
        if(!objectp(ob))
        {
            write(str + " is not an object.");
            continue;
        }
        */
        //write("Destroying : " + file_name(ob));
        seteuid(UID_SYSTEM);
        ob->dest_effect();
        objectp(ob) && destruct(ob);
    }
    
    objectp(owner) && owner->remove_property("demiplane compiler");
    objectp(owner) && "/d/common/obj/daily/entrance"->remove_traveler(owner);
    cloned_rooms = ([  ]);
    destruct(this_object());
}

mapping query_rooms()
{
    return cloned_rooms;
}

string get_room_file(int x, int y)
{
    string key;
    
    key = (string)x + "x" + (string)y;
    return file_name(cloned_rooms[key]);
}

string get_room_short(string theme)
{
    switch(theme)
    {
        case "clockwork":
            return "%^YELLOW%^Clockwork Demiplane%^RESET%^";
        break;
        
        case "offal marsh":
            return "%^GREEN%^BOLD%^Offal Marsh Demiplane%^RESET%^";
        break;
        
        case "deep caverns":
            return "%^BOLD%^BLACK%^Deep Caverns Demiplane%^RESET%^";
        break;
        
        case "feywild":
            return "%^BOLD%^MAGENTA%^Feywild Demiplane%^RESET%^";
        break;
    }
    
    return CRAYON_D->color_string("Strange Demiplane", "very black");
}

string get_room_long(string theme)
{
    switch(theme)
    {
        case "feywild":
            if(random(2))
                return "%^RESET%^%^CRST%^%^C082%^You stand in the %^C243%^shadows%^C082%^ of massive trees. The gargantua trunks stretch up and up hundreds of feet, becoming lost in a %^C245%^ha%^C250%^zy mi%^C245%^st%^C082%^ that creeps through the %^C095%^twi%^C101%^ste%^C095%^d b%^C101%^ran%^C095%^che%^C101%^s%^C082%^ and %^C041%^l%^C047%^u%^C041%^sh l%^C047%^e%^C041%^av%^C047%^e%^C041%^s%^RESET%^%^C082%^. You feel very small amongst such primal majesty, and the entire world seems to be a bit disorienting and dizzying. Despite the thickness of the canopy overhead, the forest is shocking in its %^C112%^b%^C118%^r%^C154%^i%^C148%^g%^C112%^h%^C118%^t%^C154%^n%^C148%^e%^C112%^s%^C118%^s%^RESET%^%^C082%^ and %^C190%^v%^C226%^i%^C220%^v%^C214%^i%^C190%^d %^C226%^c%^C220%^o%^C214%^l%^C190%^o%^C226%^r%^C220%^s%^RESET%^%^C082%^. The air s%^C040%^hi%^C082%^mme%^C040%^r%^C082%^s and rippl%^C040%^e%^C082%^s at times, as if enraptured by %^C043%^magic%^C082%^. Small %^C192%^lights%^C082%^ flicker and dance in the distance, luring you deeper into the dense foliage.%^RESET%^%^CRST%^";
            else if(random(2))
                return "%^RESET%^%^CRST%^%^C121%^You find yourself inundated by the reflection of a familiar forest, but it seems wilder, boundless in breadth, and overflowing with vibrancy%^C121%^. Most of the surrounding %^C040%^foliage%^C121%^ and %^C040%^trees%^C121%^ are curiously warped with elaborately patterned trunks and branches that grow any which way. Shining leaves hide fruits that %^C111%^g%^C117%^l%^C123%^o%^C159%^w%^RESET%^ %^C121%^and %^C111%^g%^C117%^l%^C123%^i%^C159%^m%^C111%^m%^C117%^e%^C123%^r%^RESET%^%^C121%^. Some of the more %^BOLD%^%^C090%^e%^C096%^x%^C102%^o%^C108%^t%^C090%^i%^C096%^c %^C102%^p%^C108%^l%^C090%^a%^C096%^n%^C102%^t%^C108%^s%^RESET%^%^C121%^ bloom with colors you have never experienced, with %^BOLD%^%^C090%^s%^C102%^c%^C090%^en%^C102%^t%^C090%^s%^RESET%^%^C121%^ that bewilder and invigorate you. The forest feels very ancient and alive, each thing with a %^C195%^breath%^C121%^ and %^C195%^magic%^C121%^ of its own, and you get the feeling that they've all taken an %^C118%^interest%^C121%^ in you.%^RESET%^%^CRST%^";
            else
                return "%^RESET%^%^CRST%^%^C042%^Standing in the shade of the forest, a sea of %^C118%^tall grasses%^C042%^ and %^C129%^w%^C128%^il%^C127%^d%^C126%^f%^C125%^l%^C124%^o%^C128%^w%^C129%^e%^C128%^r%^C127%^s%^RESET%^ %^C042%^stretch out before you. The flowers are a cacophony of %^C129%^vi%^C127%^bra%^C129%^nt c%^C127%^o%^C129%^lors%^RESET%^ %^C042%^against the %^C118%^lively green%^C042%^. They sway to the song of the %^C081%^wind%^C042%^, without care or choreography. Busy %^C153%^winged creatures%^C042%^ flit from flower to flower adding their own enchanting dance to the expansive meadow. The meadow is inundated with such life and vibrancy, you soon find yourself feeling quite %^C162%^aroused%^C042%^ and attuned to your striking surroundings. The sky above is cast in the %^C220%^g%^C226%^o%^C220%^ld%^C226%^e%^C220%^n gl%^C226%^o%^C220%^w%^C042%^ of %^C092%^t%^C098%^w%^C104%^i%^C110%^l%^C092%^i%^C098%^g%^C104%^h%^C110%^t%^RESET%^%^C042%^.%^RESET%^%^CRST%^";
        break;
        
        case "clockwork":
            if(random(2))
                return "%^RESET%^%^CRST%^%^C008%^S%^C007%^i%^C015%^lv%^C007%^e%^C008%^r%^CRST%^ %^C130%^and %^C149%^b%^C143%^r%^C137%^a%^C143%^s%^C149%^s %^C130%^cogs shine in the ambient light, a steady click and whirl of %^C156%^cl%^C150%^oc%^C144%^kw%^C156%^or%^C150%^k g%^C144%^ea%^C156%^rs %^C130%^shifting beneath the %^C007%^tr%^C015%^an%^C007%^sp%^C015%^ar%^C007%^en%^C015%^t g%^C007%^la%^C015%^ss %^CRST%^%^RESET%^%^C130%^floor. They move with a ponderous and methodical pace, like the heartbeat of some great mechanical being. Strange %^C149%^metal %^C143%^tubes %^C130%^run the length of these corridors, forming walls and junctions, rumbling and shaking with barely contained pressures. Vents periodically shutter open, the %^CRST%^%^C007%^s%^C008%^t%^C007%^e%^C008%^a%^C007%^m %^CRST%^%^C130%^screaming out as the cogs and tubing whirl about into new formations.%^RESET%^%^CRST%^";
            else
                return "%^RESET%^%^CRST%^%^C130%^Bursts of %^CRST%^%^C007%^s%^C008%^t%^C007%^e%^C008%^a%^C007%^m %^CRST%^%^C130%^obscure most of the area, and the air is full of %^C149%^metal %^C143%^wheels %^C130%^running down slender tracks as the surrounding %^C156%^ma%^C150%^ch%^C144%^in%^C156%^er%^C150%^y %^C130%^fulfills some archaic function. The floor is %^CRST%^%^C007%^tr%^C015%^an%^C007%^sp%^C015%^ar%^C007%^en%^C015%^t%^RESET%^%^C130%^, revealing layer upon layer of mighty gears and cogs that are majestic in scale, ticking away in a grand procession. Small %^C208%^ga%^C202%^s l%^C196%^am%^C208%^ps %^C130%^protrude from a slender pipe, offering some meager light that flickers with each blast of steam.%^RESET%^%^CRST%^";
        break;
        
        case "offal marsh":
            if(random(2))
                return "%^RESET%^%^CRST%^%^C065%^The slick uneven ground has a spongy composure, divided by rivulets of %^C107%^horrid %^C144%^ta%^C138%^in%^C132%^te%^C144%^d w%^C138%^at%^C132%^er%^C065%^, sluggishly carrying %^C130%^offal %^C065%^and %^C059%^waste%^C065%^. Clouds of %^CRST%^%^C008%^fli%^C007%^e%^C008%^s %^C065%^and other denizens of filth hover in sporadic swarms over the warm, wet surfaces. The air seems to shimmer and dance in the %^C071%^m%^C065%^o%^C059%^i%^C071%^s%^C065%^t %^C059%^h%^C071%^a%^C065%^z%^C059%^e%^RESET%^%^C065%^, and distant %^C142%^co%^C136%^rr%^C130%^up%^C142%^te%^C136%^d w%^C130%^at%^C142%^er%^C136%^fa%^C130%^ll%^C142%^s %^C065%^splatter and bubble and froth as more disgusting muck feeds into the area. Weak, blasted vegetation tries to survive here, but it is blackened with %^C059%^rot%^C065%^.%^RESET%^%^CRST%^";
            else
                return "%^RESET%^%^CRST%^%^C065%^This is a small copse of scrub brush, only the branches left as they rise up from the %^C142%^fe%^C136%^ti%^C130%^d m%^C142%^ar%^C136%^sh%^C065%^. The ground burbles and shudders as %^C070%^fo%^C064%^ul %^C058%^ga%^C070%^ss%^C064%^es %^C065%^erupt with a %^C059%^wet spatter%^C065%^, spraying its corruption onto the surrounding piles of %^C130%^offal%^C065%^, the semisolid surfaces swarming with writhing %^CRST%^%^C015%^ma%^C007%^g%^C015%^go%^C007%^t%^C015%^s%^RESET%^%^C065%^. The buzzing of stinging gnats and the sweltering heat give the air an oppressive weight, making the %^C144%^f%^C138%^i%^C132%^l%^C144%^t%^C138%^h %^C065%^palpable.%^RESET%^%^CRST%^";
        break;
        
        case "deep caverns":
            if(random(2))
                return "%^RESET%^%^CRST%^%^C008%^Dark, %^C103%^slick %^C091%^stone %^C097%^comprises these caverns, the walls and ceilings dripping with %^C069%^mo%^C063%^is%^C057%^tu%^C069%^re%^C097%^. The ground is worn smooth down the center path, with %^C131%^rocky debris %^C097%^collecting along the periphery. Strange %^C030%^gl%^C036%^ow%^C042%^in%^C030%^g f%^C036%^un%^C042%^gi %^C097%^grow in patches here and there, their thin tendrils raising into the air and casting the area in a subtle %^C030%^am%^C036%^b%^C030%^ie%^C024%^n%^C030%^t l%^C036%^i%^C030%^gh%^C024%^t%^RESET%^%^C097%^. Things %^C089%^sl%^C095%^it%^C101%^he%^C089%^r %^C097%^and %^C089%^sc%^C095%^am%^C101%^pe%^C089%^r %^C097%^just out of sight further down these tunnels.%^RESET%^%^CRST%^";
            else
                return "%^RESET%^%^CRST%^%^C097%^The %^C030%^so%^C036%^f%^C030%^t g%^C024%^l%^C030%^ow %^C097%^afforded by patches of %^C030%^lu%^C036%^mi%^C042%^ne%^C030%^sc%^C036%^en%^C042%^t m%^C030%^os%^C036%^se%^C042%^s %^C097%^reveals a series of rocky caverns. %^C091%^Stalagtites %^C097%^descend from the ceiling, reaching tentatively for their mirror images rising from the floor, though a smooth unfettered %^C103%^path %^C097%^weaves down the center of each tunnel. The soft drip of %^C069%^co%^C063%^nd%^C057%^en%^C069%^sa%^C063%^ti%^C057%^on %^C097%^gathering and falling echoes in otherwise silence, %^C063%^sm%^C069%^a%^C063%^ll %^C057%^p%^C063%^oo%^C069%^l%^C063%^s %^C097%^forming in pockets of %^C131%^rock %^C097%^and rippling with each intrusion from above.%^RESET%^%^CRST%^";
        break;
    }
        
    return CRAYON_D->color_string("You are lost in a strange Demiplane.", "dark black");
}

int place_monsters(int x, int y, string theme, object owner)
{
    string file, key;
    object boss, fragment;
    
    key = (string)x + "x" + (string)y;
    //In the last room, place the boss
    if(x == (MAX_WIDTH - 1) && y == (MAX_HEIGHT - 1))
    {
        switch(theme)
        {
            case "feywild":
            file = PATH + "mon/redcap";
            break;
            case "clockwork":
            file = PATH + "mon/steamgolem";
            break;
            case "offal marsh":
            file = PATH + "mon/plaguelord";
            break;
            case "deep caverns":
            file = PATH + "mon/grue";
            break;
        }
        
        if(!load_object(file))
            return 0;
        
        if(catch(boss = new(file)))
            return 0;
        
        if(catch(boss->move(cloned_rooms[key])))
            return 0;
        
        fragment = new("/d/common/obj/daily/quest_item");
        fragment->move(boss);
        
        boss->set_powerlevel(max( ({ owner->query_level() / 10, 1 }) ));
    }
    else
    {
        if(x == 0 && y == 0)
            return 0;
        
        for(int z = 0; z < random(6); z++)
        {
            if(catch(new(monsters_to_use[random(sizeof(monsters_to_use) - 1)])->move(cloned_rooms[key])))
                return 0;
        }
    }
    
    return 1;
}
        
    