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

---

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
### Directory tree
Maintain this directory oder to avoid errors
```bash
├── data
│   ├── mav0
│   │   ├── cam0
│   │   │   └── data
│   │   └── cam1
│   │       └── data
│   └── mini
│       ├── cam0
│       │   └── data
│       ├── cam1
│       │   └── data
│       └── imu0
├── include
└── src
```
