#!/bin/bash
python setup.py build_ext --inplace
python main.py -f ~/Public/DATA/BirdSongsRecordings/mr1.220405.aif -c songbird.conf
