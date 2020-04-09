import numpy as np
import matplotlib.pyplot as plt
from matplotlib import image
import argparse
import os

if __name__ == "__main__":

        ''' 
        Driver function
        Constructs and saves images according to specified filepaths
        '''
        
        ap  = argparse.ArgumentParser()
        ap.add_argument ("-ip", "--input-filepath", required = True, help = "path to directory with required text files to be converted to an image")
        ap.add_argument ("-op", "--output-filepath", required = True, help = "path to directory where resulting image is to be saved (including filename)")
        args = vars (ap.parse_args())

        channels = []

        for filename in os.listdir(args["input_filepath"]):
                if filename.endswith(".txt"):
                        channels.append(np.loadtxt(args["input_filepath"]+"/"+filename));
        print(len(channels))

        (h,w) = channels[0].shape

        if len(channels) == 1:
                plt.imsave (args["output_filepath"], channels[0], cmap = 'Greys_r')
        else:
                image = np.zeros ((h,w,len(channels)), 'uint8')
                for (index, channel) in enumerate(channels):
                        image[:,:,index] = channel
                plt.imsave (args["output_filepath"], image)






