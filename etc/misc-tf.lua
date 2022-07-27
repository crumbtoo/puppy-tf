local misctf = {}

function misctf.ifTF2Connect(s)
	-- no password
	local hostname, port = s:match("^connect%s+([a-zA-Z0-9_.]+):?([0-9]*)$")

	if not hostname then
		hostname, port, password = s:match('^connect%s+([a-zA-Z0-9_.]+):?([0-9]*);%s*password%s*(["a-zA-Z0-9_- ]+)$')
	end

	return hostname, port, password
end

return misctf
