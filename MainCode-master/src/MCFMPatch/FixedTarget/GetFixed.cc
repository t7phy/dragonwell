#include "NonPertFit/FixedTarget.hh"
#include "ResBos/loguru.hpp"

int main(int argc, char** argv)
{
    std::string fitting_config = "fixedtarget.config";
    // Startup logger
    loguru::g_stderr_verbosity = loguru::Verbosity_WARNING;

    FixedTarget m;
    m.global_settings = std::unique_ptr<IO::Settings>(new IO::Settings(fitting_config));
    m.ReadFile("e906aF_pd");

    return 1;
}
