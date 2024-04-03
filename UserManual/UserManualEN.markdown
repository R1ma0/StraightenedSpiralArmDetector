# User's Manual

This manual provides general information and operating instructions for software for processing astronomical images of galaxies with complex spiral structure - ***"Straight spiral arm detector" (SSAD)***.

The software is designed to simplify the processing of spiral galaxy patterns to extract straight arm segments (*[rows](#glossary_2)*), partially or fully automating the operations associated with the process.

The software is primarily intended for use by the scientific community in conducting research on the detection of vertex spiral galaxies.

    Manual version v1.0.0
    Programme version v1.1.0

# Table of Contents

- [Programme functions.](#prog_func)
- [System Requirements.](#system_req)
- [Programme installation.](#installation)
- [Launching the program.](#launch)
- [Programme main window.](#main_win)
  - [File menu.](#menu_file)
  - [View menu.](#menu_view)
  - [Processing menu.](#menu_proc)
  - [Preview window.](#preview_img)
- [Skeletonisation Algorithms.](#skeleton_algos)
  - [Adaptive Zonga-Suen](#adapt_zhang_suen)
- [Plain view.](#to_plain_view)
- [Glossary.](#glossary)
- [Supplementary materials.](#additions)

# <a name="prog_func">Programme functions</a>
- Loading images in formats: PNG, JPG, JPEG.
- Saving images in PNG, JPG, JPEG formats.
- Bringing an image to a floating view (rotate and stretch).
- Selection of rows by *Adaptive method of skeletonisation Zong-Sun*.
- Interface language: Russian, English.

# <a name="system_req">System Requirements</a>

Minimum configuration requirements *[PC](#glossary_3)*.
- Operating system: Windows 10.
- Free space on the hard disc: 500 MB.
- RAM capacity: 1 GB.
- Processor frequency: 2.3 GHz.
- Number of processor cores: 2.

# <a name="installation">Installation of the programme</a>

The software and all components necessary for work are distributed as an archive. Before you start working, you should unzip the files to a convenient place on your hard disc.

    WARNING! It is strongly not recommended to delete, modify or move the programme files. These actions may adversely affect its performance.

# <a name="launch">Start the programme</a>

To launch the program you need to run the file ***SSADLauncher.exe***, located in the folder specified during unpacking on your hard drive.

The following actions are available in the *[Launcher](#glossary_4)* window.

![SSADLauncher](imgEN/1_launcher.PNG "Programme Launcher Window")

- **Language** - change the *[interface](#glossary_5)* language of the Launcher and the programme.
- **Fullscreen** - launch the programme window in full screen.
- **Resolution** - set the size of the programme window when not running full screen.
- **Save** - saves the set parameters.
- **Reset** - resets the set parameters to default values (you must save to apply).
- **Manual** - opens this manual in a browser window.
- **Start** - starts the main programme.

# <a name="main_win">Main window of the programme</a>

## <a name="menu_file">"File" menu</a>

![MenuFile](imgEN/2_file_menu.PNG "File menu.")

- **Load Image** - load image for processing in PNG, JPG, JPEG formats.
- **Save Image** - saves the processed image in PNG, JPG, JPEG formats. Available after image loading.
- **Quit** - close the programme.

## <a name="menu_view">Menu "View"</a>

![MenuView](imgEN/3_view_menu.PNG "Menu 'View'")

- **Zoom** - zooms in on the image in the *[preview](#preview_img)* window. Available after the image is loaded.
- **Down** - zooms out the image in the preview window. Available after the image is loaded.

## <a name="menu_proc">Menu "Processing"</a>

![MenuProc](imgEN/4_proc_menu.PNG "Menu 'Processing'")

- **Rotate and Stretch** - brings the image to *[flat view](#glossary_6)*. Available after the image has been loaded.
- **Skeletonisation Algorithms** - ready-made sets of algorithms for processing an image by *[skeletonisation](#glossary_7)*.
- **Multiple Image Processing** - expected to be implemented in the future.

## <a name="preview_img">Preview window</a>

![PreviewImg](imgEN/5_preview_img.PNG "Preview window")

# <a name="skeleton_algos">Skeletonisation algorithms</a>

## <a name="adapt_zhang_suen">Adaptive Zonga-Sun`s</a>

Adaptive skeletonisation using the Zong-Sun method consists of the following processing algorithms.

1. adaptive Gaussian binarisation.
2. Reducing the image size while preserving the aspect ratio. Affects the performance and detail of the image.
3. Threshold binarisation. The lower the value, the more detail remains, and the higher the value, the less noisy the image becomes.
4. Adding missing pixels using a template. Used to improve the skeleton structure.
![AddingPixels](imgCommon/adding_pixels.png "Adding Pixels Template")
5. Removing extra pixels according to the template. Used to remove noise.
![RemovingPixels](imgCommon/removing_pixels.png "Removing Pixels Template")
6. Skeletonisation using the Zong-Sun method.

The settings window of the Zong-Sun method consists of the following items.

![AdaptiveZhangSuenMethod](imgEN/6_adapt_zhang_suen.PNG "Window of the adaptive Zong-Sun method")

- **Binarisation threshold value** - used in the third step of the algorithm to bring the image to binary form, as well as to change the level of its detail, in particular, to reduce noise and, as a consequence, to highlight the structure of the sleeves more clearly.
- **Gaussian constant** - subtracted from the weighted average value. Affects the level of skeleton detail.
- **Image Compression Percentage** - the percentage to which the image is compressed relative to the original image. It affects the processing and detailing time of the final image.
- **Gauss block size value (odd)** - used to specify the number of neighbouring pixels for threshold calculation.
- **Process** - starts image processing with specified parameters.

# <a name="to_plain_view">Bringing it to the "flat" view</a>

The ToPlainView window consists of the following items.

![ToPlainView](imgEN/7_to_plain_view.PNG "Plain View Window")

- **Current rotation value** - displays the current rotation angle of the image.
- **Set rotation value** - enter a new value of the image rotation angle.
- **Current Width** - displays the current image width.
- **Set Width** - enter a new image width.
- **Current Height** - displays the current height of the image.
- **Set Height** - enter the new height of the image.
- **Apply** - applies the entered values to the loaded image.

# <a name="glossary">Glossary</a>

> ### <a name="glossary_2">*Rows*</a> 
> One of the structural features of spiral galaxy patterns. Polygonal arms formed by straight segments.

> ### <a name="glossary_3">*PC*</a>
> Personal computer.

> ### <a name="glosssary_4">*Launcher*</a>
> A programme that runs any programmes or processes.

> ### <a name="glossary_5">*Interface*</a>
> A system of means for user interaction with electronic devices, based on the representation of all system objects and functions available to the user in the form of graphic screen components (windows, icons, menus, buttons, lists, etc.). 

> ### <a name="glossary_6">*Flat view*</a>
> The image is rotated and stretched along one of the axes. Applies to galaxies located at an angle to the observer.

> ### <a name="glossary_7">*Skeletonisation*</a>
> It makes it possible to represent a binary image as a set of thin lines whose mutual location, size and shape adequately describe the size, shape and orientation in space of the corresponding image regions.

# <a name="additions">Supplementary materials</a>

1. Vorontsov-Velyaminov B. A. On the nature of a new feature in the galaxy M 81 // Soviet Astronomy. - 1967. - Vol. 10, no. 6. - P. 1057-1058.
2. Galaxies with Rows / A. D. Chernin [et al.] // Astronomy Reports. - 2001. - Vol. 45, no. 11. - P. 841-853.
3. Butenko M. A., Khoperskov A. V. V. Galaxies with "twirls": a new catalogue // Astrophysical Bulletin. - 2017. - Vol. 72, no. 3. - С. 256-275.
4. Butenko M. A. Statistical processing of images of spiral galaxies with polygonal structures // Bulletin of Volgograd State University. - 2015. Vol. - 26, no. 1. - С. 52-60.