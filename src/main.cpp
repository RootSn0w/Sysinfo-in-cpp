#include <iostream>
#include <regex>
#include "utils.h"
#include "color.h"

int main (int argc, char **argv) {

	Color::Modifier red(Color::FG_RED);
    Color::Modifier def(Color::FG_DEFAULT);
	auto membuf = get_mem();
	auto upbuf  = get_uptime();
	auto screenbuf = get_screen();
	std::regex r("/?.*/");

	std::cout << "\t" << red << get_user() << def << "@" << red << get_host() << def << std::endl << std::endl;
	std::cout << red << "Packages" << def << ":\t"   << get_packages() << std::endl;
	std::cout << red << "Kernel"   << def << ":\t\t" << get_kernel() <<  std::endl;
	std::cout << red << "Uptime"   << def << ":\t\t" << upbuf.days << " days " <<  upbuf.hours << ":" << upbuf.minutes << ":" << upbuf.seconds << std::endl;
	std::cout << red << "Mem"      << def << ":\t\t" << membuf.free << "M / " << membuf.total << "M" << std::endl;
	std::cout << red << "Desktop"  << def << ":\t"   << screenbuf.desktop << " running on " << screenbuf.server << std::endl;
	std::cout << red << "Shell"    << def << ":\t\t" << std::regex_replace(get_shell(), r, "") << std::endl;
	std::cout << red << "Res"      << def << ":\t\t" << screenbuf.width << "X" << screenbuf.height << std::endl;
 
	return 0;
}
