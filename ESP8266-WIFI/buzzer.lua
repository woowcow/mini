buzzer_pin = 5
gpio.mode(buzzer_pin, gpio.OUTPUT)

led = 4   -- LED pin no.
gpio.mode( led, gpio.OUTPUT )


function beep(pin, freq, duration)
--    print ("beep!")

    pwm.setup(pin, freq, 512)
    pwm.start(pin)
    -- delay in uSeconds
    tmr.delay(duration * 1000)
    pwm.stop(pin)
    --20ms pause
    tmr.wdclr()
    tmr.delay(100000)
end




function sound ()
     gpio.write( led, gpio.HIGH )
     beep(buzzer_pin, 800, 100)
     gpio.write( led, gpio.LOW )
end

function zero ()
     for i=1,10,1 do
          gpio.write( led, gpio.HIGH )
          beep(buzzer_pin, 800, 100)
          gpio.write( led, gpio.LOW )
     end
     tmr.delay(250000)
end



for i = 800,900,20 do
  beep(buzzer_pin, i, 20)
--  print(i)
end

buzzerV=rawv/10;

--rawv=351
    count1 = buzzerV % 10;
    count2 = buzzerV % 100 / 10;
    count3 = buzzerV % 1000 / 100;
    count4 = buzzerV % 10000 / 1000;


count1 = math.floor (count1)
count2 = math.floor (count2)
count3 = math.floor (count3)
count4 = math.floor (count4)

if (rawv > 0) then
      if (count4 > 0) then                   --Output Thousands number
        for i=1,count4,1 do
          sound ()
--          print(math.floor (count4))
--        tmr.delay(10000)
        end
        tmr.delay(250000)
      end
 
    
      if (count3 > 0 or count4 > 0) then     --Output Hundred number
        for i=1,count3,1 do
          sound ()
--          print(math.floor (count3))
--        tmr.delay(10000)
        end
        tmr.delay(250000)
      end
     if (count3 == 0 and (count4 > 0)) then
          zero()
         end


      if (count2 > 0 or count3 > 0 or count4 > 0) then --Output Ten number
        for i=1,count2,1 do
          sound ()
--          print(math.floor (count2))
        end
        tmr.delay(250000)
      end
        if (count2 == 0 and ( count3 > 0 or count4 > 0)) then
          zero()
        end


        for i=1,count1,1 do        --Output number
          sound ()
--          print(math.floor (count1))
        end
      if (count1 == 0 and (count2 > 0 or count3 > 0 or count4 > 0)) then
        zero()
        end

end
