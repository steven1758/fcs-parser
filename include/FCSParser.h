#ifndef FCS_PARSER_H
#define FCS_PARSER_H

#include "FCSDataModel.h"
#include <string>
#include <memory>

class FCSParser {
private:
    std::unique_ptr<FCSDataModel> dataModel;
    std::string filePath;
    
    // Helper methods
    void parseHeader(const std::string& headerData);
    void parseKeywords(const std::string& keywordData);
    void parseData(const std::string& rawData);
    std::vector<double> decodeEvent(const char* buffer, size_t& offset);
    
public:
    FCSParser();
    ~FCSParser();
    
    // Main parsing method
    bool parse(const std::string& filename);
    
    // Data access
    const FCSDataModel* getDataModel() const { return dataModel.get(); }
    FCSDataModel* getDataModel() { return dataModel.get(); }
    
    // Validation
    bool isValid() const { return dataModel != nullptr; }
    std::string getLastError() const { return lastError; }
    
private:
    std::string lastError;
};

#endif // FCS_PARSER_H
