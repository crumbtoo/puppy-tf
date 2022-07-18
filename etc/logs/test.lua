#! /usr/bin/env luvit

local llogsTF = require("llogsTF")

-- local ret, err = llogsTF.renderlog("3229365", "[U:1:377439446]")
-- local img, err = llogsTF.renderlog(logno, "[U:1:377439446]")
llogsTF.getlatestlog("76561198337705174")


if ret then print("ret: " .. ret) end
if err then print("err: " .. err) end
