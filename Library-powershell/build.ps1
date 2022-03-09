$BuildFolder = "build" 
$ExecutableName = "math.exe"

function Build-Number {
    echo "Building Number:"
    g++ -c MathLibrary/MathLibrary.cpp -o build/MathLibrary.o
    ar rvs build/MathLibrary.lib build/MathLibrary.o
    echo "[DONE]"
    echo ""
}

function Build-Vector {
    echo "Building Vector:"
    g++ -c -IMathLibrary Vector/Vector.cpp -o build/Vector.o
    g++ -shared -o build/libVector.dll build/Vector.o build/MathLibrary.lib
    echo "[DONE]"
    echo ""
}

function Build-App {
    echo "Building App:"
    g++ -IMathLibrary -IVector -Lbuild/ -lVector MathClient/MathClient.cpp -o build/$ExecutableName
    echo "[DONE]"
    echo ""
}

function Build {
    if (-Not (Test-Path -Path $BuildFolder)) {
        mkdir $BuildFolder
    }
    Build-Number
    Build-Vector
    Build-App   
}

function Clean{
    echo "Cleaning build files"
    if (Test-Path -Path $BuildFolder) {
        rm -r $BuildFolder
    }
    echo "[DONE]"
    echo ""
}

function Run {   
    echo "Running the project at $BuildFolder/${ExecutableName}:"
    if (Test-Path -Path $BuildFolder/$ExecutableName) {
        &".\build\$ExecutableName"
    } else {
        echo "$ExecutableName not found. Firstly, consider building the project."
    }
    echo "[DONE]"
    echo ""
}

Build
Run
pause