#include <Small/Scripting/Engine.hpp>

#include <Small/System/FileSystem.hpp>
#include <fstream>
#include <sstream>

namespace sgl::Scripting
{
    bool compileScript(const std::string& file, const std::string& output, const std::string& arkscriptLibDir)
    {
        Compiler compiler(/* debug level */ 0, arkscriptLibDir, options);

        std::ifstream fileStream(file);
        std::stringstream buffer;
        buffer << fileStream.rdbuf();
        fileStream.close();

        try
        {
            compiler.feed(buffer.str(), file);
            compiler.compile();

            if (output != "")
                compiler.saveTo(output);
            else
                compiler.saveTo(file.substr(0, file.find_last_of('.')) + ".arkc");
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
        // remove files aren't ArkScript files
        files.erase(std::remove_if(
            files.begin(), files.end(),
            [](const std::string& entry) {
                return entry.substr(file.find_last_of('.')) == ".ark";
            }));

        int size = static_cast<int>(files.size());
        int count = 0;

        for (const auto& file : files)
        {
            if (compileScript(file, outputDir, arkscriptLibDir))
                count++;
        }
        return count;
    }
}