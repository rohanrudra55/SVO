#include "../include/rigid.h"
#include "../include/utils.h"
#include "../include/stereo.h"
#include "../include/feature.h"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define RESET "\033[0m"

namespace SVO{
    class System{
        private:
        Estimate poseEstimator;
        Feature trackFeatures;
        Stereo stereoTriangulate;
        ReadFrame readImage;
        std::string dataPath;
        static int imageCount;
        bool initialStep = true;
        bool showTracking=false;
        public:
        void showRealTimeTracking(){
            showTracking=true;
        }
        void setDataPath(std::string input){
            dataPath=input;
        }
        bool nextStep();
        void runSVO();
    };
}