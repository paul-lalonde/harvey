# Copyright 2015 The Go Authors. All rights reserved.
# Use of this source code is governed by a BSD-style
# license that can be found in the LICENSE file.

# We don't actually use this right now, but it's a way to automatically
# install from an ISO onto a disk image, which seems worth keeping.

set -e

ls -l
file *
ls /usr/bin/qemu*
# Download Plan 9
if [ ! -e 9legacy.iso.bz2 ]; then
  curl --fail -O http://9legacy.org/download/9legacy.iso.bz2
#  sha1sum -c 9legacy.iso.sha1
fi
if [ ! -e 9legacy.iso ]; then
  bunzip2 -k 9legacy.iso.bz2
fi

# Initialize disk image.
rm -f disk.raw
qemu-img create -f raw disk.raw 1G
# Run the installer to create the disk image.
expect <<EOF
spawn qemu-system-i386 -nographic -net user -net nic,model=virtio -m 1024 -vga none -drive if=none,id=hd,file=disk.raw,media=disk,cache=writeback -device virtio-scsi-pci,id=scsi -device scsi-hd,drive=hd -cdrom 9legacy.iso -boot d
expect -exact "Selection:"
send "1\n"
expect -exact "Plan 9"
sleep 5
# Need to wait for the kernel to boot.
expect -timeout 600 -exact "use DMA for ide drives\[yes\]:"
send "\n"
expect -exact "mouseport is (ps2, ps2intellimouse, 0, 1, 2)\[ps2\]:"
send "ps2intellimouse\n"
expect -exact "vgasize \[640x480x8\]:"
send "1280x1024x32\n"
expect -exact "monitor is \[xga\]:"
send "vesa\n"
expect -exact "% "
send "inst/textonly\n"
expect -exact "Task to do \[configfs\]:"
send "\n"
expect -exact "File system (fossil, fossil+venti)\[fossil\]:"
send "\n"
expect -exact "Task to do \[partdisk\]:"
send "\n"
expect -exact "Disk to partition (sd00, sdD0)\[no default\]:"
send "sd00\n"
expect -exact "Install mbr \(y, n\)\[no default\]:"
send "y\n"
expect -exact ">>> "
send "w\n"
expect -exact ">>> "
send "q\n"
expect -exact "Task to do \[prepdisk\]:"
send "\n"
expect -exact "Plan 9 partition to subdivide \(/dev/sd00/plan9\)\[/dev/sd00/plan9\]:"
send "\n"
expect -exact ">>> "
send "w\n"
expect -exact ">>> "
send "q\n"
expect -exact "Task to do \[fmtfossil\]:"
send "\n"
expect -exact "Fossil partition to format \(/dev/sd00/fossil\)\[/dev/sd00/fossil\]:"
send "\n"
expect -exact "Task to do \[mountfs\]:"
send "\n"
expect -exact "Fossil partition \(/dev/sd00/fossil\)\[/dev/sd00/fossil\]:"
send "\n"
expect -exact "Task to do \[configdist\]:"
send "\n"
expect -exact "Distribution is from \(local, net\)\[local\]:"
send "\n"
expect -exact "Task to do \[mountdist\]:"
send "\n"
expect -exact "Distribution disk \[no default\]:"
send "/dev/sdD0/data\n"
expect -exact "Location of archives \[browse\]:"
send "/\n"
expect -exact "Task to do \[copydist\]:"
send "\n"
# Need to wait for the copy to finish.
expect -timeout 600 -exact "Task to do \[bootsetup\]:"
send "\n"
expect -exact "Enable boot method (floppy, plan9, win9x, winnt)\[no default\]:"
send "plan9\n"
expect -exact "Install the Plan 9 master boot record (y, n)\[no default\]:"
send "y\n"
expect -exact "Task to do \[finish\]:"
send "\n"
expect -exact "Feel free to turn off your computer."
exit
EOF

## Configuration.
#expect <<EOF
#spawn qemu-system-i386 -nographic -net user -net nic,model=virtio -m 1024 -vga none -drive if=none,id=hd,file=disk.raw -device virtio-scsi-pci,id=scsi -device scsi-hd,drive=hd -cdrom 9legacy.iso -boot c
#expect -exact "Plan 9"
#sleep 5
## Need to wait for the kernel to boot.
#expect -timeout 600 -exact "term% "
#send "\n"
#expect -exact "term% "
#send "mkdir /cfg/helix\n"
#expect -exact "term% "
#send "dircp /cfg/example /cfg/helix\n"
#expect -exact "term% "
#send "echo ip/ipconfig -o mtu >>/cfg/helix/cpurc\n"
#expect -exact "term% "
#send "echo ndb/dns -r >>/cfg/helix/cpurc\n"
#expect -exact "term% "
#send "echo echo remove 10.0.0.0 /104 10.0.0.0 '>'/net/iproute >>/cfg/helix/cpurc\n"
#expect -exact "term% "
#send "echo ramfs -su >>/cfg/helix/cpustart\n"
#expect -exact "term% "
#send "echo mount -c /srv/ramfs /tmp >>/cfg/helix/cpustart\n"
#expect -exact "term% "
#send "echo aux/randfs -m /dev >>/cfg/helix/cpustart\n"
#expect -exact "term% "
#send "echo kill timesync '|' rc >>/cfg/helix/cpustart\n"
#expect -exact "term% "
#send "echo echo downloading git >>/cfg/helix/cpustart\n"
#expect -exact "term% "
#send "echo hget http://9legacy.org/9legacy/tools/git '>'/usr/glenda/bin/rc/git >>/cfg/helix/cpustart\n"
#expect -exact "term% "
#send "echo chmod +x /usr/glenda/bin/rc/git >>/cfg/helix/cpustart\n"
#expect -exact "term% "
#send "echo bind -a /usr/glenda/bin/rc /bin >>/cfg/helix/cpustart\n"
#
#expect -exact "term% "
#send "auth/wrkey\n"
#expect -exact "authid: "
#send "glenda\n"
#expect -exact "authdom: "
#send "harvey\n"
#expect -exact "auth password: "
#send "glenda123\n"
#expect -exact "secstore password: "
#send "glenda123\n"
#expect -exact "term% "
#send "fshalt\n"
#expect -exact "done halting"
#exit
#EOF
#
#
#	expect <<EOF
#	spawn qemu-system-i386 -machine accel=kvm -nographic -net user -net nic,model=virtio -m 1024 -vga none -drive if=none,id=hd,file=disk.raw -device virtio-scsi-pci,id=scsi -device scsi-hd,drive=hd -cdrom 9legacy.iso -boot c
#	expect -exact "Plan 9"
#	sleep 5
#	# Need to wait for the kernel to boot.
#	expect -timeout 600 -exact "term% "
#	send "\n"
#	expect -exact "term% "
#	send "echo 'aux/listen1 tcp!*!17007 /bin/exportfs -a &' >>/cfg/helix/cpurc\n"
#	expect -exact "term% "
#	send "echo 'aux/listen1 tcp!*!17010 /bin/cpu -R &' >>/cfg/helix/cpurc\n"
#	expect -exact "term% "
#	send "mkdir /usr/glenda/bin/amd64\n"
#	expect -exact "term% "
#	send "9fat:\n"
#	expect -exact "term% "
#	send "cp /amd64/9k10cpuf /n/9fat\n"
#	expect -exact "term% "
#	send "sed s/9pcf/9k10cpuf/ /n/9fat/plan9.ini >/tmp/plan9.ini\n"
#	expect -exact "term% "
#	send "mv /tmp/plan9.ini /n/9fat/plan9.ini\n"
#	expect -exact "term% "
#	send "sed s/sd00/$disk/ /n/9fat/plan9.ini >/tmp/plan9.ini\n"
#	expect -exact "term% "
#	send "mv /tmp/plan9.ini /n/9fat/plan9.ini\n"
#	expect -exact "term% "
#	send "unmount /n/9fat\n"
#	expect -exact "term% "
#	send "fossil/conf /dev/sd00/fossil | sed s/sd00/$disk/ >/tmp/fossil.conf\n"
#	expect -exact "term% "
#	send "fossil/conf -w /dev/sd00/fossil /tmp/fossil.conf\n"
#	expect -exact "term% "
#	send "rm /tmp/fossil.conf\n"
#	expect -exact "term% "
#	send "fshalt\n"
#	expect -exact "done halting"
#exit
#EOF

echo

echo "Done. QEMU image is disk.raw."
