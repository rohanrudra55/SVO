#include "../include/rigid.h"
#include "../include/utils.h"
#include "../include/stereo.h"
#include "../include/feature.h"

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