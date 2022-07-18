local http = require("coro-http")

local function islogsURL(s)
	local logno = '(%d+)'
	local pat

	-- only match lone numbers on 6+ digits to avoid matching non-logs
	pat = s:match("^%d%d%d%d%d%d+$")
	if pat then
		return pat
	end

	pat = s:match("^https://www%.logs%.tf/"..logno..'$')
	if pat then
		return pat
	end
	pat = s:match("^https://logs%.tf/"..logno.."$")
	if pat then
		return pat
	end

	pat = s:match("^www%.logs%.tf/"..logno.."$")
	if pat then
		return pat
	end

	pat = s:match("^logs%.tf/"..logno.."$")
	if pat then
		return pat
	end

	return false
end

return {
	islogsURL = islogsURL
}
