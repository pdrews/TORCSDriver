TORCSDriver
===========

AI driver for the TORCS race car simulator

To install:

sudo apt-get install libzmq-dev

cd TorcsSourceDir

git clone https://github.com/pdrews/TORCSDriver.git src/drivers/racerx

sudo make install

Open torcs, add the new driver to your lineup, and give it a try

To compile from the racerx directory, you will need these environment variables:

export TORCS_BASE=/your_path_to_torcs/torcs-1.3.6

export MAKE_DEFAULT=$TORCS_BASE/Make-default.mk
