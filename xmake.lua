add_rules("mode.debug", "mode.release")
set_languages("cxxlatest")
add_rules("plugin.compile_commands.autoupdate", {outputdir = ".vscode"})
includes("**/xmake.lua")