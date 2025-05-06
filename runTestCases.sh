./BuildTestRoms.sh
cmake -S . -B build 
cmake --build build --config Release -j8

mkdir -p ./results/
RomList=(
        "nya~"
        "./games/TestRom1.nes -o ./results/TestRom1.s"
        "./games/TestRom4.nes -o ./results/TestRom4.s"
        "./games/TestRom2.nes -o ./results/TestRom2.s"
)

for p in "${RomList[@]}"; do
        # Split the command string into an array
        args=($p)
        
        # Run the cl65 command with the appropriate arguments
        if ./nesda "${args[@]}"; then
            echo "Built ${args[2]} successfully"
        else
            echo "Built ${args[2]} unsuccessfully"
        fi

        echo ""
    done