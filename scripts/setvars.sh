export OFFLOADBASE=$PWD
export BASE=$PWD
export MACHINE="CLOUDLAB"

#### DEVICE NAME ########
export DEVICE="NVMemu"
#export DEVICE="optane"

export STORAGEPATH="/mnt/ram"
export AUXILLARY="/mnt/pmemdir"

######## DO NOT CHANGE BEYOUND THIS ###########
#Pass the release name
export OS_RELEASE_NAME=$1
export KERN_SRC=$BASE/kernel/linux-5.6.9
export DEVFSCLIENT=$BASE/libfs
export LIBFS=$BASE/libfs
export NVMALLOC_HOME=$LIBFS/nvmlog


#CPU parallelism
export PARA="32"
export VER="5.6.9"

#QEMU
export QEMU_IMG=$BASE
export QEMU_IMG_FILE=$QEMU_IMG/qemu-image-fresh.img
export MOUNT_DIR=$QEMU_IMG/mountdir
export QEMUMEM="36G"
export KERNEL=$BASE/KERNEL

export TEST_TMPDIR=/mnt/pmemdir

export RESULTS=$OFFLOADBASE/RESULTS/$MACHINE

#Commands
#mkdir $OUTPUTDIR
mkdir $KERNEL
