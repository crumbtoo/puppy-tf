local steam = {}
function steam.sid64_to_sid(steamID64)
	local n = tonumber(steamID64)

	local z = math.floor((n - 76561197960265728) / 2)
	local y = n % 2
	local x = 0 -- uhhhh

	return "STEAM_" .. x .. ':' .. y .. ':' .. z
end

function steam.sid64_to_sid3(steamID64)
	local s = "[U:1:"
	ffi.cdef[[uint64_t strtoull(const char*);]]
	local n = ffi.C.strtoull(steamID64)
	local acc = n - 76561197960265728ULL
	s = s .. tonumber(acc) .. ']'

	return s
end

return steam
