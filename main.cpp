#include <QCoreApplication>
#include <QFile>
#include <QByteArray>
#include <QDir>
#include <QDebug>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace std;
using namespace cv;

Mat ReadImageFromNonAsciiName(QString path)
{
    QFile file(path);
    std::vector<char> buffer;
    buffer.resize(file.size());

    file.open(QIODevice::ReadOnly);
    file.read(buffer.data(), file.size());
    file.close();

    Mat image = imdecode(buffer, cv::IMREAD_UNCHANGED);

    return image;
}

void CountBlackWhite(Mat bw, uint* black_pixels, uint* white_pixels)
{
    uint black = 0;
    uint white = 0;
    for (int i = 0; i < bw.cols; i++) {
        for (int j = 0; j < bw.rows; j++) {
            uchar pixelGrayValue = bw.at<uchar>(j, i);
            if (pixelGrayValue) white++;
            else black++;
        }
    }

    *black_pixels = black;
    *white_pixels = white;
}

int ImageLabeling(Mat image)
{
    int result = 0;

    cv::Mat gray_mat(image.size(), CV_8U);
    cv::cvtColor(image, gray_mat, COLOR_BGR2GRAY);

    Mat image_th;
    threshold(gray_mat, image_th, 10, 255, cv::THRESH_BINARY_INV);

    Mat labels;
    Mat stats;
    Mat centroids;
    cv::connectedComponentsWithStats(image_th, labels, stats, centroids);

    for (int i = 0; i < stats.rows; i++)
    {
        int x = stats.at<int>(Point(0, i));
        int y = stats.at<int>(Point(1, i));
        int w = stats.at<int>(Point(2, i));
        int h = stats.at<int>(Point(3, i));

        if((w != image.cols) && (h != image.rows))
        {
            result++;
//            std::cout << "x=" << x << " y=" << y << " w=" << w << " h=" << h << std::endl;
//            Scalar color(255, 0, 0);
//            Rect rect(x, y, w, h);
//            cv::rectangle(image, rect, color);
        }
    }

    return result;
}

int main(int argc, char *argv[])
{
    uint numofimages = 1;
    QDir directory("E:/TuDienHOA/01_DuLieu/CameraCapture/02_Data/cha_jpg_nonascii/");
    QStringList images = directory.entryList(QStringList() << "*.jpg" << "*.JPG",QDir::Files);
    foreach(QString filename, images) {
        QString path = "E:/TuDienHOA/01_DuLieu/CameraCapture/02_Data/cha_jpg_nonascii/" + filename;
        Mat image = ReadImageFromNonAsciiName(path);

        // Convert image to grayscale
        Mat gray;
        cvtColor(image, gray, COLOR_BGR2GRAY);

        // Convert image to binary
        Mat bw;
        threshold(gray, bw, 50, 255, THRESH_BINARY | THRESH_OTSU);imshow("Display Image", bw);
        //! [pre-process]

        // Black and white counting
        //! [black and white]
        uint black_pixels = 0;
        uint white_pixels = 0;

        CountBlackWhite(bw, &black_pixels, &white_pixels);

        // Image labeling
        uint numoflabel = ImageLabeling(image);

        cout
            << "Index: " << numofimages++
            << " - Number of label: " << numoflabel
            << " - Black pixels: " << black_pixels
            << " - White pixels: " << white_pixels
            << std::endl;
    }

    return 0;
}
