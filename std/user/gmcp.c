/*
  gmcp.c
  
  User.c inherit to add GMCP functionality.
  
  -- Tlaloc -- 9.16.21
*/

int gmcp_enabled;

void gmcp_enable()
{
    write("<GMCP negotiation enabled.>\n");
    gmcp_enabled = 1;
}

void gmcp(string str)
{
    write("<GMCP request received.>\n");
    write(str);
    write("\n\<GMCP request end.>\n");
}

void send_gmcp(string str)
{
    efun::send_gmcp(str);
}