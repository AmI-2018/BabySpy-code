"""
the documentation

first a local host should be created through the command prompt
command:
        windows: path of vlc\vlc --intf rc --rc-host local host:5000 and path of vlc\vlc --intf rc --rc-host local host:4000
        linux:vlc --intf rc --rc-host local host:5000 and vlc --intf rc --rc-host local host:5000
"""

import telnetlib
import subprocess

"""
print("initializing the screen saver localhost")
screen_saver=subprocess.call(r"C:\Program Files (x86)\VideoLAN\VLC\vlc --intf rc --rc-host localhost:5000")

print("initializing the player localhost")
player=subprocess.call(r"C:\Program Files (x86)\VideoLAN\VLC\vlc --intf rc --rc-host localhost:4000")
"""
print("initializing telnetlib")

tn_player = telnetlib.Telnet("localhost", "4000")
player_dir = "add F:\A1.mp4"#insert the path to video and the video name


def video_player_initialsing():

    print("opening video")
    tn_player.write(player_dir.encode()+"\n".encode())

def config_video(cmd_v):
    print(cmd_v)
    tn_player.write(cmd_v.encode()+"\n".encode())

def quit(cmd_q):
    print(cmd_q)
    tn_player.write(cmd_q.encode()+"\n".encode())

a=0


while a!=5:
    print("press 1 for the video intiialising")
    print("press 3 for the video configure the video")
    print("press 5 for the video to quit")

    a = int(input())

    if a == 1:
        print("initializing")
        video_player_initialsing()

    if a == 3:
        print("please enter what to do")
        c = """   | add XYZ  . . . . . . . . . . . . add XYZ to playlist
                | enqueue XYZ  . . . . . . . . . queue XYZ to playlist
                | playlist . . . . .  show items currently in playlist
                | play . . . . . . . . . . . . . . . . . . play stream
                | stop . . . . . . . . . . . . . . . . . . stop stream
                | next . . . . . . . . . . . . . .  next playlist item
                | prev . . . . . . . . . . . .  previous playlist item
                | goto . . . . . . . . . . . . . .  goto item at index
                | repeat [on|off] . . . .  toggle playlist item repeat
                | loop [on|off] . . . . . . . . . toggle playlist loop
                | random [on|off] . . . . . . .  toggle random jumping
                | clear . . . . . . . . . . . . . . clear the playlist
                | status . . . . . . . . . . . current playlist status
                | title [X]  . . . . . . set/get title in current item
                | title_n  . . . . . . . .  next title in current item
                | title_p  . . . . . .  previous title in current item
                | chapter [X]  . . . . set/get chapter in current item
                | chapter_n  . . . . . .  next chapter in current item
                | chapter_p  . . . .  previous chapter in current item
                |
                | seek X . . . seek in seconds, for instance `seek 12'
                | pause  . . . . . . . . . . . . . . . .  toggle pause
                | fastforward  . . . . . . . .  .  set to maximum rate
                | rewind  . . . . . . . . . . . .  set to minimum rate
                | faster . . . . . . . . . .  faster playing of stream
                | slower . . . . . . . . . .  slower playing of stream
                | normal . . . . . . . . . .  normal playing of stream
                | frame. . . . . . . . . .  play frame by frame
                | f [on|off] . . . . . . . . . . . . toggle fullscreen
                | info . . . . .  information about the current stream
                | stats  . . . . . . . .  show statistical information
                | get_time . . seconds elapsed since stream's beginning
                | is_playing . . . .  1 if a stream plays, 0 otherwise
                | get_title . . . . .  the title of the current stream
                | get_length . . . .  the length of the current stream
                |
                | volume [X] . . . . . . . . . .  set/get audio volume
                | volup [X]  . . . . . . .  raise audio volume X steps
                | voldown [X]  . . . . . .  lower audio volume X steps
                | adev [device]  . . . . . . . .  set/get audio device
                | achan [X]. . . . . . . . . .  set/get audio channels
                | atrack [X] . . . . . . . . . . . set/get audio track
                | vtrack [X] . . . . . . . . . . . set/get video track
                | vratio [X]  . . . . . . . set/get video aspect ratio
                | vcrop [X]  . . . . . . . . . . .  set/get video crop
                | vzoom [X]  . . . . . . . . . . .  set/get video zoom
                | snapshot . . . . . . . . . . . . take video snapshot
                | strack [X] . . . . . . . . .  set/get subtitle track
                | key [hotkey name] . . . . . .  simulate hotkey press
                | menu . . [on|off|up|down|left|right|select] use menu
                | help . . . . . . . . . . . . . . . this help message
                | logout . . . . . . .  exit (if in socket connection)
                | quit . . . . . . . . . . . . . . . . . . .  quit vlc"""
        print(c)
        cmd_v = input()
        config_video(cmd_v)

    if a == 5:
        print("closing")
        quit("quit")
