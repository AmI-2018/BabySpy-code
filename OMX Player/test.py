from omxplayer import OMXPlayer


print("CENTRAL_AI Startup - running initial setup")
print("Starting Central visual front end")
loop1 = OMXPlayer(r"C:\Users\Kavinda Herath\Downloads\New folder\Music\A.mp4")
vid1 = OMXPlayer(r"C:\Users\Kavinda Herath\Downloads\New folder\Music\B.MP4")

loop1.play()

a=input()

if a==1:
    loop1.pause()
    print("Intruder Detected")
    vid1.play()
    print("Playing Vid_Name_Hammerstein")


"""except KeyboardInterrupt:
    print("terminated by user")
    loop1.quit()
    vid1.quit()"""
