#ifndef OPTION_PARSER_HPP
#define OPTION_PARSER_HPP

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <cctype>

class OptionParser {
private:
    // members
    std::string name_;
    std::vector<std::string> options_;
    std::vector<std::string> params_;

public:
    // methods
    OptionParser(const int argc, char **argv) {
        name_ = std::string(argv[0]);
        if (argc > 1) {
            for (int i=1; i<argc; ++i) {
                std::string temp = argv[i];
                if(temp[0] == '-' && !(std::isdigit(temp[1]))) {
                    options_.push_back(std::string(temp));
                }
                else {
                    params_.push_back(std::string(temp));
                }
            }
        }
    }
    ~OptionParser() {}

    bool HasParams() {
        return ( params_.size() > 0);
    }

    std::string GetParam(int index) {
        if(index >= params_.size()){
            throw std::string("No such parameter exists!");
        }
        return params_[index];
    }

    bool HasOptions() {
        return (! options_.empty());
    }
    bool HasValue(const std::string & option) {
        std::string param = option + "=";
        for (auto op : options_) {
            if (op.rfind(param, 0) == 0) {
                return true;
            }
        }
        return false;
    }

    bool HasFlag(const std::string & option) {
        auto found = std::find(options_.begin(), options_.end(), option);
        if (found != options_.end()) {
            return true;
        }
        return false;
    }
    double GetDouble(const std::string & option) {
        double value = 0.0;
        value = std::stod(GetString(option));
        return value;
    }
    int GetInteger(const std::string & option) {
        int value = 0;
        value = std::stoi(GetString(option));
        return value;
    }
    std::string GetString(const std::string & option) {
        std::string param = option + "=";
        std::string value = "";
        for (auto op : options_) {
            if (op.rfind(param, 0) == 0) {
                std::size_t ePos = op.find("=");
                ++ePos;
                value = op.substr(ePos);
                break;
            }
        }
        return std::move(value);
    }
};

#endif // OPTION_PARSER_HPP
