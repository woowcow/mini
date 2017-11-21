-- Chack Volts

--zerovolts=16

if(zerovolts == nil) then zerovolts=50 end

-- tmr.alarm(1,100,1,function()

rawv = 0
raw = adc.read(0) - zerovolts
--print(adc.read(0))

if (raw>0) then
    v = raw*(3.3/1024)  -- Get Volts
   print(v) 
    rawa=string.format("%3.3f", v)  --%3.2f
    rawv=(rawa*1000) --x100 Get number *100

        if(rawv>0)then
        print(string.format("1-Raw:" .. rawv .. " V: = %.3f", v)) --%.2f
        end

    else

--    print("0-Raw:" .. raw .. " V: 0")
  end
--end)
-- Chack Volts END
