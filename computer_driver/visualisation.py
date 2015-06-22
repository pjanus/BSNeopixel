import numpy as np

from recorder import *

DIM_X = 5
DIM_Y = 40
MAX_Y = 30000.0
MAX_POWER = 100000.0
HISTORY = 43
DECAY_FACTOR = 0.9
NOISE_LEVEL = 10000
PERCENTILE = 95

def downsample(data, mult):
    """Given 1D data, return the binned average."""
    overhang = len(data) % mult
    if overhang:
        data = data[:-overhang]
    data = np.reshape(data, (mult, len(data) / mult))
    data = np.average(data, 1)
    return data


class Visualisation(object):
    def __init__(self, sr):
        self.sr = sr
        self.local_energy = numpy.zeros(HISTORY)  # a simple ring buffer
        self.local_energy_index = 0  # the index of the oldest element
        self.max = MAX_Y

        self.values = numpy.zeros(HISTORY)
        self.values_index = 0

        sr.setup()
        sr.continuousStart()

    def end(self):
        self.sr.continuousEnd()

    def detect_beat(self, signal):
        samples = signal.astype(numpy.int)  # make room for squares
        # optimized sum of squares, i.e faster version of (samples**2).sum()
        instant_energy = numpy.dot(samples, samples) / float(0xffffffff)  # normalize

        local_energy_average = self.local_energy.mean()
        local_energy_variance = self.local_energy.var()

        beat_sensibility = (-0.0025714 * local_energy_variance) + 1.65142857


        print local_energy_average, local_energy_variance, instant_energy, beat_sensibility, beat_sensibility * local_energy_average
        beat = instant_energy > beat_sensibility * local_energy_average

        self.local_energy[self.local_energy_index] = instant_energy
        self.local_energy_index -= 1
        if self.local_energy_index < 0:
            self.local_energy_index = len(self.local_energy) - 1

        return beat

    def update_max(self, sample):
        cur_max = max(sample)

        self.values[self.values_index] = cur_max
        self.values_index -= 1
        if self.values_index < 0:
            self.values_index = len(self.values) - 1

        self.max = max(NOISE_LEVEL, np.percentile(self.values, PERCENTILE))

    def get(self):
        audio = self.sr.audio.flatten()
        xs, ys = self.sr.fft(audio)
        beat = self.detect_beat(ys)

        ys = downsample(ys, DIM_X)
        self.update_max(ys)


        print self.max

        power = min(255, int(sum(ys) / MAX_POWER * 255))
        ys = [min(int(round(i)), DIM_Y - 1) for i in ys / self.max * DIM_Y]
        return ys, beat, power


v = Visualisation(SwhRecorder())