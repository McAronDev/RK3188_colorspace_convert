# RK3188_colorspace_convert
RK3188 hardware (RGA) colorspace convert demo

 
Testing colorspace convertions.


Usage: ./colorspace_convert converter in_file out_file width height

  converter: [NV12toRGB565, NV12toI420, NV12toNV12]
  in-file - raw yuv sequence file
  
  
NV12toRGB565 produces good frames but with black areas in random places. Wrong settings?
NV12toI420, NV12toNV12 added for testing. Both produces green frames with image contours
