local http = require('coro-http')
local json = require('json')
local timer = require('timer')

local steamapi = {
	key = "",
	base = "http://api.steampowered.com/ISteamUser/"
}

function steamapi:new(apikey)
	local s = {}
	setmetatable(s, self)
	self.__index = self
	self.key = apikey
	return s
end

function steamapi:formurl(m, ...)
	local s = self.base .. m .. "?key=" .. self.key
	local vargs = {...}

	for _, v in ipairs(vargs) do
		s = s .. "&" .. v
	end
	
	return s
end

function steamapi:ResolveVanityURL(vanityurl)

	local url = steamapi:formurl("ResolveVanityURL/v0001/", "vanityurl=" .. vanityurl)

	local res, body = http.request("GET", url)

	if res.code > 299 then
		print("failed to fetch: " .. res.reason)
		return
	else
		local j = json.parse(body).response
		if j.success == 1 then
			return j
		else
			print("ResolveVanityURL: steam success != 1")
			return j
		end
	end
end

function steamapi:GetPlayerSummaries(steamids)
	local url = steamapi:formurl("GetPlayerSummaries/v0002/", "steamids=" .. steamids)

	local res, body = http.request("GET", url)

	if res.code > 299 then
		print("failed to fetch: " .. res.reason)
		return
	else
		local j = json.parse(body).response
		return j
	end
end


return steamapi
