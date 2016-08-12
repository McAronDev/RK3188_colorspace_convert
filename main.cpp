#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define CONFIG_ARCH_RK30 1

#include "rga.h"


//rga_nv12torgb565 is from https://github.com/Nu3001/hardware_rk29_camera/blob/master/CameraHal.cpp

static int rga_nv12torgb565(int fd,int width, int height, char *src, short int *dst, int dstbuf_width)
{


	struct rga_req  Rga_Request;
	    int err = 0;

	    memset(&Rga_Request,0x0,sizeof(Rga_Request));

	    Rga_Request.src.yrgb_addr =  (int)src;
	    Rga_Request.src.uv_addr  = (int)src+width*height;
	    Rga_Request.src.v_addr   =  Rga_Request.src.uv_addr;
	    Rga_Request.src.vir_w =  width;
	    Rga_Request.src.vir_h = height;
	    Rga_Request.src.format = RK_FORMAT_YCbCr_420_SP;
	    Rga_Request.src.act_w = width;
	    Rga_Request.src.act_h = height;
	    Rga_Request.src.x_offset = 0;
	    Rga_Request.src.y_offset = 0;

	    Rga_Request.dst.yrgb_addr = (int)dst;
	    Rga_Request.dst.uv_addr  = 0;
	    Rga_Request.dst.v_addr   = 0;
	    Rga_Request.dst.vir_w = dstbuf_width;
	    Rga_Request.dst.vir_h = height;
	    Rga_Request.dst.format = RK_FORMAT_RGB_565;
	    Rga_Request.clip.xmin = 0;
	    Rga_Request.clip.xmax = width - 1;
	    Rga_Request.clip.ymin = 0;
	    Rga_Request.clip.ymax = height - 1;
	    Rga_Request.dst.act_w = width;
	    Rga_Request.dst.act_h = height;
	    Rga_Request.dst.x_offset = 0;
	    Rga_Request.dst.y_offset = 0;
	    Rga_Request.rotate_mode = 0;
	    Rga_Request.mmu_info.mmu_en    = 1;
	    Rga_Request.mmu_info.mmu_flag  = ((2 & 0x3) << 4) | 1;
	    Rga_Request.alpha_rop_flag |= (1 << 5); /* ddl@rock-chips.com: v0.4.3 */

    if(ioctl(fd, RGA_BLIT_SYNC, &Rga_Request) != 0) {
        printf("%s(%d):  RGA_BLIT_SYNC Failed\n", __FUNCTION__, __LINE__);
        err = -1;
    }
    return err;
}


static int rga_nv12toi420(int fd,int width, int height, char *src, short int *dst, int dstbuf_width)
{


    struct rga_req  Rga_Request;
    int err = 0;

    memset(&Rga_Request,0x0,sizeof(Rga_Request));

    Rga_Request.src.yrgb_addr =  (int)src;
    Rga_Request.src.uv_addr  = (int)src+width*height;
    Rga_Request.src.v_addr   =  Rga_Request.src.uv_addr;
    Rga_Request.src.vir_w =  width;
    Rga_Request.src.vir_h = height;
    Rga_Request.src.format = RK_FORMAT_YCbCr_420_SP;
    Rga_Request.src.act_w = width;
    Rga_Request.src.act_h = height;
    Rga_Request.src.x_offset = 0;
    Rga_Request.src.y_offset = 0;

    Rga_Request.dst.yrgb_addr = (int)dst;
    Rga_Request.dst.uv_addr  = (int)dst+width*height;
    Rga_Request.dst.v_addr   = Rga_Request.dst.uv_addr;
    Rga_Request.dst.vir_w = dstbuf_width;
    Rga_Request.dst.vir_h = height;
    Rga_Request.dst.format = RK_FORMAT_YCbCr_420_P;
    Rga_Request.clip.xmin = 0;
    Rga_Request.clip.xmax = width - 1;
    Rga_Request.clip.ymin = 0;
    Rga_Request.clip.ymax = height - 1;
    Rga_Request.dst.act_w = width;
    Rga_Request.dst.act_h = height;
    Rga_Request.dst.x_offset = 0;
    Rga_Request.dst.y_offset = 0;
    Rga_Request.rotate_mode = 0;
    Rga_Request.mmu_info.mmu_en    = 1;
    Rga_Request.mmu_info.mmu_flag  = ((2 & 0x3) << 4) | 1;
    Rga_Request.alpha_rop_flag |= (1 << 5);             /* ddl@rock-chips.com: v0.4.3 */

    if(ioctl(fd, RGA_BLIT_SYNC, &Rga_Request) != 0) {
        printf("%s(%d):  RGA_BLIT_ASYNC Failed\n", __FUNCTION__, __LINE__);
        err = -1;
    }
    return err;
}

//JUST FOR TESTING
static int rga_nv12tonv12(int fd,int width, int height, char *src, short int *dst, int dstbuf_width)
{


    struct rga_req  Rga_Request;
    int err = 0;

    memset(&Rga_Request,0x0,sizeof(Rga_Request));

    Rga_Request.src.yrgb_addr =  (int)src;
    Rga_Request.src.uv_addr  = (int)src+width*height;
    Rga_Request.src.v_addr   =  Rga_Request.src.uv_addr;
    Rga_Request.src.vir_w =  width;
    Rga_Request.src.vir_h = height;
    Rga_Request.src.format = RK_FORMAT_YCbCr_420_SP;
    Rga_Request.src.act_w = width;
    Rga_Request.src.act_h = height;
    Rga_Request.src.x_offset = 0;
    Rga_Request.src.y_offset = 0;

    Rga_Request.dst.yrgb_addr = (int)dst;
    Rga_Request.dst.uv_addr  = (int)dst+width*height;
    Rga_Request.dst.v_addr   = Rga_Request.dst.uv_addr;
    Rga_Request.dst.vir_w = dstbuf_width;
    Rga_Request.dst.vir_h = height;
    Rga_Request.dst.format = RK_FORMAT_YCbCr_420_SP;
    Rga_Request.clip.xmin = 0;
    Rga_Request.clip.xmax = width - 1;
    Rga_Request.clip.ymin = 0;
    Rga_Request.clip.ymax = height - 1;
    Rga_Request.dst.act_w = width;
    Rga_Request.dst.act_h = height;
    Rga_Request.dst.x_offset = 0;
    Rga_Request.dst.y_offset = 0;
    Rga_Request.rotate_mode = 0;
    Rga_Request.mmu_info.mmu_en    = 1;
    Rga_Request.mmu_info.mmu_flag  = ((2 & 0x3) << 4) | 1;
    Rga_Request.alpha_rop_flag |= (1 << 5);             /* ddl@rock-chips.com: v0.4.3 */

    if(ioctl(fd, RGA_BLIT_SYNC, &Rga_Request) != 0) {
        printf("%s(%d):  RGA_BLIT_ASYNC Failed\n", __FUNCTION__, __LINE__);
        err = -1;
    }
    return err;
}




int convert(char *converter, char *FilePath, char *OutFilePath , int32_t width, int32_t height)
{


	FILE *fp_in = NULL;
	FILE *fp_out = NULL;



	fp_in = fopen(FilePath,"rb");
	if(!fp_in){
		printf("open input file fail\n");
		return 0;
	}
	fp_out = fopen(OutFilePath,"wb+");
	if(!fp_out)
	{
		printf("open output file fail\n");
		return 0;
	}

	int rgaFd;
	if((rgaFd = open("/dev/rga",O_RDWR)) < 0) {
		printf("%s(%d):open rga device failed!\n",__FUNCTION__,__LINE__);
		return 0;

	}

	int (*pConverterFunc)(int fd,int width, int height, char *src, short int *dst, int dstbuf_width);
	int src_frame_size, dst_frame_size;

	if (strcmp(converter, "NV12toRGB565") == 0){
		pConverterFunc=rga_nv12torgb565;
		src_frame_size=height*width*3/2; //12bit per px
		dst_frame_size=height*width*2; //16bit per px

	}
	else if (strcmp(converter, "NV12toI420") == 0){
			pConverterFunc=rga_nv12toi420;
			src_frame_size=height*width*3/2; //12bit per px
			dst_frame_size=height*width*3/2; //12bit per px
	}
	else if (strcmp(converter, "NV12toNV12") == 0){
		pConverterFunc=rga_nv12tonv12;
		src_frame_size=height*width*3/2; //12bit per px
		dst_frame_size=height*width*3/2; //12bit per px
	}
	else{
		printf("unexpected converter!\n");
		return 0;
	}

	uint8_t *src_frame = NULL;
	src_frame = (uint8_t*)malloc(src_frame_size);

	uint8_t *dst_frame = NULL;
	dst_frame = (uint8_t*)malloc(dst_frame_size);

	//printf("Width:%d Height:%d\n", width, height);


	while(1)
	{
		//reading image
		int read_size=fread((uint8_t*)src_frame, 1, src_frame_size, fp_in);


		if (read_size == src_frame_size) {
			memset(dst_frame,0,dst_frame_size); //Cleaning. Doing this for testing
			pConverterFunc(rgaFd,width, height, (char*)src_frame , (short int*)dst_frame, width);

			fwrite((uint8_t*)dst_frame,1,dst_frame_size,fp_out);
			fflush(fp_out);
		}
		else
			break;
	}

	fclose(fp_out);
	fclose(fp_in);
	return 0;
}

int main(int argc, const char* const argv[])
{
	if (argc > 4)
		convert((char*)argv[1], (char*)argv[2], (char*)argv[3], atoi(argv[4]), atoi(argv[5]));
	else
		printf("Usage: colorspace_convert converter in_file out_file width height\n");

	printf("done.\n");
	return 0;
}
