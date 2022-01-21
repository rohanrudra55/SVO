try:
    import cv2  
    import numpy as np
    import glob
    import argparse
except:
    print('Modules not found!')
try:
    import tracker
    import rigid
    import mapping
except:
    print('Dependencies are missing! ')

if __name__ == "__main__" :

    parser=argparse.ArgumentParser(description="Estimating trajectory using stereo camera sensors.")
    parser.add_argument('-d','--dataset',type=str, default='/Users/alpha/Downloads/dataset/08/image_0/',help='Left image folder of KIITI')
    args=parser.parse_args()
    
    print('TIVRA Ai :: SVO')

    dataset=args.dataset
    filepaths=glob.glob(dataset+'/*.png')
    # dataset="/Users/alpha/Downloads/Data_to_be_shared/Indian_Road_Stereo_lite/left"
    # filepaths=glob.glob(dataset+'/*.jpg')
    filepaths.sort()
    initial=True

    # print(filepaths)
    # exit(0)
    previousLeftImage=0
    previousRightImage=0
    previousLeftPt=0

    currentLeftImage=0
    currentRightImage=0
    currentLeftPt=0

    count=0
    framepose=np.identity(4,dtype=np.double)
    trajectory=np.zeros((600,1200,3),dtype=np.uint8) #Blank imagae 
    cammodel=rigid.camera()

    wr=open("dataK2.txt","w")
    # for path in filepaths:
    #     count+=1
    #     currentLeftImage=cv2.imread(path,0)
    #     path=path.replace('image_0','image_1')
    extansion='*.jpg'
    # dataDir="/Users/alpha/Downloads/Indian_Road_Stereo_lite/left/"+extansion
    dataDir="/Users/alpha/Downloads/dataset/08/left/"+"*.png"
    filepaths=glob.glob(dataDir)
    filepath=filepaths.sort()
    for filepath in filepaths:
        currentLeftImage=cv2.imread(filepath,0)
        filepath=filepath.replace('left','right')
        currentRightImage=cv2.imread(filepath,0)
        count+=1
        # path=path.replace('left','right')
        # currentRightImage=cv2.imread(path,0)
        # currentLeftImage=cammodel.rectify(currentLeftImage,"L")
        # currentRightImage=cammodel.rectify(currentRightImage,"R")

        currentLeftPt=tracker.detectFeatures(currentLeftImage)
        #Estimating pose
        if not initial:
            framepose,trajectory,show=rigid.estimatePose(previousLeftImage,previousRightImage,currentLeftImage,currentRightImage,previousLeftPt,framepose,trajectory)
            wr.write(filepath+"  ")
            wr.write(str(framepose[0][3])+"   ")
            wr.write(str(framepose[2][3]))
            wr.write(str("\n"))

            if show and not mapping.display(trajectory):
                break
        else:
            initial=False

        #Swaping
        previousLeftImage=currentLeftImage
        previousRightImage=currentRightImage
        previousLeftPt=currentLeftPt

    print('Processed images: ',count)
