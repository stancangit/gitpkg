#!/bin/bash
sudo gcc main.c
sudo mkdir /usr/bin/.gitpkg
sudo mv a.out /usr/bin/.gitpkg/gitpkg_run
sudo chmod +x /usr/bin/.gitpkg/gitpkg_run
sudo mv gitpkg /usr/bin/gitpkg
sudo chmod +x /usr/bin/gitpkg

