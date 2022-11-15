# Gaussian-Filter
Program that filters operation on an image (matrix) to remove noise (denoising) on the image.

# Project Description

1. There is an input file (inputs.txt) which contains four parameters image size (odd number), filter size (odd number), white pixel value and black pixel value, respectively. The program read these four parameters and make the necessary calculations. When we change these values, the output results also changes.

2. Program generates a input image (Red border matrix in Figure 1) of pixel values of random data and a gaussian filter (Blue border matrix in Figure 1). Gaussian filter is also another matrix and I used given “makeKernel.cpp” to create it.

3. It would be incorrect to apply the filter on the input image directly. Because, in this case the size of the output image will decrease. For instance, when a 5x5 filter is applied to a 7x7 size input image, the output image size will decrease to 7 - 5 + 1, that is 3x3. To eliminate this undesired situation, edges of image are mirrored (Yellow parts on input grid in Figure 1) and image is placed on the input grid (constant size 21x21) of zeros. Thus, dimension of the input image and the dimension of the output image will be equal.

4. Filtering is applied for each pixel value of the input image shown in Figure 1 with blue dashed lines. As you see, size of edge mirror is equal to half of the filter size. For example, if the filter size is 5 mirror size is equal to 5/2=2. In this figure, image size and filter size is 5x5 and 3x3, respectively.

5. The edges of the mirrored image in the defined output grid (constant size 21x21), which is the same size as the input grid, are cut off.

6. The output image is obtained by extracting from the output grid, thus it is the same size with the input image.

7. As a result, program generates an output file (output.txt) containing the followings;

- input image,
- gaussian filter,
- input grid,
- output grid and
- filtered output image.

![Screenshot 2022-10-26 200300](https://user-images.githubusercontent.com/102357822/198090448-51710671-5906-4494-85cd-361b8492925c.png)


# Output Example

![Screenshot 2022-11-16 005836](https://user-images.githubusercontent.com/102357822/202034081-8abf17c4-64e3-49d1-a075-f160546d2882.png)

![Screenshot 2022-11-16 005931](https://user-images.githubusercontent.com/102357822/202034093-c53ec592-6806-43b8-8bcf-6197700a64cd.png)


