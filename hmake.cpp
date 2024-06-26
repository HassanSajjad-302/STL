#include "Configure.hpp"

void configurationSpecification(Configuration &config)
{
    config.ASSIGN(TranslateInclude::YES);

    DSC<CppSourceTarget> &stdhu = config.GetCppStaticDSC("stdhu");
    stdhu.getSourceTarget().PUBLIC_HU_DIRECTORIES("stl/inc");

    DSC<CppSourceTarget> &app = config.GetCppExeDSC("app").PRIVATE_LIBRARIES(&stdhu);
    app.getSourceTarget().MODULE_FILES("std.ixx");
}

void buildSpecification()
{
    // Clearing the include-directory and library-directory for stl library.

    VSTools &vsTools = toolsCache.vsTools[0];

    // This clears "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.39.33519\include"
    vsTools.includeDirectories.erase(vsTools.includeDirectories.begin());

    // This clears "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.39.33519\lib\x64"
    vsTools.libraryDirectories.erase(vsTools.libraryDirectories.begin() + 1);

    Configuration &exception = GetConfiguration("exception");
    exception.ASSIGN(ExceptionHandling::ON);

    Configuration &noException = GetConfiguration("no-exception");
    noException.ASSIGN(ExceptionHandling::OFF);

    configurationSpecification(exception);
    configurationSpecification(noException);
}

MAIN_FUNCTION