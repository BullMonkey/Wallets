#!/bin/bash
# create multiresolution windows icon
ICON_DST=../../src/qt/res/icons/rimbit.ico

convert ../../src/qt/res/icons/rimbit-16.png ../../src/qt/res/icons/rimbit-32.png ../../src/qt/res/icons/rimbit-48.png ${ICON_DST}
