local function cmd_log(argv, message)
	local offset = argv[1] or 0

	local db = sqlite3.open("puppy.db")

	for row in db:nrows("SELECT * FROM users WHERE id == "..message.author.id) do
		if not row.sid64 then message.channel:send("no steam profile linked. use ``set steamid``") return end

		local logno = llogsTF.getlatestlog(row.sid64, offset)
		if logno then
			local sid3 = steam.sid64_to_sid3(row.sid64)
			print(sid3)
			local img, err = llogsTF.renderlog(logno, sid3)

			print("log! - " .. img)

			if err then print(err) end

			message.channel:send {
				content = "https://logs.tf/"..logno,
				file = img
			}

			os.remove(img)
		end
	end

	db:close()
end

return cmd_log
