#ifndef __Chapter14_2_CardDefence01__CsvUtil__
#define __Chapter14_2_CardDefence01__CsvUtil__

#include <vector>
#include <map>
#include <string>

typedef std::vector<std::string> StrVec;

typedef std::vector< StrVec > StrDict;

typedef std::map< std::string, StrDict> CsvMap;

class CsvUtil
{
public:
    
    static CsvUtil* getInstance();
    
    static void destroyInstance();
    
    
    virtual void addFileData(const std::string &rSPath);
    
    
    virtual void releaseFile(const std::string &rSPath);
    

    virtual std::string getText(const int &rRow, const int &rCol, const std::string &rSCsvFilePath);
    virtual int getInt(const int &rRow, const int &rCol, const std::string &rSCsvFilePath);
    virtual double getDouble(const int &rRow, const int &rCol, const std::string &rSCsvFilePath);
    
    
    virtual StrVec getRowData(const int &rIRow, const std::string &rSCsvFilePath);
    
    virtual std::tuple<int, int> getFileRowColNum(const std::string &rSCsvFilePath);
    
    virtual int findValueInWithLine(const std::string &rSValue, const int &rIValueCol, const std::string &rSCsvFilePath);

protected:
   
    virtual StrDict &getFileDict(const std::string &rSCsvFilePath);
    
    virtual ~CsvUtil();
    
private:
    
    CsvUtil();
    
    CsvUtil(const CsvUtil &rCsvUtil) = delete;
    
    CsvUtil &operator=(const CsvUtil &rCsvUtil) = delete;
    
private:
    
    static CsvUtil* _gInstance;
    
    CsvMap* _pCsvMap;
};

#endif 
