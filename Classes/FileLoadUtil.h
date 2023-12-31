#ifndef __Chapter9_6_LoadCsv__FileLoadUtil__
#define __Chapter9_6_LoadCsv__FileLoadUtil__

#include "cocos2d.h"
#include "StringUtil.h"

class FileLoadUtil
{
public:
    
    StrVec getDataLines(const std::string &rSCsvFilePath)
    {
        StrVec linesList;
        
        if (!cocos2d::FileUtils::getInstance()->isFileExist(rSCsvFilePath))
            return linesList;
        
        ssize_t pSize = 0;
        
        StringUtil tStringUtil;
        
        std::string chDatas = cocos2d::FileUtils::getInstance()->getStringFromFile(rSCsvFilePath);
        
       linesList = tStringUtil.split(chDatas, "\n");
        
        return linesList;
    }
};

#endif 
