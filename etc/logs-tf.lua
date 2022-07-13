local http = require("coro-http")

local function islogsURL(s)
	local logno = '('..("%d"):rep(7) .. '+)'
	local pat

	pat = s:match("^"..logno.."$")
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
