lib = {
	path = PathDir(ModuleFilename()),
}

function lib:configure()
end

function lib:apply(settings)
	settings.cc.includes:Add("usr/include")
	settings.link.libpath:Add("/usr/lib/x86_64-linux-gnu")
	settings.link.libs:Add("sfml-system")
	settings.link.libs:Add("sfml-window")
	settings.link.libs:Add("sfml-graphics")
	settings.link.libs:Add("sfml-audio")
	settings.link.libs:Add("sfml-network")
end
