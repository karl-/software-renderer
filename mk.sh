#!/bin/sh

gcc src/main.c -I lib/ -o bin/renderer
./bin/renderer
open bin/test.tga
