
import cv2
import numpy as np
import mapping

def detectFeatures(image):
    fast = cv2.FastFeatureDetector_create()
    # fast.setThreshold(80)
    keypoint = fast.detect(image,None)
    points = cv2.KeyPoint_convert(keypoint)
    # print(len(points))
    # exit(0)
    return points
def limitFeatures(features):
    total=len(features)
    if total >1500:
        features=features[:1500]
    # print("Reduced features form",total,"to","less than 1000")
    return features

def trackFeatures(currentLeft,currentRight,previousLeft,previousRight,prvLPt):
    lk_params = dict( winSize = (21, 21),maxLevel = 3,
                  criteria = (cv2.TERM_CRITERIA_EPS | cv2.TERM_CRITERIA_COUNT,30, 0.01))
    prvLPt=limitFeatures(prvLPt)
    prvRPt,prvRst,err0 = cv2.calcOpticalFlowPyrLK(previousLeft,previousRight,prvLPt,None,**lk_params)
    curRPt,curRst,err1 = cv2.calcOpticalFlowPyrLK(previousRight,currentRight,prvRPt,None,**lk_params)
    curLPt,curLst,err2 = cv2.calcOpticalFlowPyrLK(currentRight,currentLeft,curRPt,None,**lk_params)
    prvNLPt,prvNLst,err3 = cv2.calcOpticalFlowPyrLK(currentLeft,previousLeft,curLPt,None,**lk_params)
    # print(len(prvRPt),len(curRPt),len(curLPt))
    visimg=mapping.visualise2D(currentLeft,prvLPt,curLPt,True)
    mapping.display(visimg,"Features")
    # return prvLPt,prvRPt,curLPt,curRPt

    #Filtering Bad Matches
    indexError = 0
    totalPoints = list(prvNLst.shape)[0]
    for size_ in range(totalPoints):

        pt0 = prvLPt[size_ - indexError]
        pt1 = prvRPt[size_ - indexError]
        pt2 = curLPt[size_ - indexError]
        pt3 = curRPt[size_ - indexError]
        pt4 = prvNLPt[size_ - indexError]

        outsideFrame = ((pt0[0]<0 or pt1[0]<0 or pt2[0]<0 or pt3[0]<0 or pt4[0]<0) or 
                            (pt0[1]<0 or pt1[1]<0 or pt2[1]<0 or pt3[1]<0 or pt4[1]<0))
        badstatus = (prvRst[size_]==0 or prvNLst[size_]==0 or curLst[size_]==0 or curRst[size_]==0)
        NoStereo = ((abs(pt0[1]-pt1[1])>3) or (abs(pt2[1]-pt3[1])>3))

        if(outsideFrame or badstatus or NoStereo):
            rmIndex=size_-indexError
            indexError+=1
            prvLPt=np.delete(prvLPt,rmIndex,axis=0)
            prvRPt=np.delete(prvRPt,rmIndex,axis=0)
            curLPt=np.delete(curLPt,rmIndex,axis=0)
            curRPt=np.delete(curRPt,rmIndex,axis=0)
            prvNLPt=np.delete(prvNLPt,rmIndex,axis=0)
    visimg=mapping.visualise2D(currentLeft,prvLPt,curLPt,True)
    mapping.display(visimg,"Features")
    # print(len(prvRPt),len(curRPt),len(curLPt),indexError)
    return prvLPt,prvRPt,curLPt,curRPt
