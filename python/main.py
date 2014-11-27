"""main.py: Starting point of the program.

Last modified: Thu Nov 27, 2014  10:37PM

"""
    
__author__           = "Dilawar Singh"
__copyright__        = "Copyright 2013, Dilawar Singh and NCBS Bangalore"
__credits__          = ["NCBS Bangalore"]
__license__          = "GNU GPL"
__version__          = "1.0.0"
__maintainer__       = "Dilawar Singh"
__email__            = "dilawars@ncbs.res.in"
__status__           = "Development"

import aifc 
import sys
import numpy as np
import pylab
import birdsong
import globals
import logging

def readAifData(file):
    global samplingFreq
    globals.logger.info("Reading %s " % file)
    f = aifc.open(file, "r") 
    samplingFreq = f.getframerate()
    globals.sampling_freq = samplingFreq
    nframes = f.getnframes()
    strData = f.readframes(nframes)
    data = np.fromstring(strData, np.short).byteswap()
    data = data[~np.isnan(data)]
    globals.logger.debug("Reading audio file is over. Got %s samples" % len(data))
    return data

def main(config):
    globals.config = config
    data = readAifData(config.get("audio", "filepath"))
    bs = birdsong.BirdSong(data)
    bs.processData(sample_size = 1e5)

def configParser(file):
    try:
        import ConfigParser as cfg
    except:
        import configparser as cfg

    config = cfg.ConfigParser()
    config.read(file)
    return config

if __name__ == '__main__':
    import argparse
    # Argument parser.
    description = '''Process bird songs'''
    parser = argparse.ArgumentParser(description=description)
    parser.add_argument('--file', '-f', metavar='input_file'
            #, nargs=1
            #, action='append'
            , required = True
            , help = 'Input song file in aifc format'
            )
    parser.add_argument('--config', '-c'
            , metavar='config file'
            , default = 'birdsongs.conf'
            , help = "Configuration file to fine tune the processing"
            )
    class Args: pass 
    args = Args()
    parser.parse_args(namespace=args)
    config = configParser(args.config)
    config.add_section("audio")
    config.set("audio", "filepath", args.file)
    main(config)
