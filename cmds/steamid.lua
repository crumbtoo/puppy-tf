-- return function(argv, message)
-- 	local id = argv[1]
-- 	local n = steamapi:ResolveVanityURL(id).steamid
-- 	message.channel:send(n)
-- end

local function colorFromStatus(status)
	if status == 0 then return 0x343738 end -- offline (or private)
	if status == 1 then return 0x4cafda end -- online
	if status == 2 then return 0x173948 end -- busy
	if status == 3 then return 0xcdc11a end -- away
	if status == 4 then return 0x000e35 end -- snooze
	return 0x1d1f23
end

return function(argv, message)
	local id = steam.get_sid64(argv[1])

	print("sid64: "..id)
	local summary = steamapi:GetPlayerSummaries(id).players[1]

	message.channel:send({
		embed = {
			type = "rich",
			-- title = summary.personaname,
			-- description = "madeline/sydney", --	real name and location
			color = colorFromStatus(summary.personastate),
			fields = {
				{
					name = "SteamID",
					value = '`'..steam.sid64_to_sid(id)..'`',
					inline = false
				},
				{
					name = "SteamID3",
					value = '`'..steam.sid64_to_sid3(id)..'`',
				},
				{
					name = "SteamID64",
					value = '`'..id..'`'
				}
			},
			author = {
				name = summary.personaname,
				url = summary.profileurl,
				icon_url = summary.avatarfull
			}
			-- author = {
			-- 	name = "mime girl",
			-- 	url = "https://steamcommunity.com/id/crumbt00/",
			-- 	icon_url = "https://avatars.akamai.steamstatic.com/a8205a238312dd04bc44af504609319987f76368_full.jpg"
			-- }
		}
	})

	print(summary.personaname)
	print(summary.profileurl)
	print(summary.avatarfull)
end
