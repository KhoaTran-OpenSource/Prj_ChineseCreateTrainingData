#include <QCoreApplication>
#include <QFile>
#include <QByteArray>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    QString path = "E:/TuDienHOA/01_DuLieu/CameraCapture/02_Data/cha_jpg_nonascii/䳗.jpg";
    QFile file(path);
    std::vector<char> buffer;
    buffer.resize(file.size());
    if (!file.open(QIODevice::ReadOnly)) {
        return 1;
    }
    file.read(buffer.data(), file.size());
    file.close();
    cv::Mat image = cv::imdecode(buffer, cv::IMREAD_UNCHANGED);
    imshow("Display Image", image);
    cv::waitKey(0);

    return 0;
}
