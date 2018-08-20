#include <iostream>
#include <regex>
#include "utils.h"

int main (int argc, char **argv) {

	auto membuf = get_mem();
	auto upbuf  = get_uptime();
	auto screenbuf = get_screen();
	std::regex r("/?.*/");

	std::cout << "\t" << get_user() << "@" << get_host() << std::endl << std::endl;
	std::cout << "Kernel:\t\t" << get_kernel() <<  std::endl;
	std::cout << "Uptime:\t\t" << upbuf.days << " days " <<  upbuf.hours << ":" << upbuf.minutes << ":" << upbuf.seconds << std::endl;
	std::cout << "Mem:\t\t" << membuf.free << "M / " << membuf.total << "M" << std::endl;
	std::cout << "Desktop:\t" << screenbuf.desktop << " running on " << screenbuf.server << std::endl;
	std::cout << "Shell:\t\t" << std::regex_replace(get_shell(), r, "") << std::endl;
	std::cout << "Res:\t\t" << screenbuf.width << "X" << screenbuf.height << std::endl;

 
	return 0;
}
