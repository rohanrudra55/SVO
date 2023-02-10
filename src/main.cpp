// MIT License

// Copyright(c) 2023 Rohan Rudra

//     Permission is hereby granted,
//     free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and / or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

//     The above copyright notice and this permission notice shall be included in all copies
//     or
//     substantial portions of the Software.

//     THE SOFTWARE IS PROVIDED "AS IS",
//     WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//     FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//     AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
//     DAMAGES OR OTHER
//     LIABILITY,
//     WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//     OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//     SOFTWARE.

#include "../include/system.h"
// #define AUTO
// If you set the dataset paths explicitly the enable AUTO

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
    std::cout << GREEN << "Type -h for more options" << RESET << std::endl;
    // TO USE IN THIS MODE SET THE DATASET ABSOLUTE PATH HERE
    compute.setDataPath("/Users/alpha/Downloads/2011_09_26/2011_09_26_drive_0001_sync");
    compute.showRealTimeTracking();
    compute.runSVO();
}

#endif