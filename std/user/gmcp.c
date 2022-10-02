// gmcp.c
// Keeps track of the player's GMCP data/settings.
// Handles the player's GMCP requests.
// Spade, 14 July 2022

int         gmcp_enabled = 0; // Indicates whether or not we should be sending GMCP messages to this player
mapping module_data = ([  ]); // Contains data for supported modules

int check_gmcp()
{
    //In-game setting that turns it on/off
    if(!this_object()->query("gmcp"))
        return 0;
    
    return 1;
}

void query_clients_gmcp_compatability()
{
    if (has_gmcp(this_object()))
    {
        gmcp_enabled = 1;
    }
    else
    {
        gmcp_enabled = 0;
    }
}

int query_gmcp_enabled()
{
    if(!check_gmcp())
        return 0;
    
    return gmcp_enabled;
}

// Handle requests from the client
void gmcp(string str)
{       
    write("<GMCP request received.>\n");
    write(str);
    write("\n<GMCP request end.>\n");
}

void gmcp_update_character(string module, mapping data)
{
    if(!check_gmcp())
        return;

    if (gmcp_enabled)
    {
        int i;

        if (!mapp(module_data))
        {
            module_data = ([  ]);
        }

        if (!mapp(module_data["character_" + module]))
        {
            module_data["character_" + module] = ([  ]);
        }

        for (i = 0; i < sizeof(data); ++i)
        {
            mixed current_key = keys(data)[i];
            module_data["character_" + module][current_key] = data[current_key];
        }

        send_gmcp("character." + module + " " + json_encode(data));

        return;
    }
}

// This is a high-frequency call, and should be kept small.
// Deprecated
void gmcp_update_character_vitals(mapping data)
{
    if(!check_gmcp())
        return;
    
    if (gmcp_enabled)
    {
        int i;

        if (!mapp(module_data))
        {
            module_data = ([  ]); 
        }
    
        if (!mapp(module_data["character_vitals"]))
        {
            module_data["character_vitals"] = ([  ]);
        }
    
        for (i = 0; i < sizeof(data); ++i)
        {
            mixed current_key = keys(data)[i];
            module_data["character_vitals"][current_key] = data[current_key];
        }
    
        send_gmcp("character.vitals " + json_encode(module_data["character_vitals"]));

        return;
    }
}

// This is an even-higher frequency call, and should be kept small.
// Deprecated
void gmcp_update_character_survival(mapping data)
{
    if(!check_gmcp())
    {
        gmcp_enabled = 0;
        return;
    }
    if (gmcp_enabled)
    {
        int i;

        if (!mapp(module_data))
        {
            module_data = ([  ]); 
        }
    
        if (!mapp(module_data["character_survival"]))
        {
            module_data["character_survival"] = ([  ]);
        }
    
        for (i = 0; i < sizeof(data); ++i)
        {
            mixed current_key = keys(data)[i];
            module_data["character_survival"][current_key] = data[current_key];
        }
    
        send_gmcp("character.survival " + json_encode(module_data["character_survival"]));

        return;
    }
}

// Deprecated
void gmcp_update_character_resources(mapping data)
{
    //In-game setting that turns it on/off
    if(!this_object()->query("gmcp"))
    {
        gmcp_enabled = 0;
        return;
    }
    
    if (gmcp_enabled)
    {
        int i;

        if (!mapp(module_data))
        {
            module_data = ([  ]); 
        }
    
        if (!mapp(module_data["character_resources"]))
        {
            module_data["character_resources"] = ([  ]);
        }
    
        for (i = 0; i < sizeof(data); ++i)
        {
            mixed current_key = keys(data)[i];
            module_data["character_resources"][current_key] = data[current_key];
        }
    
        send_gmcp("character.resources " + json_encode(module_data["character_resources"]));

        return;
    }
}

// Send a message to the client
void send_gmcp(string str)
{
    if(!check_gmcp())
    {
        gmcp_enabled = 0;
        return;
    }
    
    efun::send_gmcp(str);
}
