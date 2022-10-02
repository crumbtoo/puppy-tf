local function cmd_echo(argv, message)
	local s = ""
	for i = 1, #argv do
		s = s .. argv[i] .. ' '
	end

	message.channel:send(s)
end

return cmd_echo

