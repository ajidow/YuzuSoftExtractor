#include <evImgCover.h>
#include <opencv2/opencv.hpp>

void evImgCover::imageCover(std::string signalImageLocation)
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

std::string evImgCover::getFileLocation()
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

void evImgCover::SetFileAfterFix(const char* FAF)
{
    fileAfterFix = FAF;
}

void evImgCover::fun()
{
    for (int cnt = 0; cnt <= 999; ++cnt)
        {
            fileNumber = cnt;
            std::string location = getFileLocation();
            if (location == "")
            {
                continue;
            }
            std::string json = JSON_Reader.readfile(location.c_str());
            //std::cout << json << std::endl;
            //rapidjson::Document doc;
           Begin(json.c_str());
        }
}

void evImgCover::Begin(const char* jsonstr)
{
    if (JSON_Reader.d.Parse(jsonstr).HasParseError())
    {
        throw std::string("parse error occured!\n");
    }
    if (!JSON_Reader.d.IsObject())
    {
        throw std::string("Should be an Object!\n");
    }

    const rapidjson::Value& vLayer = JSON_Reader.d["layers"];
    if (vLayer.IsArray())
    {
        std::stringstream tmp;
        for (rapidjson::SizeType i = 0; i < vLayer.Size(); ++i)
        {
            JSON_Reader.nameInJson[i] = vLayer[i]["name"].GetString();
        }
        JSON_Reader.nameInJson[0][1] = 'a';
        for (int i = (vLayer.Size() - 1); i >= 0; --i)
        {
            if (JSON_Reader.d.Parse(jsonstr).HasParseError())
            {
                throw std::string("parse error occured!\n");
            }
            if (JSON_Reader.nameInJson[i][1] == 'a')
            {

                tmp << vLayer[i]["layer_id"].GetInt();

                std::string originalImageName = tmp.str() + ".png";
                tmp.str("");
                originalImageLocation = "./" + fileLocation + "/" + originalImageName;
                originalImageCode = JSON_Reader.nameInJson[i][0];
                Position.from = vLayer[i]["layer_id"].GetInt();
                continue;
            }
            else if (JSON_Reader.nameInJson[i][1] == '\0')
            {
                if (JSON_Reader.nameInJson[i][0] == 'A')
                {
                    tmp << vLayer[i]["layer_id"].GetInt();
                    std::string originalImageName = tmp.str() + ".png";
                    tmp.str("");
                    originalImageLocation = "./" + fileLocation + "/" + originalImageName;
                    originalImageCode = JSON_Reader.nameInJson[i][0];
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
            if (JSON_Reader.nameInJson[i][0] == originalImageCode)
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
}