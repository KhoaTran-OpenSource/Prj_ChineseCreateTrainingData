#include <QCoreApplication>
#include <QFile>
#include <QByteArray>
#include <QDir>
#include <QDataStream>
#include <QDebug>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace std;
using namespace cv;

#define W 384
#define H 384

QString separate = ",";
QString training_data = "";
QByteArray sepa;

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

int ImageLabeling(Mat image, QDataStream&outstream)
{
    int result = 0;
    uint total_w = 0;
    uint total_h = 0;

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
            total_w += (uint)w;
            total_h += (uint)h;
//            std::cout << "x=" << x << " y=" << y << " w=" << w << " h=" << h << std::endl;
//            Scalar color(255, 0, 0);
//            Rect rect(x, y, w, h);
//            cv::rectangle(image, rect, color);
        }
    }

    // write Image labeling
    QString s_label = QString::number(result);
    outstream.writeRawData(sepa.data(), 1);
    outstream.writeRawData(s_label.toUtf8().data(), s_label.size());

    QString s_total_w = QString::number(total_w * 99 / (W));
    QString s_total_h = QString::number(total_h * 99 / (H));

    outstream.writeRawData(sepa.data(), 1);
    outstream.writeRawData(s_total_w.toUtf8().data(), s_total_w.size());

    outstream.writeRawData(sepa.data(), 1);
    outstream.writeRawData(s_total_h.toUtf8().data(), s_total_h.size());

    return result;
}

void ImageContours(Mat image, QDataStream&outstream)
{
    // Find all the Contours in the thresholded image
    vector<vector<Point>> contours;
    findContours(image, contours, RETR_LIST, CHAIN_APPROX_NONE);

    outstream.writeRawData(sepa.data(), 1);
    QString s_contours = QString::number(contours.size());
    outstream.writeRawData(s_contours.toUtf8().data(), s_contours.size());
}

int main(int argc, char *argv[])
{
    QString defaultLocation = PROJECT_PATH;
    training_data = defaultLocation + "/data/";
    sepa = separate.toUtf8();

    // End line
    QByteArray line_end;
    line_end.resize(2);
    line_end[0] = 0x0D;
    line_end[1] = 0x0A;

    QFile outfile(defaultLocation + "/chinese_letter.data");
    outfile.open(QIODevice::WriteOnly);
    QDataStream outstream(&outfile);

    uint numofimages = 1;
    QDir directory(training_data);
    QStringList images = directory.entryList(QStringList() << "*.jpg" << "*.JPG",QDir::Files);
    foreach(QString filename, images) {
        if(numofimages >= 2)
        {
            outstream.writeRawData(line_end.data(), 2);
        }

        QString path = training_data + filename;
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

        cout << "Index: " << numofimages++ << std::endl;

        QByteArray myStringChars = filename.remove(1, 4).toUtf8();

        // write character
        outstream.writeRawData(myStringChars.data(), 3);
        outstream.writeRawData(sepa.data(), 1);

        // write number of black
        QString s_black_pixels = QString::number(black_pixels * 99 / (W * H));
        outstream.writeRawData(s_black_pixels.toUtf8().data(), s_black_pixels.size());
        outstream.writeRawData(sepa.data(), 1);

        // write number of black
        QString s_white_pixels = QString::number(white_pixels * 99 / (W * H));
        outstream.writeRawData(s_white_pixels.toUtf8().data(), s_white_pixels.size());

        // Image labeling
        ImageLabeling(image, outstream);

        // Contours
        ImageContours(bw, outstream);

    }

    outfile.flush();
    outfile.close();

    return 0;
}
