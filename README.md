# ImageTransformer
This project is intended as a deeper forray into C++ and design patterns than what was taught in coursework at school. Initially written as a school project, this image transformer is a refactor of a separate program. No third party libaries were used in this program. 

In simple terms, the design is as follows:

User input -> load file -> adapt raw image values to generic format -> transform values of the generic format -> adapt generic format back to original -> write image back to disk.

Usage:

ImageTransformer.exe inputFilePath transformationChoice outputfilePath



Current supported image types:

Bmp 24 / 32 bit images


Current supported transformation types:

Cellshade
Greyscale
Rotate 180 degrees
Gaussian blur

In progress:

Pixelate
ScaleUp
ScaleDown
Rotate 90 degrees
