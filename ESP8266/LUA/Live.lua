
--apikey="EH4CtlwRi4Tg3IGnBZZH14DIjKMJsN"
RSSI=wifi.sta.getrssi()
print("RSSI is " .. RSSI)
http.get("http://" .. url .. "/woowcow_api.php?apikey=" .. apikey .. "&ip=" .. wifi.sta.getip() .. "&rssi=" .. RSSI, nil, function(code, data)
    if (code < 0) then
      print("HTTP request failed")
    else
      print(code, data)
    end
  end)
