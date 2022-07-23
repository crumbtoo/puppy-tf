local cmds = {}

cmds["echo"] = {call = require("./cmds/echo")}
cmds["steamid"] = {call = require("./cmds/steamid"), usage = "``steam [steamid64 | vanity URL]``"}
cmds["log"] = {call = require("./cmds/log")}
cmds["set"] = {call = require("./cmds/set")}

return cmds

