class Video(object):
    def __init__(self,path):
        self.path = path

    def play(self):
        from os import startfile
        startfile(self.path)

    def pause(self):
        startfile(self.path)
class Movie_MP4(Video):
    type = "MP4"

movie = Movie_MP4(r"C:\Users\Kavinda Herath\Downloads\New folder (2)\New folder\MusicA.mp4")
movie.play()
