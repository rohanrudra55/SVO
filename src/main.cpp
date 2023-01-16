
#include "../include/system.h"
#define AUTO

#ifdef AUTO
int main(int argc, char **argv)
{
    std::cout << "\033[2J\033[1;1H" << std::endl;
    static SVO::System compute;
    if (argc > 1)
    {
        if (std::string(argv[1]) == "-h")
        {
            std::cout << GREEN << "***WELCOME***\n"
                      << RESET << "1) " << RED << "-h" << RESET << BLUE << "\t\tHelp Menu\n"
                      << RESET << "2) " << RED << "-d" << RESET << BLUE << "\tAbsolute Kitti Dataset path\n"
                      << RESET << "3) " << RED << "-t" << RESET << BLUE << "\t\tView Tracking" << RESET << std::endl;
        }

        else
        {
            if (std::string(argv[1]) == "-d")
            {
                compute.setDataPath(std::string(argv[2]));
            }
            if (std::string(argv[1]) == "-t" || std::string(argv[3]) == "-t")
            {
                std::cout << GREEN << "Enabling Tracking Viewer" << RESET << std::endl;
                compute.showRealTimeTracking();
            }
            compute.runSVO();
        }
    }
    else
    {
        std::cout << BLUE << "Type -h for HELP" << RESET << std::endl;
    }
    return 0;
}
#else

int main(int argc, char **argv)
{
    std::cout << "\033[2J\033[1;1H" << std::endl;
    static SVO::System compute;
    std::cout << BLUE << "Type -h for more options" << RESET << std::endl;
    // TO USE IN THIS MODE SET THE DATASET ABSOLUTE PATH HERE
    compute.setDataPath("/Users/alpha/Downloads/2011_09_26/2011_09_26_drive_0001_sync");
    compute.runSVO();
}

#endif