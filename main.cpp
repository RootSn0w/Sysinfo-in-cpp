#include <iostream>
#include <stdlib.h>
#include <string.h>

/*
	Made by: me
	Pacman's ghost by: User
*/

using namespace std;

int main (int argc, char **argv) {

	auto pac1 = "\033[1;32m    ▄██████▄";
	auto pac2 = "\033[1;32m  ▄\033[1;37m█▀█\033[1;32m██\033[1;37m█▀█\033[1;32m██▄";
	auto pac3 = "\033[1;32m  █\033[1;37m▄▄█\033[1;32m██\033[1;37m▄▄█\033[1;32m███";
	auto pac4 = "\033[1;32m  ████████████";
	auto pac5 = "\033[1;32m  ██▀██▀▀██▀██";
 	auto pac6 = "\033[1;32m  ▀   ▀  ▀   ▀";


	char packages[56];
	int sharedMem;
	int usedMem;
	int totalMem;
	char uptime[56];
	char desktop[56];
	char kernel[56];
	char os[56];
	char user[56];
	char host[56];
	char cpu[56];
	char resolution[56];
	auto blue = "\033[0m\033[1;34m";
	auto white = "\033[0m\033[0m";

	FILE *fp;
	
	// Memory
	// Used
	fp = popen("free -m | grep Mem | awk '{print $3}'", "r");
	fscanf(fp, "%d", &usedMem);
	// Shared
	fp = popen("free -m | grep Mem | awk '{print $5}'", "r");
	fscanf(fp, "%d", &sharedMem);
	// Total
	fp = popen("free -m | grep Mem | awk '{print $2}'", "r");
	fscanf(fp, "%d", &totalMem);
	

	// Uptime
	fp = popen("uptime -p | cut -b 4-", "r");
	fgets(uptime, 56, fp);
	uptime[strlen(uptime) - 1] = '\0';


	// Desktop Session
	fp = popen("env | grep DESKTOP_SESSION= | cut -b 17-", "r");
	fgets(desktop, 56, fp);
	desktop[strlen(desktop) - 1] = '\0';


	// Kernel Version
	fp = popen("uname -rm", "r"); 
	fgets(kernel, 56, fp);
	kernel[strlen(kernel) - 1] = '\0';


	// Distro
	fp = popen("cat /etc/os-release | grep PRETTY_NAME | cut -c 14- | rev | cut -c 2- | rev", "r");
	fgets(os, 56, fp);
	os[strlen(os) - 1] = '\0';


	// User
	fp = popen("echo $USER", "r");
	fgets(user, 56, fp);
	user[strlen(user) - 1] = '\0';
	

	// Hostname
	fp = popen("hostname", "r"); 
	fgets(host, 56, fp);
	host[strlen(host) - 1] = '\0';


	// CPU
	fp = popen("cat /proc/cpuinfo | grep \"model name\" | awk 'getline' | awk 'getline' | cut -c 14-", "r"); 
	fgets(cpu, 56, fp);
	cpu[strlen(cpu) - 1] = '\0';


	// Resolution
	fp = popen("xrandr| grep \" connected\" | awk '{print $3}' | rev | cut -c 5- | rev", "r");
	fgets(resolution, 56, fp);
	resolution[strlen(resolution) - 1] = '\0';


	// Packages
	if (strstr(os, "Arch") != NULL){
		fp = popen("pacman -Qq | wc -l", "r"); 
		fgets(packages, 56, fp);
		packages[strlen(packages) - 1] = '\0';
	} else if (strstr(os, "Gentoo") != NULL) {
		fp = popen("ls -d /var/db/pkg/*/* | wc -l", "r");
		fgets(packages, 56, fp);
		packages[strlen(packages) - 1] = '\0';
	} else {
		strcpy(packages, "Unknow (Only works in Arch and Gentoo)");
	}

	pclose(fp);



	cout << blue << "\t\t" << user << white << "@" << blue << host << endl;
	cout << "\t\t----------------" << endl;
	cout << pac1 << blue << "\tOS: " << white << os << endl;
	cout << pac2 << blue << "\tKernel: " << white << kernel << endl;
	cout << pac3 << blue << "\tUptime: " << white << uptime << endl;
	cout << pac4 << blue << "\tResolution: " << white << resolution << endl;
	cout << pac5 << blue << "\tPackages: " << white << packages << endl;
	cout << pac6 << blue << "\tDesktop: " << white << desktop << endl;
	cout << "\t" << blue << "\tCPU: " << white << cpu << endl;
	cout << "\t" << blue << "\tRAM: " << white << sharedMem + usedMem << "MB / " << totalMem << "MB" << endl;

	return 0;
}
