--[[ GPIO0 ---/\/\/\---|<--o Vcc
 LED from dark to light and the from light to dark]]

--tmr.alarm(3,3000,1,function()
pwmpin=4
pwm.setup(pwmpin,500,1020) 

pwm.start(pwmpin)

for i = 1020,0,-20 do
    pwm.setduty(pwmpin,i)
--    tmr.delay(5000)
--    print(i)
end

--tmr.delay(1000000)

for i=0,1020,20 do
    pwm.setduty(pwmpin,i)
--   tmr.delay(5000)
--    print(i)
end


pwm.setduty(pwmpin, 1023) -- turn off the ledpin
pwm.close(pwmpin)

--end)