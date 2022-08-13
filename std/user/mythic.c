/*
  mythic.c
  
  Handles the Awakening Soul (Mythic paths) system.
  
  -- Tlaloc --
*/

#define DAILY_LIMIT 1000

mapping mythic = ([ 
                    "soul power" : 0,
                    "daily soul power" : 0,
                    "daily count" : 0,
                    "path"  : 0,
                    "level" : 0,
                 ]);
                 

void heart_beat()
{
    if(mythic["daily soul power"])
        if(!hour(time()) && !minutes(time()))
            mythic["daily soul power"] = 0;
}
        

void reset_mythic()
{
    mythic["soul power"] = 0;
    mythic["path"] = 0;
    mythic["level"] = 0;
}

int is_awakened()
{
    if(this_object()->query_level() < 50)
        return 0;
    
    if(!this_object()->query("awakened quest"))
        return 0;
    
    return 1;
}

mixed set_mythic(string str, mixed arg)
{
    string *map_keys;
    if(!stren(str) || !arg)
        return 0;
    
    map_keys = keys(mythic);
    
    if(member_array(str, map_keys) < 0)
        return 0;
    
    return mythic[str] = arg;
}

int add_soul_power(int x)
{
    if(is_awakened())
        return 0;
    
    if(mythic["daily soul power"] >= DAILY_LIMIT)
        return 0;
    
    if(mythic["daily soul power"] + x >= DAILY_LIMIT)
        x = DAILY_LIMIT - mythic["daily soul power"];
    
    return mythic["soul power"] += x;
}

 
    