#!/bin/bash
sudo gcc -zexecstack -fno-stack-protector -g main.c
sudo mkdir /usr/bin/.gitpkg
sudo mkdir /tmp/gitpkg
sudo mv a.out /usr/bin/.gitpkg/gitpkg_run
sudo chmod +x /usr/bin/.gitpkg/gitpkg_run
sudo cp gitpkg /usr/bin/gitpkg
sudo chmod +x /usr/bin/gitpkg

