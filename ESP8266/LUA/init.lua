-- if can boot D0 -> Gnd remove init.lua
gpio.mode(0, gpio.INPUT, gpio.PULLUP)
if gpio.read(0) == 0 then
file.remove("init.lua")
end

--print('IP is ' .. wifi.sta.getip())
--tmr.alarm(1, 1000, tmr.ALARM_AUTO, function()
--     if wifi.sta.getip() == nil then
--          print('Waiting for IP ...')
--     else
--          print('IP is ' .. wifi.sta.getip())
--     tmr.stop(1)
--     end
--end)

--wifi.setmode(wifi.STATION)
wifi.sta.sleeptype(wifi.MODEM_SLEEP)    --power saving

dofile("setup.lua")
dofile("webserver.lua")

tmr.alarm(0,10000,1,function() 
dofile("GetZeroVolts.lua")
end)

tmr.alarm(1,100,1,function()
dofile("ChackVolts.lua")
end)

tmr.alarm(2,20,1,function()
dofile("SendData.lua")
end)

tmr.alarm(3,3000,1,function()
dofile("Led.lua")
end)

if(live == "on")then
tmr.alarm(4,120000,1,function()
dofile("Live.lua")
end)
end
