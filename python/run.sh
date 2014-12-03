#!/bin/bash
set -e
python setup.py build_ext --inplace
python main.py -f ~/Public/DATA/two_bird_together.aif -c songbird.conf
