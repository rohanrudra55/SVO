#include"utils.h"

// GLOBAL VARIABLES
// int Utils::limit;
std::fstream Utils::fin;
std::string Utils::path;
cv::Mat Utils::StereomapL_x,Utils::StereomapL_y,Utils::StereomapR_x,Utils::StereomapR_y,Utils::reprojection_matrix;
bool Utils::foundCSV=0,Utils::foundXML=0;

void Utils::display(cv::Mat &show_data,std::string frame){
    cv::imshow(frame,show_data);
    if (cv::waitKey(60) == 27)
    {
        cv::destroyAllWindows();
        exit(1);
    }
}
//======================================================================

void Utils::readRectifyData(){
    cv::FileStorage xml_read("../src/Parameters/Stereomap.xml",cv::FileStorage::READ);
    if(!xml_read.isOpened()){
    std::cout<<"XML file not found"<<std::endl;
        exit(1);
    }
    std::cout<<"Data Loaded...\n";
    StereomapL_x=xml_read["StereomapL_x"].mat();
    StereomapL_y=xml_read["StereomapL_y"].mat();
    StereomapR_x=xml_read["StereomapR_x"].mat();
    StereomapR_y=xml_read["StereomapR_y"].mat();
    reprojection_matrix=xml_read["To3DMap"].mat();   

    xml_read.release();

}
void Utils::rectifyImage(cv::Mat &leftimage,cv::Mat &rightimage){
        // // UNDISTORT AND RECTIFY IMAGE
    cv::Mat copy_left;
    cv::Mat copy_right;
    std::cout<<"\nData"<<StereomapL_x.at<float>(0,0)<<"\n";
    cv::remap(leftimage,copy_left,StereomapL_x,StereomapL_y,cv::INTER_LINEAR);
    cv::remap(rightimage,copy_right,StereomapR_x,StereomapR_y,cv::INTER_LINEAR);
    leftimage=copy_left;
    rightimage=copy_right;
    // cv::imwrite("Data2.png",copy_left);
    
}
bool Utils::readERoC(cv::Mat &limage,cv::Mat &rimage){
    std::string first,secondl,secondr;
    // cv::Mat img;

    if(!foundCSV){
        fin.open((path+"cam0/data.csv"),std::ios::in);
                if ( !fin ) {
                    std::cout<<path;
                    std::cout << "File not found";
                    exit(1);
                }
    }
  
    while (true) {
        getline(fin, first,',');
                fin>>secondl;
        if(foundCSV){
            secondr=path+"cam1/data/"+secondl;
            secondl=path+"cam0/data/"+secondl;
            limage = cv::imread(secondl);
            rimage= cv::imread(secondr);
            std::cout<<"\n"<<secondl<<"\n";
            std::cout<<secondr<<"\n";
            return true;
        }
        else
            foundCSV=CSV ;
        }
    return false;
}
bool Utils::readERoC(cv::Mat &image){
    std::string first,second;
    // cv::Mat img;

    if(!foundCSV){
        fin.open((path+"cam0/data.csv"),std::ios::in);
                if ( !fin ) {
                    std::cout<<path;
                    std::cout << "File not found";
                    exit(1);
                }
    }
  
    while (true) {
        getline(fin, first,',');
                fin>>second;
        if(foundCSV){
            second=path+"cam0/data/"+second;
            image = cv::imread(second);
            std::cout<<"\n"<<second<<"\n";
            return true;
        }
        else
            foundCSV=CSV ;
        }
    return false;
}
bool Utils::readKITTI(cv::Mat &image,int number){
    std::string finalPath;
    // std::cout<<number;
    char p[7];
    sprintf(p,"%06d",number);
    finalPath=path+"left/"+p+".png";
    std::cout<<finalPath<<std::endl;;
    image=cv::imread(finalPath,0);
    return !(image.empty());
}
bool Utils::readKITTI(cv::Mat &imagel,cv::Mat &imager,int number){
    std::string finalPathl,finalPathr;
    // std::cout<<number;
    char p[7];
    sprintf(p,"%06d",number);
    finalPathl=path+"left/"+p+".png";
    finalPathr=path+"right/"+p+".png";
    // std::cout<<finalPathl<<std::endl;
    imagel=cv::imread(finalPathl,0);
    imager=cv::imread(finalPathr,0);
    return !(imagel.empty());
}
//======================================================================
// int main(){
//     Utils test;
//     test.setPath("../data/mini/cam0/");
//     cv::Mat image;
//     for(int i=0;i<10;i++){
//         image=test.read();
//         test.display(image);
//     }
// }

//======================================================================
// void read_parameters(instirnct& data,extrinct& data_ ,char side){
//     instirnct left_camera,right_camera;
//     extrinct initial_left_camera,initial_right_camera;
//     FILE *path;
//     if(side=='l')
//         path=fopen("../resource/left/000000.txt","r");
//     else
//         path=fopen("../resource/right/000000.txt","r");
//     // If the file is not read then the code will stop here to prevent errors in further calculations
//     if(path==NULL){
//         puts("File not found!\n");
//         exit(0);
//     }
//     // reading each number from the file and storing it in the matrix
//     int colum=0,row=0;
//     cv::Mat matrix;
//     double number;
//     while(fscanf(path,"%lf",&number)!=EOF){
//         if(colum==4){
//             colum=0;
//             row++;
//         }
//         matrix.at<double>(row,colum)=number;
//         colum++;
//         if(row==4 && colum==2)
//             break;
//     }
//     cv::decomposeProjectionMatrix(matrix,data.camera_matrix,data_.rotational_matrix_1,data_.transversal_matrix);
//     data.c_x=data.camera_matrix.at<double>(0,2);
//     data.c_y=data.camera_matrix.at<double>(1,2);
// }