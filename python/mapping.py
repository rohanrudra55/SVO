import cv2
import numpy as np
import matplotlib.pyplot as plt

def display(image=None,tag="Image"):
    cv2.imshow(tag,image)
    if cv2.waitKey(1)==27:
        cv2.destroyAllWindows()
        return False
    return True


def visualise2D(image,keypoints1,keypoints2,both=False):
    radius = 2
    visualize=cv2.cvtColor(image,cv2.COLOR_GRAY2BGR,3)
    for point in keypoints1:
        cv2.circle(visualize,(int(point[0]),int(point[1])),radius=2,color=(0,255,0))
    if both:
        for point in keypoints2:
            cv2.circle(visualize,(int(point[0]),int(point[1])),radius=2,color=(0,0,255))
    return visualize

def visualize_trajectory_2d(xpose,ypose,markx,marky,path_name="trajectory",show_ori=False):
    fig,ax = plt.subplots(figsize=(5,5))
    n_pose = len(xpose)
    ax.plot(xpose,ypose,'r-',label=path_name) # pose[0,3,:] -> x , pose[1,3,:] -> y
    ax.scatter(xpose[0],ypose[0],marker='s',label="start")
    ax.scatter(xpose[-1],ypose[-1],marker='o',label="end")
    
    # plot landmarks
    ax.scatter(markx, marky, 1, label="landmarks")

    # if show_ori:
    #     select_ori_index = list(range(0,n_pose,max(int(n_pose/50), 1)))
    #     yaw_list = []
        
    #     # for i in select_ori_index:
    #     #     _,_,yaw = mat2euler(pose[:3,:3,i])
    #     #     yaw_list.append(yaw)
    
    #     dx = np.cos(yaw_list)
    #     dy = np.sin(yaw_list)
    #     dx,dy = [dx,dy]/np.sqrt(dx**2+dy**2)
    #     ax.quiver(pose[0,3,select_ori_index],pose[1,3,select_ori_index],dx,dy,\
    #         color="b",units="xy",width=1)
    
    ax.set_xlabel('x')
    ax.set_ylabel('y')
    ax.axis('equal')
    ax.grid(False)
    ax.legend()
    plt.show(block=True)
    return fig, ax