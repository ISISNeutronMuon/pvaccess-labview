# Introduction #
This document is a record of steps taken to achieve a successful build and deploy of the shared object library on NI RT Linux.
# Basics #
This web page was a useful reference: https://nilrt-docs.ni.com/remote/vscode_remote.html  
I built on a PXIe-8840 Quad-Core.  The operating system, as quoted by NIMax is NI Linux Real-Time x64 5.10.59-rt52.  The Linux RT System Image version is 21.3.
# Required Packages #
The web page above suggests the following packages, all of which I installed (using opkg install):  
packagegroup-core-buildessential  
gdb  
python-core  
cmake  

I don’t think cmake is required by anything in this process, apart from the final pvaccess-labview library build.  However note that this requires cmake version 4.  Opkg on NI RT Linux 21 only offer cmake 3, so I downloaded and installed cmake 4 via the cmake web site.

While trying to get epics-base to build I also installed the following (using opkg install):  
perl-module-getopt-std  
perl-module-findbin  
perl-module-base  
perl-module-pod-simple-html 
perl-module-pod-simple-pullparser  
perl-module-pod-text  
perl-module-text-wrap  
perl-module-parent  
perl-module-pod-simple-methody  

Plus these, which may have been unnecessary, due to misunderstandings on my part:  
perl-pod  
perl-module-pod-html  
perl-module-simple  

Finally in order to get pvxs to build I needed:  
libevent-dev

Note that the PVXS source distribution tends to come with libevent source bundled, so you can build it yourself.  As it happens RT Linux appears to come with the libevent runtime in the base image.  Installing libevent-dev with opkg is considerably quicker and simpler than building from source.

# Build epics-base #
The epics-base distribution was obtained with:  
wget https://epics-controls.org/download/base/base-7.0.0.tar.gz

This was tar extracted, then the build was executed by changing directory to the top level of the epics-base structure and running the make command (with no parameters).  Once the various perl modules had been installed this completed successfully in a few minutes.
# Build PVXS #
The PVXS distribution was obtained with:  
wget https://github.com/epics-base/pvxs/archive/refs/tags/1.3.2.tar.gz  
This was tar extracted.  Before building, its necessary to edit configure/RELEASE.local under the PVXS root directory, providing a path to the epics-base build directories.  Mine looks like this:  
EPICS_BASE=$(TOP)/../base-7.0.9

After this has been done the build is executed by running the make command in the PVXS root directory.  This worked successfully once libevent-dev had been installed.
# Build pvaccess-labview SO library #
The pvaccess-labview distribution can be obtained with:  
wget https://github.com/ISISNeutronMuon/pvaccess-labview/archive/main.zip  
(or you could clone the entire git repository).  Unzipping this file creates a folder called pvaccess-labview-main.  Change directory into this folder.  
You may have to edit the CMakelists.txt:  
Edit the symbol definitions for EPICS_BASE_ROOT and PVXS_ROOT to be correct for the relative paths to those folders in your build structure.  
If you have chosen to install libevent-dev via opkg rather than build the libevent bundled with PVXS, you will need to edit the symbol definition for EVENT_LIB; set it to point at /usr/lib.  
Then you can build – using cmake 4:  
cmake -B build  
cmake –build build  
If the build is successful, you will find the build product libpva_labview.so in the build folder.
# Deployment to an RT target #
## Shared Object Library Dependencies ##
libpva_labview.so is dependent on libpvxs.so (from PVXS) and libCom.so (from EPICS base).  libpvxs.so is in turn dependent on libevent_core.so and libevent_pthreads.so.  All other sub-dependencies should be dealt with by standard system libraries.  You’ll need to deploy all of the above shared objects to a production RT target.  
To get the libevent libraries on your target machine the easiest way is to opkg install libevent-core and libevent-pthreads.  The rest will need to be network copied from the build folders on your build target.
## Destination Folder and File Naming ##
The LabView part of the library is written to look for the shared object library in any of the standard Linux shared object folders.  There are several of these, but the one that is typically used for application libraries is /usr/local/lib.  
Linux shared object libraries typically have names containing version information.  The EPICS and PVXS shared objects built according to this document are actually named:  
libCom.so.3.23.2  
libpvxs.so.1.4  
libpva_labview.so is not currently named with version information.  
It is conventional to provide the version numbered SOs and then to symbolically link them to unversioned copies, for instance:  
ln -s libCom.so.3.23.2 libCom.so  

The folder listing for /usr/local/lib should end up something like this:  
 ls -l /usr/local/lib  
lrwxrwxrwx    1 admin    administ        16 Nov  6 14:34 libCom.so -> libCom.so.3.23.2*  
-rwxr-xr-x    1 admin    administ   2363072 Nov  6 14:31 libCom.so.3.23.2*  
-rwxr-xr-x    1 admin    administ    501936 Nov  6 14:31 libpva_labview.so*  
lrwxrwxrwx    1 admin    administ        14 Nov  6 14:34 libpvxs.so -> libpvxs.so.1.3*  
-rwxr-xr-x    1 admin    administ   8791248 Nov  6 14:31 libpvxs.so.1.3*  
## Updating the SO loader ##
The Linux shared object library loader maintains a cached directory of all shared object libraries on the target.  Once you have copied new libraries to a target you need to update this cache.  This can be done simply with the command ldconfig, or by rebooting the target (which you will most likely be doing anyway, if you are deploying a new LabView RT build).
# NI RT Linux 2025
The same build and deploy process has also been done on RT Linux 2025, using the same PXIe-8881 build target.  There were some slight differences, which may be related to updated versions of EPICS and PVXS, rather than the OS version.  
The EPICS base build appeared to require more perl modules to be installed:  
lib-perl  
perl-module-encode-encoding  
perl-module-extutils-parsex  
perl-module-charnames  
perl-module-transcodesmart  
The EPICS and PVXS shared object libraries were numbered slightly differently, presumably because later versions of the source code were used:  
libCom.so.3.24.1  
libpvxs.so.1.4  
