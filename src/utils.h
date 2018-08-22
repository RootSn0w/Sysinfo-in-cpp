#ifndef UTILS_H
#define UTILS_H

#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <sys/stat.h>
#include <X11/Xlib.h>
#include <unistd.h>
#include <string>
#include <cstdlib>
#include <fstream>

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

enum manager {
    portage = 1,
    pacman = 2,
    dpkg = 3
};

int check_manager(){
    struct stat buffer;
    if (stat("/usr/bin/dpkg",   &buffer) == 0) return dpkg;
    if (stat("/usr/bin/pacman", &buffer) == 0) return pacman;
    if (stat("/usr/bin/emerge", &buffer) == 0) return portage;
}

int get_packages(int manager){

    switch (manager){
        case dpkg:{
            std::ifstream file("/var/lib/dpkg/status");
            std::string line;
            int count = 0;

            while(std::getline(file, line)){
                if (line == "Status: install ok installed") count++;
            }
            file.close();
            return count;
        }
        default:
            return 0;
            break;
    }
}

std::string get_distro(){

    std::ifstream file("/etc/os-release");
    std::string line;

    std::getline(file, line);

    file.close();
    return line.replace(line.size() - 1, line.size(), "").replace(line.begin(), line.begin() + 6, "");
}

std::string get_shell(){
    return std::getenv("SHELL");
}

std::string get_user(){
    return std::getenv("USER");
}

screeninfo get_screen(){

    Display* pdsp = XOpenDisplay(NULL);
    Screen* pscr = DefaultScreenOfDisplay(pdsp);
    struct screeninfo buffer;

    if (!pdsp)
        throw ("Failed to open default display.");

    if (!pscr)
        throw ("Failed to obtain the default screen of given display.");

    buffer.width = pscr->width;
    buffer.height = pscr->height;
    buffer.desktop = std::getenv("XDG_SESSION_DESKTOP");
    buffer.server = std::getenv("XDG_SESSION_TYPE");

    XCloseDisplay(pdsp);
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

#endif