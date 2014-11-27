"""main.py: Starting point of the program.

Last modified: Sat Jan 18, 2014  05:01PM

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

def readAifData(file):
    global samplingFreq
    print("INFO : Reading %s " % file)
    f = aifc.open(file, "r") 
    samplingFreq = f.getframerate()
    nframes = f.getnframes()
    strData = f.readframes(nframes)
    data = np.fromstring(strData, np.short).byteswap()
    data = data[~np.isnan(data)]
    return data

def main(config):
    globals.config = config
    data = readAifData(config.get("audio", "filepath"))
    data = filterData(data)
    birdSong = birdsong.BirdSong(data)
    birdsong.process()

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
