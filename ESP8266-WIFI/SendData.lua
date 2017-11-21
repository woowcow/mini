-- Send data to server
--tmr.alarm(1,1,1,function()
if(rawv == nil) then rawv=0 end
if rawv>0 then
--apikey="EH4CtlwRi4Tg3IGnBZZH14DIjKMJsN"
http.get("http://" .. url .. "/woowcow_api.php?apikey=" .. apikey .. "&data=" .. rawv, nil, function(code, data)
rawv = 0
    if (code < 0) then
      print("HTTP request failed")
      print("1")
    else
      print(code, data)
      print("2")
    end
  end
  )
  
dofile("buzzer.lua");
rawv = 0
end
--end)
-- Send data to server END
