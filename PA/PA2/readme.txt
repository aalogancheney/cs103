CSCI 103 Programming Assignment 2, Chroma Key, Fall 2014

Name: Aaron Cheney

Email Address: acheney@usc.edu

=============================== Prelab =======================================

Pixel                |    RGB Value     |  Distance from Chroma Key
-------------------------------------------------------------------
Top-left background  | (69, 138, 19)    |  n/a
Arm                  | (253, 158, 114)  |  208.04
Vest                 | (29, 31, 28)     |  114.59
Shirt                | (251, 216, 248)  |  302.74

================================== Review ===================================
Response 1: I chose to sample the top three rows and left three columns.
These pixels are almost always going to be entirely in the background. The
reason for not sampling more rows/columns is that sometimes the 
foreground might extend farther up the image or more to the left. Any fewer
pixels and I would run the risk of not having enough sample points for
the average.

Response 2: For the Colbert image the acceptable thresholds fall between 60
and 80, and for the Bird image the acceptable thresholds fall between 40-90, 
a much larger range than the Colbert image. Since the background of the bird
is more or less a constant it is easier to define a threshold that gets rid
of almost every green pixel. It also helps that the bird does not contain
colors that are "close" to the background.

Colbert range: from 60 to 80
Bird range: from 40 to 90

Response 3: I decided to determine what exactly makes the background unique
from the foreground. The problem with method1() is that you not only need
a threshold, but that the distance function does not consider individual
R, G, or B values -- it takes them all into consideration. This can make
two colors seem "close" together when in fact they are not visualy 
close. 

First I use the averageRGB() function to get the average values of the R,
G and B values in the first 3 rows and columns of the image. Then I use
two functions, maximumRGB() and minimumRGB() to determine the maximum and
minimum values each color component achieves within those first 3 rows
and columns. Within each maximumRGB() and minimumRGB() function I also
consider that part of the foreground may sneak into those 3 rows/columns
or that there may be a sample of pixels that shouldn't be considered, so
I ignore the first 10 maximum/minimum values in those sampled rows/
columns above a certain threshold. 

Next I use those maximum and minimum values as a range for deviation from
the average for each R, G, and B values. A small tollerance value is 
added to this range, in case the maximum and minimum values are not 
very different from one another, as shadows from the foreground could 
cause an issue. This "fudge factor" is set to 5.

The last step is creating the mask array from these ranges and values. 
After this, the steps are identical to method1(). 

I did not consider other methods, but I had to do a fair amount of 
tweaking to get my code to work for a range of images. For example,
the astro.bmp image contains some white pixels in the first three rows/
columns, and this threw off my range. This is when I decided to throw
out the first 10 maximum/minimum values I ran into, so that if there 
are more than 10 values on the outlying distance from the average then
they are more than likely part of the background and should be counted
toward the maximum/minimum. 

The pros for my method are that all of the numbers can be adjusted in
the code to sample more rows/columns, allow for a greater tollerance,
or ignore more maximum/minimum values. Also, there is no user input
required for my method. Although the tollerance and allowance
variables are coded into the program, they are universal for most 
images and deviations from the chromakey.

Each one of the images we were given provided a different challenge:

- Bird: background is mostly static except for the pixels around the
  bird itself. 
- Colbert: there are some parts of the green screen that are lighter
  and darker than the rest, such as inbetween his legs or near is 
  body.
- Faded Colbert (which would be fun to see): the background color is
  not very different from the foreground, so we cannot be too lenient
  when deciding which pixels to replace. 
- Astro: there are parts of the image in the first few rows/columns 
  that are not part of the background yet appear in the sampled 
  pixels.
- Smurfbert: similar to the faded colbert, but not as dramatic.

For each of the images my program handles their cases very well and
produces a very acceptable image for these range of challences.  

The cons for my method are that some images may require a larger/smaller
tollerance or a bigger fudge factor to make the end result look
good. These can, however, be changed within the code.

Another downside to my approach is that my method works best for a 
background with a larger variance in the first few rows and columns.
As an example, in the Bird image the first few rows and columns are 
basically the same color, so my minimum and maximum values are not 
very far apart and do not tollerate a large variance later. The 
problem with this is that the areas directly around the bird, which are
slightly darker than the rest of the image, are not considered part of
the background. To account for this I have included a small fudge factor
of 5 to buff up the range of acceptable values in the background. 

On the other hand, when the background color is close to the foreground 
image, as in the faded.bmp image of Colbert, my fudge factor starts causing 
bits of the foreground to be replaced with the background image. The
small factor of 5 seems insignificant, but it can swing the image one
way or the other: removing it for the Bird image and I am left with 
a large green outline of the image; remove it from the faded image and
I get a near perfect replacement. 

EDIT: After experimentation I redefined my fudge factor as 2 instead of 5,
which was a decent compromise for both the bird and faded images. 

================================ Remarks ====================================

Filling in anything here is OPTIONAL.

Approximately how long did you spend on this assignment?

: About 6-7 hours.

Were there any specific problems you encountered? This is especially useful to
know if you turned it in incomplete.

: No particular issues, just programming challenges. Having the extra 
pictures to test our code shed light on some oversights in my method and I
was able to fix them. Having those extra images earlier would have made
the process smoother. 

Do you have any other remarks?

: No.
