/**
 *  @file boot_splash.c
 *  @author MOBIUSLOOPFOUR <scratch.joint-0i@icloud.com>
 *
 *  Copyright MOBIUSLOOPFOUR 2021
 *  All rights reserved.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 *  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 *  OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 *  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 *  SUCH DAMAGE.
 *
 *  @brief Basic impl. of the POSIX libc string functions. strdup will not be implemented
 *          in kernel space. (malloc)
 *
 */


/* courtesy of p-uefi */

#include <uefi.h>

/* public domain image loader - http://nothings.org/stb_image.h */
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

/**
 * Display PNG image
 */

static 
__do_splash(const char *path)
{
    efi_status_t status;
    efi_guid_t gopGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    efi_gop_t *gop = NULL;
    FILE *f;
    unsigned char *buff;
    uint32_t *data;
    int w, h, l;
    long int size;
    stbi__context s;
    stbi__result_info ri;

    if((f = fopen(path, "r"))) {
        fseek(f, 0, SEEK_END);
        size = ftell(f);
        fseek(f, 0, SEEK_SET);
        buff = (unsigned char*)malloc(size);
        if(!buff) {
            printf("Unable to allocate memory\n");
            return 1;
        }
        fread(buff, size, 1, f);
        fclose(f);
        ri.bits_per_channel = 8;
        s.read_from_callbacks = 0;
        s.img_buffer = s.img_buffer_original = buff;
        s.img_buffer_end = s.img_buffer_original_end = buff + size;
        data = (uint32_t*)stbi__png_load(&s, &w, &h, &l, 4, &ri);
        if(!data) {
            fprintf(stdout, "Unable to decode BootSplash.png: %s\n", stbi__g_failure_reason);
            return 0;
        }
    } else {
        fprintf(stderr, "Unable to load image\n");
        return 0;
    }

    status = BS->LocateProtocol(&gopGuid, NULL, (void**)&gop);
    if(!EFI_ERROR(status) && gop) {
        status = gop->SetMode(gop, 0);
        ST->ConOut->Reset(ST->ConOut, 0);
        ST->StdErr->Reset(ST->StdErr, 0);
        if(EFI_ERROR(status)) {
            fprintf(stderr, "Unable to set video mode\n");
            return 0;
        }
    } else {
        fprintf(stderr, "Unable to get graphics output protocol\n");
        return 0;
    }

    if(gop->Mode->Information->PixelFormat == PixelBlueGreenRedReserved8BitPerColor ||
        (gop->Mode->Information->PixelFormat == PixelBitMask && gop->Mode->Information->PixelInformation.BlueMask != 0xff0000)) {
        for(l = 0; l < w * h; l++)
            data[l] = ((data[l] & 0xff) << 16) | (data[l] & 0xff00) | ((data[l] >> 16) & 0xff);
    }

    memset((void*)gop->Mode->FrameBufferBase, 0, gop->Mode->FrameBufferSize);
    gop->Blt(gop, data, EfiBltBufferToVideo, 0, 0, (gop->Mode->Information->HorizontalResolution - w) / 2,
        (gop->Mode->Information->VerticalResolution - h) / 2, w, h, 0);

    free(data);
    free(buff);
    return 0;
}

boot_splash_success(void) {
    return 0; /* don't splash for now */
}

boot_failure_feedback(void) {

    int i = __do_splash("\\System\\Stash\\Resources\\Prohibited.bin");
    exit_bs();
    while (1) {__asm__("hlt"); }

    return i;
}

disk_failure_feedback(void) {

    int i = __do_splash("\\System\\Stash\\Resources\\Diskless.bin");
    exit_bs();
    while (1) {__asm__("hlt"); }

    return i;
}
