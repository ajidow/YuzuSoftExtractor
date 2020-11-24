#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>
#include <io.h>
#include <sstream>
#include <opencv2/opencv.hpp>

std::string nameInJson[501];
int fileNumber = 0;
std::string fileAfterFix;
std::string originalImageLocation;
std::string jsonFileLocation;
std::string fileLocation;
char originalImageCode;

struct coordinate {
    int x;
    int y;
    int from;
    int to;
};

coordinate Position;

std::string getFileLocation()
{
    // std::string PrefileLocation = "./";
    std::string modifyFileLocation = "ev";  //modify == ev
    std::stringstream num;
    num << fileNumber;
    modifyFileLocation += num.str();       //modify == ev101
    num.str("");
    modifyFileLocation += fileAfterFix;  //modify == ev101a
    //fileLocation =PrefileLocation + modifyFileLocation;             //fileL == ./ev101a
    fileLocation = modifyFileLocation;
    if (!(_access(("./" + fileLocation).c_str(), 0) == -1))
    {
        jsonFileLocation = (modifyFileLocation + ".json");
        return jsonFileLocation;
    }
    else {
        return "";
    }
}

std::string readfile(const char* filename)
{
    FILE* fp = std::fopen(filename, "rb");
    if (!fp)
    {
        std::cout << "Open file failed!   " << "file:" << filename << std::endl;
        return "";
    }

    char* buf = new char[1024 * 1024];
    int n = fread(buf, 1, 1024 * 1024, fp);
    fclose(fp);

    std::string res;
    if (n >= 0)
    {
        res.append(buf, 0, n);
    }
    delete[]buf;
    return res;
}

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

int ParseJson2(const char* jsonstr)
{
    rapidjson::Document d;
    if (d.Parse(jsonstr).HasParseError())
    {
        throw std::string("parse error occured!\n");
    }
    if (!d.IsObject())
    {
        throw std::string("Should be an Object!\n");
    }

    const rapidjson::Value& vLayer = d["layers"];
    if (vLayer.IsArray())
    {
        std::stringstream tmp;
        for (rapidjson::SizeType i = 0; i < vLayer.Size(); ++i)
        {
            //std::cout << v[i]["name"].GetString() << std::endl;
            nameInJson[i] = vLayer[i]["name"].GetString();

        }
        nameInJson[0][1] == 'a';
        for (int i = (vLayer.Size() - 1); i >= 0; i--)//rapidjson::SizeType
        {
            //  if (_access(vLayer[i], 0) == -1)
              //    break;

            if (nameInJson[i][1] == 'a')
            {
                tmp << vLayer[i]["layer_id"].GetInt();

                std::string originalImageName = tmp.str() + ".png";
                tmp.str("");
                originalImageLocation = "./" + fileLocation + "/" + originalImageName;
                originalImageCode = nameInJson[i][0];
                Position.from = vLayer[i]["layer_id"].GetInt();
                continue;
            }
            else if (nameInJson[i][1] == '\0')
            {
                if (nameInJson[i][0] == 'A')
                {
                    tmp << vLayer[i]["layer_id"].GetInt();
                    std::string originalImageName = tmp.str() + ".png";
                    tmp.str("");
                    originalImageLocation = "./" + fileLocation + "/" + originalImageName;
                    originalImageCode = nameInJson[i][0];
                    Position.from = vLayer[i]["layer_id"].GetInt();
                }
                else {
                    tmp.str("");
                    tmp << vLayer[i]["layer_id"].GetInt();
                    Position.x = vLayer[i]["left"].GetInt();
                    Position.y = vLayer[i]["top"].GetInt();
                    Position.to = vLayer[i]["layer_id"].GetInt();
                    std::string signalImgLocation = "./" + fileLocation + "/" + tmp.str() + ".png";
                    tmp.str("");
                    imageCover(signalImgLocation);
                }
                continue;
            }
            //std::cout << nameInJson[i][1] << std::endl;
           // std::cout << originalImageName << std::endl;
            if (nameInJson[i][0] == originalImageCode)
            {
                tmp.str("");
                tmp << vLayer[i]["layer_id"].GetInt();
                Position.x = vLayer[i]["left"].GetInt();
                Position.y = vLayer[i]["top"].GetInt();
                Position.to = vLayer[i]["layer_id"].GetInt();
                std::string signalImgLocation = "./" + fileLocation + "/" + tmp.str() + ".png";
                tmp.str("");
                imageCover(signalImgLocation);
            }
        }
    }
    return 0;
}

void fun()
{
    for (int cnt = 0; cnt <= 999; ++cnt)
    {
        fileNumber = cnt;
        // fileNumber = 113;//113
        std::string location = getFileLocation();
        if (location == "")
        {
            continue;
        }
        std::string json = readfile(location.c_str());
        //std::cout << json << std::endl;
        //rapidjson::Document doc;
        ParseJson2(json.c_str());
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    //std::string a = ".//";
    //std::string b = "ev101_aa";
    //std::string res = a + b;

    fileAfterFix = "a";
    fun();
    fileAfterFix = "_a";
    fun();
    fileAfterFix = "_mm";
    fun();
    fileAfterFix = "mm";
    fun();
    return 0;
}