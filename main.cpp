#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
Mat  Image;
Mat Mopology(Mat);
Mat Mopology1(Mat);
int main()
{
    vector<Vec4i> hierarchy;
    Mat mask,result,img_threshold;
    VideoCapture cam("C:/Users/ksrnd/Desktop/Light/real/2019040101_30.avi");
    //    Image = imread("C:/Users/ksrnd/Desktop/Light/real/20190401_01_30.png");
    while (true) {
        cam >> Image;
        Mat img_hsv;
        cvtColor(Image,img_hsv,COLOR_RGB2HSV);
        inRange(img_hsv, Scalar(0, 0, 255), Scalar(179, 255, 255), mask);

        Mopology(mask);
        imshow("mask1",mask);
        Mat ImageRoi;
        vector<vector<Point>> contours,contours1;
        vector<vector<Point>> RoiContours;
        findContours( mask, contours, CV_RETR_EXTERNAL, CHAIN_APPROX_SIMPLE );
        vector<vector<Point>> contours_poly(contours.size());
        vector<Rect> boundRect(contours.size());
        Rect bounding_rect;
        Rect Roi_rect;
        for ( size_t i=0; i<contours.size(); i++) {

            Roi_rect=boundingRect(contours[i]);
            approxPolyDP(contours[i],contours_poly[i],3,true);
            boundRect[i]=boundingRect(contours_poly[i]);
            int X = boundRect[i].x-100;
            int Y = boundRect[i].y-50;
            int H = boundRect[i].height+150;
            int W = boundRect[i].width+150;

            ImageRoi=Image(Rect(X,Y,W,H));
            rectangle(Image, Rect(X,Y,W,H),  Scalar(0,255,255),1, 4,0);

            imshow("ImageRoi",ImageRoi);
        }


        cvtColor(ImageRoi,mask,COLOR_RGB2GRAY);


//            const int MEDIAN_BLUR_FILTER_SIZE = 11;
//            medianBlur(mask, mask, MEDIAN_BLUR_FILTER_SIZE);
//            Mat edges;
//            const int LAPLACIAN_FILTER_SIZE = 5;
//            Laplacian(mask, mask, CV_8U, LAPLACIAN_FILTER_SIZE);
//            const int EDGES_THRESHOLD = 80;
//            threshold(mask, mask, EDGES_THRESHOLD, 255, THRESH_BINARY);
        blur(ImageRoi, mask, Size(3, 3));
        Canny(ImageRoi, mask, 70, 150, 3);
        imshow("threshold",mask);
        Mopology1(mask);
        findContours( mask, contours1, CV_RETR_EXTERNAL, CHAIN_APPROX_SIMPLE );

        for( int i = 0; i< contours1.size(); i++ ) {
            bounding_rect=boundingRect(contours1[i]);
//            rectangle(ImageRoi, bounding_rect,  Scalar(0,255,255),1, 4,0);

            Point centerRect = (bounding_rect.tl()+bounding_rect.br())*0.5;

            circle(ImageRoi,centerRect,3,Scalar(255,0,255));
        }
        imshow("mask",mask);
        imshow("Image",Image);
        if (waitKey(1)==27)break;
    }


//    waitKey();

}
Mat Mopology(Mat mask)
{
    //Expanding Function, reducing Function
    Mat element = getStructuringElement(MORPH_RECT,Size(7,7));
    morphologyEx(mask,mask,MORPH_CLOSE,element,Point(-1,-1),20);
    erode(mask, mask, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    erode(mask, mask, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    erode(mask, mask, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    erode(mask, mask, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    erode(mask, mask, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    erode(mask, mask, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

    return mask;
}
Mat Mopology1(Mat mask)
{
    //Expanding Function, reducing Function
    Mat element = getStructuringElement(MORPH_RECT,Size(3,7));
    morphologyEx(mask,mask,MORPH_CLOSE,element,Point(-1,-1),11);
    erode(mask, mask, getStructuringElement(MORPH_RECT, Size(4, 2)) );
    erode(mask, mask, getStructuringElement(MORPH_RECT, Size(4, 2)) );
    erode(mask, mask, getStructuringElement(MORPH_RECT, Size(4, 2)) );
    erode(mask, mask, getStructuringElement(MORPH_RECT, Size(4, 2)) );
    erode(mask, mask, getStructuringElement(MORPH_RECT, Size(4, 2)) );
    erode(mask, mask, getStructuringElement(MORPH_RECT, Size(4, 2)) );
    erode(mask, mask, getStructuringElement(MORPH_RECT, Size(4, 2)) );
    erode(mask, mask, getStructuringElement(MORPH_RECT, Size(4, 2)) );
    erode(mask, mask, getStructuringElement(MORPH_RECT, Size(4, 2)) );


    return mask;
}
