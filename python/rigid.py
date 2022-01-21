import cv2
import math
import numpy as np
import tracker 

class camera:
    def __init__(self):
        #INDIAN DATASET
        imageSize=(1920,1080)
    
        leftDis=np.array([-0.177288, 0.0299518, 0.0, 0.0, 0.0])
        leftR= [[0.9999121806728741, -0.0008263015096623995, 0.013226797338454508], [0.0007244497743564737, 0.9999700663536536, 0.007703347921135117], [-0.013232766700197374, -0.007693089267956763, 0.9998828482692227]]
        leftP=np.array([[1403.11, 0.0, 1000.3, 0.0], [0.0, 1403.11, 549.43, 0.0], [0.0, 0.0, 1.0, 0.0]])

        rightDis=np.array([-0.173732, 0.0278646, 0.0, 0.0, 0.0])
        rightR=[[0.9999121806728741, -0.0008263015096623995, 0.013226797338454508], [0.0007244497743564737, 0.9999700663536536, 0.007703347921135117], [-0.013232766700197374, -0.007693089267956763, 0.9998828482692227]]
        rightP=np.array([[1401.92, 0.0, 1005.05, -168.37319999999997], [0.0, 1401.92, 620.367, 0.0], [0.0, 0.0, 1.0, 0.0]])

        t=np.array([-0.1200, 0.0, 0.0])
        r=np.array([[0.9999121806728741,-0.0008263015096623995, 0.013226797338454508],[0.0007244497743564737,    0.9999700663536536, 0.007703347921135117],[-0.013232766700197374, -0.007693089267956763,   0.9998828482692227]])

        lk, lr,lt, _, _, _, _ = cv2.decomposeProjectionMatrix(leftP)
        rk, rr,rt, _, _, _, _ = cv2.decomposeProjectionMatrix(rightP)

        self.flength = lk[0][0]
        self.baseline = rt[0] - lt[0]

        #Rectification
        r1,r2,p1,p2,Q,_,_=cv2.stereoRectify(lk,leftDis,lr,rightDis,imageSize,r,t)
        self.leftMap1,self.leftMap2=cv2.initUndistortRectifyMap(lk,leftDis,r1,p1,imageSize,cv2.CV_32FC1)
        self.rightMap1,self.rightMap2=cv2.initUndistortRectifyMap(rk,rightDis,r2,p2,imageSize,cv2.CV_32FC1)

    def rectify(self,image,c="L"):
        x=406
        y=248
        h=607
        w=1103
        if c == "L":
            image=cv2.remap(image,self.leftMap1,self.leftMap2,cv2.INTER_NEAREST)
        else:
            image=cv2.remap(image,self.rightMap1,self.rightMap2,cv2.INTER_NEAREST)
        finalimage = image[y:y+h, x:x+w]
        return finalimage


def isRotationMatrix(R) :
    Rt = np.transpose(R)
    shouldBeIdentity = np.dot(Rt, R)
    I = np.identity(3, dtype = R.dtype)
    n = np.linalg.norm(I - shouldBeIdentity)
    return n < 1e-6

def rotationMatrixToEulerAngles(R) :
    assert(isRotationMatrix(R))
    sy = math.sqrt(R[0,0] * R[0,0] +  R[1,0] * R[1,0])
    singular = sy < 1e-6
    if  not singular :
        x = math.atan2(R[2,1] , R[2,2])
        y = math.atan2(-R[2,0], sy)
        z = math.atan2(R[1,0], R[0,0])
    else :
        x = math.atan2(-R[1,2], R[1,1])
        y = math.atan2(-R[2,0], sy)
        z = 0

    return np.array([x, y, z])

def estimatePose(prvLImg,prvRImg,curLImg,curRImg,prvLPt,oldFramepose,trajectory):


    projMatL=np.array([[718.856, 0, 607.193,0],[0, 718.856,185.216, 0],[0,0, 1, 0]])
    projMatR=np.array([[718.856, 0, 607.193,-386.02567],[0, 718.856,185.216, 0],[0,0, 1, 0]])

    # projMatL=np.array([[1403.11, 0.0, 1000.3, 0.0], [0.0, 1403.11, 549.43, 0.0], [0.0, 0.0, 1.0, 0.0]])
    # projMatR=np.array([[1401.92, 0.0, 1005.05, -168.37], [0.0, 1401.92, 620.36, 0.0], [0.0, 0.0, 1.0, 0.0]])

    insMat=np.array([[projMatL[0, 0], projMatL[0, 1], projMatL[0, 2]], [projMatL[1, 0], projMatL[1, 1], projMatL[1, 2]],[projMatL[2, 0], projMatL[2, 1], projMatL[2, 2]]])
    displayScale=1
    xPadding=400
    yPadding=200
    rotation = np.zeros(shape=(3,3))
    translation = np.zeros(shape=(3,1))
    distCoeffs = np.zeros(shape=(4,1))
    rvec = np.zeros(shape=(3,1))
    inliers=0
    inlierRate=0.01
    sucess=False
    newFramepose=oldFramepose
    x=0
    z=0
   
    prvLPt,prvRPt,curLPt,curRPt=tracker.trackFeatures(curLImg,curRImg,prvLImg,prvRImg,prvLPt)
    # print((curLPt))
    points4D=cv2.triangulatePoints(projMatL,projMatR,prvLPt.transpose(),prvRPt.transpose())
    points3D=cv2.convertPointsFromHomogeneous(points4D.transpose())
    # print(points3D)
    # exit(0)
    sucess,rvec,tvec,inliers= cv2.solvePnPRansac(points3D,curLPt,insMat,distCoeffs,useExtrinsicGuess=True,iterationsCount=500,reprojectionError=0.5,confidence=0.99,flags=cv2.SOLVEPNP_ITERATIVE)
    if sucess:
        rotation,jac=cv2.Rodrigues(rvec)
        rotationInEuler=rotationMatrixToEulerAngles(rotation)

        if(abs(rotationInEuler[0])<0.1 and abs(rotationInEuler[1])<0.1 and abs(rotationInEuler[2])<0.1):
            poseNormalize=(pow(tvec[0],2) + pow(tvec[1],2) + pow(tvec[2],2))
            if (poseNormalize < 100 and poseNormalize > 0.0005*0.0005):
                rigidBodyTrans=np.linalg.inv(np.vstack((np.hstack((rotation,tvec)),np.array([0,0,0,1]))))
                newFramepose=np.matmul(oldFramepose,rigidBodyTrans)
                x=int(newFramepose[0][3])+xPadding
                z=int(newFramepose[2][3])+yPadding
                # print(CYAN.format('X: '),x,CYAN.format(' Y: '),z)
            else:
                return newFramepose,trajectory,False
        else:
            return newFramepose,trajectory,False
    else:
        return newFramepose,trajectory,False
    
    if (len(inliers)/list(curLPt.shape)[0] < inlierRate):
        return newFramepose,trajectory,False
    else:
        cv2.circle(trajectory,center=(x,z),radius=1,color=(255,0,0),thickness=1,lineType=cv2.LINE_4)

    return newFramepose,trajectory,sucess
