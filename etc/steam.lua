local steam = {}
function steam.sid64_to_sid(steamID64)
	local n = tonumber(steamID64)

	local z = math.floor((n - 76561197960265728) / 2)
	local y = n % 2
	local x = 0 -- uhhhh

	return "STEAM_" .. x .. ':' .. y .. ':' .. z
end

function steam.sid64_to_sid3(steamID64)
	local z = math.floor((steamID64 - 76561197960265728) / 2)
	local y = steamID64 % 2

	return string.format("[U:1:%d]", z*2+y)
end

return steam
