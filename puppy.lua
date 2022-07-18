#! /usr/bin/env luvit

local discordia = require("discordia")
local options = require("options")
local cmds = require("commands")
local client = discordia.Client()
_G.ffi = require("ffi")
_G.steamapi = require("./etc/steamapi"):new(options.steamapikey)
local logs = require("./etc/logs-tf.lua")
_G.llogsTF = require("./etc/logs/llogsTF")
local timer = require("timer")
_G.steam = require("./etc/steam")
_G.sqlite3 = require("lsqlite3")
discordia.extensions()

local puppypass = {
	steamapi = steamapi
}

client:on("ready", function()
	print(client.user.name .. " is up")
end)

client:on("messageCreate", function(message)
	print(message.content)

	-- if msg starts with prefix, run command
	if message.content:sub(1, #options.prefix) == options.prefix then
		local argv = message.content:split(" ")
		local command = cmds[table.remove(argv, 1):sub(2)]
		if command then
			command.call(argv, message, puppypass)
		end
		return
	end

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
			file = img
		}

		os.remove(img)
	end
	
end)

client:run("Bot " .. options.token)
