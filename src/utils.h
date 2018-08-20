#ifndef UTILS_H
#define UTILS_H

#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <X11/Xlib.h>
#include <unistd.h>
#include <string>
#include <cstdlib>

struct uptime {
	int days;
	int hours;
	int minutes;
    int seconds;
};

struct meminfo {
    long free;
    long total;
};

struct screeninfo {
    int height;
    int width;
    std::string desktop;
    std::string server;
};

std::string get_shell(){
    return std::getenv("SHELL");
}

std::string get_user(){
    return std::getenv("USER");
}

screeninfo get_screen(){

    Display* pdsp = NULL;
    Screen* pscr = NULL;
    struct screeninfo buffer;

    pdsp = XOpenDisplay( NULL );
    if ( !pdsp )
        throw ("Failed to open default display.");

    pscr = DefaultScreenOfDisplay( pdsp );
    if ( !pscr )
        throw ("Failed to obtain the default screen of given display.");

    buffer.width = pscr->width;
    buffer.height = pscr->height;
    buffer.desktop = std::getenv("XDG_SESSION_DESKTOP");
    buffer.server = std::getenv("XDG_SESSION_TYPE");

    XCloseDisplay( pdsp );
    return buffer;
}

std::string get_kernel(){

    struct utsname utsinfo;
    uname(&utsinfo);
    std::string buff;

    buff  = utsinfo.sysname;
    buff += " ";
    buff += utsinfo.release;
    buff += " ";
    buff += utsinfo.machine;

    return buff;
}

uptime get_uptime(){

    struct sysinfo upinfo;
    struct uptime buff;
    long up = upinfo.uptime;

    sysinfo(&upinfo);

    buff.days = up / 60 / 60 / 24;
    buff.hours = (up / 60/ 60) % 24;
    buff.minutes = (up / 60) % 60;
    buff.seconds = up % 60;

    return buff;
}

std::string get_host(){

    char host[128];
    std::string buff;

    gethostname(host, 128);
    buff = host;

    return buff;
}

meminfo get_mem(){

    struct sysinfo meminfo;
    struct meminfo info;

    sysinfo(&meminfo);
    
    info.free  = (meminfo.totalram - meminfo.freeram) / 1024 / 1024;
    info.total = meminfo.totalram / 1024 / 1024;

    return info;
}

// meminfo get_mem(){

//     struct meminfo buffer;

//     long pageSize = sysconf(_SC_PAGESIZE);
//     long avPages  = sysconf(_SC_AVPHYS_PAGES);
//     long totalPages = sysconf(_SC_PHYS_PAGES);
    
//     long totalMem = totalPages * pageSize;
//     long availableMem = avPages * pageSize;
    
//     buffer.free  = (totalMem - availableMem)  / 1024 / 1024;
//     buffer.total = totalMem / 1024 / 1024;

//     return buffer;
// }

#endif