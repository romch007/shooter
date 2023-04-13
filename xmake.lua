add_rules("mode.debug", "mode.release")

set_languages("cxx20")

add_rules("mode.debug", "mode.release", "mode.valgrind")

set_rundir(".")
set_targetdir("./build/$(plat)_$(arch)_$(mode)")

set_warnings("all")

add_requires("sfml", "cxxopts")

target("shooter")
    set_kind("binary")
    add_files("src/*.cpp")
    add_headerfiles("include/*.hpp")
    add_includedirs("include")
    add_packages("sfml", "cxxopts")
