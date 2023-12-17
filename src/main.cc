#include <iostream>
#include <fstream>
#include <json.hpp>

using json = nlohmann::json;

class Project {

    enum CppStandard {
        CPP98, CPP03, CPP11, CPP14, CPP17, CPP20, CPP23, LASTEST,
    };

    enum BuildSystem
    {
        CMake, SCons, XMake, Bazel, Unknown,
    };

    std::string projectName;
    std::string version;
    std::string description;
    std::string author;
    std::string license;
    BuildSystem buildSystem;
    CppStandard cppStandard;

    struct Object {
        std::string name;
        enum Type {
            EXECUTABLE, DYNAMIC, STATIC,
        };
        Type type;

        std::vector<std::string> header;
        std::vector<std::string> source;
    };

    std::vector<Object> objects;

public:
    void loadConfiguration(const std::string& filename) {
        std::ifstream ifs(filename);
        if (ifs.is_open()) {
            ifs >> data;
            ifs.close();
        } else {
            std::cerr << "Error opening file: " << filename << std::endl;
        }
    }
    void setupConfiguration() {
        projectName = data["projectName"];
        version = data["version"];
        description = data["description"];
        author = data["author"];
        license = data["license"];
        auto buildSystemName = data["buildSystem"];
        if (buildSystemName == "CMake") {
            buildSystem = CMake;
        }
        else {
            buildSystem = Unknown;
        }

        cppStandard = std::map<std::string, CppStandard> {
            { "C++98", CPP98 },
            { "C++03", CPP03 },
            { "C++11", CPP11 },
            { "C++14", CPP14 },
            { "C++17", CPP17 },
            { "C++20", CPP20 },
            { "C++23", CPP23 },
        }[data["cppStandard"]];

        for (const auto& object : data["objects"]) {
            Object objectItem;
            objectItem.name = object["name"];
            objectItem.type = std::map<std::string, Object::Type>{
                { "executable", Object::EXECUTABLE },
                { "static", Object::STATIC },
                { "dynamic", Object::DYNAMIC },
            }[object["type"]];

            for (const auto& header : object["header"]) {
                objectItem.header.push_back(header);
            }
            for (const auto& source : object["source"]) {
                objectItem.source.push_back(source);
            }
        }
    }

    void printConfiguration() const {
        std::cout << "Project Name: " << data["projectName"] << std::endl;
        std::cout << "Version: " << data["version"] << std::endl;
        std::cout << "Description: " << data["description"] << std::endl;
        std::cout << "Author: " << data["author"] << std::endl;
        std::cout << "License: " << data["license"] << std::endl;
        std::cout << "Build System: " << data["buildSystem"] << std::endl;
        std::cout << "C++ Standard: " << data["cppStandard"] << std::endl;

        std::cout << "Objects:" << std::endl;
        for (const auto& object : data["objects"]) {
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
        for (const auto& dep : data["dependencies"].items()) {
            std::cout << "  " << dep.key() << ": " << dep.value() << std::endl;
        }

        std::cout << "Dependency Directories:" << std::endl;
        for (const auto& depDir : data["dependencyDirectories"]) {
            std::cout << "  " << depDir << std::endl;
        }

        std::cout << "Project Options:" << std::endl;
        for (const auto& option : data["ProjectOptions"]) {
            std::cout << "  " << option << std::endl;
        }

        std::cout << "Scripts:" << std::endl;
        std::cout << "  Prebuild: " << data["scripts"]["prebuild"] << std::endl;
        std::cout << "  Postbuild: " << data["scripts"]["postbuild"] << std::endl;
    }

    void generateCMakeLists() const {

        std::ofstream outputFile("CMakeLists.txt");

        outputFile << "cmake_minimum_required(VERSION 3.10)\n";
        outputFile << "project(" << data["projectName"] << " VERSION " << data["version"] << ")\n";
        outputFile << "set(CMAKE_CXX_STANDARD " << data["cppStandard"] << ")\n\n";
    }

private:
    json data;
};

int main() {
    Project Project;
    Project.loadConfiguration("nyctous.json");
    Project.printConfiguration();

    return 0;
}

