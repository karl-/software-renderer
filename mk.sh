#!/bin/sh

gcc src/* -I lib/ -o bin/renderer
./bin/renderer
open bin/test.tga
