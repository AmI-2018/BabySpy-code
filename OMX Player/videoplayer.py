import subprocess

def videoplayer(on):
    def close_program(p):
        p.terminate()

    b=0
    p = subprocess.Popen(["C:\Program Files (x86)\VideoLAN\VLC/vlc.exe",
                          r"C:\Users\Kavinda Herath\Downloads\New folder (2)\New folder\Music\B.mp4"])

    if on == 1:
        close_program(p)
        p1 = subprocess.Popen(["C:\Program Files (x86)\VideoLAN\VLC/vlc.exe",
                          r"C:\Users\Kavinda Herath\Downloads\New folder (2)\New folder\Music\A.mp4"])
        b=2

    if on == 0:

        p = subprocess.Popen(["C:\Program Files (x86)\VideoLAN\VLC/vlc.exe",
                              r"C:\Users\Kavinda Herath\Downloads\New folder (2)\New folder\Music\B.mp4"])

        if b == 2:
            close_program(p1)
        else:
            close_program(p)




a = int(input())

while a!=3:
    videoplayer(a)
    a = int(input())
