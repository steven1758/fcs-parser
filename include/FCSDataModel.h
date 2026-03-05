#ifndef FCS_DATA_MODEL_H
#define FCS_DATA_MODEL_H

#include <vector>
#include <map>
#include <string>

struct FCSParameter {
    std::string name;
    int bits;
    double amplification;
    double range;
    int decade;
};

struct FCSEvent {
    std::vector<double> parameters;
};

class FCSDataModel {
private:
    std::string version;
    std::map<std::string, std::string> keywords;
    std::vector<FCSParameter> parameters;
    std::vector<FCSEvent> events;
    
public:
    // Constructor & Destructor
    FCSDataModel() = default;
    ~FCSDataModel() = default;
    
    // Getters & Setters
    void setVersion(const std::string& ver) { version = ver; }
    std::string getVersion() const { return version; }
    
    void addKeyword(const std::string& key, const std::string& value) {
        keywords[key] = value;
    }
    std::string getKeyword(const std::string& key) const {
        auto it = keywords.find(key);
        return it != keywords.end() ? it->second : "";
    }
    
    void addParameter(const FCSParameter& param) {
        parameters.push_back(param);
    }
    const std::vector<FCSParameter>& getParameters() const {
        return parameters;
    }
    
    void addEvent(const FCSEvent& event) {
        events.push_back(event);
    }
    const std::vector<FCSEvent>& getEvents() const {
        return events;
    }
    
    size_t getEventCount() const { return events.size(); }
    size_t getParameterCount() const { return parameters.size(); }
};

#endif // FCS_DATA_MODEL_H