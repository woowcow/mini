    -- A simple http server
    srv=net.createServer(net.TCP)
    srv:listen(80,function(conn)
      conn:on("receive",function(conn,payload)
        print(payload)
        conn:send("<h1>woowcow</h1><br>WLAN IP:" .. wifi.sta.getip())
      end)
      conn:on("sent",function(conn) conn:close() end)
    end)
    