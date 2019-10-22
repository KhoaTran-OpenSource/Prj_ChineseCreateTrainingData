QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencvlib/lib/ -lopencv_core411 -lopencv_calib3d411 -lopencv_highgui411 -lopencv_photo411 -lopencv_imgcodecs411 -lopencv_stitching411 -lopencv_dnn411 -lopencv_imgproc411 -lopencv_ts411 -lopencv_features2d411 -lopencv_java411 -lopencv_video411 -lopencv_flann411 -lopencv_ml411 -lopencv_videoio411 -lopencv_gapi411 -lopencv_objdetect411
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencvlib/lib/ -lopencv_core411d
#else:unix: LIBS += -L$$PWD/../opencvlib/lib/ -lopencv_core411

#LIBS += C:/Workspace/OpenCV/opencv/buildMW/bin/libopencv_core411.dll
#LIBS += C:/Workspace/OpenCV/opencv/buildMW/bin/libopencv_highgui411.dll
#LIBS += C:/Workspace/OpenCV/opencv/buildMW/bin/libopencv_imgcodecs411.dll
#LIBS += C:/Workspace/OpenCV/opencv/buildMW/bin/libopencv_imgproc411.dll
#LIBS += C:/Workspace/OpenCV/opencv/buildMW/bin/libopencv_features2d411.dll
#LIBS += C:/Workspace/OpenCV/opencv/buildMW/bin/libopencv_calib3d411.dll

LIBS += -LC:/Workspace/OpenCV/opencv/buildMW/bin/ libopencv_core411 libopencv_highgui411 libopencv_imgcodecs411 libopencv_imgproc411 libopencv_features2d411 libopencv_calib3d411

INCLUDEPATH += C:/Workspace/OpenCV/opencv/modules/core/include/
INCLUDEPATH += C:/Workspace/OpenCV/opencv/modules/calib3d/include/
INCLUDEPATH += C:/Workspace/OpenCV/opencv/modules/dnn/include/
INCLUDEPATH += C:/Workspace/OpenCV/opencv/modules/features2d/include/
INCLUDEPATH += C:/Workspace/OpenCV/opencv/modules/flann/include/
INCLUDEPATH += C:/Workspace/OpenCV/opencv/modules/gapi/include/
INCLUDEPATH += C:/Workspace/OpenCV/opencv/modules/highgui/include/
INCLUDEPATH += C:/Workspace/OpenCV/opencv/modules/imgcodecs/include/
INCLUDEPATH += C:/Workspace/OpenCV/opencv/modules/imgproc/include/
INCLUDEPATH += C:/Workspace/OpenCV/opencv/modules/ml/include/
INCLUDEPATH += C:/Workspace/OpenCV/opencv/modules/objdetect/include/
INCLUDEPATH += C:/Workspace/OpenCV/opencv/modules/photo/include/
INCLUDEPATH += C:/Workspace/OpenCV/opencv/modules/stitching/include/
INCLUDEPATH += C:/Workspace/OpenCV/opencv/modules/ts/include/
INCLUDEPATH += C:/Workspace/OpenCV/opencv/modules/video/include/
INCLUDEPATH += C:/Workspace/OpenCV/opencv/modules/videoio/include/
INCLUDEPATH += C:/Workspace/OpenCV/opencv/modules/world/include/
INCLUDEPATH += C:/Workspace/OpenCV/opencv/build

DEPENDPATH += C:/Workspace/OpenCV/opencv/modules/core/include/
DEPENDPATH += C:/Workspace/OpenCV/opencv/modules/calib3d/include/
DEPENDPATH += C:/Workspace/OpenCV/opencv/modules/dnn/include/
DEPENDPATH += C:/Workspace/OpenCV/opencv/modules/features2d/include/
DEPENDPATH += C:/Workspace/OpenCV/opencv/modules/flann/include/
DEPENDPATH += C:/Workspace/OpenCV/opencv/modules/gapi/include/
DEPENDPATH += C:/Workspace/OpenCV/opencv/modules/highgui/include/
DEPENDPATH += C:/Workspace/OpenCV/opencv/modules/imgcodecs/include/
DEPENDPATH += C:/Workspace/OpenCV/opencv/modules/imgproc/include/
DEPENDPATH += C:/Workspace/OpenCV/opencv/modules/ml/include/
DEPENDPATH += C:/Workspace/OpenCV/opencv/modules/objdetect/include/
DEPENDPATH += C:/Workspace/OpenCV/opencv/modules/photo/include/
DEPENDPATH += C:/Workspace/OpenCV/opencv/modules/stitching/include/
DEPENDPATH += C:/Workspace/OpenCV/opencv/modules/ts/include/
DEPENDPATH += C:/Workspace/OpenCV/opencv/modules/video/include/
DEPENDPATH += C:/Workspace/OpenCV/opencv/modules/videoio/include/
DEPENDPATH += C:/Workspace/OpenCV/opencv/modules/world/include/
DEPENDPATH += C:/Workspace/OpenCV/opencv/build

# Default location for workspace
DEFINES += PROJECT_PATH=\\\"$$PWD\\\"
