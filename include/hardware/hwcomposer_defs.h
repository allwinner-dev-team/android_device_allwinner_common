/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_INCLUDE_HARDWARE_HWCOMPOSER_DEFS_H
#define ANDROID_INCLUDE_HARDWARE_HWCOMPOSER_DEFS_H

#include <stdint.h>
#include <sys/cdefs.h>

#include <hardware/gralloc.h>
#include <hardware/hardware.h>
#include <cutils/native_handle.h>

__BEGIN_DECLS

/*****************************************************************************/

#define HWC_MODULE_API_VERSION_0_1  HARDWARE_MODULE_API_VERSION(0, 1)

#define HWC_DEVICE_API_VERSION_0_1  HARDWARE_DEVICE_API_VERSION(0, 1)
#define HWC_DEVICE_API_VERSION_0_2  HARDWARE_DEVICE_API_VERSION(0, 2)
#define HWC_DEVICE_API_VERSION_0_3  HARDWARE_DEVICE_API_VERSION(0, 3)


enum {
    /* hwc_composer_device_t::set failed in EGL */
    HWC_EGL_ERROR = -1
};

/*
 * hwc_layer_t::hints values
 * Hints are set by the HAL and read by SurfaceFlinger
 */
enum {
    /*
     * HWC can set the HWC_HINT_TRIPLE_BUFFER hint to indicate to SurfaceFlinger
     * that it should triple buffer this layer. Typically HWC does this when
     * the layer will be unavailable for use for an extended period of time,
     * e.g. if the display will be fetching data directly from the layer and
     * the layer can not be modified until after the next set().
     */
    HWC_HINT_TRIPLE_BUFFER  = 0x00000001,

    /*
     * HWC sets HWC_HINT_CLEAR_FB to tell SurfaceFlinger that it should clear the
     * framebuffer with transparent pixels where this layer would be.
     * SurfaceFlinger will only honor this flag when the layer has no blending
     *
     */
    HWC_HINT_CLEAR_FB       = 0x00000002
};

/*
 * hwc_layer_t::flags values
 * Flags are set by SurfaceFlinger and read by the HAL
 */
enum {
    /*
     * HWC_SKIP_LAYER is set by SurfaceFlnger to indicate that the HAL
     * shall not consider this layer for composition as it will be handled
     * by SurfaceFlinger (just as if compositionType was set to HWC_OVERLAY).
     */
    HWC_SKIP_LAYER = 0x00000001,
};

/*
 * hwc_layer_t::compositionType values
 */
enum {
    /* this layer is to be drawn into the framebuffer by SurfaceFlinger */
    HWC_FRAMEBUFFER = 0,

    /* this layer will be handled in the HWC */
    HWC_OVERLAY = 1,

    /* this is the background layer. it's used to set the background color.
     * there is only a single background layer */
    HWC_BACKGROUND = 2,
};

/*
 * hwc_layer_t::blending values
 */
enum {
    /* no blending */
    HWC_BLENDING_NONE     = 0x0100,

    /* ONE / ONE_MINUS_SRC_ALPHA */
    HWC_BLENDING_PREMULT  = 0x0105,

    /* SRC_ALPHA / ONE_MINUS_SRC_ALPHA */
    HWC_BLENDING_COVERAGE = 0x0405
};

/*
 * hwc_layer_t::transform values
 */
enum {
    /* flip source image horizontally */
    HWC_TRANSFORM_FLIP_H = HAL_TRANSFORM_FLIP_H,
    /* flip source image vertically */
    HWC_TRANSFORM_FLIP_V = HAL_TRANSFORM_FLIP_V,
    /* rotate source image 90 degrees clock-wise */
    HWC_TRANSFORM_ROT_90 = HAL_TRANSFORM_ROT_90,
    /* rotate source image 180 degrees */
    HWC_TRANSFORM_ROT_180 = HAL_TRANSFORM_ROT_180,
    /* rotate source image 270 degrees clock-wise */
    HWC_TRANSFORM_ROT_270 = HAL_TRANSFORM_ROT_270,
};

/* attributes queriable with query() */
enum {
    /*
     * availability: HWC_DEVICE_API_VERSION_0_2
     * must return 1 if the background layer is supported, 0 otherwise
     */
    HWC_BACKGROUND_LAYER_SUPPORTED      = 0,

    /*
     * availability: HWC_DEVICE_API_VERSION_0_3
     * returns the vsync period in nanosecond
     */
    HWC_VSYNC_PERIOD                    = 1,
};

/* Allowed events for hwc_methods::eventControl() */
enum {
    HWC_EVENT_VSYNC     = 0,
    HWC_EVENT_ORIENTATION    // To notify HWC about the device orientation
};

/* Allwinner additions */
/* names for setParameter() */
enum {
    /* rotation of the source image in degrees (0 to 359) */
    HWC_LAYER_ROTATION_DEG  	= 1,
    /* enable or disable dithering */
    HWC_LAYER_DITHER        	= 3,
    HWC_LAYER_SETMODE = 9,
    /* transformation applied (this is a superset of COPYBIT_ROTATION_DEG) */
    HWC_LAYER_SETINITPARA,
    /* set videoplayer init overlay parameter */
    HWC_LAYER_SETVIDEOPARA,
    /* set videoplayer play frame overlay parameter*/
    HWC_LAYER_SETFRAMEPARA,
    /* get videoplayer play frame overlay parameter*/
    HWC_LAYER_GETCURFRAMEPARA,
    /* query video blank interrupt*/
    HWC_LAYER_QUERYVBI,
    /* set overlay screen id*/
    HWC_LAYER_SETSCREEN,

    HWC_LAYER_SHOW,

    HWC_LAYER_RELEASE,

    HWC_LAYER_SET3DMODE,
    HWC_LAYER_SETFORMAT,

    HWC_LAYER_VPPON,
    HWC_LAYER_VPPGETON,

    HWC_LAYER_SETLUMASHARP,
    HWC_LAYER_GETLUMASHARP,

    HWC_LAYER_SETCHROMASHARP,
    HWC_LAYER_GETCHROMASHARP,

    HWC_LAYER_SETWHITEEXTEN,
    HWC_LAYER_GETWHITEEXTEN,

    HWC_LAYER_SETBLACKEXTEN,
    HWC_LAYER_GETBLACKEXTEN,
};

/* possible overlay formats */
enum
{
    HWC_FORMAT_MINVALUE     = 0x50,
    HWC_FORMAT_RGBA_8888    = 0x51,
    HWC_FORMAT_RGB_565      = 0x52,
    HWC_FORMAT_BGRA_8888    = 0x53,
    HWC_FORMAT_YCbYCr_422_I = 0x54,
    HWC_FORMAT_CbYCrY_422_I = 0x55,
    HWC_FORMAT_MBYUV420	    = 0x56,
    HWC_FORMAT_MBYUV422	    = 0x57,
    HWC_FORMAT_YUV420PLANAR = 0x58,
    HWC_FORMAT_DEFAULT      = 0x99,    // The actual color format is determined
    HWC_FORMAT_MAXVALUE     = 0x100
};
/* End of Allwinner additions */
/*****************************************************************************/

__END_DECLS

#endif /* ANDROID_INCLUDE_HARDWARE_HWCOMPOSER_DEFS_H */
