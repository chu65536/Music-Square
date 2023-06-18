import mido

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
        time = round(time, 3)
        if msg.type == 'note_on':
            delays.append(time)

    return delays

def parse(track):
    delays = getDelays(track)
    global output
    output += delays


with open('path.txt') as f:
    path = f.readline()

path += '.mid'
mid = mido.MidiFile(path)
time = 0.0
for i, track in enumerate(mid.tracks):
    
    parse(track)
    print("Track {}: {} - Parsed!".format(i, track.name))


tmp_set = set(output)
output = (list(tmp_set))
output.sort()

with open(r'delays.txt', 'w') as fp:
    for item in output:
        fp.write("%s\n" % item)
    print('Map Generated!')



    
