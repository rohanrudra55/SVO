
#include "../include/system.h"
#define RED     "\033[31m" 
#define GREEN   "\033[32m"      
#define YELLOW  "\033[33m"      
#define BLUE    "\033[34m"
#define RESET   "\033[0m"
int main(int argc, char **argv){
    std::cout << "\033[2J\033[1;1H"<<std::endl;
    static SVO::System compute;
    if(argc>1){
        if(std::string(argv[1])=="-h"){
            std::cout<<GREEN<<"***WELCOME***\n"<<RESET<<"1) "<<RED<<"-h"<<RESET<<BLUE<<"\t\tHelp Menu\n"<<RESET<<"2) "<<RED<<"/.../"<<RESET<<BLUE<<"\tAbsolute Kitti Dataset path\n"<<RESET<<"3) "<<RED<<"t"<<RESET<<BLUE<<"\t\tView Tracking"<<RESET<<std::endl;
            return 1;
        }
        else{
            compute.setDataPath(std::string(argv[1]));
        }
        if(argc==3){
            if(std::string(argv[2])=="t")
                compute.showRealTimeTracking();
            else
                return 1;
        }    
    }
    else{
        std::cout<<"If this is not on Rohan's Computer then set data path"<<std::endl;
        return 1;
    }
    compute.runSVO();
    return 0;
}