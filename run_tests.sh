echo ""
echo "================================================================"
echo "Building Sim..."
echo "================================================================"
echo ""

make

echo ""
echo "================================================================"
echo "Running unit tests (code-based test cases)..."
echo "================================================================"
echo ""

./sim 2 8 val_trace_gcc1 > res.txt
diff -i -w res.txt ./data/validation_runs/pipe_2_8_gcc.txt > /dev/null
diff_val=$?
if  [[ $diff_val != 0 ]]; then
        echo -e "\e[91mfail (output mismatch)\e[m"
else
        echo -e "\e[92mPASS!\e[m"
fi


./sim 8 8 val_trace_gcc1 > res.txt
diff -i -w res.txt ./data/validation_runs/pipe_8_8_gcc.txt > /dev/null
diff_val=$?
if  [[ $diff_val != 0 ]]; then
        echo -e "\e[91mfail (output mismatch)\e[m"
else
        echo -e "\e[92mPASS!\e[m"
fi


./sim 64 1 val_trace_gcc1 > res.txt
diff -i -w res.txt ./data/validation_runs/pipe_64_1_gcc.txt > /dev/null
diff_val=$?
if  [[ $diff_val != 0 ]]; then
        echo -e "\e[91mfail (output mismatch)\e[m"
else
        echo -e "\e[92mPASS!\e[m"
fi


./sim 128 8 val_trace_gcc1 > res.txt
diff -i -w res.txt ./data/validation_runs/pipe_128_8_gcc.txt > /dev/null
diff_val=$?
if  [[ $diff_val != 0 ]]; then
        echo -e "\e[91mfail (output mismatch)\e[m"
else
        echo -e "\e[92mPASS!\e[m"
fi


./sim 256 8 val_trace_gcc1 > res.txt
diff -i -w res.txt ./data/validation_runs/pipe_256_8_gcc.txt > /dev/null
diff_val=$?
if  [[ $diff_val != 0 ]]; then
        echo -e "\e[91mfail (output mismatch)\e[m"
else
        echo -e "\e[92mPASS!\e[m"
fi
