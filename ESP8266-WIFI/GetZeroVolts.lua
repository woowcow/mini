if Volts_array == nil then Volts_array={} end

--tmr.alarm(0,1000,1,function() 
-- Get Zero Volts
-- print('Get Zero Volts...')
--tmr.delay(15000)


zero_Volts = 0
for x = 1,5 do
    for i = 1,100 do
         if adc.read(0) > zero_Volts then
         zero_Volts=adc.read(0)
         
         end
    end
--tmr.delay(1000)
--print("---" .. zero_Volts)
end

-- print('Get Zero Volts: ' .. zero_Volts)
-- Get Zero Volts END

-- 取得眾數
if Volts_array[zero_Volts] == nil then
Volts_array[zero_Volts] = 1
else
Volts_array[zero_Volts] = Volts_array[zero_Volts]+1
end

--zero_Volts = 0
--count=0

-- Get max count Volts
count = 0
for key,value in pairs(Volts_array) do
--    print(key,value)
    if value > count then 
    count = value
    zero_Volts = key 
    end
end
print('Zero Volts: ' .. zero_Volts)


--end)
