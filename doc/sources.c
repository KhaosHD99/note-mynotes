#deb cdrom:[Ubuntu-Netbook 10.04 LTS _Lucid Lynx_ - Release armel+imx51 (20100427.1)]/ lucid main
# See http://help.ubuntu.com/community/UpgradeNotes for how to upgrade to
# newer versions of the distribution.

deb http://ports.ubuntu.com/ubuntu-ports/ lucid main restricted
deb-src http://archive.ubuntu.com/ubuntu lucid main restricted

## Major bug fix updates produced after the final release of the
## distribution.
deb http://ports.ubuntu.com/ubuntu-ports/ lucid-updates main restricted
deb-src http://archive.ubuntu.com/ubuntu lucid-updates main restricted

## N.B. software from this repository is ENTIRELY UNSUPPORTED by the Ubuntu
## team. Also, please note that software in universe WILL NOT receive any
## review or updates from the Ubuntu security team.
deb http://ports.ubuntu.com/ubuntu-ports/ lucid universe
deb-src http://archive.ubuntu.com/ubuntu lucid universe
deb http://ports.ubuntu.com/ubuntu-ports/ lucid-updates universe
deb-src http://archive.ubuntu.com/ubuntu lucid-updates universe

## N.B. software from this repository is ENTIRELY UNSUPPORTED by the Ubuntu 
## team, and may not be under a free licence. Please satisfy yourself as to 
## your rights to use the software. Also, please note that software in 
## multiverse WILL NOT receive any review or updates from the Ubuntu
## security team.
deb http://ports.ubuntu.com/ubuntu-ports/ lucid multiverse
deb-src http://archive.ubuntu.com/ubuntu lucid multiverse
deb http://ports.ubuntu.com/ubuntu-ports/ lucid-updates multiverse
deb-src http://archive.ubuntu.com/ubuntu lucid-updates multiverse

## Uncomment the following two lines to add software from the 'backports'
## repository.
## N.B. software from this repository may not have been tested as
## extensively as that contained in the main release, although it includes
## newer versions of some applications which may provide useful features.
## Also, please note that software in backports WILL NOT receive any review
## or updates from the Ubuntu security team.
# deb http://ports.ubuntu.com/ubuntu-ports/ lucid-backports main restricted universe multiverse
# deb-src http://archive.ubuntu.com/ubuntu lucid-backports main restricted universe multiverse

## Uncomment the following two lines to add software from Canonical's
## 'partner' repository.
## This software is not part of Ubuntu, but is offered by Canonical and the
## respective vendors as a service to Ubuntu users.
# deb http://archive.canonical.com/ubuntu lucid partner
# deb-src http://archive.canonical.com/ubuntu lucid partner

deb http://ports.ubuntu.com/ubuntu-ports/ lucid-security main restricted
deb-src http://ports.ubuntu.com/ubuntu-ports/ lucid-security main restricted
deb http://ports.ubuntu.com/ubuntu-ports/ lucid-security universe
deb-src http://ports.ubuntu.com/ubuntu-ports/ lucid-security universe
deb http://ports.ubuntu.com/ubuntu-ports/ lucid-security multiverse
deb-src http://ports.ubuntu.com/ubuntu-ports/ lucid-security multiverse
