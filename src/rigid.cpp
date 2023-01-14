// #include"camera.h"

// int main(int argc,char *argv[]){
//     // processing arguments
//     char choice='d';
//     std::string left_dir,right_dir;
//     if(argc>1)
//     char choice=(argv[1])[1];
//     switch(choice){
//         case 'h':
//             std::cout<<"-h for help\n-d to run with default data\n-m to run with manual data\n"<<std::endl;
//             break;
//         case 'd':
//             left_dir="../resource/mini/cam0/data/image";
//             right_dir="../resource/mini/cam1/data/image";
//             break;
//         case 'm':
//             std::cout<<"Enter left directory path:\t";
//             std::cin>>left_dir;
//             std::cout<<"Enter right directory path:\t";
//             std::cin>>right_dir;
//         default:
//     }


//     stereo images;
//     features left_compute,right_compute;
//     extrinct left,right;
//     // read_parameters(left_camera,initial_left_camera,'l');
//     // read_parameters(right_camera,initial_right_camera,'r');
//     cv::Mat matched,mask;
//     std::vector<cv::DMatch>  matches1to2;
//     char left_path[60];
//     char right_path[60];
    
//     for(int i=1;i<45;i++){
//         sprintf(left_path,"%s%05d%s",left_dir,i,".png");
//         std::cout<<left_path<<std::endl;
//         sprintf(right_path,"%s%05d%s",right_dir,i,".png");
//         images.left=cv::imread(left_path,cv::IMREAD_GRAYSCALE);
//         images.right=cv::imread(right_path,cv::IMREAD_GRAYSCALE);
//         detect_features(images.left,left_compute);
//         // calculateExtrinctParameters(left,left_compute);
//         detect_features(images.right,right_compute);
//         // calculateExtrinctParameters(left,right_compute);
//         // std::cout<<images;
//         cv::imshow("Matched",matched);
//         if (cv::waitKey(50) == 27){
// 			std::cout << "Esc key is pressed by user. Stoppig the video" << std::endl;
// 			break;
// 			}
//     }