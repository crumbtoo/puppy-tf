local user_options = {}


local function uo_steamid(argv, message, db)
	if not argv[2] then 
		message.channel:send("usage: ``set steamid [vanity URL | steamid64 | steam profile link]``")
		return
	end

	local n = 0

	for row in db:nrows("SELECT 1 FROM users WHERE id == "..message.author.id) do
		n = 1
		local pat = argv[2]:match("https://steamcommunity%.com/id/(%w+)/?")
		local sid

		if pat then
			sid = pat
			print(sid)
		else
			pat = argv[2]:match("https://steamcommunity%.com/profiles/(%d+)/?")
			if pat then
				sid = steamapi:ResolveVanityURL(pat).steamid
				if not sid then message.channel:send("invalid vanity URL") end
				print(sid)
			else
				sid = steamapi:ResolveVanityURL(argv[2]).steamid
				if not sid then message.channel:send("invalid vanity URL") end
				print(sid)
			end
		end

		
		local stmt = db:prepare("UPDATE users SET sid64 = ?")
		stmt:bind_values(sid)
		stmt:step()
		stmt:reset()
	end
	
	if n == 0 then
		local stmt = db:prepare("INSERT INTO users VALUES (?, ?);")
		stmt:bind_values(message.author.id, argv[2])
		stmt:step()
		stmt:finalize()
	end
end

user_options["steamid"] = uo_steamid

local function cmd_set(argv, message)
	local db;

	local f = io.open("puppy.db", "r")
	if f == nil then
		db = sqlite3.open("puppy.db")
		db:exec[=[
			CREATE TABLE users(id text primary key, sid64 text)
		]=]
	else
		io.close(f)
		db = sqlite3.open("puppy.db")
	end

	if user_options[argv[1]] then
		user_options[argv[1]](argv, message, db)
	end
	db:close();
end

return cmd_set
