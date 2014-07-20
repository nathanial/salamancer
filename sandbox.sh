#!/bin/bash
sudo cp /home/nathan/Sources/cef_binary_3.2078.1761_linux64/out/Release/chrome-sandbox ./dist/bin/chrome-sandbox #needed if you build on NFS!
sudo chown root:root ./dist/bin/chrome-sandbox
sudo chmod 4755 ./dist/bin/chrome-sandbox