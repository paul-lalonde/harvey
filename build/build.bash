#!/bin/bash
set -e

rm -f /tmp/image

if [ $HARVEY_GOLANG"" == "" ]; then
               echo Not including Go in the image
       else
	      mkdir -p ../sys/go
              echo sudo mount --bind $HARVEY_GOLANG ../sys/go
              sudo mount --bind $HARVEY_GOLANG ../sys/go
              ls -l ../sys/go
              function cleanup {
                       echo unmounting sys/go
                       sudo umount ../sys/go
               }
               trap cleanup EXIT
fi


# Download Plan 9
if [ ! -e 9legacy.iso ] && [ ! -e 9legacy.iso.bz2 ]; then
  curl -L --fail -O https://github.com/Harvey-OS/harvey/releases/download/9legacy/9legacy.iso.bz2
fi
if [ ! -e 9legacy.iso ]; then
  bunzip2 -k 9legacy.iso.bz2
fi

$(cd ..; bash ./build/mkdirs)

$(cd ..; tar --format ustar --exclude './build' --exclude harvey.tgz --exclude .git --exclude '9legacy.iso*' -czf harvey.tgz *)

expect <<EOF
spawn qemu-system-i386 -accel kvm -nographic -net user -net nic,model=virtio -m 4096 -vga none -cdrom 9legacy.iso -boot d -hda ../harvey.tgz
expect -exact "Selection:"
send "2\n"
expect -exact "Plan 9"
sleep 5
expect -timeout 600 "root is from (tcp, local)"
send "local\n"
expect -exact "mouseport is (ps2, ps2intellimouse, 0, 1, 2)\[ps2\]:"
send "ps2intellimouse\n"
expect -exact "vgasize \[640x480x8\]:"
send "1280x1024x32\n"
expect -exact "monitor is \[xga\]:"
send "vesa\n"

# Mount the host's fileserver
#expect -exact "term% "
#send "9fs tcp!10.0.2.2!5640 /n/harvey\n"

set timeout 2400

# 9fs is fucking slow, so let's be stupid
expect -exact "term% "
send "ramfs -u -m /n/harvey\n"
expect -exact "term% "
send "cd /n/harvey\n"
expect -exact "term% "
send "gunzip < /dev/sdC0/data | tar x\n"

# Go to the build dir
expect -exact "term% "
send "cd /n/harvey/build/scripts\n"
expect -exact "term% "
send "rc build && rc repl && rc iso\n"

# and shut down
expect -exact "term% "
send "ls -l /tmp/dist/\n"
expect -exact "term% "
send "srv -c tcp!10.0.2.2!5640 host /n/host\n"
expect -exact "term% "
send "time fcp /tmp/dist/plan9-new.iso.bz2 /n/host/\n"
expect -exact "term% "
send "cd /n/host\n"
expect -exact "term% "
send "mkusbboot -r /n/harvey -p /sys/lib/sysconfig/proto/allproto -s 2048\n"
expect -exact "term% "
send "fshalt\n"
expect -exact "done halting"
exit
EOF

rm ../harvey.tgz
