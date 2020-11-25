#include <evImgCover.h>
#include <opencv2/opencv.hpp>

void imageCover(std::string signalImageLocation)
{
    cv::Mat srcImg = cv::imread(originalImageLocation);
    cv::Mat signal = cv::imread(signalImageLocation);
    cv::Mat imageROI = srcImg(cv::Rect(Position.x, Position.y, signal.cols, signal.rows));
    cv::Mat mask = cv::imread(signalImageLocation, 0);
    signal.copyTo(imageROI, mask);
    std::stringstream tmp;
    tmp << Position.from;

    std::string outputImgName = tmp.str();
    outputImgName += "_";
    tmp.str("");
    tmp << Position.to;
    outputImgName += tmp.str();
    tmp.str("");
    outputImgName += ".png";
    //std::cout << outputImgName << std::endl;
    std::string preLocation = "A" + fileLocation + "_new";

    if (_access(("./" + preLocation).c_str(), 0) == -1)
        system(("mkdir " + preLocation).c_str());

    cv::imwrite(preLocation + "/" + outputImgName, srcImg);//preLocation+
    std::cout << preLocation + "/" + outputImgName << " has merged successfully" << std::endl;
}