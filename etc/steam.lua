local steam = {ident = 76561197960265728}

function steam.get_sid64(s)
	local t, id = s:match("https://steamcommunity.com/(%w+)/([a-zA-Z0-9_-]+)/")
	local sid64

	if t == "id" then
		print("id")
		sid64 = steamapi:ResolveVanityURL(id).steamid
	elseif t == "profiles" then
		print("profiles")
		sid64 = id
	elseif not t then
		sid64 = steamapi:ResolveVanityURL(s)

		if not sid64 then
			if s:match("%d+") then
				return s
			end
		else
			return sid64.steamid
		end
	end


	return sid64
end

function steam.sid64_to_sid(steamID64)
	local n = tonumber(steamID64)

	local z = math.floor((n - steam.ident) / 2)
	local y = n % 2
	local x = 0 -- uhhhh

	return "STEAM_" .. x .. ':' .. y .. ':' .. z
end

function steam.sid64_to_sid3(steamID64)
	local s = "[U:1:"
	-- god i fucking hate lua 5.1
	-- this shit just turns a string into a u64
	ffi.cdef[[uint64_t strtoull(const char*);]] 
	local n = ffi.C.strtoull(steamID64)

	local acc = n - steam.ident
	s = s .. tonumber(acc) .. ']'

	return s
end

return steam
