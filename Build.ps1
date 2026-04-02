# PowerShell script to build GLFW and the main OpenGL SuperBible project

# Set the root directory (adjust if needed)
$rootDir = "$PSScriptRoot"

# Change to GLFW directory
Push-Location "$rootDir\extern\glfw-3.0.4"

try {
    # Generate Visual Studio project files for GLFW
    & cmake -S . -B build\Release
    & cmake -S . -B build\Debug

    # Build Debug configuration
    & cmake --build build\Release --config Release
    & cmake --build build\Debug --config Debug

    # Copy and rename libraries to lib directory
    Copy-Item "build\Debug\src\Debug\glfw3.lib" "$rootDir\lib\glfw3_d.lib"
    Copy-Item "build\Release\src\Release\glfw3.lib" "$rootDir\lib\glfw3.lib"

    # Copy PDB files
    Copy-Item "build\Debug\src\Debug\glfw3.pdb" "$rootDir\lib\glfw3.pdb"
}
finally {
    # Return to the original directory
    Pop-Location
}

# Generate Visual Studio project files for main project
& cmake -S . -B build

Write-Host "Build completed."