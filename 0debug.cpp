#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv)
{
    Mat img1 = imread("image1.jpg");
    Mat img2 = imread("image2.jpg");

    Mat gray1, gray2;
    cvtColor(img1, gray1, COLOR_BGR2GRAY);
    cvtColor(img2, gray2, COLOR_BGR2GRAY);

    CascadeClassifier face_cascade;
    face_cascade.load("haarcascade_frontalface_default.xml");

    std::vector<Rect> faces1, faces2;
    face_cascade.detectMultiScale(gray1, faces1, 1.1, 5);
    face_cascade.detectMultiScale(gray2, faces2, 1.1, 5);

    for (size_t i = 0; i < faces1.size(); i++)
    {
        rectangle(img1, faces1[i], Scalar(0, 255, 0), 2);
    }
    for (size_t i = 0; i < faces2.size(); i++)
    {
        rectangle(img2, faces2[i], Scalar(0, 255, 0), 2);
    }

    imshow("Image 1", img1);
    imshow("Image 2", img2);
    waitKey(0);
    destroyAllWindows();

    if (faces1.size() > 0)
    {
        Rect roi1 = faces1[0];
        Mat face1 = gray1(roi1);
        resize(face1, face1, Size(128, 128));
        Mat features1 = face1.reshape(1, 1);

        if (faces2.size() > 0)
        {
            Rect roi2 = faces2[0];
            Mat face2 = gray2(roi2);
            resize(face2, face2, Size(128, 128));
            Mat features2 = face2.reshape(1, 1);

            double distance = norm(features1, features2, NORM_L2);

            if (distance < 100)
            {
                printf("Same person\n");
            }
            else
            {
                printf("Different person\n");
            }
        }
        else
        {
            printf("No face detected in image 2\n");
        }
    }
    else
    {
        printf("No face detected in image 1\n");
    }

    return 0;
}
