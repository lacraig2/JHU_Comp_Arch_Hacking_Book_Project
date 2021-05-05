# This example supports x86, x86_64, and ARM.
# 
# It checks if you are on the right architecture
# when running the ARM example and uses QEMU
# if your machine isn't ARM.


arch=$(arch)

if [[ "$#"  -lt  1 ]]; then
    arg1=$(arch)
else
    arg1=$1
fi

if [[ $arg1 == "amd64" || $arg1 == "x86_64" ]]; then
    echo "[INFO] You selected an amd64 demo"
    ./demo_amd64 `python -c "print('a'*24+'HACK')"`
elif [[ $arg1 == "arm" ]]; then
    echo "You selected an arm demo"
    if [[ $arch == "arm" ]]; then
        echo "[INFO] Running on native arm machine"
        ./demo ABCDABCDABCDABCEEEEEHACK
    else
        echo "[INFO] Running in qemu-arm"
        qemu-arm -L /usr/arm-linux-gnueabihf/ ./demo_arm ABCDABCDABCDABCEEEEEHACK
    fi
else
    echo "Defaulted to i386"
    ./demo_i386 `python -c "print('a'*28+'HACK')"`
fi