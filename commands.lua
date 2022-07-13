local cmds = {}

cmds["echo"] = {call = require("./cmds/echo")}
cmds["steamid"] = {call = require("./cmds/steamid")}

return cmds

