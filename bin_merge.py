import os
import subprocess

def merge_bin_action():
    # Retrieve the build directory where PlatformIO outputs binaries
    build_dir = ".pio/build/qemu"

    # Define paths to the individual binaries
    bootloader = os.path.join(build_dir, "bootloader.bin")
    app_bin = os.path.join(build_dir, "firmware.bin")
    partition_table = os.path.join(build_dir, "partitions.bin")
    
    combined_bin = os.path.join(build_dir, "combined.bin")

    # Construct the merge command using the known memory offsets
    merge_cmd = (
        "esptool.py --chip esp32 merge_bin -o {} "
        "0x1000 {} 0x8000 {} 0x10000 {}"
    ).format(combined_bin, bootloader, partition_table, app_bin)

    # Inform the user and execute the command
    print("Merging binaries into: " + combined_bin)
    subprocess.check_call(merge_cmd, shell=True)

merge_bin_action()
