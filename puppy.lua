#! /usr/bin/env luvit

local discordia = require("discordia")
local options = require("options")
local cmds = require("commands")
local client = discordia.Client()
_G.ffi = require("ffi")
_G.steamapi = require("./etc/steamapi"):new(options.steamapikey)
local logs = require("./etc/logs-tf.lua")
local misctf = require("./etc/misc-tf.lua")
_G.llogsTF = require("./etc/logs/llogsTF")
local timer = require("timer")
_G.steam = require("./etc/steam")
_G.sqlite3 = require("lsqlite3")
discordia.extensions()

client:on("ready", function()
	print(client.user.name .. " is up")

	-- check if db exists
	local dbcheck = io.open(options.dbname)
	if not dbcheck then
		print("database '"..options.dbname.."' not found, creating.")

		local db = sqlite3.open(options.dbname)
		db:exec("CREATE TABLE users(id text primary key, sid64 text)")
	else
		io.close(dbcheck)
	end
end)

client:on("messageCreate", function(message)
	if message.author.bot then return end

	-- if msg starts with prefix, run command
	if message.content:sub(1, #options.prefix) == options.prefix then
		local argv = message.content:split(" ")
		local command = cmds[table.remove(argv, 1):sub(2)]
		if command then
			if command.call(argv, message, options) == -1 then
				message.channel:send("usage: " .. command.usage)
			end
		end
		return
	end

	-- if msg is log
	local logno, h = logs.islogsURL(message.content)
	if logno then
		local img, err

		if h then
			img, err = llogsTF.renderlog(logno, steam.sid64_to_sid3(h))
		else
			img, err = llogsTF.renderlog(logno)
		end

		print("log! - " .. img)

		if err then print(err) end

		message.channel:send {
			content = "https://logs.tf/"..logno,
			file = img
		}

		os.remove(img)
		return
	end

	-- if msg is tf2 connect info
	if misctf.ifTF2Connect(message.content) then
		message.channel:send {
			embed = {
				title = "serveme.tf",
				description = "5/24 Players",
				url = "https://developer.valvesoftware.com/wiki/Server_queries"
			}
		}

		return
	end
end)

client:run("Bot " .. options.token)
