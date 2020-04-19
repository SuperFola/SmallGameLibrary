#include <Small/System/FileSystem.hpp>

#include <filesystem>

namespace sgl::System
{
    std::vector<std::string> listDir(const std::string& directory)
    {
        std::vector<std::string> files;

        for (const auto& entry: std::filesystem::directory_iterator(directory))
            files.push_back(entry.path().string());

        return files;
    }
}