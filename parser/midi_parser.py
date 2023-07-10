import mido
import os

TEMPO = 500000
output = []

def getDelays(track):
    delays = []
    time = 0.0
    for msg in track:
        if msg.type == 'set_tempo':
            global TEMPO
            TEMPO = msg.tempo

        time += mido.tick2second(msg.time, mid.ticks_per_beat, TEMPO)
        if msg.type == 'note_on':
            delays.append(time)

    return delays

def parse(track):
    delays = getDelays(track)
    global output
    output += delays


songs = []
files = os.listdir('resources/songs')
for f in files:
    cur = f.removesuffix('.mid')
    mid = cur + '.mid'
    ogg = cur + '.ogg'
    if mid in files and ogg in files:
        songs.append(cur)

for i, s in enumerate(songs, start=1):
    print("{}: {}".format(i, s))

index = int(input('Select song number: '))
song = songs[index - 1]

with open('resources/song_name.txt', 'w') as fp:
    fp.write(song)

path = 'resources/songs/' + song + '.mid'
mid = mido.MidiFile(path)
time = 0.0
for i, track in enumerate(mid.tracks):
    
    parse(track)
    print("Track {}: {} - Parsed!".format(i, track.name))


tmp_set = set(output)
output = (list(tmp_set))
output.sort()
with open('resources/delays.txt', 'w') as fp:
    for item in output:
        fp.write("%s\n" % item)


    
