#!/bin/bash
set -e
rm -f *.png *.eps
python setup.py build_ext --inplace
python main.py -f ~/Public/DATA/two_bird_together.aif -c songbird.conf
