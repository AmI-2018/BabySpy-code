#input must be give when the the video to distract is needed
import time
from omxplayer import OMXPlayer

a=2

print("running initial setup")
loop1 = OMXPlayer('FILE PATH',args=['--win', '100 100 640 480','--loop'])#ARGS FOR THE CONTROL OF THE WINDOW SIZE
vid1 = OMXPlayer('FILE PATH',args=['--win', '100 100 480 360'])

while a==2:
    print("Motion detection activated")
    time.sleep(2)
    print("Security system functioning")
    loop1.play()
    a = input()
    while a==1:
        time.sleep(0.1)
        a = input()
        if a == 1:
            loop1.pause()
            print("Intruder Detected")
            vid1.play()
            print("Playing Vid_Name_Hammerstein")

        else:
            loop1.play()
            print("Intruder Detected")
            vid1.pause()
            print("Playing Vid_Name_Hammerstein")


