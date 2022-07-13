return function(argv, message)
	local s = ""
	local id = argv[1]
	local n = steamapi:ResolveVanityURL(id).steamid
	message.channel:send(n)
end
