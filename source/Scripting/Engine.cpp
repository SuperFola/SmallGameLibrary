#include <Small/Scripting/Engine.hpp>

#include <Small/System/FileSystem.hpp>
#include <fstream>
#include <sstream>

namespace sgl::Scripting
{
    bool compileScript(const std::string& file, const std::string& output, const std::string& arkscriptLibDir)
    {
        Ark::Compiler compiler(/* debug level */ 0, arkscriptLibDir);

        std::ifstream fileStream(file);
        std::stringstream buffer;
        buffer << fileStream.rdbuf();
        fileStream.close();

        try
        {
            compiler.feed(buffer.str(), file);
            compiler.compile();
            compiler.saveTo(output + "/" + std::filesystem::path(file.substr(0, file.find_last_of('.')) + ".arkc").filename().string());
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
            return false;
        }
        catch (...)
        {
            std::cerr << "[ArkScript] Unknown lexer-parser-or-compiler error" << std::endl;
            return false;
        }

        return true;
    }

    int compileAllScriptsIn(const std::string& path, const std::string& outputDir, const std::string& arkscriptLibDir)
    {
        std::vector<std::string> files = System::listDir(path);

        int size = static_cast<int>(files.size());
        int count = 0;

        for (const auto& file : files)
        {
            // only keep arkscript files
            if (file.substr(file.find_last_of('.')) != ".ark")
                continue;

            if (compileScript(file, outputDir, arkscriptLibDir))
                count++;
        }
        return count;
    }
}