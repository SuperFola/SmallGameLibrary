#include <Small/Scripting/Engine.hpp>

#include <fstream>
#include <sstream>

namespace sgl::Scripting
{
    bool compileScript(const std::string& file, const std::string& output)
    {
        Compiler compiler(/* debug level */ 0, ArkScriptLibDir, options);

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
}