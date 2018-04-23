# store $PWD
__mrjob_PWD=$PWD

# obtain exclusive file lock
exec 9>/tmp/wrapper.lock.wc.ravi.20180403.035948.083535
python3 -c 'import fcntl; fcntl.flock(9, fcntl.LOCK_EX)'

# setup commands
{
  export PYTHONPATH=$__mrjob_PWD/mrjob.zip:$PYTHONPATH
} 0</dev/null 1>&2

# release exclusive file lock
exec 9>&-

# run task from the original working directory
cd $__mrjob_PWD
"$@"
