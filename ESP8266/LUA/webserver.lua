if(ap == "on")then
    wifi.setmode(wifi.STATIONAP)
    print('Setting up WIFI...')
    --wifi.sta.config('MY_SSID', 'MY_PASSWORD')
--    wifi.ap.config({ ssid = 'woowcow-' .. apname, auth = AUTH_OPEN })
    cfg={}
    cfg.ssid='woowcow-' .. apname
    if(appwd ~= "")then cfg.pwd=appwd end
    wifi.ap.config(cfg)
else
    wifi.setmode(wifi.STATION)
end

print(wifi.ap.getip())


station_cfg={}
station_cfg.ssid=ssid
station_cfg.pwd=pwd
station_cfg.save=true
wifi.sta.config(station_cfg)
print(wifi.sta.getip()) 
wifi.sta.autoconnect(1)

-- a simple http server
srv=net.createServer(net.TCP) 
srv:listen(80,function(conn) 
    conn:on("receive",function(conn,payload) 
    print(payload) 
        

    local _, _, method, vars = string.find(payload, "([A-Z]+) /(.+) HTTP")
        if(method == nil)then
            _, _, method, path = string.find(payload, "([A-Z]+) (.+) HTTP");
        end
        local _GET = {}
        print(vars)
        if (vars ~= nil)then
            vars = string.gsub(vars,'?','')
            print(vars)
            for getdata in string.gmatch(vars,"[^&]+") do
                for k, v in string.gmatch(getdata, "(%w.+)=(%w.+)&*") do
                  _GET[k] = v
--                    print(k .. ' : ' .. v)
                end
            end
        end


--print(_GET.apikey)
--print(_GET.ap)
--print(_GET.live)
--print(_GET.url)
if(_GET.ap == nil)then _GET.ap = "" end
if(_GET.live == nil)then _GET.live = "" end
if(_GET.apname == nil)then _GET.apname = "" end
if(_GET.appwd == nil)then _GET.appwd = "" end

        if(_GET.apikey ~= nil)then

        if file.open("setup.lua", "w+") then
              file.writeline('ssid = "' .. _GET.ssid .. '"')
              file.writeline('pwd = "' .. _GET.pwd .. '"')
              file.writeline('apikey = "' .. _GET.apikey .. '"')
              file.writeline('ap = "' .. _GET.ap .. '"')
              file.writeline('live = "' .. _GET.live .. '"')
              file.writeline('url = "' .. _GET.url .. '"')
              file.writeline('apname = "' .. _GET.apname .. '"')
              file.writeline('appwd = "' .. _GET.appwd .. '"')
              file.close();
              print("Write settings... OK")
              dofile("setup.lua")
              dofile("webserver.lua")
        end

       end
           


if(ap ~= "")then apon="checked" else apon="" end
if(live ~= "")then liveon="checked" else liveon="" end
if(ap == "")then showapid = "Disable" else showapid = wifi.ap.getip() end
if(wifi.sta.getip() == nil)then showip = "Disable" else showip = wifi.sta.getip() end


buf='<!DOCTYPE html><html><head><style>body{background-color:#FFF}.BOX{border-radius:10px;width:450px;height:450px;border:1px solid #444;position:absolute;left:50%;top:50%;margin-top:-225px;margin-left:-225px;text-align:center;background-color:#EBEBEB}.BOX h1{position:relative;text-align:center}a:link{text-decoration:none;color:#000}a:visited{text-decoration:none;color:#000}a:hover{text-decoration:underline}a:active{text-decoration:none}</style><meta charset=utf-8></head><body><div class=BOX><h1><a href="https://www.woowcow.com/" target=_blank>woowcow</a></h1><form id=form1 name=form1><p>'
buf=buf .. '<span style="solid;font-size: 50%;background-color: #000000;border-radius:5px;color: #FFFFFF;padding: 4px;">AP IP: ' .. showapid .. ' WLAN IP: ' .. showip .. ' RSSI: ' .. wifi.sta.getrssi() .. '</span>'
buf=buf .. '<br><br><label><input type=checkbox name=ap value=on id=ap ' .. apon .. '> AP 基地台模式 (關閉可省電)</label><br>'
buf=buf .. '<label><input type=checkbox name=live value=on id=live ' .. liveon .. '> 回傳捕牛器目前狀態</label><br></p><p>'
buf=buf .. 'WIFI<br>SSID <input name=ssid id=ssid size="30" value=' .. ssid .. '>'
buf=buf .. '<br>PASSWORD <input name=pwd id=pwd size="30" value=' .. pwd .. '>'
buf=buf .. '<br>AP<br>NAME <input name=apname id=apname size="30" value=' .. apname .. '>'
buf=buf .. '<br>PASSWORD <input name=appwd id=appwd size="30" value=' .. appwd .. '>'
buf=buf .. '<br><br>Server <input name=url id=url size="30" value=' .. url .. '>'
buf=buf .. '<br>API-KEY <input name=apikey id=apikey size="30" value=' .. apikey .. '>'
buf=buf .. '</p><p><input type=submit></p></form></div></body></html>'

    conn:send(buf)



        
    conn:on("sent",function(conn) conn:close() end)
    end) 
end)

wifi.sta.sleeptype(wifi.MODEM_SLEEP)    --WIFI SLEEP
-- wifi.sta.sleeptype(wifi.NONE_SLEEP)  --關閉休眠
