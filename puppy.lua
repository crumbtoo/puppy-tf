#! /usr/bin/env luvit

local discordia = require("discordia")
local options = require("options")
local cmds = require("commands")
local client = discordia.Client()
_G.steamapi = require("./etc/steamapi"):new(options.steamapikey)
local logs = require("./etc/logs-tf.lua")
local llogsTF = require("./etc/logs/llogsTF")
local timer = require("timer")
_G.steam = require("./etc/steam")
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

	local logno = logs.islogsURL(message.content)
	if logno then
		local img, err = llogsTF.renderlog(logno, "[U:1:377439446]")

		print("log! - " .. img)

		if err then print(err) end


		message.channel:send {
			file = img
		}
	end
	
end)

client:run("Bot " .. options.token)
