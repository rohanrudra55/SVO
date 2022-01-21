#!/usr/bin/env python3
try:        #If any of the modules are not insatlled then it will handel teh errors
    import cv2
    import numpy as np
    import argparse as ag
    import csv
    import os
except:
    print('Modules missing. Check requirements.txt')


criteria=(cv2.TermCriteria_EPS+cv2.TERM_CRITERIA_MAX_ITER,30,0.001)
path=[]
class Camera:
    objectPoint=[]
    imagePoint=[]
    mtx=[]
    dist=[]
    nx=7 #CHESSBOARD ROWS
    ny=6 #CHESSBOARD COLUMS
    def readData(self,filepath,total,start,camera):
        print(filepath)
        filename=filepath+'data.csv'
        count=0
        # hp=Camera()
        with open(filename,'r') as csvfile:
            csvreader=csv.reader(csvfile)
            fields=next(csvreader)
            for row in csvreader:
                if int(row[0])>=start:
                    imagepath=filepath+'/data/'+row[1]
                    # print(imagepath)
                    image=cv2.imread(imagepath)
                    # display(image)
                    self.findPoints(image)  
                    count+=1
                    if count==total:
                        self.calibrateCamera(image,camera)
                        break
# ################################## FINN OBJECT POINTS AND CALIBRATE  ##################################
    def findPoints(self,image):
        objectPoints=self.objectPoint
        imagePoints=self.imagePoint
        nx=self.nx
        ny=self.ny
        gray=cv2.cvtColor(image,cv2.COLOR_BGR2GRAY)
        objp=np.zeros((ny*nx,3),np.float32)
        objp[:,:2]=np.mgrid[0:nx,0:ny].T.reshape(-1,2)
        #Calculating Image Points
        ret, corners = cv2.findChessboardCorners(gray, (nx, ny), None)
        if ret == True:
            corners=cv2.cornerSubPix(gray,corners,(5,5),(-1,-1),criteria)
            imagePoints.append(corners)              
            objectPoints.append(objp)
            #DRAW CHESS BOARD CORNERS
            # edited_image=np.copy(image)
            # edited_image=cv2.drawChessboardCorners(image, (nx, ny), corners, ret) 
        else:
            print('Image is not proper!')
            exit()
    def calibrateCamera(self,image,camera):
        objectPoints=self.objectPoint
        imagePoints=self.imagePoint
        # Calibrating Camera
        gray=cv2.cvtColor(image,cv2.COLOR_BGR2GRAY)
        ret, self.mtx,self.dist, rvecs, tvecs = cv2.calibrateCamera(objectPoints, imagePoints, gray.shape[::-1], None, None)
        # mtx=mtx.astype('str')
        newfile='Parameters/'+camera+'Data.csv'
        with open(newfile, 'w') as csvfile: 
            csvwriter = csv.writer(csvfile) 
        # # writing the fields 
            header=['Parameter','Values']
            csvwriter.writerow(header)
            cm=['Camera Matrix']+(np.reshape(self.mtx,9)).tolist()
            csvwriter.writerow(cm)
            rm=['Rotational Matrix']+rvecs 
            csvwriter.writerow(rm)
            tv=['Translational Vector']+tvecs  
            csvwriter.writerow(tv)
            dm=['Distortion Matrix']+ (np.reshape(self.dist,5)).tolist()
            csvwriter.writerow(dm)
class Stereo:
    imageSize=(752,480)
    newCameraMatricL=[]
    newDistortL=[]
    newCameraMatricR=[]
    newDistortR=[]
    rtvec=[]
    tvec=[]
    def clibrateStereoCamera(self,objectPoint,imagePointL,imagePointR,cameraMatrixL,distortL,cameraMatrixR,distortR):
        ret,self.newCameraMatricL,self.newDistortL,self.newCameraMatricR,self.newDistortR,self.rtvec,self.tvec,e,f=cv2.stereoCalibrate(objectPoint,imagePointL,imagePointR,cameraMatrixL,distortL,cameraMatrixR,distortR,self.imageSize,criteria)
        with open('Parameters/StereoData.csv', 'w') as csvfile: 
            csvwriter = csv.writer(csvfile) 
        #SAVING
            header=['Parameter','Values']
            csvwriter.writerow(header)
            cm=['Left Camera Matrix']+(np.reshape(self.newCameraMatricL,9)).tolist()
            csvwriter.writerow(cm)
            cm=['Right Camera Matrix']+(np.reshape(self.newCameraMatricR,9)).tolist()
            csvwriter.writerow(cm)
            rm=['Rotational Matrix']+(np.reshape(self.rtvec,9)).tolist()
            csvwriter.writerow(rm)
            tv=['Translational Vector']+(np.reshape(self.tvec,3)).tolist()
            csvwriter.writerow(tv)
            dm=['Left Distortion Matrix']+ (np.reshape(self.newDistortL,5)).tolist()
            csvwriter.writerow(dm)
            dm=['Right Distortion Matrix']+ (np.reshape(self.newDistortR,5)).tolist()
            csvwriter.writerow(dm)
            fm=['Fundamental Matrix']+ (np.reshape(f,9)).tolist()
            csvwriter.writerow(fm)
            em=['Essential Matrix']+ (np.reshape(e,9)).tolist()
            csvwriter.writerow(em)
        ################################## RECTIFY IMAGE  ##################################
        r1,r2,p1,p2,Q,_,_=cv2.stereoRectify(self.newCameraMatricL,self.newDistortL,self.newCameraMatricR,self.newDistortR,self.imageSize,self.rtvec,self.tvec)
        leftMap1,leftMap2=cv2.initUndistortRectifyMap(self.newCameraMatricL,distortL,r1,p1,self.imageSize,cv2.CV_32FC1)
        rightMap1,rightMap2=cv2.initUndistortRectifyMap(self.newCameraMatricR,distortR,r2,p2,self.imageSize,cv2.CV_32FC1)
        cv_file=cv2.FileStorage('Parameters/Stereomap.xml',cv2.FILE_STORAGE_WRITE,"UTF-8")
        cv_file.write('StereomapL_x',leftMap1)
        cv_file.write('StereomapL_y',leftMap2)
        cv_file.write('StereomapR_x',rightMap1)
        cv_file.write('StereomapR_y',rightMap2)
        cv_file.write('To3DMap',Q)
        cv_file.release()

    # ################################## WRITE TO TEXT  ##################################
    # @classmethod
    # def write_data(line,data,action='a',matrix=True):
    #     f=open('Parameetr.txt',action)
    #     f.writelines(line+':\t')
    #     if matrix==True:
    #         for row in range(0,data.shape[0]):
    #             for col in range(0,data.shape[1]):
    #                 f.write(str((data[row,col])))
    #                 f.write(',\t')
    #     else:
    #         for row in range(0,3):
    #             value=data[0][row]
    #             f.write(str(value[0]))
    #             f.write(',\t')
    #     f.write('\n')
    #     f.close()






def display(image):
    cv2.imshow('Image',image)
    if cv2.waitKey(50)==27:
        cv2.destroyAllWindows
    

# ################################## FUNDAMENTAL MATRIX ##################################

# def calculateFundamental(chess_board,image):
#     orb=cv2.ORB_create()
#     left_keypoints,des1=orb.detectAndCompute(chess_board,None)
#     right_keypoints,des2=orb.detectAndCompute(image,None)
#     left_k=cv2.KeyPoint_convert(left_keypoints)
#     right_k=cv2.KeyPoint_convert(right_keypoints)
#     retval,mask=cv2.findFundamentalMat(left_k[:20],right_k[:20],cv2.FM_RANSAC,ransacReprojThreshold=3,confidence=0.99)
#     write_data("Fundamanetal Matrix",retval)
#     # print('Fundamental matrix:\n',retval) #Fundamental matrix
#     bf=cv2.BFMatcher(cv2.NORM_HAMMING, crossCheck=True) # Its true so it will take less features 
#     matches=bf.match(des1,des2)
#     matches=sorted(matches, key=lambda x:x.distance)
#     print('Matched keypoints:',len(matches))
#     matching_result=cv2.drawMatches(chess_board,left_keypoints,image,right_keypoints,matches, None)
#     display(matching_result)

def main():
    # Reading the arguments for different purposes 
    parser=ag.ArgumentParser(description="Calibrate the camera and note the camera parameters\nNOTE: It should be a stereo pair.Organise the files in left and right directory")
    # parser.add_argument('-s','--single_image',type=bool,default=False,help='To work on single image')
    # parser.add_argument('-c','--chess_board',type=str,default='../data/ChessBoard.png',help='The path of the chess board image')
    # parser.add_argument('-i','--image',type=str,default='../data/Image.jpg',help='The path of the camera image')
    # parser.add_argument('-ud','--undistort',type=bool,default=False,help='To undistor the image')
    parser.add_argument('-ld','--left_directory',type=str,default='../data/mav0/cam0/',help='The path of the image data')
    parser.add_argument('-rd','--right_directory',type=str,default='../data/mav0/cam1/',help='The path of the image data')
    parser.add_argument('-f','--first_image',type=int,default=1403709004987836928,help='Starting image')
    parser.add_argument('-n','--number_of_images',type=int,default=50,help='The total number of images')
    args=parser.parse_args()
    os.mkdir("Parameters")
    left=Camera()
    right=Camera()
    left.readData(args.left_directory,args.number_of_images,args.first_image,'Left')
    right.readData(args.right_directory,args.number_of_images,args.first_image,'Right')
    cam=Stereo()
    cam.clibrateStereoCamera(left.objectPoint,left.imagePoint,right.imagePoint,left.mtx,left.dist,right.mtx,right.dist)


if __name__ == "__main__":
    main()