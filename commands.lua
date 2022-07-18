local cmds = {}

cmds["echo"] = {call = require("./cmds/echo")}
cmds["steamid"] = {call = require("./cmds/steamid")}
cmds["log"] = {call = require("./cmds/log")}
cmds["set"] = {call = require("./cmds/set")}

return cmds

