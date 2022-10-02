local function cmd_MamaaaaaaaJustKilledAMan(argv, message)
	local i = 0
	local lastid = message.id
	local HisHead = {}

	if #argv == 0 then
		message.channel:send("usage: ``;MamaaaaaaaJustKilledAMan <deadnames...>``\n(sorry)")
		return
	end

	for i = 1, #argv do
		HisHead[i] = argv[i]:lower()
	end
	
	print('going going oing')

	while message.channel:getMessage(lastid) do
		message.channel:getMessagesBefore(lastid, 100):forEach(function(m)
			for k = 1, #HisHead do
				if string.find(m.content:lower(), HisHead[k]) then
					io.stderr:write(string.format("BAD %s: %5d [%s]:[%s] - %s\n", HisHead[k], i, m.timestamp, m.id, m.content))
					m:delete()
				end
			end

			print(string.format("%5d [%s]:[%s] - %s", i, m.timestamp, m.id, m.content))
			lastid = m.id
			i = i + 1
		end)
	end
end

return cmd_MamaaaaaaaJustKilledAMan

