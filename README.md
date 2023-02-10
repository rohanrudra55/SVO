# Stereo Visual Odometry

Stereo Visual Odometry Implementation in C++ on KIITI Dataset.

### Requirements

- OpenCV
- Cmake

### Usage

###### Manual
```
mkdir build
cd build
cmake ..
make
./output -h
```
###### Auto
Put the absolute path of KIITI Dataset in setup.sh file and run following.

```
sudo chmod +x setup.sh
./setup.sh
```
*Incase of `ERROR : header file not found` edit `.vscode/c_cpp_properties.json`*
---



<iframe width="560" height="315" src="https://www.youtube.com/embed/6wEz8SlAyjg" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>




---

Image Calibration

To calibrate camera parameters  take a picture of the  $7*9$ chessboard from your camera and keep the  ' *Image.jpg* ' in the **data** folder or specify the path  and run the `Helper.py` file in **src**. It will save the data in `parameters.txt` in **src** folder. By default you can use the chessboard in data folder or you can specify the path of your own files.

### Requirements

- OpenCV
- Numpy
- Matplotlib
- Argparser

For extra features run :
```bash
cd src
chmod +x Helper.py
./Helper.py -h
```
---
### Dataset Directory tree
Mini Daatset [Download](https://drive.google.com/drive/folders/1XBfhRd-oVWh8zIGadBds30igMTi7Ylom?usp=sharing)
KITTI Dataset [Download](https://www.cvlibs.net/datasets/kitti/raw_data.php)
Maintain this directory oder to avoid errors
```bash
.
├── image_00
│   ├── data  [108]
│   └── timestamps.txt
├── image_01
│   ├── data  [108]
│   └── timestamps.txt
├── image_02
│   ├── data  [108]
│   └── timestamps.txt
├── image_03
│   ├── data  [108]
│   └── timestamps.txt
├── oxts
│   ├── data  [108]
│   ├── dataformat.txt
│   └── timestamps.txt
└── velodyne_points
    ├── data  [108]
    ├── timestamps.txt
    ├── timestamps_end.txt
    └── timestamps_start.txt
```

### Project Tree
```bash
.
├── CMakeLists.txt
├── LICENSE
├── README.md
├── Research
│   ├── 10.1007@s00530-020-00662-9.pdf
│   └── SVO Paper.pdf
├── include
│   ├── feature.h
│   ├── rigid.h
│   ├── stereo.h
│   ├── system.h
│   └── utils.h
├── requirements.txt
├── setup.sh
└── src
    ├── Helper.py
    ├── Parameters
    │   ├── LeftData.csv
    │   ├── RightData.csv
    │   ├── StereoData.csv
    │   └── Stereomap.xml
    ├── feature.cpp
    ├── main.cpp
    ├── stereo.cpp
    ├── system.cpp
    └── utils.cpp
```
