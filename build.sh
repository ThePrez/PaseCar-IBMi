#!/QOpenSys/pkgs/bin/bash

echo "library list:"
liblist 
liblist -a pasecar
echo "new library list:"
liblist

system "crtlib edmund" &
thejob=$(getjobid $!)
wait

echo "job was : $(getjobid $thepid)"
