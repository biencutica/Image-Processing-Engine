# C++ Image Processing Engine

This is a lightweight image processing engine built from scratch in C++. It is designed to load and manipulate plain-text (ASCII) PGM images, offering a range of powerful editing features through a custom-built Image class.

This project was built without external image libraries to demonstrate core C++ principles, including manual memory management and algorithm implementation.

## Key Features

### File Operations

-- Loads plain-text (ASCII) PGM files into a custom Image object.

-- Saves the manipulated image data back to a new PGM file.

### Editing & Adjustments

-- Brightness & Contrast: Adjust the overall brightness and contrast of the image.

-- Gamma Correction: Apply non-linear gamma correction.

-- 2D Convolution: Apply custom kernels using a 2D convolution algorithm.

### Drawing Module

-- Lines: Draw lines between two points.

-- Shapes: Draw circles, rectangles, and squares.

## Technical Highlights

* **Built from Scratch:** The entire engine, including the Image class and all processing algorithms, is implemented in pure C++ without external libraries.

* **Robust Memory Management:** The Image class correctly implements manual memory management, adhering to the Rule of Three (copy constructor, copy assignment operator, and destructor).

* **Intuitive API:** The class uses operator overloading for intuitive, pixel-wise arithmetic (e.g., image-to-image or image-to-scalar operations).

# Technologies Used

* **C++** (including advanced features like manual memory management and operator overloading)

* **Standard Library (STL)**
