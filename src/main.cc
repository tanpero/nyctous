#include <iostream>
#include <fstream>
#include <json.hpp>

using json = nlohmann::json;

class CMake {
public:
    void LoadConfiguration(const std::string& filename) {
        std::ifstream ifs(filename);
        if (ifs.is_open()) {
            ifs >> config_json;
            ifs.close();
        } else {
            std::cerr << "Error opening file: " << filename << std::endl;
        }
    }

    void PrintConfiguration() const {
        std::cout << "Project Name: " << config_json["projectName"] << std::endl;
        std::cout << "Version: " << config_json["version"] << std::endl;
        std::cout << "Description: " << config_json["description"] << std::endl;
        std::cout << "Author: " << config_json["author"] << std::endl;
        std::cout << "License: " << config_json["license"] << std::endl;
        std::cout << "Build System: " << config_json["buildSystem"] << std::endl;
        std::cout << "C++ Standard: " << config_json["cppStandard"] << std::endl;

        std::cout << "Objects:" << std::endl;
        for (const auto& object : config_json["objects"]) {
            std::cout << "  " << object["name"] << std::endl;
            std::cout << "    Type: " << object["type"] << std::endl;
            std::cout << "    Headers:" << std::endl;
            for (const auto& header : object["header"]) {
                std::cout << "      " << header << std::endl;
            }
            std::cout << "    Sources:" << std::endl;
            for (const auto& source : object["source"]) {
                std::cout << "      " << source << std::endl;
            }
        }

        std::cout << "Dependencies:" << std::endl;
        for (const auto& dep : config_json["dependencies"].items()) {
            std::cout << "  " << dep.key() << ": " << dep.value() << std::endl;
        }

        std::cout << "Dependency Directories:" << std::endl;
        for (const auto& depDir : config_json["dependencyDirectories"]) {
            std::cout << "  " << depDir << std::endl;
        }

        std::cout << "CMake Options:" << std::endl;
        for (const auto& option : config_json["cmakeOptions"]) {
            std::cout << "  " << option << std::endl;
        }

        std::cout << "Scripts:" << std::endl;
        std::cout << "  Prebuild: " << config_json["scripts"]["prebuild"] << std::endl;
        std::cout << "  Postbuild: " << config_json["scripts"]["postbuild"] << std::endl;
    }

private:
    json config_json;
};

int main() {
    CMake cmake;
    cmake.LoadConfiguration("nyctous.json");
    cmake.PrintConfiguration();

    return 0;
}

