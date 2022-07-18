return function(argv, message)
	local id = argv[1]
	local n = steamapi:ResolveVanityURL(id).steamid
	message.channel:send(n)
end
