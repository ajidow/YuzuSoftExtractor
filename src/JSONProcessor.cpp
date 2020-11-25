#include "JSONProcessor.h"

std::string JSON_Processor::readfile(const char* filename)
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

int JSON_Processor::ParseJson(const char* jsonstr)
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
        nameInJson[0][1] = 'a';
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
