make

if [ ! -z "$1" ]
then
    if [ $1 == 1 ]
    then
    echo "======================PIPE_2_8_GCC======================"
    ./sim 2 8 val_trace_gcc1

    elif [ $1 == 2 ]
    then

    echo "======================PIPE_8_8_GCC======================"
    ./sim 8 8 val_trace_gcc1

    elif [ $1 == 3 ]
    then

    echo "======================PIPE_64_1_GCC======================"
    ./sim 64 1 val_trace_gcc1

    elif [ $1 == 4 ]
    then

    echo "======================PIPE_128_8_GCC======================="
    ./sim 128 8 val_trace_gcc1

    elif [ $1 == 5 ]
    then

    echo "======================PIPE_256_8_GCC======================="
    ./sim 256 8 val_trace_gcc1

    fi
else

echo "======================PIPE_2_8_GCC======================"
./sim 2 8 val_trace_gcc1

echo "======================PIPE_8_8_GCC======================"
./sim 8 8 val_trace_gcc1

echo "======================PIPE_64_1_GCC======================"
./sim 64 1 val_trace_gcc1

echo "======================PIPE_128_8_GCC======================="
./sim 128 8 val_trace_gcc1

echo "======================PIPE_256_8_GCC======================="
./sim 256 8 val_trace_gcc1

fi