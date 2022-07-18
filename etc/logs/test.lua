#! /usr/bin/env luvit

local llogsTF = require("llogsTF")

local ret, err = llogsTF.renderlog("3229365", "[U:1:377439446]")

if ret then print("ret: " .. ret) end
if err then print("err: " .. err) end
